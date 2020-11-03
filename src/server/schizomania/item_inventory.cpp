/*
 * Copyright (c) 2016-2020 Marco Hladik <marco@icculus.org>
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


*/
class item_inventory:CBaseEntity
{
    int m_iItemID;             				// Item ID for the game item database.
    int m_iItemAmount;          			// Amount to give for the game item database.
	void(void) item_inventory;
	virtual void(void) touch;
	virtual void(string, string) SpawnKey;
};

//=======================
// void item_inventory::SpawnKey(void)
//
// Spawnkeys
// - itemid: The item index number in the item (enum)database.
// - itemamount: The amount of 'itemid' items that are contained in this
//               pickup.
//=======================
void
item_inventory::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "itemid":
		m_iItemID = stoi(strValue);
		break;
	case "itemamount":
		m_iItemAmount = stoi(strValue);
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
	if (other.classname != "player") {
		return;
	}


	player pl = (player)other;

	// Player pickup sound and log.
	Logging_Pickup(other, this, __NULL__);
	sound(pl, CHAN_ITEM, "items/gunpickup2.wav", 1, ATTN_NORM);
	
	dprint(sprintf("%i", m_iItemID));

	// Write out EV_ITEM_PICKUP bytes.
	WriteByte(MSG_MULTICAST, SVC_CGAMEPACKET);
	WriteByte(MSG_MULTICAST, EV_ITEM_PICKUP);
	WriteByte(MSG_MULTICAST, m_iItemID);
	WriteByte(MSG_MULTICAST, m_iItemAmount);
	msg_entity = this;

	// Multicast it.
	multicast([0,0,0], MSG_MULTICAST);
	
	// WriteString(MSG_MULTICAST, strMessage);
	

	// if (iFlags & EHH_ALLPLAYERS)
	// 	multicast([0,0,0], MULTICAST_ALL);
	// else
	// 	multicast([0,0,0], MULTICAST_ONE_R);
	// pl.ammo_9mm += ammo_9mm;
	// pl.g_items |= weapon_items;
	// Weapons_RefreshAmmo(pl);
	//sendevent("Item_Pickup", "i", m_iItemID);

	remove(this);
}

//=======================
// void item_inventory::item_inventory(void)
//
// Constructor.
//=======================
void item_inventory::item_inventory(void)
{
	//SetModel(model);
	SetSize([-16,-16,0], [16,16,16]);
	SetSolid(SOLID_TRIGGER);
	SetMovetype(MOVETYPE_TOSS);
}