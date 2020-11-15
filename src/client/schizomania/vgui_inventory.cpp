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

#define UI_INVENTORY_ITEM_WIDTH 96
#define UI_INVENTORY_ITEM_HEIGHT 96

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
	if (!winInventory)
		return;

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

// entity eModel;
// void
// UI_ItemButton_Draw(void) 
// {
// 	vector vecDistance = [90, 0, 0];
// 	CUI3DView v = (CUI3DView)self;
// 		static int initialized = FALSE;
// 		if ( !initialized ) {
// 			initialized = TRUE;
// 			eModel = spawn();
// 			setmodel(eModel, "models/player.mdl" );
// 			AngleVectors( v.Get3DAngles() );
// 			v.Set3DPos( v_forward * -vecDistance[0] + v_right * vecDistance[1] + v_up * vecDistance[2] );
// 		}
// 		addentity( eModel );
// 		eModel.frame1time += frametime;
// }
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
	vector buttonPos = [4, 32, 0];

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

		itemButtons[i].SetPos(buttonPos);
		itemButtons[i].SetSize( [UI_INVENTORY_ITEM_WIDTH, UI_INVENTORY_ITEM_HEIGHT]);
		itemButtons[i].SetItemID(i);
		itemButtons[i].SetItemAmount(pl.inventory_items[i]);

		// Increment X by 32.
		buttonPos.x += UI_INVENTORY_ITEM_WIDTH + 4;
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
		winInventory.SetSize('420 320');

		// Setup the default buttons.
		btnUse = spawn(CUIButton);
		btnUse.SetTitle("Use");
		btnUse.SetSize( '108 24' );
		btnUse.SetPos( '306 32' );
		btnUse.SetFunc(VGUI_Inventory_Use);

		btnEquip = spawn(CUIButton);
		btnEquip.SetTitle("Equip");
		btnEquip.SetSize( '108 24' );
		btnEquip.SetPos( '306 62' );
		btnEquip.SetFunc(VGUI_Inventory_Equip);

		btnDrop = spawn(CUIButton);
		btnDrop.SetTitle("Drop");
		btnDrop.SetSize( '108 24' );
		btnDrop.SetPos( '306 92' );
		btnDrop.SetFunc(VGUI_Inventory_Drop);

		btnClose = spawn(CUIButton);
		btnClose.SetTitle("Close");
		btnClose.SetSize( '108 24' );
		btnClose.SetPos( '306 290' );
		btnClose.SetFunc(VGUI_Inventory_Close);

		g_uiDesktop.Add(winInventory);
		winInventory.Add(btnUse);
		winInventory.Add(btnEquip);
		winInventory.Add(btnDrop);
		winInventory.Add(btnClose);

		VGUI_Inventory_UpdateItems();
	}

	winInventory.Show();
	winInventory.SetPos((video_res / 2) - (winInventory.GetSize() / 2));
}
