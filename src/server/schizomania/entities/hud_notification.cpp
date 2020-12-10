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
    float m_flDuration;

	void(void) hud_notification;

	virtual void(entity, int) Trigger;
	virtual void(string, string) SpawnKey;
};

void hud_notification::Trigger(entity act, int state)
{
	WriteByte(MSG_MULTICAST, SVC_CGAMEPACKET);
	WriteByte(MSG_MULTICAST, EV_HUD_NOTIFICATION);
    WriteFloat(MSG_MULTICAST, m_flDuration);
	WriteString(MSG_MULTICAST, m_strMessage);

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
    case "duration":
        m_flDuration = stof(strValue);
    break;
	default:
		CBaseTrigger::SpawnKey(strKey, strValue);
	}
}

void hud_notification::hud_notification(void)
{
	CBaseTrigger::CBaseTrigger();
}
