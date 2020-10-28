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

/*QUAKED player_weaponstrip (1 0 0) (-8 -8 -8) (8 8 8)
"targetname"    Name

Strips the activator of all of its weapons.

Trivia:
This entity was introduced in Half-Life (1998).
*/

class player_weaponstrip:CBaseTrigger
{
	void(void) player_weaponstrip;
	virtual void(entity, int) Trigger;
};

void
player_weaponstrip::Trigger(entity act, int unused)
{
	base_player pl;

	if (!(act.flags & FL_CLIENT)) {
		return;
	}

	pl = (base_player)act;

	for (int i = 1; i < Weapon_GetCount(); i++) {
		pl.g_items &= ~Weapon_GetBitID(i);
		pl.activeweapon = 0;
		pl.a_ammo1 = 0;
		pl.a_ammo2 = 0;
		pl.a_ammo3 = 0;
	}
}

void
player_weaponstrip::player_weaponstrip(void)
{
	CBaseTrigger::CBaseTrigger();
}
