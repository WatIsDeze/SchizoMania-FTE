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
static CUIPic picBackground;
static CUI3DItem itemButtons[INVENTORY_ITEM_MAX];
static int selectedItemID;

#define UI_INVENTORY_ITEM_WIDTH 96
#define UI_INVENTORY_ITEM_HEIGHT 96

// Defined here so it can be used in each VGUI_Inventory_ function.
static CUIButton btnUse;
static CUIButton btnEquip;
static CUIButton btnInspect;
static CUIButton btnDrop;
static CUIButton btnClose;

void
VGUI_Inventory_UpdateItems(void);

//=======================
// void VGUI_Inventory_Use(void)
//
// Uses the selected inventory item.
//=======================
void
VGUI_Inventory_Use()
{
	player pl = pSeat->m_ePlayer;

	if (!winInventory)
		return;

	if (!(selectedItemID >= 1 && selectedItemID < INVENTORY_ITEM_MAX))
		return;
	
	// Drop the currently selected item.
	sendevent("Useitem", "ii", (float)selectedItemID, 1);

	// This is the last item of this kind that we're dropping.
	// We want to make sure it is unselected when picking it up again.
	if (itemButtons[selectedItemID].GetItemAmount() <= 1) {
		// Remove selected flag.
		itemButtons[selectedItemID].FlagRemove(ITEM_SELECTED);
		
		// Reset selected item ID.
		selectedItemID = 0;
	}

	// Close item display.
	VGUI_Inventory_Close();
}

//=======================
// void VGUI_Inventory_Equip(void)
//
// Equips the selected inventory item.
//=======================
void
VGUI_Inventory_Equip(void)
{
	player pl = pSeat->m_ePlayer;

	if (!winInventory)
		return;

	if (!(selectedItemID >= 1 && selectedItemID < INVENTORY_ITEM_MAX))
		return;
	
	// Drop the currently selected item.
	sendevent("Equipitem", "i", (float)selectedItemID);

	// TODO: Mark as EQUIPED for rendering.
	itemButtons[selectedItemID].FlagRemove(ITEM_SELECTED);
		
	// Close item display.
	VGUI_Inventory_Close();
}

//=======================
// void VGUI_Inventory_Drop(void)
//
// Drops the selected inventory item.
//=======================
void
VGUI_Inventory_Drop(void)
{
	player pl = pSeat->m_ePlayer;

	if (!winInventory)
		return;

	if (!(selectedItemID >= 1 && selectedItemID < INVENTORY_ITEM_MAX))
		return;
	
	// Drop the currently selected item.
	sendevent("Dropitem", "ii", (float)selectedItemID, 1);

	// This is the last item of this kind that we're dropping.
	// We want to make sure it is unselected when picking it up again.
	if (itemButtons[selectedItemID].GetItemAmount() <= 1) {
		// Remove selected flag.
		itemButtons[selectedItemID].FlagRemove(ITEM_SELECTED);
		
		// Reset selected item ID.
		selectedItemID = 0;
	}

	// Close item display.
	VGUI_Inventory_Close();
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

	// Bit of a hack but whatever.. Reset button states the cheesy way. We got a game to finish!
	btnUse.m_iFlags = 0;
	btnUse.m_iFlags |= BUTTON_DISABLED | BUTTON_VISIBLE;
	btnEquip.m_iFlags = 0;
	btnEquip.m_iFlags |= BUTTON_DISABLED | BUTTON_VISIBLE;
	btnDrop.m_iFlags = 0;
	btnDrop.m_iFlags |= BUTTON_DISABLED | BUTTON_VISIBLE;
	btnClose.m_iFlags = 0;
	btnClose.m_iFlags |= BUTTON_VISIBLE;

	// Reset selected item ID.
	selectedItemID = 0;

	// Update item view.
	VGUI_Inventory_UpdateItems();

	// Hide item display.
	picBackground.FlagRemove(UI_VISIBLE);
	winInventory.Hide();
}

//=======================
// void VGUI_Inventory_ItemSelect(float itemID)
//
// Called when an item is selected.
//=======================
void
VGUI_Inventory_ItemSelect(float itemID) {
	player pl = pSeat->m_ePlayer;

	// By default, clear all flags from the buttons.
	for (int i = 1; i < INVENTORY_ITEM_MAX; i++) {
		itemButtons[i].FlagRemove(ITEM_SELECTED);
	}

	// Should we disable, or enable the use button?
	if (g_inventory_items[itemID].use == __NULL__) {
		btnUse.FlagAdd(BUTTON_DISABLED);
	} else {
		btnUse.FlagRemove(BUTTON_DISABLED);
	}

	// Should we disable, or enable the equip button?
	if (g_inventory_items[itemID].equip == __NULL__) {
		btnEquip.FlagAdd(BUTTON_DISABLED);
	} else {
		btnEquip.FlagRemove(BUTTON_DISABLED);
	}

	// Should we disable, or enable the inspect button?
	if (g_inventory_items[itemID].inspect == __NULL__) {
		btnInspect.FlagAdd(BUTTON_DISABLED);
	} else {
		btnInspect.FlagRemove(BUTTON_DISABLED);
	}

	// Should we disable, or enable the drop button?
	if (itemButtons[itemID].GetItemAmount() >= 1) {
		btnDrop.FlagRemove(BUTTON_DISABLED);
	} else {
		btnDrop.FlagAdd(BUTTON_DISABLED);
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
	player pl = pSeat->m_ePlayer;//(player)self;

	// Used for determining current button position.
	vector buttonPos = [8, 32, 0];
	int xiteration = 0;

	// Loop through all possible item ID's.
	for (int i = 1; i < INVENTORY_ITEM_MAX; i++) {
		// Make sure all item buttons are pre-spawned.
		if (!itemButtons[i]) {
			itemButtons[i] = spawn( CUI3DItem );
			itemButtons[i].FlagRemove(ITEM_VISIBLE);
			// Last but not least, add button to window.
			winInventory.Add(itemButtons[i]);
		}

		// Increment Y position after each 8 items and reset X.
		if (xiteration == 3) {
			buttonPos.y += UI_INVENTORY_ITEM_HEIGHT + 4;
			buttonPos.x = 8;
			xiteration = 0;
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

			// Next X iteration.
			xiteration += 1;
		}

		// Pass item ID and Amount.
		itemButtons[i].SetItemID(i);
		itemButtons[i].SetItemAmount(itemAmount);

		// Setup item select callback.
		itemButtons[i].SetItemSelectFunc( VGUI_Inventory_ItemSelect );

	}
}

//=======================
// void VGUI_Inventory_Precache(void)
//
// Precache bg etc.
//=======================
void
VGUI_Inventory_Precache(void) 
{
	precache_pic("textures/ui/inventory/background.tga");
}

//=======================
// void VGUI_Inventory_Show(void)
//
// Initializes inventory if needed, and shows it.
//=======================
void
VGUI_Inventory_Show(void) {
	static int initialized;

	if (!initialized) {
		initialized = TRUE;

		// Mainmenu background.
		picBackground = spawn(CUIPic);
		picBackground.SetImage("textures/ui/inventory/background.tga");
		picBackground.SetSize( '1280 768' );

		// Inventory window.
		winInventory = spawn(CUIWindow);
		winInventory.SetTitle("Inventory");
		winInventory.SetSize('440 320');
		winInventory.FlagAdd(WINDOW_NO_VISUAL | WINDOW_NO_DRAG);

		// Setup the default buttons.
		btnUse = spawn(CUIButton);
		btnUse.SetTitle("Use");
		btnUse.SetSize( '108 24' );
		btnUse.SetPos( '326 32' );
		btnUse.FlagAdd( BUTTON_DISABLED );
		btnUse.SetFunc(VGUI_Inventory_Use);

		btnEquip = spawn(CUIButton);
		btnEquip.SetTitle("Equip");
		btnEquip.SetSize( '108 24' );
		btnEquip.SetPos( '326 62' );
		btnEquip.FlagAdd( BUTTON_DISABLED );
		btnEquip.SetFunc(VGUI_Inventory_Equip);

		btnInspect = spawn(CUIButton);
		btnInspect.SetTitle("Inspect");
		btnInspect.SetSize( '108 24' );
		btnInspect.SetPos( '326 92' );
		btnInspect.FlagAdd( BUTTON_DISABLED );
		btnInspect.SetFunc(VGUI_Inventory_Drop);

		btnDrop = spawn(CUIButton);
		btnDrop.SetTitle("Drop");
		btnDrop.SetSize( '108 24' );
		btnDrop.SetPos( '326 122' );
		btnDrop.FlagAdd( BUTTON_DISABLED );
		btnDrop.SetFunc(VGUI_Inventory_Drop);

		btnClose = spawn(CUIButton);
		btnClose.SetTitle("Close");
		btnClose.SetSize( '108 24' );
		btnClose.SetPos( '326 290' );
		btnClose.SetFunc(VGUI_Inventory_Close);

		g_uiDesktop.Add(picBackground);
		g_uiDesktop.Add(winInventory);
		winInventory.Add(btnUse);
		winInventory.Add(btnEquip);
		winInventory.Add(btnInspect);
		winInventory.Add(btnDrop);
		winInventory.Add(btnClose);
	}

	VGUI_Inventory_UpdateItems();

	winInventory.SetPos((video_res / 2) - (winInventory.GetSize() / 2));
	picBackground.SetPos((video_res / 2) - (picBackground.GetSize() / 2));

	winInventory.Show();
	picBackground.FlagAdd(UI_VISIBLE);
}
