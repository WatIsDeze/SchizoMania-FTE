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

enum
{
	KNIFE_TPOSE,
	KNIFE_IDLE1,
	KNIFE_ATTACK1,
	KNIFE_ATTACK2,
	KNIFE_ATTACK3,
	KNIFE_ATTACK4,
	KNIFE_DRAW1,
	KNIFE_HOLSTER1
};

//=======================================================================//
// w_knife_precache
//
// Precaches all knife audio, and models.
//=======================================================================//
void
w_knife_precache(void)
{
#ifdef SERVER

	Sound_Precache("weapon_knife.slash");
	Sound_Precache("weapon_knife.slashhit");
	Sound_Precache("weapon_knife.stab");
	Sound_Precache("weapon_knife.stabhit");
	Sound_Precache("weapon_knife.hit");
	Sound_Precache("weapon_knife.deploy");

	precache_model("models/w_knife.mdl");
#else
	precache_model("models/weapons/knife/v_knife.mdl");
	precache_model("models/p_knife.mdl");
#endif
}

//=======================================================================//
// w_knife_updateammo
//
// Updates ammo. No need for this with the knife.
//=======================================================================//
void
w_knife_updateammo(player pl)
{
#ifdef SERVER
	Weapons_UpdateAmmo(pl, -1, -1, -1);
#endif
}

//=======================================================================//
// w_knife_wmodel
//
// Return string path to knife world model.
//=======================================================================//
string
w_knife_wmodel(void)
{
	return "models/w_knife.mdl";
}

//=======================================================================//
// w_knife_wmodel
//
// Return string path to knife player model.
//=======================================================================//
string
w_knife_pmodel(void)
{
	return "models/p_knife.mdl";
}

//=======================================================================//
// w_knife_wmodel
//
// Message for obituary, death msg.
//=======================================================================//
string
w_knife_deathmsg(void)
{
	return "";
}

//=======================================================================//
// w_knife_draw
//
// Weapon DRAW function, not as in rendering, but fetching it from your pockets.
//=======================================================================//
void
w_knife_draw(void)
{
#ifdef CLIENT
	Weapons_SetModel("models/weapons/knife/v_knife.mdl");
	Weapons_ViewAnimation(KNIFE_DRAW1);
#endif
}

//=======================================================================//
// w_knife_primary
//
// Primary shot action.
//=======================================================================//
void
w_knife_primary(void)
{
	player pl = (player)self;

	if (pl.w_attack_next > 0.0) {
		return;
	}

	int r = (float)input_sequence % 2;
	switch (r) {
	case 0:
		Weapons_ViewAnimation(KNIFE_ATTACK1);
		break;
	default:
		Weapons_ViewAnimation(KNIFE_ATTACK2);
		break;
	}
	pl.w_idle_next = 1.0f;
	pl.w_attack_next = 0.7f;

#ifdef SERVER
	vector src;
	Weapons_MakeVectors();
	src = pl.origin + pl.view_ofs;
	traceline(src, src + (v_forward * 32), FALSE, pl);

	Sound_Play(pl, CHAN_WEAPON, "weapon_knife.slash");

	if (self.flags & FL_CROUCHING)
		Animation_PlayerTopTemp(ANIM_SHOOTCROWBAR, 0.45f);
	else
		Animation_PlayerTopTemp(ANIM_CR_SHOOTCROWBAR, 0.45f);

	if (trace_fraction >= 1.0) {
		return;
	}

	if (trace_ent.iBleeds) {
		FX_Blood(trace_endpos, [1,0,0]);
		Sound_Play(pl, CHAN_WEAPON, "weapon_knife.slashhit");
	} else {
		Sound_Play(pl, CHAN_WEAPON, "weapon_knife.hit");
	}

	if (trace_ent.takedamage) {
		Damage_Apply(trace_ent, pl, 15, WEAPON_KNIFE, DMG_SLASH);
	}
#endif
}

//=======================================================================//
// w_knife_secondary
//
// Seconday shot action.
//=======================================================================//
void
w_knife_secondary(void)
{
	player pl = (player)self;

	if (pl.w_attack_next > 0.0) {
		return;
	}

	int r = (float)input_sequence % 2;
	switch (r) {
	case 0:
		Weapons_ViewAnimation(KNIFE_ATTACK3);
		break;
	default:
		Weapons_ViewAnimation(KNIFE_ATTACK4);
		break;
	}
	pl.w_idle_next = 1.0f;
	pl.w_attack_next = 1.2f;

#ifdef SERVER
	vector src;
	Weapons_MakeVectors();
	src = pl.origin + pl.view_ofs;
	traceline(src, src + (v_forward * 32), FALSE, pl);

	//Sound_Play(pl, CHAN_WEAPON, "weapon_knife.miss");
	Sound_Play(pl, CHAN_WEAPON, "weapon_knife.stab");

	if (trace_fraction >= 1.0) {
		return;
	}

	/* don't bother with decals, we got squibs */
	if (trace_ent.iBleeds) {
		FX_Blood(trace_endpos, [1,0,0]);
		Sound_Play(pl, CHAN_WEAPON, "weapon_knife.stabhit");
	} else {
		Sound_Play(pl, CHAN_WEAPON, "weapon_knife.hit");
	}

	if (trace_ent.takedamage) {
		Damage_Apply(trace_ent, pl, 65, WEAPON_KNIFE, DMG_SLASH);
	}
#endif
}

//=======================================================================//
// w_snark_release
//
// Called whenever a weapon's fire button (primary, secondary) has been released.
//=======================================================================//
void w_knife_release(void)
{
	player pl = (player)self;
	if (pl.w_idle_next > 0.0) {
		return;
	}

	Weapons_ViewAnimation(KNIFE_IDLE1);
	pl.w_idle_next = 3.2f;
	// r = (float)input_sequence % 3;
	// switch (r) {
	// case 0:
	// 	Weapons_ViewAnimation(KNIFE_IDLE1);
	// 	pl.w_idle_next = 1.2f;
	// 	break;
	// case 1:
	// 	Weapons_ViewAnimation(KNIFE_IDLE1);
	// 	pl.w_idle_next = 2.1f;
	// 	break;
	// default:
	// 	Weapons_ViewAnimation(KNIFE_IDLE1);
	// 	pl.w_idle_next = 1.8f;
	// 	break;
	// }
}

//=======================================================================//
// w_knife_aimanim
//
// Returns player model aim animation to use.
//=======================================================================//
float
w_knife_aimanim(void)
{
	return self.flags & FL_CROUCHING ? ANIM_CR_AIMCROWBAR : ANIM_AIMCROWBAR;
}

//=======================================================================//
// w_knife_hudpic
//
// We won't be using this...
//=======================================================================//
void
w_knife_hudpic(int selected, vector pos, float a)
{
// #ifdef CLIENT
// 	if (selected) {
// 		drawsubpic(
// 			pos,
// 			[170,45],
// 			g_hud11_spr,
// 			[0,135/256],
// 			[170/256,45/256],
// 			g_hud_color,
// 			1.0f,
// 			DRAWFLAG_ADDITIVE
// 		);
// 	} else {
// 		drawsubpic(
// 			pos,
// 			[170,45],
// 			g_hud10_spr,
// 			[0,135/256],
// 			[170/256,45/256],
// 			g_hud_color,
// 			1.0f,
// 			DRAWFLAG_ADDITIVE
// 		);
// 	}
// #endif
}

weapon_t w_knife =
{
	.name		= "knife",
	.id			= ITEM_KNIFE,
	.slot		= 2,
	.slot_pos	= 0,
	.allow_drop	= FALSE,
	.draw		= w_knife_draw,
	.holster	= __NULL__,
	.primary	= w_knife_primary,
	.secondary	= w_knife_secondary,
	.reload		= __NULL__,
	.release	= w_knife_release,
	.crosshair	= __NULL__,
	.precache	= w_knife_precache,
	.pickup		= __NULL__,
	.updateammo	= w_knife_updateammo,
	.wmodel		= w_knife_wmodel,
	.pmodel		= w_knife_pmodel,
	.deathmsg	= w_knife_deathmsg,
	.aimanim	= w_knife_aimanim,
	.hudpic		= w_knife_hudpic
};

#ifdef SERVER
void
weapon_knife(void)
{
	Weapons_InitItem(WEAPON_KNIFE);
}
#endif
