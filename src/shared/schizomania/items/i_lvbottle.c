
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
// void i_lvbottle_precache(void)
// 
// Precache.
//=======================
void i_lvbottle_precache(void) {
#ifdef SERVER
	Sound_Precache("item_lvbottle.use");
	precache_model("models/lvbottle.mdl");
#else
	precache_model("models/lvbottle.mdl");
#endif
}

//=======================
// void i_lvbottle_use(void)
//
// Use.
//=======================
void i_lvbottle_use(void) {

}

//=======================
// string i_lvbottle_wmodel(void)
//
// Return item model string path.
//=======================
string i_lvbottle_wmodel(void) {
    return "models/lvbottle.mdl";
}

inventory_item_t i_lvbottle = 
{
	.name		= "A bottle of lv",
	.ID			= INVENTORY_ITEM_LVBOTTLE,

	.use		= i_lvbottle_use,
	.precache	= i_lvbottle_precache,
    .wmodel     = i_lvbottle_wmodel
};

/* pickups */
#ifdef SERVER
// void
// weapon_9mmhandgun(void)
// {
// 	Weapons_InitItem(WEAPON_GLOCK);
// }

// void
// weapon_glock(void)
// {
// 	Weapons_InitItem(WEAPON_GLOCK);
// }
#endif