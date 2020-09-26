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

/*QUAKED egui_mainmenu (0 0 0.8) (-16 -16 0) (16 16 36)

SCHIZOMANIA ENTITY

Used to trigger mainmenu mode when placed in a map.
Use in combination with info_intermission.

*/
class egui_mainmenu:CBaseEntity
{
	void(void) egui_mainmenu;
	virtual void(void) Respawn;
};

void egui_mainmenu::Respawn(void)
{
	think = __NULL__;
	nextthink = -1;
}

void egui_mainmenu::egui_mainmenu(void)
{
	CBaseEntity::CBaseEntity();
	egui_mainmenu::Respawn();
}