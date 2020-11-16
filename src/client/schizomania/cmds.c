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

//=======================
// VGUI Menu Function definitions.
//
// Placed here due to our VGUI code being included later on in progs.src
//=======================
void VGUI_Inventory_Show(void);
void VGUI_Inventory_Close(void);

//=======================
// int Game_ConsoleCommand(void)
//
// SchizoMania console command implementations.
//=======================
int
Game_ConsoleCommand(void)
{
	switch(argv(0)) {
		case "drop":
			float itemID = 0;
			float amount = 0;
			if (argv(1)) {
				itemID = stof(argv(1));
			}
			if (argv(2)) {
				amount = stof(argv(2));
			}

			sendevent("Dropitem", "ii", itemID, amount);
			break;
		case "inventory":
			VGUI_Inventory_Show();
			break;
		default:
		return FALSE;
	}
	return TRUE;
}
