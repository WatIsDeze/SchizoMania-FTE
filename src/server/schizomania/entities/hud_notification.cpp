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

/*QUAKED hud_notification (1 0 0) (-8 -8 -8) (8 8 8) GTF_ALLPLAYERS
"targetname"    Name
"target"        Target to trigger when triggered.
"delay"			TODO: Dun work yet? - How long to wait before triggering.
"effect"        Effect to apply to the text.
                    Valid values:
                        0 = Fade In/Out
                        1 = Credits
                        2 = Scan Out
"color"         The main colour in RGB8.
"color2"        The highlight colour in RGB8.
"position"      0 = Top, 1 = Right, 2 = Bottom, 3 = Left.

Displays HUD update messages.
For example, when picking up an item.
When a door is locked, or a key is required etc.

If GTF_ALLPLAYERS is set, it'll display the message to not just the activator,
but all players on the level.
*/

enumflags
{
	GTF_ALLPLAYERS
};

class hud_notification:CBaseTrigger
{
    int m_iPosition;
	int m_iEffect;
	vector m_vecColor1;
	vector m_vecColor2;
		
	void(void) hud_notification;

	virtual void(entity, int) Trigger;
	virtual void(string, string) SpawnKey;
};

void hud_notification::Trigger(entity act, int state)
{
	WriteByte(MSG_MULTICAST, SVC_CGAMEPACKET);
	WriteByte(MSG_MULTICAST, EV_HUD_NOTIFICATION);
	WriteString(MSG_MULTICAST, m_strMessage);
	WriteByte(MSG_MULTICAST, m_iPosition);
	WriteByte(MSG_MULTICAST, m_iEffect);
	WriteByte(MSG_MULTICAST, m_vecColor1[0]);
	WriteByte(MSG_MULTICAST, m_vecColor1[1]);
	WriteByte(MSG_MULTICAST, m_vecColor1[2]);
	WriteByte(MSG_MULTICAST, m_vecColor2[0]);
	WriteByte(MSG_MULTICAST, m_vecColor2[1]);
	WriteByte(MSG_MULTICAST, m_vecColor2[2]);

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

void
hud_notification::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
    case "position":
        m_iPosition = stoi(strValue);
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
	default:
		CBaseTrigger::SpawnKey(strKey, strValue);
	}
}

void hud_notification::hud_notification(void)
{
	CBaseTrigger::CBaseTrigger();

	// Default hud notification.
    m_iPosition = 1;
	m_iEffect = 2;
	m_vecColor1 = [255, 255, 255];
	m_vecColor2 = [180, 0, 0];
}
