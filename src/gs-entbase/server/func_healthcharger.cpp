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

/*QUAKED func_healthcharger (0 .5 .8) ?
"targetname"    Name
"target"        Target when triggered.
"killtarget"    Target to kill when triggered.
"snd_first"     Sound to play when first used.
"snd_charging"  Sound to play when first charging.
"snd_done"      Sound to play when first finished charging.

Brush that fills up your health when used, to a maximum of 100 HP.

Trivia:
This entity was introduced in Half-Life (1998).
*/

class func_healthcharger:CBaseTrigger
{
	entity m_eUser;
	float m_flDelay;
	float m_flCheck;

	string m_strSndFirst;
	string m_strSndCharging;
	string m_strSndDone;

	void(void) func_healthcharger;
	virtual void(void) customphysics;
	virtual void(void) OnPlayerUse;
	virtual void(string, string) SpawnKey;
};

void
func_healthcharger::OnPlayerUse(void)
{
	/* let's not let this become too funny... */
	if (eActivator.health <= 0)
		return;

	eActivator.flags |= FL_USE_RELEASED;

	/* First come first serve */ 
	if (m_eUser && eActivator != m_eUser)
		return;

	/* First time */
	if (m_eUser == world)
		sound(this, CHAN_VOICE, m_strSndFirst, 1.0, ATTN_NORM);

	if (m_flDelay > time)
		return;

	if (eActivator.health >= 100) {
		eActivator.flags &= ~FL_USE_RELEASED;
		sound(this, CHAN_VOICE, m_strSndDone, 1.0, ATTN_NORM);
	} else {
		if (m_eUser == world)
			sound(this, CHAN_ITEM, m_strSndCharging, 1.0, ATTN_NORM);

		eActivator.health = bound(0, eActivator.health += 1, 100);
	}

	m_eUser = eActivator;
	m_flDelay = time + 0.1f;
	m_flCheck = time + 0.25f;
}

void
func_healthcharger::customphysics(void)
{
	if (m_flCheck > time)
		return;

	if (m_eUser) {
		sound(this, CHAN_ITEM, "common/null.wav", 1.0, ATTN_NORM);
		m_eUser = world;
	}
}

void
func_healthcharger::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "snd_first":
		m_strSndFirst = strValue;
		break;
	case "snd_charging":
		m_strSndCharging = strValue;
		break;
	case "snd_done":
		m_strSndDone = strValue;
		break;
	default:
		CBaseTrigger::SpawnKey(strKey, strValue);
	}
}

void
func_healthcharger::func_healthcharger(void)
{
	m_strSndFirst = "items/medshot4.wav";
	m_strSndCharging = "items/medcharge4.wav";
	m_strSndDone = "items/medshotno1.wav";

	CBaseTrigger::CBaseTrigger();

	precache_sound(m_strSndFirst);
	precache_sound(m_strSndCharging);
	precache_sound(m_strSndDone);

	SetSolid(SOLID_BSP);
	SetMovetype(MOVETYPE_PUSH);
	SetOrigin(origin);
	SetModel(model);
	PlayerUse = OnPlayerUse;
}
