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

/*QUAKED monster_zombie (0 0.8 0.8) (-16 -16 0) (16 16 72)

SCHIZOMANIA ENTITY

Zombie Derrick from Mixamo. WIP: Has 2 melee attacks, can bite, neckbite,
crawl, and foot bite.

*/

enum {
	ZOMBIE_TPOSE,
	ZOMBIE_AGONIZING,
	ZOMBIE_ATTACK1,
	ZOMBIE_ATTACK2,
	ZOMBIE_DYING1,
	ZOMBIE_DYING1_FAST,
	ZOMBIE_DYING2,
	ZOMBIE_DYING2_FAST,
	ZOMBIE_HIT_REACT_A,
	ZOMBIE_HIT_REACT_B,
	ZOMBIE_IDLE1,
	ZOMBIE_IDLE_HUNT,
	ZOMBIE_IDLE_SCRATCH,
	ZOMBIE_RUNNING1,
	ZOMBIE_SCREAM,
	ZOMBIE_TURN_BACKFACE,
	ZOMBIE_WALKING1,
	ZOMBIE_WALKING2,
	ZOMBIE_WALKING3
};

class monster_zombie:CBaseMonster
{
	float m_flIdleTime;

	void(void) monster_zombie;

	virtual void(void) Pain;
	virtual void(void) Death;
	virtual void(void) IdleNoise;
	virtual void(void) Respawn;

	virtual int(void) AnimIdle;
	virtual int(void) AnimWalk;
	virtual int(void) AnimRun;

	virtual void(void) AttackThink;
	virtual int(void) AttackMelee;
	virtual void(void) AttackFlailOne;
	virtual void(void) AttackFlailTwo;
};

int
monster_zombie::AnimIdle(void)
{
	return ZOMBIE_IDLE1;
}

int
monster_zombie::AnimWalk(void)
{
	m_flChaseSpeed = 42;
	return ZOMBIE_WALKING2;
}

int
monster_zombie::AnimRun(void)
{
	m_flChaseSpeed = 46;
	return ZOMBIE_WALKING2;
}

void
monster_zombie::AttackThink(void)
{
	if (m_iSequenceState != SEQUENCESTATE_NONE)
		return;

	if (m_flAttackThink > time) {
		return;
	}

	/* reset */
	if (m_eEnemy.solid == SOLID_CORPSE || (m_eEnemy && m_eEnemy.health <= 0)) {
		m_eEnemy = __NULL__;
		ClearRoute();
	}

	/* do we have a clear shot? */
	other = world;
	traceline(origin, m_eEnemy.origin, MOVE_OTHERONLY, this);

	/* something is blocking us */
	if (trace_fraction < 1.0f) {
		m_iMState = MONSTER_IDLE;

		/* FIXME: This is unreliable, but unlikely that a player ever is here */
		if (m_vecLKPos != [0,0,0]) {
			ClearRoute();
			NewRoute(m_vecLKPos);
			m_flSequenceSpeed = 140;
			m_vecLKPos = [0,0,0];
		}
	} else {
		m_iMState = MONSTER_AIMING;

		/* make sure we remember the last known position. */
		m_vecLKPos = m_eEnemy.origin;
	}

	if (m_iMState == MONSTER_AIMING) {
		int m;
		if (vlen(origin - m_eEnemy.origin) < 96)
			m = AttackMelee();
		else {
			m = AttackRanged();

			/* if we don't have the desired attack mode, walk */
			if (m == FALSE)
				m_iMState = MONSTER_CHASING;	

		}
	}
}

int
monster_zombie::AttackMelee(void)
{

	if (random() < 0.5) {
		AnimPlay(ZOMBIE_ATTACK1);

		// Setup the hit function. (TODO: Maybe use a model event?)
		think = AttackFlailOne;
		nextthink = time + 1.0;
	} else {
		AnimPlay(ZOMBIE_ATTACK2);
	
		// Setup the hit function. (TODO: Maybe use a model event?)
		think = AttackFlailTwo;
		nextthink = time + 0.8;
	}

	m_flAttackThink = m_flAnimTime;
	Sound_Play(this, CHAN_VOICE, "monster_zombie.attack");
	
	return TRUE;
}

void
monster_zombie::AttackFlailOne(void)
{
	// Calculate attack trace, 64 distance.
	makevectors(angles);
	vector vecDest = origin + v_forward * 32;

	// Do a trace.
	traceline(origin, vecDest, FALSE, this);

	if (trace_fraction >= 1.0 || trace_ent.takedamage != DAMAGE_YES) {
		Sound_Play(this, CHAN_WEAPON, "monster_zombie.attackmiss");
		return;
	}

	Damage_Apply(trace_ent, this, 25, 0, 0);
	Sound_Play(this, CHAN_WEAPON, "monster_zombie.attackhit");
}

void
monster_zombie::AttackFlailTwo(void)
{
	// Calculate attack trace, 64 distance.
	makevectors(angles);
	vector vecDest = origin + v_forward * 42;

	// Do a trace.
	traceline(origin, vecDest, FALSE, this);

	if (trace_fraction >= 1.0 || trace_ent.takedamage != DAMAGE_YES) {
		Sound_Play(this, CHAN_WEAPON, "monster_zombie.attackmiss");
		return;
	}

	Damage_Apply(trace_ent, this, 25, 0, 0);
	Sound_Play(this, CHAN_WEAPON, "monster_zombie.attackhit");
}

void
monster_zombie::Pain(void)
{
	CBaseMonster::Pain();

	if (m_flAnimTime > time) {
		return;
	}

	if (random() < 0.75f) {
		return;
	}

	Sound_Play(this, CHAN_VOICE, "monster_zombie.pain");
	SetFrame(ZOMBIE_HIT_REACT_A);
	m_flAnimTime = time + 1.5f;
}

void
monster_zombie::Death(void)
{
	/* if we're already dead (corpse) don't change animations */
	if (style != MONSTER_DEAD) {
		/* headshots == different animation */
		if (g_dmg_iHitBody == BODY_HEAD) {
			if (random() < 0.5) {
				SetFrame(ZOMBIE_DYING1_FAST);
			} else {
				SetFrame(ZOMBIE_DYING2_FAST);
			}
		} else {
			if (random() < 0.5) {
				SetFrame(ZOMBIE_DYING1);
			} else {
				SetFrame(ZOMBIE_DYING2);
			}
		}

		Sound_Play(this, CHAN_VOICE, "monster_zombie.pain");
	}

	/* set the functional differences */
	CBaseMonster::Death();
}

void
monster_zombie::IdleNoise(void)
{
	/* don't make noise if we're dead (corpse) */
	if (style == MONSTER_DEAD) {
		return;
	}

	if (m_flIdleTime > time) {
		return;
	}
	m_flIdleTime = time + random(2,10);

	Sound_Play(this, CHAN_VOICE, "monster_zombie.idle");
}

void
monster_zombie::Respawn(void)
{
	CBaseMonster::Respawn();
	SetFrame(ZOMBIE_IDLE1);
}

void
monster_zombie::monster_zombie(void)
{
	Sound_Precache("monster_zombie.alert");
	Sound_Precache("monster_zombie.attack");
	Sound_Precache("monster_zombie.attackhit");
	Sound_Precache("monster_zombie.attackmiss");
	Sound_Precache("monster_zombie.idle");
	Sound_Precache("monster_zombie.pain");
	netname = "Zombie Derrick";
	model = "models/characters/zombie_derrick/zombie_derrick.vvm";
	base_health = Skill_GetValue("zombie_derrick_health", 80);
	base_mins = [-16,-16,0];
	base_maxs = [16,16,72];

	m_iAlliance = MAL_ALIEN;
	CBaseMonster::CBaseMonster();

	m_flChaseSpeed = 42;
}
