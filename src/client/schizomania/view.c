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

//=======================
// void View_DrawHoveredItem(void)
//
// Does a trace check to see if an item is in range and hovered.
// If it is, give it a shell.
//=======================
entity oldItemTraceEnt;

void View_HandleHoverObject(void) {
	player pl = (player)pSeat->m_ePlayer;

	// Prep vectors.
	vector vecAng = [pl.pitch, pl.angles[1], pl.angles[2]];
	vector vecSrc = pl.origin + pl.view_ofs;
	makevectors(vecAng);

	// Do the entity trace.
	traceline(vecSrc, vecSrc + (v_forward * 64), MOVE_HITMODEL, self);

	// We undo the the effects on the entity found in the previous frame.
	// After that, we'll see if we're still focussed on it. If so, we re-apply them again.
	if (oldItemTraceEnt != __NULL__) {
		if (oldItemTraceEnt.gflags & GF_HOVER_FULLBRIGHT) {
			// Remove effect.
			oldItemTraceEnt.effects &= ~EF_FULLBRIGHT;

			// We lost focus on a useable object. Let's inform the player seat about this.
			pSeat->m_iHasFocusOnUseable = FALSE;
		}		

		// Reset entity reference.
		oldItemTraceEnt = __NULL__;
	}

	// If we hit a trace, and it had GF_HOVER_FULLBRIGHT, EF_FULLBRIGHT it again.
	if (trace_ent != world) {
		// All of the below fail, exception for CBaseEntity.
		if (trace_ent.gflags & GF_HOVER_FULLBRIGHT) {
			trace_ent.effects |= EF_FULLBRIGHT;

			// We have focus on a useable object. Let's inform the player seat about this.
			pSeat->m_iHasFocusOnUseable = TRUE;
		}
		
		// Store it so we can remove effect when unhovered.
		oldItemTraceEnt = trace_ent;
	}
}

void
View_UpdateWeapon(entity vm, entity mflash)
{
	player pl = (player)pSeat->m_ePlayer;

	/* only bother upon change */
	if (pSeat->m_iLastWeapon == pl.activeweapon) {
		return;
	}
	pSeat->m_iOldWeapon = pSeat->m_iLastWeapon;
	pSeat->m_iLastWeapon = pl.activeweapon;

	if (!pl.activeweapon) {
		return;
	}

	/* hack, we changed the wep, move this into Game_Input/PMove */
	Weapons_Draw();

	/* we forced a weapon call outside the prediction,
	 * thus we need to update all the net variables to
	 * make sure these updates are recognized. this is
	 * vile but it'll have to do for now */
	pl.net_w_attack_next = pl.w_attack_next;
	pl.net_w_idle_next = pl.w_idle_next;
	pl.net_viewzoom = pl.viewzoom;
	pl.net_weapontime = pl.weapontime;

	/* figure out when the attachments start. in FTE attachments for
	 * HLMDL are treated as bones. they start at numbones + 1 */
	skel_delete(mflash.skeletonindex);
	mflash.skeletonindex = skel_create(vm.modelindex);
	pSeat->m_iVMBones = skel_get_numbones(mflash.skeletonindex) + 1;
	pSeat->m_iVMEjectBone = pSeat->m_iVMBones + 1;
}
