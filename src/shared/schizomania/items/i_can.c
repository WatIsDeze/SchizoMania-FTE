
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
// void i_can_precache(void)
// 
// Precache.
//=======================
void
i_can_precache(void) {
#ifdef SERVER
	Sound_Precache("item_can.use");
	precache_model("models/can.mdl");
#else
	precache_model("models/can.mdl");
#endif
}

//=======================
// void i_can_use(void)
//
// Use.
//=======================
void
i_can_use(player pl) {

}

//=======================
// string i_can_wmodel(void)
//
// Return item model string path.
//=======================
string 
i_can_wmodel(void) {
    return "models/can.mdl";
}

inventory_item_t i_can = 
{
	.name		= "Soda Can",

    .txtPickup	= "picked up a Can of Soda",
    .txtDrop	= "dropped a Can of Soda",
	.txtUse		= "drank a Can of Soda",
	.txtDescription = "A can of Soda. Its refreshing drink is capable of healing 5 points.",

	.ID			= INVENTORY_ITEM_CAN,
	.mins		= [-8,-8, 0],
	.maxs		= [8, 8, 8],

	.use		= i_can_use,
	.inspect	= __NULL__,
	.pickup		= __NULL__,
	.equip		= __NULL__,
	.drop		= __NULL__,
	
	.precache	= i_can_precache,
    .wmodel     = i_can_wmodel
};