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
// Game entity server class. Handles networking for gflags and flags
// accordingly. Used for pickups, or anything else that requires a trigger
// to network flags.
//
// Any game trigger that requires so,  should be derived from this class.
//=========================================================================
class CGameEntity:CBaseEntity
{
	float m_iFlags;
	float m_iGFlags;

	void(void) CGameEntity;

	virtual void(void) Respawn;
	virtual void(string strKey, string strValue) SpawnKey;
    virtual float(entity ePEnt, float fChanged) SendEntity;
	
	virtual void(float fFlags) SetFlags;
	virtual void(float fGFlags) SetGFlags;
};

//=======================
// void CGameEntity::SetFlags(float fGFlags)
//
// Set flags, best called like: SetFlags(gflags & SOME_FLAG)
//=======================
void 
CGameEntity::SetFlags(float fFlags) {
	if (flags == fFlags)
		return;

	flags = fFlags;
	SendFlags |= GAMEFL_CHANGED_FLAGS;
}

//=======================
// void CGameEntity::SetGFlags(float fGFlags)
//
// Set gflags, best called like: SetGFlags(gflags & SOME_FLAG)
//=======================
void 
CGameEntity::SetGFlags(float fGFlags) {
	if (gflags == fGFlags)
		return;

	gflags = fGFlags;
	SendFlags |= GAMEFL_CHANGED_FLAGS;
}

//=======================
// void CGameEntity::Respawn(void)
//
// Send gflags and flags.
//=======================
float 
CGameEntity::SendEntity(entity ePEnt, float fChanged) {
	// if (!CBaseEntity::SendEntity(ePEnt, fChanged)) {
	// 	return FALSE;
	// }
	// CBaseEntity::SendEntity(ePEnt, fChanged);

	WriteByte(MSG_ENTITY, ENT_GAMEENTITY);
	WriteFloat(MSG_ENTITY, fChanged);

	/* really trying to get our moneys worth with 23 bits of mantissa */
	if (fChanged & BASEFL_CHANGED_ORIGIN) {
		WriteCoord(MSG_ENTITY, origin[0]);
		WriteCoord(MSG_ENTITY, origin[1]);
		WriteCoord(MSG_ENTITY, origin[2]);
	}
	if (fChanged & BASEFL_CHANGED_ANGLES) {
		WriteFloat(MSG_ENTITY, angles[0]);
		WriteFloat(MSG_ENTITY, angles[1]);
		WriteFloat(MSG_ENTITY, angles[2]);
	}
	if (fChanged & BASEFL_CHANGED_MODELINDEX) {
		WriteShort(MSG_ENTITY, modelindex);
	}
	if (fChanged & BASEFL_CHANGED_SOLID) {
		WriteByte(MSG_ENTITY, solid);
	}
	if (fChanged & BASEFL_CHANGED_MOVETYPE) {
		WriteByte(MSG_ENTITY, movetype);
	}
	if (fChanged & BASEFL_CHANGED_SIZE) {
		WriteCoord(MSG_ENTITY, mins[0]);
		WriteCoord(MSG_ENTITY, mins[1]);
		WriteCoord(MSG_ENTITY, mins[2]);
		WriteCoord(MSG_ENTITY, maxs[0]);
		WriteCoord(MSG_ENTITY, maxs[1]);
		WriteCoord(MSG_ENTITY, maxs[2]);
	}
	if (fChanged & BASEFL_CHANGED_FRAME) {
		WriteByte(MSG_ENTITY, frame);
	}
	if (fChanged & BASEFL_CHANGED_SKIN) {
		WriteByte(MSG_ENTITY, skin + 128);
	}
	if (fChanged & BASEFL_CHANGED_EFFECTS) {
		WriteFloat(MSG_ENTITY, effects);
	}
	if (fChanged & BASEFL_CHANGED_BODY) {
		WriteByte(MSG_ENTITY, m_iBody);
	}
	if (fChanged & BASEFL_CHANGED_SCALE) {
		WriteFloat(MSG_ENTITY, scale);
	}

#ifdef GS_RENDERFX
	if (fChanged & BASEFL_CHANGED_RENDERFX) {
		WriteByte(MSG_ENTITY, m_iRenderFX);
	}
	if (fChanged & BASEFL_CHANGED_RENDERMODE) {
		WriteByte(MSG_ENTITY, m_iRenderMode);
	}
	if (fChanged & BASEFL_CHANGED_RENDERCOLOR) {
		WriteFloat(MSG_ENTITY, m_vecRenderColor[0]);
		WriteFloat(MSG_ENTITY, m_vecRenderColor[1]);
		WriteFloat(MSG_ENTITY, m_vecRenderColor[2]);
	}
	if (fChanged & BASEFL_CHANGED_RENDERAMT) {
		WriteFloat(MSG_ENTITY, m_flRenderAmt);
	}
#else
	if (fChanged & BASEFL_CHANGED_ALPHA) {
		WriteFloat(MSG_ENTITY, alpha);
	}
#endif

    // Process flags and gflags.
	if (fChanged & GAMEFL_CHANGED_FLAGS) {
		WriteFloat(MSG_ENTITY, flags);
		WriteFloat(MSG_ENTITY, gflags);
	}

	// Succeeded.
	return TRUE;
}

//=======================
// void CGameEntity::Respawn(void)
//
// Respawn.
//=======================
void 
CGameEntity::Respawn(void) {
    CBaseEntity::Respawn();
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
	// Call Super class constructor. 
	CBaseEntity::CBaseEntity(); 
	classname = "CGameEntity";

}