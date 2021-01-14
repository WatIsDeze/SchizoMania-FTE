
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
	precache_model("models/weapons/knife/w_knife.vvm");
#else
	precache_model("models/weapons/knife/w_knife.vvm");
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
// void i_pistol_pickup(void)
//
// Pickup.
//=======================
void i_knife_pickup(player pl) {
#ifdef SERVER
	Weapons_AddItem(pl, WEAPON_KNIFE, 20);
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
void i_knife_equip(player pl) {
#ifdef SERVER
//	Weapons_Holster();
	pl.activeweapon = WEAPON_KNIFE;
	Weapons_Draw();
#endif
}

//=======================
// void i_pistol_drop(void)
//
// Drop.
//=======================
void Weapons_Holster();
void i_knife_drop(player pl) {
#ifdef SERVER
dprint("===================\nDROPPED KNIFE\n=============");
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
    return "models/weapons/knife/w_knife.vvm";
}

inventory_item_t i_knife = 
{
	.name		= "Knife",

    .txtPickup	= "pickd up a ^xF42Knife",
    .txtDrop	= "dropped a ^xF42Knife",
	.txtUse		= "used a ^xF42Knife",
	.txtDescription = "A sharp hunting ^xF42knife^xFFF, good for... 'hunting'.",

	.ID			= INVENTORY_ITEM_KNIFE,
	.mins		= [-6, -6, 0],
	.maxs		= [6, 6, 10],
	
	.use		= __NULL__,
	.inspect	= __NULL__,
	.pickup		= i_knife_pickup,
	.equip		= i_knife_equip,
	.drop		= i_knife_drop,
	
	.precache	= i_knife_precache,
    .wmodel     = i_knife_wmodel
};