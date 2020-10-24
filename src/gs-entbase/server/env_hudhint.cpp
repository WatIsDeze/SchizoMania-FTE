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

/*QUAKED env_hudhint (0 0 0) (-8 -8 -8) (8 8 8) EVF_FADEDROM EVF_MODULATE EVF_ONLYUSER
"targetname"    Name
"target"        Target when triggered.
"killtarget"    Target to kill when triggered.
"rendercolor"   RGB8 Color of the fade effect.
"renderamt"     A8 alpha value we'll hit at max.
"duration"      Duration of the effect in seconds.
"holdtime"      How long we'll hold on the max color/alpha.

When triggered, creates a colored overlay that blinds all players, or just
the one who triggered it if EVF_ONLYUSER is set.
*/

void env_hudhint_send(entity eActivator, string strMessage, int iFlags);

enumflags
{
	EHH_ALLPLAYERS
};

class env_hudhint:CBaseTrigger
{
	string m_strMessage;

	void(void) env_hudhint;
	virtual void(entity, int) Trigger;
	virtual void(string, string) SpawnKey;
};

void
env_hudhint::Trigger(entity act, int state)
{
	env_hudhint_send(act, m_strMessage, spawnflags);
}

void
env_hudhint::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "message":
		m_strMessage = strValue;
		break;
	default:
		CBaseTrigger::SpawnKey(strKey, strValue);
	}
}

void
env_hudhint::env_hudhint(void)
{
	CBaseTrigger::CBaseTrigger();
}

void
env_hudhint_send(entity eActivator, string strMessage, int iFlags)
{
	WriteByte(MSG_MULTICAST, SVC_CGAMEPACKET);
	WriteByte(MSG_MULTICAST, EV_HUDHINT);
	WriteString(MSG_MULTICAST, strMessage);
	msg_entity = eActivator;

	if (iFlags & EHH_ALLPLAYERS)
		multicast([0,0,0], MULTICAST_ALL);
	else
		multicast([0,0,0], MULTICAST_ONE_R);
}
