
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
// void i_winebottle_precache(void)
// 
// Precache.
//=======================
void i_winebottle_precache(void) {
#ifdef SERVER
	Sound_Precache("item_winebottle.use");
	precache_model("models/winebottle.mdl");
#else
	precache_model("models/winebottle.mdl");
#endif
}

//=======================
// void i_winebottle_use(void)
//
// Use.
//=======================
void i_winebottle_use(void) {

}

//=======================
// string i_winebottle_wmodel(void)
//
// Return item model string path.
//=======================
string i_winebottle_wmodel(void) {
    return "models/winebottle.mdl";
}

inventory_item_t i_winebottle = 
{
	.name		= "Wine Bottle",
	.description = "An old sweet red wine.",
	.ID			= INVENTORY_ITEM_WINEBOTTLE,

	.use		= i_winebottle_use,
	.precache	= i_winebottle_precache,
    .wmodel     = i_winebottle_wmodel
};