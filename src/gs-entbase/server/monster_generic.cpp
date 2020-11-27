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

/*QUAKED monster_generic (1 0 0) (-8 -8 -8) (8 8 8)

SCHIZOMANIA ENTITY

Causes the activators first-person camera to switch to the view of 
this entity.
- targetname: The entity trigger targetname.
- angles:     Sets the pitch, yaw and roll angles of the entity.
- model:      Model to display at start.

Flags:
	- MGF_NONSOLID 4
*/

#define MGF_NONSOLID 4

class monster_generic:CBaseNPC
{
	void(void) monster_generic;

	virtual void(void) Death;
	virtual void(entity act, int state) Trigger;
	virtual void(void) Respawn;
};

void
monster_generic::Respawn(void)
{
	CBaseNPC::Respawn();

	if (spawnflags & MGF_NONSOLID) {
		takedamage = DAMAGE_NO;
		iBleeds = FALSE;
		solid = SOLID_NOT;
	}
}

void
monster_generic::Death(void)
{
	m_iFlags = 0x0;


	/* make sure we're not causing any more obituaries */
	flags &= ~FL_MONSTER;
	m_iFlags = 0x0;
	// /* gibbing action */
	// SetMovetype(MOVETYPE_NONE);
	// SetSolid(SOLID_CORPSE);
	// health = 50 + health; 
	// style = MONSTER_DEAD;
}

void
monster_generic::Trigger(entity act, int state)
{
	// UseTargets(act, TRIG_TOGGLE, 0);
	SetModelindex(0);
	SetSolid(SOLID_NOT);
	SetMovetype(MOVETYPE_NONE);
	customphysics = __NULL__;

	//eActivator.view2 = this;

	dprint(sprintf("^monster_generic::^3Trigger^7:\n"));
}

void
monster_generic::monster_generic(void)
{
	base_mins = [-16,-16,0];
	base_maxs = [16,16,72];

	spawnflags |= MSF_MULTIPLAYER;
	CBaseNPC::CBaseNPC();
}
