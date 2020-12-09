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
- target: Triggered when picked up.
- killtarget: Kills the target entity when picked up. [TODO: Implement]
- itemID: The item index number in the item (enum)database.
- amount: The amount of 'itemid' items that are contained in this
          pickup.

*/
class item_inventory:CGameEntity
{
    int m_iItemID;             			// Item ID for the game item database.
    int m_iAmount;          			// Amount to give for the game item database.
	
	string m_strTarget;					// Targetname of the entity to trigger when item is picked up.
	string m_strKillTarget;				// Targetname of the entity to kill when triggered.
	void(void) item_inventory;
	virtual void(void) Respawn;
	virtual void(void) OnPlayerUse;
	virtual void(string, string) SpawnKey;

	virtual void(int) SetItem;
	virtual void(int) SetAmount;
};

// Predefined.
void Item_Pickup(player pl, int itemID, int amount);

//=======================
// void SetItem(int itemID)
//=======================
void item_inventory::SetItem(int itemID) {
	// Ensure it is in bounds.
	m_iItemID = bound(0, itemID, INVENTORY_ITEM_MAX - 1);

	// Update model.
	SetModel(g_inventory_items[itemID].wmodel());
}

//=======================
// void SetAmount(int amount)
//=======================
void item_inventory::SetAmount(int amount) {
	// Ensure it is in bounds.
	m_iAmount = bound(0, amount, 255);
}

//=======================
// void SpawnKey(void)
//
// Spawnkeys
// - itemID: The item index number in the item (enum)database.
// - mount:  The amount of 'itemid' items that are contained in this
//           pickup.
//=======================
void item_inventory::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "itemID":
		m_iItemID = stoi(strValue);
		break;
	case "amount":
		m_iAmount = stoi(strValue);
		break;
	default:
		CGameEntity::SpawnKey(strKey, strValue);
	}
}

//=======================
// void OnPlayerUse(void)
//
// Executed only if used by a player, returns otherwise.
//
// Plays a pickup sound, logs the pickup event and sends a pickup event
// off to the client.
//=======================
void item_inventory::OnPlayerUse(void)
{
	// Determine whether it is a player, AI etc don't interact with these.
	if (eActivator.classname != "player") {
	  	return;
	}

	// Ensure the player is alive.
	if (eActivator.health <= 0) {
		return;
	}

	// Cast to player.
	player pl = (player)eActivator;

	Item_Pickup(pl, m_iItemID, m_iAmount);

	// Remove from world, we don't want to pick it up twice.
	remove(this);
}

//=======================
// void Respawn(void)
//
// Respawn.
//=======================
void item_inventory::Respawn(void) {
	// Ensure item ID is in bounds.
	m_iItemID = bound(0, m_iItemID, INVENTORY_ITEM_MAX - 1);

	// Set defaults.
	SetModel(g_inventory_items[m_iItemID].wmodel());
	SetGFlags(gflags | GF_HOVER_FULLBRIGHT);
	SetSize(g_inventory_items[m_iItemID].mins, g_inventory_items[m_iItemID].maxs);
	SetSolid(SOLID_CORPSE);
	SetMovetype(MOVETYPE_TOSS);

	// Set PlayerUse
	PlayerUse = OnPlayerUse;
}

//=======================
// void item_inventory(void)
//
// Constructor.
//=======================
void item_inventory::item_inventory(void)
{	
	// Call Super class constructor. 
	CGameEntity::CGameEntity();
	classname = "item_inventory";
	
	// Respawn.
	Respawn();
}