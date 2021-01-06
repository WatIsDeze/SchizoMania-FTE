
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
// void i_glock18_precache(void)
// 
// Precache.
//=======================
void i_glock18_precache(void) {
#ifdef SERVER
//	Sound_Precache("item_glock.use");
	precache_model("models/weapons/pistol/w_pistol.vvm");
#else
	precache_model("models/weapons/pistol/w_pistol.vvm");
#endif
}

//=======================
// void i_glock18_pickup(void)
//
// Pickup.
//=======================
void i_glock18_pickup(player pl) {
#ifdef SERVER
	Weapons_AddItem(pl, WEAPON_GLOCK, 20);
#endif
}

//=======================
// void i_glock18_equip(void)
//
// Equip..
//=======================
#ifdef SERVER
// Predefine.
void Weapons_Draw(void)
#endif
void i_glock18_equip(player pl) {
#ifdef SERVER
	pl.activeweapon = WEAPON_GLOCK;
	Weapons_Draw();
#endif
}

//=======================
// void i_glock18_drop(void)
//
// Drop.
//=======================
void Weapons_Holster();
void i_glock18_drop(player pl) {
#ifdef SERVER
dprint("===================\nDROPPED GLOKC\n=============");
	Weapons_Holster();
	Weapons_RemoveItem(pl, WEAPON_GLOCK);
	pl.activeweapon = 0;
#endif
}

//=======================
// string i_glock18_wmodel(void)
//
// Return item model string path.
//=======================
string i_glock18_wmodel(void) {
    return "models/weapons/pistol/w_pistol.vvm";
}

inventory_item_t i_glock18 = 
{
	.name		= "Glock 18",

    .txtPickup	= "picked up a ^xF42Glock 18",
	.txtDrop	= "dropped a ^xF42Glock 18",
    .txtUse		= "used a ^xF42Glock 18",
	.txtDescription = "The ^xF42Glock 18^FFF is a powerful tool in combat.",

	.ID			= INVENTORY_ITEM_GLOCK,
	.mins		= [-8,-8, 0],
	.maxs		= [8, 8, 8],
	
	.use		= __NULL__,
	.pickup		= i_glock18_pickup,
	.equip		= i_glock18_equip,
	.drop		= i_glock18_drop,

	.precache	= i_glock18_precache,
    .wmodel     = i_glock18_wmodel
};