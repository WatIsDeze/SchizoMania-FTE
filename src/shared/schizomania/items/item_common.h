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
// INVENTORY ITEM
//
// Defines the model for each item in the item "database".
//=======================
typedef struct {
    string name;            // Item name.
    string txtPickup;       // Text for display when a player picks up this item.
    string txtDrop;          // Text for display when a player drops this item.
    string txtUse;          // Text for display when a player uses this item.
    string txtDescription;   // Text for display when item is being viewed in inventory.
    float ID;               // Item ENUM inventory Index.

    void(player) use;
    void(void) precache;

    string() wmodel;        // Returns weapon model.
} inventory_item_t;