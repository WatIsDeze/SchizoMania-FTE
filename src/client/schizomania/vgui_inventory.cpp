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

static CUIWindow winInventory;
static CUI3DItem itemButtons[INVENTORY_ITEM_MAX];
static int selectedItemID;

#define UI_INVENTORY_ITEM_WIDTH 96
#define UI_INVENTORY_ITEM_HEIGHT 96

// Defined here so it can be used in each VGUI_Inventory_ function.
void
VGUI_Inventory_UpdateItems(void);

//=======================
// void VGUI_Inventory_Use(void)
//
// Uses the selected inventory item.
//=======================
void
VGUI_Inventory_Use(void)
{
	if (!winInventory)
		return;

	// TODO: Implement.
	winInventory.Hide();
}

//=======================
// void VGUI_Inventory_Equip(void)
//
// Equips the selected inventory item.
//=======================
void
VGUI_Inventory_Equip(void)
{
	if (!winInventory)
		return;

	// TODO: Implement.
	winInventory.Hide();
}

//=======================
// void VGUI_Inventory_Drop(void)
//
// Drops the selected inventory item.
//=======================
void
VGUI_Inventory_Drop(void)
{
	player pl = (player)self;

	if (!winInventory)
		return;

	dprint(sprintf("SELECTED ID = %i, %f", selectedItemID, (float)pl.inventory_items[selectedItemID]));
	
	if (!(selectedItemID >= 1 && selectedItemID < INVENTORY_ITEM_MAX))
		return;
	
	// Drop the currently selected item.
	sendevent("Dropitem", "ii", (float)selectedItemID, 1);

	// Update item view.
	VGUI_Inventory_UpdateItems();

	// TODO: Implement.
	winInventory.Hide();
}

//=======================
// void VGUI_Inventory_Close(void)
//
// Closes the inventory, nothing special.
//=======================
void
VGUI_Inventory_Close(void)
{
	if (!winInventory)
		return;

	winInventory.Hide();
}

//=======================
// void VGUI_Inventory_ItemSelect(float itemID)
//
// Called when an item is selected.
//=======================
void
VGUI_Inventory_ItemSelect(float itemID) {
	// By default, clear all flags from the buttons.
	for (int i = 1; i < INVENTORY_ITEM_MAX; i++) {
		itemButtons[i].FlagRemove(ITEM_SELECTED);
	}

	// Store selected itemID.
	selectedItemID = (int)itemID;
}

//=======================
// void VGUI_Inventory_UpdateItems(void)
//
// Initializes inventory item list if needed, and updates it.
//=======================
void
VGUI_Inventory_UpdateItems(void)
{
	player pl = (player)self;

	// Used for determining current button position.
	vector buttonPos = [8, 32, 0];

	// Loop through all possible item ID's.
	for (int i = 1; i < INVENTORY_ITEM_MAX; i++) {
		// Increment Y position after each 8 items.
		if (i % 8)
			buttonPos.y += UI_INVENTORY_ITEM_HEIGHT + 4;

		// Spawn the item button in case it didn't exist yet.
		if (!itemButtons[i]) {
			itemButtons[i] = spawn( CUI3DItem );

			// Last but not least, add button to window.
			winInventory.Add(itemButtons[i]);
		}

		// Position button accordingly.
		itemButtons[i].SetPos(buttonPos);
		itemButtons[i].SetSize( [UI_INVENTORY_ITEM_WIDTH, UI_INVENTORY_ITEM_HEIGHT]);
		
		// Setup 3D view properties.
		itemButtons[i].Set3DAngles([35, 0, 0]);

		// Determine whether this button should be visible or not. (In case of 0 items)
		int itemAmount = pl.inventory_items[i];

		if (itemAmount <= 0) {
			itemButtons[i].FlagRemove(ITEM_VISIBLE);
		} else {
			itemButtons[i].FlagAdd(ITEM_VISIBLE);
			
			// Only Increment X by width define in case this button was visible.
			buttonPos.x += UI_INVENTORY_ITEM_WIDTH + 4;
		}

		// Pass item ID and Amount.
		itemButtons[i].SetItemID(i);
		itemButtons[i].SetItemAmount(itemAmount);

		// Setup item select callback.
		itemButtons[i].SetItemSelectFunc( VGUI_Inventory_ItemSelect );
	}
}

//=======================
// void VGUI_Inventory_Show(void)
//
// Initializes inventory if needed, and shows it.
//=======================
void
VGUI_Inventory_Show(void) {
	static int initialized;
	static CUIButton btnUse;
	static CUIButton btnEquip;
	static CUIButton btnDrop;
	static CUIButton btnClose;

	if (!initialized) {
		initialized = TRUE;
		winInventory = spawn(CUIWindow);
		winInventory.SetTitle("Inventory");
		winInventory.SetSize('440 320');

		// Setup the default buttons.
		btnUse = spawn(CUIButton);
		btnUse.SetTitle("Use");
		btnUse.SetSize( '108 24' );
		btnUse.SetPos( '326 32' );
		btnUse.SetFunc(VGUI_Inventory_Use);

		btnEquip = spawn(CUIButton);
		btnEquip.SetTitle("Equip");
		btnEquip.SetSize( '108 24' );
		btnEquip.SetPos( '326 62' );
		btnEquip.SetFunc(VGUI_Inventory_Equip);

		btnDrop = spawn(CUIButton);
		btnDrop.SetTitle("Drop");
		btnDrop.SetSize( '108 24' );
		btnDrop.SetPos( '326 92' );
		btnDrop.SetFunc(VGUI_Inventory_Drop);

		btnClose = spawn(CUIButton);
		btnClose.SetTitle("Close");
		btnClose.SetSize( '108 24' );
		btnClose.SetPos( '326 290' );
		btnClose.SetFunc(VGUI_Inventory_Close);

		g_uiDesktop.Add(winInventory);
		winInventory.Add(btnUse);
		winInventory.Add(btnEquip);
		winInventory.Add(btnDrop);
		winInventory.Add(btnClose);
	}

	VGUI_Inventory_UpdateItems();

	winInventory.Show();
	winInventory.SetPos((video_res / 2) - (winInventory.GetSize() / 2));
}
