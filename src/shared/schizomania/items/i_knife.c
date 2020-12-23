
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
// void i_knife_precache(void)
// 
// Precache.
//=======================
void i_knife_precache(void) {
#ifdef SERVER
	Sound_Precache("item_glock.use");
	precache_model("models/w_knife.mdl");
#else
	precache_model("models/w_knife.mdl");
#endif
}

//=======================
// void i_knife_use(void)
//
// Use.
//=======================
void i_knife_use(player pl) {

}

//=======================
// void i_glock18_pickup(void)
//
// Pickup.
//=======================
void i_knife_pickup(player pl) {
#ifdef SERVER
	Weapons_AddItem(pl, WEAPON_KNIFE, 20);
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
void i_knife_equip(player pl) {
#ifdef SERVER
//	Weapons_Holster();
	pl.activeweapon = WEAPON_KNIFE;
	Weapons_Draw();
#endif
}

//=======================
// void i_glock18_drop(void)
//
// Drop.
//=======================
void Weapons_Holster();
void i_knife_drop(player pl) {
#ifdef SERVER
dprint("===================\nDROPPED GLOKC\n=============");
	Weapons_Holster();
	Weapons_RemoveItem(pl, WEAPON_KNIFE);
	pl.activeweapon = 0;
#endif
}

//=======================
// string i_knife_wmodel(void)
//
// Return item model string path.
//=======================
string i_knife_wmodel(void) {
    return "models/w_knife.mdl";
}

inventory_item_t i_knife = 
{
	.name		= "Knife",

    .txtPickup	= "pickd up a ^xF42Knife",
    .txtDrop	= "dropped a ^xF42Knife",
	.txtUse		= "used a ^xF42Knife",
	.txtDescription = "A sharp hunting ^xF42knife^xFFF, good for... 'hunting'.",

	.ID			= INVENTORY_ITEM_KNIFE,
	.mins		= [-8,-8, 0],
	.maxs		= [8, 8, 8],
	
	.use		= i_knife_use,
	.pickup		= i_knife_pickup,
	.equip		= i_knife_equip,
	.drop		= i_knife_drop,
	
	.precache	= i_knife_precache,
    .wmodel     = i_knife_wmodel
};