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
"wait"			TODO: Dun work yet? - How long to wait before triggering.
"duration"      How long the notification is displayed.
"message"       Message, supports multiline and ^x### hex codes for coloring.
"style"         0 = SMALL, 1 = LARGE.

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
    int m_iStyle;

	void(void) hud_notification;

	virtual void(entity act, string intype, string data) Input;
	virtual void(entity, int) Trigger;
	virtual void(string, string) SpawnKey;
};

/* entities receive the inputs here and need to act on intype and data
   accordingly. this is just a stub for unknown event troubleshooting */
void
hud_notification::Input(entity act, string intype, string data)
{
	// Call by default.
	CBaseTrigger::Input(act, intype, data);

	// Show HUD notification.
	if (intype == "OnTrigger") {
		WriteByte(MSG_MULTICAST, SVC_CGAMEPACKET);
		WriteByte(MSG_MULTICAST, EV_HUD_NOTIFICATION);

		WriteByte(MSG_MULTICAST, m_iStyle);
		WriteFloat(MSG_MULTICAST, m_flDuration);
		WriteString(MSG_MULTICAST, m_strMessage);

		if (spawnflags & GTF_ALLPLAYERS) {
			msg_entity = this;
			multicast(origin, MULTICAST_ALL_R);
		} else {
			msg_entity = act;
			multicast(origin, MULTICAST_ONE_R);
		}
	}
}

void hud_notification::Trigger(entity act, int state)
{
	WriteByte(MSG_MULTICAST, SVC_CGAMEPACKET);
	WriteByte(MSG_MULTICAST, EV_HUD_NOTIFICATION);

    WriteByte(MSG_MULTICAST, m_iStyle);
    WriteFloat(MSG_MULTICAST, m_flDuration);
	WriteString(MSG_MULTICAST, m_strMessage);

	if (spawnflags & GTF_ALLPLAYERS) {
		msg_entity = this;
		multicast(origin, MULTICAST_ALL_R);
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
    case "style":
        m_iStyle = stoi(strValue);
        break;
	default:
		CBaseTrigger::SpawnKey(strKey, strValue);
	}
}

void hud_notification::hud_notification(void)
{
    m_flDuration = 2;
    m_iStyle = 1;
	CBaseTrigger::CBaseTrigger();
}
