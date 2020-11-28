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

/* cast a single bullet shot */
void
TraceAttack_FireSingle(vector vecPos, vector vAngle, int iDamage, int iWeapon)
{
	string tex;
	vector range;
	float surf;
	float maxPenetrationThickness = 8;

	range = (vAngle * 8196);

	traceline(vecPos, vecPos + range, MOVE_LAGGED | MOVE_HITMODEL, self);

	// UNCOMMENT FOR DEBUG INFO.
	// dprint("==================================================\n");
	// dprint(sprintf("Tracing from:\n	%v'\nto\n%v\n", vecPos, vecPos + range));
	// dprint(sprintf("Thickness: %f\n", thickness));
	// dprint("==================================================\n");
	// dprint(sprintf("trace_allsolid		= %f\n", trace_allsolid));
	// dprint(sprintf("trace_startsolid	= %f\n", trace_startsolid));
	// dprint(sprintf("trace_fraction		= %f\n", trace_fraction));
	// dprint(sprintf("trace_endpos		= %v\n", trace_endpos));
	// dprint(sprintf("trace_plane_normal	= %v\n", trace_plane_normal));
	// dprint(sprintf("trace_plane_dist	= %f\n", trace_plane_dist));
	// dprint(sprintf("trace_ent			= %S\n", trace_ent.classname));
	// dprint(sprintf("trace_inopen		= %f\n", trace_inopen));
	// dprint(sprintf("trace_inwater		= %f\n", trace_inwater));

	// If it starts solid, it means the walls are too thick.
	if (trace_startsolid > 0) {
		return;
	}

	if (trace_fraction >= 1.0f)
		return;

	if (trace_ent.takedamage == DAMAGE_YES) {
		/* modify the damage based on the location */
		switch (trace_surface_id) {
		case BODY_HEAD:
			/* the helmet is one power house */
			// if (trace_ent.items & ITEM_HELMET) {
			// 	iDamage = 0;
			// 	sound(self, CHAN_ITEM, "weapons/ric_metal-2.wav", 1, ATTN_IDLE);
			// 	trace_ent.items &= ~ITEM_HELMET;
			// 	return;
			// } else {
				iDamage *= 2;
			//}
			break;
		case BODY_STOMACH:
			iDamage *= 0.9;
			break;
		case BODY_LEGLEFT:
		case BODY_LEGRIGHT:
			iDamage *= 0.4;
			break;
		}

		// /* only headshots count in HL */
		// if (trace_surface_id == BODY_HEAD)
		// 	iDamage *= 3;

		Damage_Apply(trace_ent, self, iDamage, iWeapon, DMG_BULLET);
	}

	if (trace_ent.iBleeds == TRUE) {
		FX_Blood(trace_endpos, [1,0,0]);
		return;
	}
	
	surf = getsurfacenearpoint(trace_ent, trace_endpos);
	tex = getsurfacetexture(trace_ent, surf);

	/* our hashtable is the key to all this */
	switch ((float)hash_get(hashMaterials, tex)) {
	case 'G':
	case 'V':
		// maxPenetrationThickness = 4;
		FX_Impact(IMPACT_METAL, trace_endpos, trace_plane_normal);
		break;
	case 'M':
	case 'P':
		FX_Impact(IMPACT_METAL, trace_endpos, trace_plane_normal);
		break;
	case 'D':
	case 'W':
		// maxPenetrationThickness = 8;
		FX_Impact(IMPACT_WOOD, trace_endpos, trace_plane_normal);
		break;
	case 'Y':
		// maxPenetrationThickness = 16;
		FX_Impact(IMPACT_GLASS, trace_endpos, trace_plane_normal);
		break;
	case 'N':
		// maxPenetrationThickness = 8;
		FX_Impact(IMPACT_DEFAULT, trace_endpos, trace_plane_normal);
		break;
	case 'T':
	default:
		// maxPenetrationThickness = 8;
		FX_Impact(IMPACT_DEFAULT, trace_endpos, trace_plane_normal);
		break;
	}

#ifdef BULLETPENETRATION
	if (iTotalPenetrations > 0) {
		iTotalPenetrations -= 1;
		TraceAttack_FireSingle(trace_endpos + (v_forward * maxPenetrationThickness), vAngle, iDamage / 2, iWeapon);
		//TraceAttack_FireSingle(trace_endpos + (vAngle * 8), vAngle, iDamage / 2, iWeapon);
	}
#endif
}

/* fire a given amount of shots */
void
TraceAttack_FireBullets(int iShots, vector vecPos, int iDamage, vector vecSpread, int iWeapon)
{
	vector vDir;
	makevectors(self.v_angle);

	while (iShots > 0) {
		vDir = aim(self, 100000);
// #ifndef BULLETPATTERNS
// 		vDir += random(-1,1) * vecSpread[0] * v_right;
// 		vDir += random(-1,1) * vecSpread[1] * v_up;
// #else
		player pl = (player)self;

		/* weapons have already applied their multiplier... so attempt this */
		int multiplier = pl.scma_shotmultiplier - iShots;
		float frand = (multiplier / 6);

		/* shoddy attempt at spray patterns */
		if (frand < 1)
			frand = frand;
		else if (frand <= 2)
			frand = 2 - (frand * 1.5);

		vDir += frand * vecSpread[0] * v_right;
		vDir += (vecSpread[1] * v_up) * 2;
//#endif
		TraceAttack_FireSingle(vecPos, vDir, iDamage, iWeapon);
		iShots--;
	}
}

#ifdef BULLETPENETRATION
void
TraceAttack_SetPenetrationPower(int power)
{
	iTotalPenetrations = power;
}
#endif
