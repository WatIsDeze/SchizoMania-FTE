
/*
 * Copyright (c) 2020 Mike Poortman <someemail@mail.com>
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
// void i_pistol_precache(void)
// 
// Precache.
//=======================
void i_pistol_precache(void) {
#ifdef SERVER
//	Sound_Precache("ITEM_PISTOL.use");
	precache_model("models/weapons/pistol/w_pistol.vvm");
#else
	precache_model("models/weapons/pistol/w_pistol.vvm");
#endif
}

//=======================
// void i_pistol_pickup(void)
//
// Pickup.
//=======================
void i_pistol_pickup(player pl) {
#ifdef SERVER
	Weapons_AddItem(pl, WEAPON_PISTOL, 20);
#endif
}

//=======================
// void i_pistol_equip(void)
//
// Equip..
//=======================
#ifdef SERVER
// Predefine.
void Weapons_Draw(void)
#endif
void i_pistol_equip(player pl) {
#ifdef SERVER
	pl.activeweapon = WEAPON_PISTOL;
	Weapons_Draw();
#endif
}

//=======================
// void i_pistol_drop(void)
//
// Drop.
//=======================
void Weapons_Holster();
void i_pistol_drop(player pl) {
#ifdef SERVER
dprint("===================\nDROPPED GLOKC\n=============");
	Weapons_Holster();
	Weapons_RemoveItem(pl, WEAPON_PISTOL);
	pl.activeweapon = 0;
#endif
}

//=======================
// string i_pistol_wmodel(void)
//
// Return item model string path.
//=======================
string i_pistol_wmodel(void) {
    return "models/weapons/pistol/w_pistol.vvm";
}

inventory_item_t i_pistol = 
{
	.name		= "Pistol (9mm)",

    .txtPickup	= "picked up a ^xF42Pistol (9mm)",
	.txtDrop	= "dropped a ^xF42Pistol (9mm)",
    .txtUse		= "used a ^xF42Pistol (9mm)",
	.txtDescription = "The ^xF42Pistol (9mm)FFF is a powerful tool in combat.",

	.ID			= INVENTORY_ITEM_PISTOL,
	.mins		= [-8,-8, 0],
	.maxs		= [8, 8, 8],
	
	.use		= __NULL__,
	.pickup		= i_pistol_pickup,
	.equip		= i_pistol_equip,
	.drop		= i_pistol_drop,

	.precache	= i_pistol_precache,
    .wmodel     = i_pistol_wmodel
};