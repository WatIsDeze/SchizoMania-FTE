
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
// string i_can_wmodel(void)
//
// Return item model string path.
//=======================
string 
i_null_wmodel(void) {
    return "";
}

inventory_item_t i_null = 
{
	.name		= "NULL ITEM",
    
	.txtPickup	= "picked up a ^xF42NULL ITEM",
    .txtUse		= "used a ^xF42NULL ITEM",       
	.txtDrop	= "dropped a ^xF42NULL ITEM",
	.txtDescription = "^xF42NULL ITEM",

	.ID			= INVENTORY_ITEM_NULL,
	.mins		= [-8,-8, 0],
	.maxs		= [8, 8, 8],
	
	.use		= __NULL__,
	.pickup		= __NULL__,
	.equip		= __NULL__,
	.drop		= __NULL__,
	
	.precache	= __NULL__,
    .wmodel     = i_null_wmodel
};
