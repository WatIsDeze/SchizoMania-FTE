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

/*QUAKED trigger_cdaudio (0 .5 .8) ?
"targetname"    Name
"health"        Music track to play.

Switches the background music track when triggered.

Trivia:
This entity was introduced in Half-Life (1998).
*/

class trigger_cdaudio:CBaseTrigger
{
	int m_iCDTrack;
	void(void) trigger_cdaudio;

	virtual void(entity, int) Trigger;
	virtual void(void) Respawn;
	virtual void(void) touch;
	virtual void(string, string) SpawnKey;
};

void
trigger_cdaudio::Trigger(entity act, int unused)
{
	if (!(act.flags & FL_CLIENT)) {
		return;
	}

	dprint(sprintf("^2trigger_cdaudio::^3Trigger^7: CD Track %i requested\n", 
		m_iCDTrack));

	WriteByte(MSG_MULTICAST, SVC_CGAMEPACKET);
	WriteByte(MSG_MULTICAST, EV_MUSICTRACK);
	WriteByte(MSG_MULTICAST, m_iCDTrack);
	msg_entity = world;
	multicast([0,0,0], MULTICAST_ALL_R);

	remove(this);
}

void
trigger_cdaudio::touch(void)
{
	Trigger(other, TRIG_TOGGLE);
}

void
trigger_cdaudio::Respawn(void)
{
	InitBrushTrigger();
}

void
trigger_cdaudio::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "health":
		m_iCDTrack = stoi(strValue);
		break;
	default:
		CBaseTrigger::SpawnKey(strKey, strValue);
		break;
	}
}

void
trigger_cdaudio::trigger_cdaudio(void)
{
	CBaseTrigger::CBaseTrigger();
}
