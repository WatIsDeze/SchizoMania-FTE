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

/*QUAKED random_trigger (1 0 0) (-8 -8 -8) (8 8 8)
"targetname"    Name
"target"        Target when triggered
"killtarget"    Target to kill when triggered
"start_state"   Start state (either 0 or 1)
"wait"          Minimum time
"random_min"    Minimum added random time
"random_max"    Maximum added random time

When triggered, it'll calculate some random interval until it triggers
its targets, based on some limits given.

Trivia:
It was introduced in Gunman Chronicles (2000).
*/

class random_trigger:CBaseTrigger
{
	float m_flMinTime;
	float m_flRandMin;
	float m_flRandMax;
	int m_iStartState;

	void(void) random_trigger;

	virtual void(entity,int) Trigger;
	virtual void(void) Respawn;
	virtual void(string, string) SpawnKey;
};

void
random_trigger::Trigger(entity act, int state)
{
	float r;

	if (GetMaster() == FALSE)
		return;

	r = time + m_flMinTime + random(m_flRandMin, m_flRandMax);
	UseTargets(other, TRIG_TOGGLE, r);
}

void
random_trigger::Respawn(void)
{
	if (m_iStartState == 1)
		Trigger(this, TRIG_ON);
}

void
random_trigger::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "start_state":
		m_iStartState = stoi(strValue);
		break;
	case "wait":
		m_flMinTime = stof(strValue);
		break;
	case "random_min":
		m_flRandMin = stof(strValue);
		break;
	case "random_max":
		m_flRandMax = stof(strValue);
		break;
	default:
		CBaseTrigger::SpawnKey(strKey, strValue);
	}
}

void
random_trigger::random_trigger(void)
{
	CBaseTrigger::CBaseTrigger();
}
