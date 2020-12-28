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

/*QUAKED solid_bsp_test (0 0 0.8) (-16 -16 0) (16 16 36)

SCHIZOMANIA ENTITY:

Entity for pickup items which go in the inventory.
- target: Triggered when picked up.
- killtarget: Kills the target entity when picked up. 
- itemID: The item index number in the item (enum)database.
- amount: The amount of 'itemid' items that are contained in this
          pickup.

*/
class solid_bsp_test:CBaseEntity
{
	void(void) solid_bsp_test;
	virtual void(void) Respawn;
	virtual void(void) OnPlayerUse;
	virtual void(string, string) SpawnKey;
};

//=======================
// void SpawnKey(void)
//
// Spawnkeys
// - itemID: The item index number in the item (enum)database.
// - mount:  The amount of 'itemid' items that are contained in this
//           pickup.
//=======================
void solid_bsp_test::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	default:
		CBaseEntity::SpawnKey(strKey, strValue);
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
void solid_bsp_test::OnPlayerUse(void)
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

    // Let us know something.
    dprint("I am triggered by %s", pl.classname);
	
	// Remove from world, we don't want to pick it up twice.
//	remove(this);
}

//=======================
// void Respawn(void)
//
// Respawn.
//=======================
void solid_bsp_test::Respawn(void) {
	CBaseEntity::Respawn();

	// Set defaults.
	SetModel(model);
//	SetGFlags(gflags | GF_HOVER_FULLBRIGHT);
	// SetSize(g_inventory_items[m_iItemID].mins, g_inventory_items[m_iItemID].maxs);
	SetSolid(SOLID_SLIDEBOX);
	SetMovetype(MOVETYPE_PUSH);
//	droptofloor();

	// Set PlayerUse
	PlayerUse = OnPlayerUse;
}

//=======================
// void item_inventory(void)
//
// Constructor.
//=======================
void solid_bsp_test::solid_bsp_test(void)
{	
    precache_model(model);
	// Call Super class constructor. 
	CBaseEntity::CBaseEntity();
	classname = "item_inventory";
	
	// Respawn.
	Respawn();
}

CLASSEXPORT(solid_bsp_test, solid_bsp_test)