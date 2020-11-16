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
// void Item_Use(base_player pl, int itemID, int amount)
//
// Uses the amount of items on the given player.
//=======================
void
Item_Use(player pl, int itemID, int amount)
{
	// Ensure ItemID is valid and amount are in bounds.
	if (itemID <= 0 || itemID >= INVENTORY_ITEM_MAX) {
		// Debug print.
		dprint(sprintf("Tried to drop invalid itemID: %i", itemID));
		return;
	}

	itemID = bound(0, itemID, INVENTORY_ITEM_MAX - 1);
	amount = bound(0, amount, 255);

	// Loop for amount of items.
	for (int i = 0; i < amount; i++) {
		// Use. (We shouldn't be in this situation if one can't use an item
		//       th UI should prevent ths to begn with.)
		if (g_inventory_items[itemID].use != __NULL__) {
			g_inventory_items[itemID].use(pl);

			// Decrement.
		    pl.inventory_items[itemID] = bound(0, pl.inventory_items[itemID] - 1, 255);
		} else {
			dprint(sprintf("ItemID %i is lacking a use functon.", itemID));
		}
	}

	// Spawn dropable.
	item_inventory drop = spawn(item_inventory);
	drop.classname = "item_inventory";
	drop.SetItem(itemID);
	drop.SetAmount(amount);
	drop.SetSize([-8,-8,0], [8,8,16]);
	drop.SetGFlags(GF_HOVER_FULLBRIGHT);
	setorigin(drop, pl.origin);
	drop.nextthink = time + 1.5f;	

	makevectors(pl.v_angle);
	drop.velocity = v_forward * 256;
	drop.avelocity[1] = 500;
	
	// Write out EV_ITEM_DROP event.
	WriteByte(MSG_MULTICAST, SVC_CGAMEPACKET);
	WriteByte(MSG_MULTICAST, EV_ITEM_DROP);
	WriteByte(MSG_MULTICAST, itemID);
	WriteByte(MSG_MULTICAST, amount);
	msg_entity = pl;

	// Multicast it.
	multicast([0,0,0], MULTICAST_ONE_R);
}

//=======================
// void CSEv_Useitem_ii(float itemID, float amount)
//
// Use item event implementation.
//=======================
void
CSEv_Useitem_ii(float itemID, float amount)
{
	player pl = (player)self;
	Item_Use(pl, itemID, amount);
}

//=======================
// void Item_Drop(base_player pl, int itemID, int amount)
//
// Spawns an item_inventory with a MOVETYPE_TOSS which can be picked up
// again later on.
//=======================
void
Item_Drop(player pl, int itemID, int amount)
{
	static void DropItem_Enable(void)
	{
		// CBaseEntity item = CBaseEntity(self);

		// item.SetSolid(SOLID_CORPSE);
	}

	// Ensure ItemID is valid and amount are in bounds.
	if (itemID <= 0 || itemID >= INVENTORY_ITEM_MAX) {
		// Debug print.
		dprint(sprintf("Tried to drop invalid itemID: %i", itemID));
		return;
	}

	itemID = bound(0, itemID, INVENTORY_ITEM_MAX - 1);
	amount = bound(0, amount, 255);

	// Enssure the player has enough of these items.
	if (pl.inventory_items[itemID] <= 0) {
		dprint(sprintf("Player tried to drop itemID: %i, but doesn't have this item", itemID));
		return;
	}

    // Remove item from the player inventory.
    pl.inventory_items[itemID] = bound(0, pl.inventory_items[itemID] - amount, 255);

	// Spawn dropable.
	item_inventory drop = spawn(item_inventory);
	drop.classname = "item_inventory";
	drop.SetItem(itemID);
	drop.SetAmount(amount);
	drop.SetSize([-8,-8,0], [8,8,16]);
	drop.SetGFlags(GF_HOVER_FULLBRIGHT);
	setorigin(drop, pl.origin);
	// drop.SetSolid(SOLID_NOT);
	drop.think = DropItem_Enable;
	drop.nextthink = time + 1.5f;
	drop.movetype = MOVETYPE_TOSS;

	makevectors(pl.v_angle);
	drop.velocity = v_forward * 256;
	drop.avelocity[1] = 500;
	
	// Write out EV_ITEM_DROP event.
	WriteByte(MSG_MULTICAST, SVC_CGAMEPACKET);
	WriteByte(MSG_MULTICAST, EV_ITEM_DROP);
	WriteByte(MSG_MULTICAST, itemID);
	WriteByte(MSG_MULTICAST, amount);
	msg_entity = pl;

	// Multicast it.
	multicast([0,0,0], MULTICAST_ONE_R);
}

//=======================
// void CSEv_Dropitem_ii(float itemID, float amount)
//
// Dropitem event implementation.
//=======================
void
CSEv_Dropitem_ii(float itemID, float amount)
{
	player pl = (player)self;
	Item_Drop(pl, itemID, amount);
}