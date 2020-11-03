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
//=======================================================================//
//
// ITEM EVENT IMPLEMENTATIONS.
//
//=======================================================================//
//=======================
// void Items_Event_Pickup(void) 
//
// Parses the EV_ITEM_PICKUP message. Adds items to client inventory and
// informs the client about the picked up item.
//=======================
void Items_Event_Pickup(void) {
    // Read message values.
    int itemID = readbyte();
    int itemAmount = readbyte();

    // 
    string playerName = "Player"; //getplayerkeyvalue(fSender, "name");
    CSQC_Parse_Print(sprintf("%s picked up itemID: %i x %i", playerName, itemID, itemAmount), PRINT_CHAT);

    // Cast to player.
    player pl = (player)self;

    // Add item to the player inventory.
    pl.inventory_items[itemID] += itemAmount;

    // Ensure it is in bounds.
    pl.inventory_items[itemID] = bound(0, pl.inventory_items[itemID], 255);
    // HUD_WeaponPickupNotify(w);
}

//=======================
// void Items_Event_Drop(void) 
//
// Parses the EV_ITEM_DROP message. Removes item from the inventory
// and drops the item on the floor.
//=======================
void Items_Event_Drop(void) {
    // Read message values.
    int itemID = readbyte();
    int itemAmount = readbyte();

    // 
    string playerName = "Player"; //getplayerkeyvalue(fSender, "name");
    CSQC_Parse_Print(sprintf("%s dropped itemID: %i x %i", playerName, itemID, itemAmount), PRINT_CHAT);

    // Cast to player.
    player pl = (player)self;

    // Remove item from the player inventory.
    pl.inventory_items[itemID] -= itemAmount;

    // Ensure it is in bounds.
    pl.inventory_items[itemID] = bound(0, pl.inventory_items[itemID], 255);
}