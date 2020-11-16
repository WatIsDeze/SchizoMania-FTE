
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
	.description = "A sharp hunting knife, good for combat.",
	.ID			= INVENTORY_ITEM_KNIFE,

	.use		= i_knife_use,
	.precache	= i_knife_precache,
    .wmodel     = i_knife_wmodel
};