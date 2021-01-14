
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
// void i_medkit_precache(void)
// 
// Precache.
//=======================
void i_medkit_precache(void) {
#ifdef SERVER
	Sound_Precache("items.medkit.use");
	precache_model("models/items/medkit/w_medkit.vvm");
#else
	precache_model("models/items/medkit/w_medkit.vvm");
#endif
}

//=======================
// void i_medkit_use(void)
//
// Use.
//=======================
void i_medkit_use(player pl) {
    #ifdef SERVER
        // Heal the player.
	    Damage_Apply(pl, pl, -20, 0, DMG_GENERIC);

        // Play medkit sound.
        Sound_Play(pl, CHAN_ITEM, "items.medkit.use");
    //  dprint("server - i_medkit_use");
    #endif
    // #else
    //     // Play medkit sound.
    //     Sound_Play(pl, CHAN_ITEM, "item.healthkit");
    //     dprint("client - i_medkit_use");
    // #endif
}

//=======================
// string i_medkit_wmodel(void)
//
// Return item model string path.
//=======================
string i_medkit_wmodel(void) {
    return "models/items/medkit/w_medkit.vvm";
}

inventory_item_t i_medkit = 
{
	.name		= "Medkit",

    .txtPickup	= "picked up a ^xF42Medkit",
    .txtDrop	= "dropped a ^xF42Medkit",
    .txtUse		= "used a ^xF42Medkit",
	.txtDescription = "A ^xF42Medkit,^xFFFcapable of healing 20 points on use.",

	.ID			= INVENTORY_ITEM_MEDKIT,
	.mins		= [-6,-6, 0],
	.maxs		= [6, 6, 8],

	.use		= i_medkit_use,
    .inspect	= __NULL__,
	.pickup		= __NULL__,
	.equip		= __NULL__,
	.drop		= __NULL__,
    
	.precache	= i_medkit_precache,
    .wmodel     = i_medkit_wmodel
};