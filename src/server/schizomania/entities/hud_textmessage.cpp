/*
 * Copyright (c) 2016-2020 Marco Hladik <marco@icculus.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*QUAKED hud_textmessage (1 0 0) (-8 -8 -8) (8 8 8) GTF_ALLPLAYERS
"targetname"    Name
"target"        Target to trigger when triggered.
"delay"			TODO: Dun work yet? - How long to wait before triggering.
"x"             Horizontal position of text. 
                    (0 - 1.0 = left to right, -1 = center)
"y"             Vertical position of text.
                    (0 - 1.0 = top to bottom, -1 = center)
"effect"        Effect to apply to the text.
                    Valid values:
                        0 = Fade In/Out
                        1 = Credits
                        2 = Scan Out
"color"         The main colour in RGB8.
"color2"        The highlight colour in RGB8.
"fadein"        Time taken to fade in each character.
"fadeout"       Time taken to fade out message.
"holdtime"      Length of time to hold message on screen after fading in.
"fxtime"        Time the highlight lags behind the leading edge of the text in
                seconds.
"channel"       Message channel to use. Meant for overriding messages.

This entity displays a message on the screen, usually centered.
It is meant for dialogues, when the player is conversing.
Talking to other entities, and/or himself.

TODO: Change font style maybe when he talks to himself?

If GTF_ALLPLAYERS is set, it'll display the message to not just the activator,
but all players on the level.
*/

enumflags
{
	GTF_ALLPLAYERS
};

class hud_textmessage:CBaseTrigger
{
	float m_flPosX;
	float m_flPosY;
	int m_iEffect;
	vector m_vecColor1;
	vector m_vecColor2;
	float m_flFadeIn;
	float m_flFadeOut;
	float m_flHoldTime;
	float m_flFXTime;
	int m_iChannel;
		
	void(void) hud_textmessage;

	// Base class funcs.
	virtual void (entity act, string intype, string data) Input;
	virtual void(entity, int) Trigger;
	virtual void(string, string) SpawnKey;

	// Text message funcs.
	virtual void(entity act) ShowTextMessage;

};

void hud_textmessage::ShowTextMessage(entity act) {
	WriteByte(MSG_MULTICAST, SVC_CGAMEPACKET);
	WriteByte(MSG_MULTICAST, EV_HUD_MESSAGE);
	WriteByte(MSG_MULTICAST, m_iChannel);
	WriteString(MSG_MULTICAST, m_strMessage);
	WriteFloat(MSG_MULTICAST, m_flPosX);
	WriteFloat(MSG_MULTICAST, m_flPosY);
	WriteByte(MSG_MULTICAST, m_iEffect);
	WriteByte(MSG_MULTICAST, m_vecColor1[0]);
	WriteByte(MSG_MULTICAST, m_vecColor1[1]);
	WriteByte(MSG_MULTICAST, m_vecColor1[2]);
	WriteByte(MSG_MULTICAST, m_vecColor2[0]);
	WriteByte(MSG_MULTICAST, m_vecColor2[1]);
	WriteByte(MSG_MULTICAST, m_vecColor2[2]);
	WriteFloat(MSG_MULTICAST, m_flFadeIn);
	WriteFloat(MSG_MULTICAST, m_flFadeOut);
	WriteFloat(MSG_MULTICAST, m_flHoldTime);
	WriteFloat(MSG_MULTICAST, m_flFXTime);

	if (spawnflags & GTF_ALLPLAYERS) {
		msg_entity = this;
		multicast(origin, MULTICAST_ALL);
	} else {
		msg_entity = act;
		multicast(origin, MULTICAST_ONE_R);
	}

	// Trigger target.
	UseTargets(msg_entity, TRIG_TOGGLE, m_flDelay);
}
/* entities receive the inputs here and need to act on intype and data
   accordingly. this is just a stub for unknown event troubleshooting */
void
hud_textmessage::Input(entity act, string intype, string data)
{
	// Call by default.
	CBaseTrigger::Input(act, intype, data);

	// Show HUD notification.
	if (intype == "OnTrigger") {
		ShowTextMessage(act);
	}
}

void hud_textmessage::Trigger(entity act, int state)
{
	dprint("I am triggered by %s", act.classname);
	ShowTextMessage(act);
}

void
hud_textmessage::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "x":
		m_flPosX = stof(strValue);
		break;
	case "y":
		m_flPosY = stof(strValue);
		break;
	case "effect":
		m_iEffect = stoi(strValue);
		break;
	case "color":
		m_vecColor1 = stov(strValue);
		break;
	case "color2":
		m_vecColor2 = stov(strValue);
		break;
	case "fadein":
		m_flFadeIn = stof(strValue);
		break;
	case "fadeout":
		m_flFadeOut = stof(strValue);
		break;
	case "holdtime":
		m_flHoldTime = stof(strValue);
		break;
	case "fxtime":
		m_flFXTime = stof(strValue);
		break;
	case "channel":
		m_iChannel = stoi(strValue);
		break;
	default:
		CBaseTrigger::SpawnKey(strKey, strValue);
	}
}

void hud_textmessage::hud_textmessage(void)
{
	CBaseTrigger::CBaseTrigger();

	// Default position of the hud textmessages.
	m_flPosX = -1.0f;
	m_flPosY = 0.8f;
	m_vecColor1 = [255, 255, 255];
	m_vecColor2 = [180, 0, 0];
	m_flDelay = 2.5f;
	m_iEffect = 2;
	m_flFXTime = 0.25f;
	m_flFadeIn = 0.01f;
	m_flFadeOut = 1.5f;
	m_flHoldTime = 2.5f;
}
