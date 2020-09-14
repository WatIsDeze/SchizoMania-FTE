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

void
w_railgun_precache(void)
{
	precache_model("models/v_tfc_railgun.mdl");
	precache_model("models/w_railgun.mdl");
	precache_model("models/p_railgun.mdl");
}

void
w_railgun_updateammo(player pl)
{
#ifdef SERVER
	Weapons_UpdateAmmo(pl, __NULL__, __NULL__, __NULL__);
#endif
}

string
w_railgun_wmodel(void)
{
	return "models/w_railgun.mdl";
}
string
w_railgun_pmodel(void)
{
	return "models/p_railgun.mdl";
}

string
w_railgun_deathmsg(void)
{
	return "%s was assaulted by %s's Assault Cannon.";
}

void
w_railgun_draw(void)
{
	Weapons_SetModel("models/v_tfc_railgun.mdl");
	Weapons_ViewAnimation(0);
}

float
w_railgun_aimanim(void)
{
	return self.flags & FL_CROUCHING ? ANIM_CR_AIMCROWBAR : ANIM_AIMCROWBAR;
}

void
w_railgun_hudpic(int selected, vector pos, float a)
{
#ifdef CLIENT
	if (selected) {
		drawsubpic(
			pos,
			[170,45],
			"sprites/tfchud07.spr_0.tga",
			[0,0],
			[170/256,45/256],
			g_hud_color,
			a,
			DRAWFLAG_ADDITIVE
		);
	} else {
		drawsubpic(
			pos,
			[170,45],
			"sprites/tfchud07.spr_0.tga",
			[0,0],
			[170/256,45/256],
			g_hud_color,
			a,
			DRAWFLAG_ADDITIVE
		);
	}
#endif
}

weapon_t w_railgun =
{
	.name		= "railgun",
	.id			= ITEM_RAILGUN,
	.slot		= 1,
	.slot_pos	= 3,
	.draw		= w_railgun_draw,
	.holster	= __NULL__,
	.primary	= __NULL__,
	.secondary	= __NULL__,
	.reload		= __NULL__,
	.release	= __NULL__,
	.crosshair	= __NULL__,
	.precache	= w_railgun_precache,
	.pickup		= __NULL__,
	.updateammo	= w_railgun_updateammo,
	.wmodel		= w_railgun_wmodel,
	.pmodel		= w_railgun_pmodel,
	.deathmsg	= w_railgun_deathmsg,
	.aimanim	= w_railgun_aimanim,
	.hudpic		= w_railgun_hudpic
};
