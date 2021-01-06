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
	PISTOL_TPOSE,
	PISTOL_ATTACK1,
	PISTOL_IDLE1,
	PISTOL_RELOAD1,
	PISTOL_DRAW1,
	PISTOL_HOLSTER1
	// ITEM_PISTOL_IDLE1,
	// ITEM_PISTOL_IDLE2,
	// ITEM_PISTOL_IDLE3,
	// ITEM_PISTOL_SHOOT_BURST1,
	// ITEM_PISTOL_SHOOT_BURST2,
	// ITEM_PISTOL_SHOOT,
	// ITEM_PISTOL_SHOOT_EMPTY,
	// ITEM_PISTOL_RELOAD1,
	// ITEM_PISTOL_DRAW1,
	// ITEM_PISTOL_UNUSED1,
	// ITEM_PISTOL_UNUSED2,
	// ITEM_PISTOL_DRAW2,
	// ITEM_PISTOL_RELOAD2
};

void
w_pistol_precache(void)
{
#ifdef SERVER
	Sound_Precache("weapon_pistol.deploy");
	Sound_Precache("weapon_pistol.fire");
	Sound_Precache("weapon_pistol.reload");
	precache_model("models/weapons/pistol/w_pistol.vvm");
#else
	precache_model("models/weapons/pistol/v_pistol.vvm");
#endif
}

void
w_pistol_updateammo(player pl)
{
#ifdef SERVER
	Weapons_UpdateAmmo(pl, pl.glock_mag, pl.ammo_9mm, -1);
#endif
}

string
w_pistol_wmodel(void)
{
	return "models/weapons/pistol/w_pistol.vvm";
}

string
w_pistol_pmodel(void)
{
	return "";
}

string
w_pistol_deathmsg(void)
{
	return "";
}

int
w_pistol_pickup(int new, int startammo)
{
#ifdef SERVER
	player pl = (player)self;

	// if (new) {
	// 	pl.glock_mag = 20;
	// } else {
	// 	if (pl.ammo_9mm < MAX_A_9MM) {
	// 		pl.ammo_9mm = bound(0, pl.ammo_9mm + 20, MAX_A_9MM);
	// 	} else {
	// 		return FALSE;
	// 	}
	// }
#endif
	return TRUE;
}

void
w_pistol_draw(void)
{
	player pl = (player)self;
	Weapons_SetModel("models/weapons/pistol/v_pistol.vvm");
	Weapons_ViewAnimation(PISTOL_DRAW1);
#ifdef CLIENT
//	Got to do this for crosshair support.
	pl.scma_cross_mindist = 8;
	pl.scma_cross_deltadist = 3;
#else
	Sound_Play(pl, CHAN_WEAPON, "weapon_pistol.deploy");
#endif
}

void
w_pistol_holster(void)
{
#ifdef CLIENT
	Weapons_ViewAnimation(PISTOL_HOLSTER1);
#endif
}

void
w_pistol_primary(void)
{
	player pl = (player)self;

	if (pl.w_attack_next > 0.0) {
		return;
	}

	if (pl.gflags & GF_SEMI_TOGGLED) {
		return;
	}
	/* ammo check */
#ifdef CLIENT
	if (!pl.a_ammo1) {
		return;
	}
#else
	if (!pl.glock_mag) {
		return;
	}
#endif

	// Counter-Strike crosshair stuff.
	SCMA_ShotMultiplierAdd(pl, 1);
	float accuracy = SCMA_CalculateAccuracy(pl, 200);

	/* actual firing */
#ifdef CLIENT
	pl.a_ammo1--;
	View_SetMuzzleflash(MUZZLE_SMALL);
	Weapons_ViewPunchAngle([-2,0,0]);

	if (pl.a_ammo1) {
		Weapons_ViewAnimation(PISTOL_ATTACK1);
	} else {
		//Weapons_ViewAnimation(PISTOL_ATTACK_EMPTY);
	}
#else
	pl.glock_mag--;
	TraceAttack_SetPenetrationPower(1);
	TraceAttack_FireBullets(1, pl.origin + pl.view_ofs, Skill_GetValue("plr_9mm_bullet", 8), [accuracy,accuracy], WEAPON_PISTOL);
	//TraceAttack_FireBullets(1, pl.origin + pl.view_ofs, Skill_GetValue("plr_9mm_bullet"), [0.01,0.01], WEAPON_ITEM_PISTOL);
	if (pl.a_ammo3) {
		Sound_Play(pl, CHAN_WEAPON, "weapon_pistol.fire");
	} else {
		Sound_Play(pl, CHAN_WEAPON, "weapon_pistol.fire");
	}

	if (self.flags & FL_CROUCHING)
		Animation_PlayerTopTemp(ANIM_SHOOT1HAND, 0.45f);
	else
		Animation_PlayerTopTemp(ANIM_CR_SHOOT1HAND, 0.45f);
#endif

	if (pl.a_ammo3) {
		// int r = (float)input_sequence % 2;
		// switch (r) {
		// case 0:
		// 	Weapons_ViewAnimation(ITEM_PISTOL_SHOOT_BURST1);
		// 	break;
		// default:
		// 	Weapons_ViewAnimation(ITEM_PISTOL_SHOOT_BURST2);
		// 	break;
		// }
		// pl.w_attack_next = 0.5f;
	} else {
		if (pl.a_ammo1 <= 0) {
			Weapons_ViewAnimation(PISTOL_ATTACK1);
		} else {
//			Weapons_ViewAnimation(PISTOL_ATTACK1_EMPTY);
		}
		pl.w_attack_next = 0.15f;
	}

	pl.gflags |= GF_SEMI_TOGGLED;
	pl.w_idle_next = pl.w_attack_next;
}

void
w_pistol_secondary(void)
{
	player pl = (player)self;

	if (pl.w_attack_next > 0) {
		return;
	}

	/* toggle burst-fire */
	pl.a_ammo3 = 1 - pl.a_ammo3;

#ifdef CLIENT
	if (pl.a_ammo3) {
		CSQC_Parse_CenterPrint("Switched to Burst-Fire mode");
	} else {
		CSQC_Parse_CenterPrint("Switched to Semi-Automatic mode");
	}
#endif

	pl.w_attack_next = 1.0f;
	pl.w_idle_next = pl.w_attack_next;
}

void
w_pistol_reload(void)
{
	player pl = (player)self;

	if (pl.w_attack_next > 0.0) {
		return;
	}

#ifdef CLIENT
	if (pl.a_ammo1 >= 20) {
		return;
	}
	if (!pl.a_ammo2) {
		return;
	}
#else
	if (pl.glock_mag >= 20) {
		return;
	}
	if (!pl.ammo_9mm) {
		return;
	}

	Weapons_ReloadWeapon(pl, player::glock_mag, player::ammo_9mm, 20);
	Weapons_UpdateAmmo(pl, pl.glock_mag, pl.ammo_9mm, -1);

	Sound_Play(pl, CHAN_WEAPON, "weapon_pistol.reload");
#endif
	Weapons_ViewAnimation(PISTOL_RELOAD1);

	pl.w_attack_next = 2.1f;
	pl.w_idle_next = pl.w_attack_next;
}

void
w_pistol_release(void)
{
	player pl = (player)self;

	if (pl.w_idle_next > 0.0) {
		return;
	}

	Weapons_ViewAnimation(PISTOL_IDLE1);
	pl.w_idle_next = 2.5f;
}

float
w_pistol_aimanim(void)
{
	return self.flags & FL_CROUCHING ? ANIM_CR_AIM1HAND : ANIM_AIM1HAND;
}

void
w_pistol_hud(void)
{
#ifdef CLIENT
//	vector cross_pos;
//	vector aicon_pos;

//	cross_pos = g_hudmins + (g_hudres / 2) + [-12,-12];
//	aicon_pos = g_hudmins + [g_hudres[0] - 48, g_hudres[1] - 42];
	SCMA_DrawCrosshair();
	// // drawsubpic(
	// // 	cross_pos,
	// // 	[24,24],
	// // 	g_cross_spr,
	// // 	[0.1875,0],
	// // 	[0.1875, 0.1875],
	// // 	[1,1,1],
	// // 	1.0f,
	// // 	DRAWFLAG_NORMAL
	// // );

	// HUD_DrawAmmo1();
	// HUD_DrawAmmo2();
	// vector aicon_pos = g_hudmins + [g_hudres[0] - 48, g_hudres[1] - 42];
	// drawsubpic(aicon_pos, [24,24], g_hud7_spr, [48/256,72/256], [24/256, 24/256], g_hud_color, pSeat->m_flAmmo2Alpha, DRAWFLAG_ADDITIVE);
	// // drawsubpic(
	// // 	aicon_pos,
	// // 	[24,24],
	// // 	g_hud7_spr,
	// // 	[0,72/128],
	// // 	[24/256, 24/128],
	// // 	g_hud_color,
	// // 	pSeat->m_flAmmo2Alpha,
	// // 	DRAWFLAG_ADDITIVE
	// // );
#endif
}

void
w_pistol_hudpic(int selected, vector pos, float a)
{
#ifdef CLIENT
	if (selected) {
		drawsubpic(
			pos,
			[170,45],
			g_hud4_spr,
			[0,45/256],
			[170/256,45/256],
			g_hud_color,
			a,
			DRAWFLAG_ADDITIVE
		);
	} else {
		drawsubpic(
			pos,
			[170,45],
			g_hud1_spr,
			[0,45/256],
			[170/256,45/256],
			g_hud_color,
			a,
			DRAWFLAG_ADDITIVE
		);
	}
#endif
}

weapon_t w_pistol =
{
	.name		= "pistol",
	.id			= ITEM_PISTOL,
	.slot		= 1,
	.slot_pos	= 0,
	.draw		= w_pistol_draw,
	.holster	= w_pistol_holster,
	.primary	= w_pistol_primary,
	.secondary	= w_pistol_secondary,
	.reload		= w_pistol_reload,
	.release	= w_scma_weaponrelease,
	.crosshair	= w_pistol_hud,
	.precache	= w_pistol_precache,
	.pickup		= w_pistol_pickup,
	.updateammo	= w_pistol_updateammo,
	.wmodel		= w_pistol_wmodel,
	.pmodel		= w_pistol_pmodel,
	.deathmsg	= w_pistol_deathmsg,
	.aimanim	= w_pistol_aimanim,
	.hudpic		= w_pistol_hudpic
};

/* pickups */
#ifdef SERVER
// void
// weapon_9mmhandgun(void)
// {
// 	Weapons_InitItem(WEAPON_ITEM_PISTOL);
// }

void
weapon_pistol(void)
{
	Weapons_InitItem(WEAPON_PISTOL);
}
#endif
