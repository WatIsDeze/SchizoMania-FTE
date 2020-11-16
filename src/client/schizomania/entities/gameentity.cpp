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

//=========================================================================
// Game entity client class. Handles networking for gflags and flags
// accordingly
//
// Any game entity should be derived from this class.
//=========================================================================
class CGameEntity:CBaseEntity
{
	void(void) CGameEntity;
	virtual void(void) Respawn;
	virtual void(string strKey, string strValue) SpawnKey;
	virtual void(float flChanged) ReceiveEntity;
};

//=======================
// void CGameEntity::Respawn(void)
//
// Read gflags and flags.
//=======================
void CGameEntity::ReceiveEntity(float flChanged) {
    if (flChanged & BASEFL_CHANGED_ORIGIN) {
		origin[0] = readcoord();
		origin[1] = readcoord();
		origin[2] = readcoord();
	}
	if (flChanged & BASEFL_CHANGED_ANGLES) {
		angles[0] = readfloat();
		angles[1] = readfloat();
		angles[2] = readfloat();
	}
	if (flChanged & BASEFL_CHANGED_MODELINDEX) {
		modelindex = readshort();
	}
	if (flChanged & BASEFL_CHANGED_SOLID) {
		solid = readbyte();
	}
	if (flChanged & BASEFL_CHANGED_MOVETYPE) {
		movetype = readbyte();

		if (movetype == MOVETYPE_PHYSICS) {
			movetype = MOVETYPE_NONE;
		}
	}
	if (flChanged & BASEFL_CHANGED_SIZE) {
		mins[0] = readcoord();
		mins[1] = readcoord();
		mins[2] = readcoord();
		maxs[0] = readcoord();
		maxs[1] = readcoord();
		maxs[2] = readcoord();
	}
	if (flChanged & BASEFL_CHANGED_FRAME) {
		frame1time = 0.0;
		frame2time = 0.0f;
		frame = readbyte();
	}
	if (flChanged & BASEFL_CHANGED_SKIN) {
		skin = readbyte() - 128;
	}
	if (flChanged & BASEFL_CHANGED_EFFECTS) {
		effects = readfloat();
	}
	if (flChanged & BASEFL_CHANGED_BODY) {
		m_iBody = readbyte();
		setcustomskin(this, "", sprintf("geomset 1 %i\n", m_iBody));
	}
	if (flChanged & BASEFL_CHANGED_SCALE) {
		scale = readfloat();
	}

#ifdef GS_RENDERFX
	if (flChanged & BASEFL_CHANGED_RENDERFX) {
		m_iRenderFX = readbyte();
	}
	if (flChanged & BASEFL_CHANGED_RENDERMODE) {
		m_iRenderMode = readbyte();
	}
	if (flChanged & BASEFL_CHANGED_RENDERCOLOR) {
		m_vecRenderColor[0] = readfloat();
		m_vecRenderColor[1] = readfloat();
		m_vecRenderColor[2] = readfloat();
	}
	if (flChanged & BASEFL_CHANGED_RENDERAMT) {
		m_flRenderAmt = readfloat();
	}
#else
	if (flChanged & BASEFL_CHANGED_ALPHA) {
		alpha = readfloat();
	}
#endif

	if (modelindex) {
		drawmask = MASK_ENGINE;
	} else {
		drawmask = 0;
	}

	setorigin(this, origin);
	setsize(this, mins, maxs);

    // Process flags and gflags
    if (flChanged & GAMEFL_CHANGED_FLAGS) {
		flags = readfloat();
		gflags = readfloat();
	}
}

//=======================
// void CGameEntity::Respawn(void)
//
// Respawn.
//=======================
void CGameEntity::Respawn(void) {
    //CBaseEntity::Respawn();
}

//=======================
// void CGameEntity::SpawnKey(string strKey, string strValue)
//
// Spawnkeys.
//=======================
void
CGameEntity::SpawnKey(string strKey, string strValue)
{
	CBaseEntity::SpawnKey(strKey, strValue);
	// switch (strKey) {
	// case "classname":
	// case "spawnflags":
	// 	break;
	// default:
	// 	print(sprintf("^3%s^7::SpawnKey:: Unknown key '%s' with value '%s'\n",
	// 	      classname, strKey, strValue));
	// 	break;
	// }
}

//=======================
// void CGameEntity::CGameEntity(void)
//
// Constructor.
//=======================
void CGameEntity::CGameEntity(void)
{	
	CBaseEntity::CBaseEntity();
	// Call Super class constructor. 
	classname = "CGameEntity";
}