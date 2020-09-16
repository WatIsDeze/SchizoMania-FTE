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

/*QUAKED weapon_9mmhandgun (0 0 1) (-16 -16 0) (16 16 32)
"model" "models/w_9mmhandgun.mdl"

HALF-LIFE (1998) ENTITY

9mm Handgun/Glock Weapon
Same as weapon_glock

*/

/*QUAKED weapon_glock (0 0 1) (-16 -16 0) (16 16 32)
"model" "models/w_9mmhandgun.mdl"

HALF-LIFE (1998) ENTITY

9mm Handgun/Glock Weapon
Same as weapon_9mmhandgun

*/

enum
{
	GLOCK_IDLE1,
	GLOCK_IDLE2,
	GLOCK_IDLE3,
	GLOCK_SHOOT_BURST1,
	GLOCK_SHOOT_BURST2,
	GLOCK_SHOOT,
	GLOCK_SHOOT_EMPTY,
	GLOCK_RELOAD1,
	GLOCK_DRAW1,
	GLOCK_UNUSED1,
	GLOCK_UNUSED2,
	GLOCK_DRAW2,
	GLOCK_RELOAD2
};

void
w_glock_precache(void)
{
#ifdef SERVER
	Sound_Precache("weapon_glock18.fire");
	Sound_Precache("weapon_glock18.burstfire");
	precache_model("models/w_glock18.mdl");
#else
	precache_model("models/v_glock18.mdl");
	precache_model("models/p_glock18.mdl");
#endif
}

void
w_glock_updateammo(player pl)
{
#ifdef SERVER
	Weapons_UpdateAmmo(pl, pl.glock_mag, pl.ammo_9mm, -1);
#endif
}

string
w_glock_wmodel(void)
{
	return "models/w_glock18.mdl";
}

string
w_glock_pmodel(void)
{
	return "models/p_glock18.mdl";
}

string
w_glock_deathmsg(void)
{
	return "";
}

int
w_glock_pickup(int new, int startammo)
{
#ifdef SERVER
	player pl = (player)self;

	if (new) {
		pl.glock_mag = 20;
	} else {
		if (pl.ammo_9mm < MAX_A_9MM) {
			pl.ammo_9mm = bound(0, pl.ammo_9mm + 20, MAX_A_9MM);
		} else {
			return FALSE;
		}
	}
#endif
	return TRUE;
}

void
w_glock_draw(void)
{
	player pl = (player)self;
	Weapons_SetModel("models/v_glock18.mdl");
	int r = (float)input_sequence % 2;
	switch (r) {
	case 0:
		Weapons_ViewAnimation(GLOCK_DRAW1);
		break;
	default:
		Weapons_ViewAnimation(GLOCK_DRAW2);
		break;
	}

#ifdef CLIENT
//	Got to do this for crosshair support.
//	pl.cs_cross_mindist = 8;
//	pl.cs_cross_deltadist = 3;
#endif
}

// void
// w_glock_holster(void)
// {
// #ifdef CLIENT
// 	Weapons_ViewAnimation(GLOCK_HOLSTER);
// #endif
// }

void
w_glock_primary(void)
{
	player pl = (player)self;

	if (pl.w_attack_next > 0.0) {
		return;
	}

	if (pl.flags & FL_SEMI_TOGGLED) {
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
	//Cstrike_ShotMultiplierAdd(pl, 1);
	//float accuracy = Cstrike_CalculateAccuracy(pl, 200);

	/* actual firing */
#ifdef CLIENT
	pl.a_ammo1--;
	View_SetMuzzleflash(MUZZLE_SMALL);
	//Weapons_ViewPunchAngle([-2,0,0]);

	//if (pl.a_ammo1) {
//		Weapons_ViewAnimation(GLOCK_SHOOT);
//	} else {
//		Weapons_ViewAnimation(GLOCK_SHOOT_EMPTY);
//	}
#else
	pl.glock_mag--;
	//TraceAttack_SetPenetrationPower(0);
	//TraceAttack_FireBullets(1, pl.origin + pl.view_ofs, 25, [accuracy,accuracy], WEAPON_GLOCK18);
	TraceAttack_FireBullets(1, pl.origin + pl.view_ofs, Skill_GetValue("plr_9mm_bullet"), [0.01,0.01], WEAPON_GLOCK);
	if (pl.a_ammo3) {
		Sound_Play(pl, CHAN_WEAPON, "weapon_glock18.burstfire");
	} else {
		Sound_Play(pl, CHAN_WEAPON, "weapon_glock18.fire");
	}

	if (self.flags & FL_CROUCHING)
		Animation_PlayerTopTemp(ANIM_SHOOT1HAND, 0.45f);
	else
		Animation_PlayerTopTemp(ANIM_CR_SHOOT1HAND, 0.45f);
#endif

	if (pl.a_ammo3) {
		int r = (float)input_sequence % 2;
		switch (r) {
		case 0:
			Weapons_ViewAnimation(GLOCK_SHOOT_BURST1);
			break;
		default:
			Weapons_ViewAnimation(GLOCK_SHOOT_BURST2);
			break;
		}
		pl.w_attack_next = 0.5f;
	} else {
		if (pl.a_ammo1 <= 0) {
			Weapons_ViewAnimation(GLOCK_SHOOT_EMPTY);
		} else {
			Weapons_ViewAnimation(GLOCK_SHOOT);
		}
		pl.w_attack_next = 0.15f;
	}

	pl.flags |= FL_SEMI_TOGGLED;
	pl.w_idle_next = pl.w_attack_next;
}

void
w_glock_secondary(void)
{
	player pl = (player)self;

	if (pl.w_attack_next > 0) {
		return;
	}

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
w_glock_reload(void)
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
#endif

	int r = (float)input_sequence % 2;
	switch (r) {
	case 0:
		Weapons_ViewAnimation(GLOCK_RELOAD1);
		break;
	default:
		Weapons_ViewAnimation(GLOCK_RELOAD2);
		break;
	}

	pl.w_attack_next = 2.1f;
	pl.w_idle_next = pl.w_attack_next;
}

void
w_glock_release(void)
{
	player pl = (player)self;
	int r;

	if (pl.w_idle_next > 0.0) {
		return;
	}

	r = (float)input_sequence % 3;
	switch (r) {
	case 1:
		Weapons_ViewAnimation(GLOCK_IDLE2);
		pl.w_idle_next = 2.5f;
		break;
	case 2:
		Weapons_ViewAnimation(GLOCK_IDLE3);
		pl.w_idle_next = 3.5f;
		break;
	default:
		Weapons_ViewAnimation(GLOCK_IDLE1);
		pl.w_idle_next = 3.75f;
		break;
	}
}

float
w_glock_aimanim(void)
{
	return self.flags & FL_CROUCHING ? ANIM_CR_AIM1HAND : ANIM_AIM1HAND;
}

void
w_glock_hud(void)
{
#ifdef CLIENT
	vector cross_pos;
	vector aicon_pos;

	cross_pos = g_hudmins + (g_hudres / 2) + [-12,-12];
	aicon_pos = g_hudmins + [g_hudres[0] - 48, g_hudres[1] - 42];

	drawsubpic(
		cross_pos,
		[24,24],
		g_cross_spr,
		[0.1875,0],
		[0.1875, 0.1875],
		[1,1,1],
		1.0f,
		DRAWFLAG_NORMAL
	);

	HUD_DrawAmmo1();
	HUD_DrawAmmo2();

	drawsubpic(
		aicon_pos,
		[24,24],
		g_hud7_spr,
		[0,72/128],
		[24/256, 24/128],
		g_hud_color,
		pSeat->m_flAmmo2Alpha,
		DRAWFLAG_ADDITIVE
	);
#endif
}

void
w_glock_hudpic(int selected, vector pos, float a)
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

weapon_t w_glock =
{
	.name		= "9mmhandgun",
	.id			= ITEM_GLOCK,
	.slot		= 1,
	.slot_pos	= 0,
	.draw		= w_glock_draw,
	.holster	= __NULL__,
	.primary	= w_glock_primary,
	.secondary	= w_glock_secondary,
	.reload		= w_glock_reload,
	.release	= w_scma_weaponrelease,
	.crosshair	= w_glock_hud,
	.precache	= w_glock_precache,
	.pickup		= w_glock_pickup,
	.updateammo	= w_glock_updateammo,
	.wmodel		= w_glock_wmodel,
	.pmodel		= w_glock_pmodel,
	.deathmsg	= w_glock_deathmsg,
	.aimanim	= w_glock_aimanim,
	.hudpic		= w_glock_hudpic
};

/* pickups */
#ifdef SERVER
void
weapon_9mmhandgun(void)
{
	Weapons_InitItem(WEAPON_GLOCK);
}

void
weapon_glock(void)
{
	Weapons_InitItem(WEAPON_GLOCK);
}
#endif
