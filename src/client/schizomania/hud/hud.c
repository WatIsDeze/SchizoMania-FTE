
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
void HUD_DrawWeaponSelect(void);

#define SCMA_CROSS_COLOR [1,0,0]
#define SCMA_CROSS_ALPHA 0.8f

//=========================================================================
// void HUD_Init(void)
//
// Precaches, and general initialization of subsystems.
//=========================================================================
void
HUD_Init(void)
{
	// FONT_HUD_MESSAGE = loadfont("font", "", "18", -1);
	// FONT_HUD_NOTIFICATION = loadfont("font", "", "16", -1);
	// FONT_HUD_CROSSHAIRINFO = loadfont("font", "", "14", -1);
    
	FONT_HUD_MESSAGE = loadfont("", "gfx/shell/lunchds.ttf", "18 outline=2", -1, 0, 0);
	FONT_HUD_NOTIFICATION = loadfont("", "gfx/shell/lunchds.ttf", "18 outline=2", -1, 0, 0);
	FONT_HUD_CROSSHAIRINFO = loadfont("", "gfx/shell/lunchds.ttf?outline=1", "17 outline=2", -1, 0, 0);
    

    // Initialize notification list.
    HUDNotification_Init();
}

//=========================================================================
// void HUD_Flashlight_Draw(void)
//
// A temporary, very simple, and slightly messy function.
//=========================================================================
void
HUD_Flashlight_Draw(void) {
	// Fetch player.
	player pl = (player)pSeat->m_ePlayer;

	// Ensure it ain't world or __NULL__
	if (pl == world || pl == __NULL__) 
		return;
	
	// Cast to int, so it's neatly rounded for sprintf.
	int battery = pl.flashlight_battery;

	// Generate the display string.
	string strBatteryLife = strcat(sprintf("Flashlight: %i", battery), "%");

	// Last but not least, calculate its width and position.
	int strWidth = stringwidth(strBatteryLife, TRUE, [20, 20]);
	vector pos;
	pos[0] = g_hudmins[0] + (g_hudres[0]) - (strWidth + 20);
	pos[1] = 20;

	// Render time!
	drawfont = FONT_HUD_MESSAGE;
	drawstring(pos, strBatteryLife, '20 20', [1, 1, 1], 0.75, DRAWFLAG_ADDITIVE);
	drawfont = FONT_CON;
}

//=========================================================================
// HUD_DrawUseableCrosshair
//
// Draws the "focus is on a useable" object crosshair. This will inform
// the player of the fact that this object can be interacted with.
//=========================================================================
void
HUD_DrawUseableCrosshair(void)
{

}

//=========================================================================
// HUD_DrawDefaultCrosshair
//
// Draws the default crosshair seen when no weapon is equiped, and on is
// wondering around. Searching the area for whichever quest he is on.
//=========================================================================
void
HUD_DrawDefaultCrosshair(void)
{

	// Static scale variable, for hovering effect.
	static float scale = 2;

	// Are we focussing?
	int hasFocusOnUseable = pSeat->m_iHasFocusOnUseable;

	// Default line and text pos setup. (Center of screen, in accordance to hud scale.)
	vector vert1, vert2, hori1, hori2, text1;
	vert1 = vert2 = hori1 = hori2 = text1 = g_hudmins + (g_hudres / 2);

	// Default line sizes.
	float line_length = 10;
	float line_half_length = line_length / 2;

	// Let it increment in size, back and forth.
	if (hasFocusOnUseable) {
		// Accum.
		scale -= clframetime;

		if (scale < 1) {
			scale = 2;
		}

		// Adjust.
		line_length *= scale;
		line_half_length = line_length / 2;
	} else {
		line_length = 10;
		line_half_length = line_length / 2;
	}

	// Left line.
	vert1[0] -= line_half_length;
	vert1[1] -= line_half_length;

	// Right line.
	vert2[0] += line_half_length;	
	vert2[1] -= line_half_length;

	// Top line.
	hori1[0] -= line_half_length;
	hori1[1] -= line_half_length;

	// Bottom line.
	hori2[0] -= line_half_length;
	hori2[1] += line_half_length;

	// Draw them.
	drawfill(vert1, [1, line_length], SCMA_CROSS_COLOR, SCMA_CROSS_ALPHA, DRAWFLAG_ADDITIVE);
	drawfill(vert2, [1, line_length], SCMA_CROSS_COLOR, SCMA_CROSS_ALPHA, DRAWFLAG_ADDITIVE);
	drawfill(hori1, [line_length, 1], SCMA_CROSS_COLOR, SCMA_CROSS_ALPHA, DRAWFLAG_ADDITIVE);
	drawfill(hori2, [line_length + 1, 1], SCMA_CROSS_COLOR, SCMA_CROSS_ALPHA, DRAWFLAG_ADDITIVE);

	// Last but not least, draw a given string to the screen right below
	// the cursor in case we're focussing on an object.
	if (hasFocusOnUseable) {
		string strFocus = "press ^xF42\"E\"^xFFF to pick up";
		//string strFocusSizeStr = "Press \"E\" to pick up";
		int strWidth = stringwidth(strFocus, TRUE, [14, 14]);

		// Calculate position.
		vector pos = text1;
		pos.x -= strWidth / 2;
		pos.y += 22;

		// Render time!
		drawfont = FONT_HUD_CROSSHAIRINFO;
		drawstring(pos, strFocus, '14 14', [1, 1, 1], 1.0, DRAWFLAG_NORMAL);
		drawfont = FONT_CON;
	}
}

//=========================================================================
// HUD_DrawCrosshairs
//
// Takes care of drawing the appropriate crosshair.
//
// When focus is on a usable object, the weapon crosshair will disappear
// and make room for the "use" crosshair.
//
// When no weapon is equiped, it'll show a nice crosshair that can be used
// when "investigating" the environment.
//=========================================================================
void
HUD_DrawCrosshairs(void)
{
	// We need to know what we're in for.
	int hasFocusOnUseable = pSeat->m_iHasFocusOnUseable;
	
	// Are we focussing on an object?
	//if (hasFocusOnUseable) {
	//	HUD_DrawUseableCrosshair();
	//} else {
		HUD_DrawDefaultCrosshair();
	//}
	// Draw weapon crosshair.
//	SCMA_DrawGunCrosshair();
}

/* main entry */
void
HUD_Draw(void)
{
	// Unused var atm.
	//player pl = (player)pSeat->m_ePlayer;

	// Draw the notifications. (Item pickup messages, etc)
    HUDNotification_Draw();

	// Draw messages after notifications. (These are actual dialogues in-game)
    HUDMessage_Draw();

	// The flashlight Hud thing... Not needed atm.
//	HUD_Flashlight_Draw();

	// /* little point in not drawing these, even if you don't have a suit */
	HUD_DrawCrosshairs();

	// Draw damage indicators last.
	Damage_Draw();

	// This is there for developer purposes. Waypoint system depends on it.
	Textmenu_Draw();
}

/* specatator main entry */
void
HUD_DrawSpectator(void)
{
	// FIXME
	Textmenu_Draw();

}
