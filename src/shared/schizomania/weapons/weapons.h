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
// g_items FLAGS
// --
// Need to rename these in the future to prevent name collisions
// with the new inventory item system.
//=======================
#define ITEM_CROWBAR		0x00000001i
#define ITEM_GLOCK			0x00000002i
#define ITEM_PYTHON			0x00000004i
#define ITEM_MP5			0x00000008i
#define ITEM_CROSSBOW		0x00000010i
#define ITEM_SHOTGUN		0x00000020i
#define ITEM_RPG			0x00000040i
#define ITEM_GAUSS			0x00000080i

#define ITEM_EGON			0x00000100i
#define ITEM_HORNETGUN		0x00000200i
#define ITEM_HANDGRENADE	0x00000400i
#define ITEM_TRIPMINE		0x00000800i
#define ITEM_SATCHEL		0x00001000i
#define ITEM_SNARK			0x00002000i
#define ITEM_SUIT			0x00004000i
#define ITEM_LONGJUMP		0x00008000i

#define ITEM_UNUSED17		0x00010000i
#define ITEM_UNUSED18		0x00020000i
#define ITEM_UNUSED19		0x00040000i
#define ITEM_UNUSED20		0x00080000i
#define ITEM_UNUSED21		0x00100000i
#define ITEM_UNUSED22		0x00200000i
#define ITEM_UNUSED23		0x00400000i
#define ITEM_UNUSED24		0x00800000i

#define ITEM_UNUSED25		0x01000000i
#define ITEM_UNUSED26		0x02000000i
#define ITEM_UNUSED27		0x04000000i
#define ITEM_UNUSED28		0x08000000i
#define ITEM_UNUSED29		0x10000000i
#define ITEM_UNUSED30		0x20000000i
#define ITEM_UNUSED31		0x40000000i
#define ITEM_UNUSED32		0x80000000i

//=======================
// Weapon indices, according to weapon table.
//=======================
enum
{
	WEAPON_NONE,
	WEAPON_CROWBAR,
	WEAPON_GLOCK,
	WEAPON_PYTHON,
	WEAPON_MP5,
	WEAPON_SHOTGUN,
	WEAPON_CROSSBOW,
	WEAPON_RPG,
	WEAPON_GAUSS,
	WEAPON_EGON,
	WEAPON_HORNETGUN,
	WEAPON_HANDGRENADE,
	WEAPON_SATCHEL,
	WEAPON_TRIPMINE,
	WEAPON_SNARK
};

//=======================
// Maximum ammo for each weapon.
//=======================
#define MAX_A_9MM		250
#define MAX_A_357		36
#define MAX_A_BUCKSHOT		125
#define MAX_A_M203_GRENADE	10
#define MAX_A_BOLT		50
#define MAX_A_ROCKET		5
#define MAX_A_URANIUM		100
#define MAX_A_HANDGRENADE	10
#define MAX_A_SATCHEL		5
#define MAX_A_TRIPMINE		10
#define MAX_A_SNARK		10
#define MAX_A_HORNET		8