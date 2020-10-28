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

/*QUAKED env_spark (1 0 0) (-8 -8 -8) (8 8 8) x x x x x EVSPARK_TOGGLE EVSPARK_STARTON
"targetname"    Name
"target"        Target when triggered.
"killtarget"    Target to kill when triggered.
"angles"        Sets the pitch, yaw and roll angles of the spark.
"MaxDelay"      Delay between sparks when start-on (or toggle) is set

Creates a series (or just one) spark effect with sound when triggered.

Trivia:
This entity was introduced in Half-Life (1998).
*/

enumflags
{
	EVSPARK_UNUSED1,
	EVSPARK_UNUSED2,
	EVSPARK_UNUSED3,
	EVSPARK_UNUSED4,
	EVSPARK_UNUSED5,
	EVSPARK_TOGGLE,
	EVSPARK_STARTON
};

class env_spark:CBaseTrigger
{
	float m_flMaxDelay;

	void(void) env_spark;
	virtual void(void) CreateSpark;
	virtual void(void) TimedSpark;
	virtual void(entity, int) Trigger;
	virtual void(void) Respawn;
	virtual void(string, string) SpawnKey;
};

void
env_spark::CreateSpark(void)
{
	Sound_Play(this, CHAN_AUTO, "env_spark.sfx");
	FX_Spark(self.origin, self.angles);
}

void
env_spark::TimedSpark(void)
{
	CreateSpark();
	nextthink = time + (random() * m_flMaxDelay);
}

void
env_spark::Trigger(entity act, int state)
{
	if (spawnflags & EVSPARK_TOGGLE) {
		switch (state) {
		case TRIG_OFF:
			think = __NULL__;
			nextthink = 0;
			break;
		case TRIG_ON:
			think = TimedSpark;
			nextthink = time + (random() * m_flMaxDelay);
			break;
		default:
			if (think != __NULL__) {
				Trigger(act, TRIG_OFF);
			} else {
				Trigger(act, TRIG_ON);
			}
		}
	} else {
		CreateSpark();
	}
}

void
env_spark::Respawn(void)
{
	if (m_flMaxDelay <= 0) {
		m_flMaxDelay = 1.0f;
	}

	if (spawnflags & EVSPARK_STARTON) {
		Trigger(this, TRIG_ON);
	}
}

void
env_spark::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "MaxDelay":
		m_flMaxDelay = stof(strValue);
		break;
	default:
		CBaseTrigger::SpawnKey(strKey, strValue);
	}
}

void
env_spark::env_spark(void)
{
	Sound_Precache("env_spark.sfx");
	CBaseTrigger::CBaseTrigger();
}
