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

/*QUAKED env_beverage (1 0 0) (-8 -8 -8) (8 8 8)
"targetname"    Name
"target"        Target when triggered.
"killtarget"    Target to kill when triggered.
"health"        Amount of soda-cans that can be dispensed at maximum
"angles"        Sets the pitch, yaw and roll angles of the soda

Upon triggered, the entity will spawn item_food in its place in
the shape of a soda can.
*/

/* dependency from item_food.cpp */
void item_sodacan(void);

// TODO: Implement support for skins
enum
{
	SKIN_COCACOLA,
	SKIN_SPRITE,
	SKIN_DIETCOKE,
	SKIN_ORANGE,
	SKIN_SURGE,
	SKIN_MOXIE,
	SKIN_RANDOM
};

class env_beverage:CBaseTrigger
{
	int m_iUses;
	int m_iReady;
	int m_iSkin;
	void(void) env_beverage;
	virtual void(entity, int) Trigger;
	virtual void(string, string) SpawnKey;
};

void
env_beverage::Trigger(entity act, int unused)
{
	if (m_iReady == FALSE || m_iUses <= 0) {
		return;
	}

	entity eCan = spawn();
	setorigin(eCan, origin);
	eCan.angles = angles;
	eCan.owner = this;
	eCan.think = item_sodacan;
	eCan.nextthink = time;

	m_iUses--;
	m_iReady = FALSE;
}

void
env_beverage::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "health":
		m_iUses = stoi(strValue);
		break;
	default:
		CBaseTrigger::SpawnKey(strKey, strValue);
	}
}

void
env_beverage::env_beverage(void)
{
	precache_model("models/can.mdl");
	precache_sound("weapons/g_bounce3.wav");

	CBaseTrigger::CBaseTrigger();

	if (!m_iUses) {
		m_iUses = 10;
	}
	m_iReady = TRUE;
}
