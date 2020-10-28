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

/*QUAKED targ_speaker (1 0 0) (-8 -8 -8) (8 8 8)
"targetname"    Name
"target"        Target when triggered
"killtarget"    Target to kill when triggered
"tsnoise"       Path to the sound file
"volume"        Volume to play the sound as (normalized, 0.0 - 1.0)

This entity plays a sample upon triggering at a specified volume.

Trivia:
It was introduced in Gunman Chronicles (2000).
It's not any more useful than an ambient_generic.
I suspect it's a carry-over from when Gunman was a Quake II mod, as
Quake/Quake II did not have an entity that allowed custom sound samples
to be played.
*/

class targ_speaker:CBaseTrigger
{
	string m_strSample;
	float m_flVolume;

	void(void) targ_speaker;

	virtual void(entity,int) Trigger;
	virtual void(string, string) SpawnKey;
};

void
targ_speaker::Trigger(entity act, int state)
{
	if (GetMaster() == FALSE)
		return;

	sound(this, CHAN_AUTO, m_strSample, m_flVolume, ATTN_NORM);
	
}

void
targ_speaker::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "tsnoise":
		m_strSample = strValue;
		break;
	case "volume":
		m_flVolume = stof(strValue);
		break;
	default:
		break;
	}
}

void
targ_speaker::targ_speaker(void)
{
	CBaseTrigger::CBaseTrigger();
}
