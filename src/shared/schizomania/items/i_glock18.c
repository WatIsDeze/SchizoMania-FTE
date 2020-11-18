
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
	Sound_Precache("item_glock.use");
	precache_model("models/w_glock18.mdl");
#else
	precache_model("models/w_glock18.mdl");
#endif
}

//=======================
// void i_glock18_use(void)
//
// Use.
//=======================
void i_glock18_use(player pl) {

}

//=======================
// string i_glock18_wmodel(void)
//
// Return item model string path.
//=======================
string i_glock18_wmodel(void) {
    return "models/w_glock18.mdl";
}

inventory_item_t i_glock18 = 
{
	.name		= "Glock 18",

    .txtPickup	= "picked up a Glock 18",
	.txtDrop	= "dropped a Glock 18",
    .txtUse		= "used a Glock 18",
	.txtDescription = "The Glock 18 is a powerful tool in combat.",

	.ID			= INVENTORY_ITEM_GLOCK,

	.use		= i_glock18_use,
	.precache	= i_glock18_precache,
    .wmodel     = i_glock18_wmodel
};