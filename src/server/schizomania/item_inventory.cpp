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

/*QUAKED item_inventory (0 0 0.8) (-16 -16 0) (16 16 36)

SCHIZOMANIA ENTITY:

Entity for pickup items which go in the inventory.
- itemID: The item index number in the item (enum)database.
- mount:  The amount of 'itemid' items that are contained in this
          pickup.

*/
class item_inventory:CBaseEntity
{
    int m_iItemID;             			// Item ID for the game item database.
    int m_iAmount;          			// Amount to give for the game item database.
	
	void(void) item_inventory;
	virtual void(void) touch;
	virtual void(string, string) SpawnKey;

	virtual void(int) SetItem;
	virtual void(int) SetAmount;
};

//=======================
// void item_inventory::SetItem(int itemID)
//=======================
void
item_inventory::SetItem(int itemID) {
	m_iItemID = itemID;

	if (itemID == 1)
		SetModel("models/can.mdl");
	if (itemID == 2)
		SetModel("models/winebottle.mdl");
}

//=======================
// void item_inventory::SetAmount(int amount)
//=======================
void
item_inventory::SetAmount(int amount) {
	m_iAmount = amount;
}

//=======================
// void item_inventory::SpawnKey(void)
//
// Spawnkeys
// - itemID: The item index number in the item (enum)database.
// - mount:  The amount of 'itemid' items that are contained in this
//           pickup.
//=======================
void
item_inventory::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "itemID":
		m_iItemID = stoi(strValue);
		break;
	case "amount":
		m_iAmount = stoi(strValue);
		break;
	default:
		CBaseEntity::SpawnKey(strKey, strValue);
	}
}

//=======================
// void item_inventory::touch(void)
//
// Executed only if touched by a player, returns otherwise.
//
// Plays a pickup sound, logs the pickup event and sends a pickup event
// off to the client.
//=======================
void item_inventory::touch(void)
{
	// Determine whether it is a player, AI etc don't interact with these.
	if (other.classname != "player") {
		return;
	}

	// In case the itemID or amount is invalid, debug this.
	if (m_iItemID < 0 || m_iItemID > 255) {
		dprint(sprintf("Invalid itemID: %i - Should be between 0 to 256", m_iItemID));
		return;
	}
	if (m_iAmount < 0 || m_iAmount > 255) {
		dprint(sprintf("Invalid m_iAmount: %i - Should be between 0 to 256", m_iAmount));
		return;
	}

	// Cast to player.
	player pl = (player)other;

	// Add item to the player inventory.
	pl.inventory_items[m_iItemID] += m_iAmount;
	if (pl.inventory_items[m_iItemID] < 0)
		pl.inventory_items[m_iItemID] = 0;
	if (pl.inventory_items[m_iItemID] > 255)
		pl.inventory_items[m_iItemID] = 255;

	// Player pickup sound and log.
	Logging_Pickup(other, this, __NULL__);
	sound(pl, CHAN_ITEM, "items/gunpickup2.wav", 1, ATTN_NORM);
	
	// Write out EV_ITEM_PICKUP event.
	WriteByte(MSG_MULTICAST, SVC_CGAMEPACKET);
	WriteByte(MSG_MULTICAST, EV_ITEM_PICKUP);
	WriteByte(MSG_MULTICAST, m_iItemID);
	WriteByte(MSG_MULTICAST, m_iAmount);
	msg_entity = other;

	// Multicast it.
	multicast([0,0,0], MSG_MULTICAST);

	// Remove from world, we don't want to pick it up twice.
	remove(this);
}

//=======================
// void item_inventory::item_inventory(void)
//
// Constructor.
//=======================
void item_inventory::item_inventory(void)
{
	// Setup base itemID and amount.
	m_iItemID = 1;
	m_iAmount = 1;

	//SetModel(model);
	SetSize([-16,-16,0], [16,16,16]);
	SetSolid(SOLID_TRIGGER);
	SetMovetype(MOVETYPE_TOSS);

	// Place in Precache function?
	// precache_model("models/can.mdl");
	// precache_model("model/winebottle.mdl");
	// Sound_Precache("item.pickup");
	// Sound_Precache("item.drop");
}