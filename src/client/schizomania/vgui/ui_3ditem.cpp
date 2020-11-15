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
// Somehow not available in this file, like in menu qc?
vector v_forward;
vector v_up;
vector v_right;
void AngleVectors ( vector angles )
{
	float angle;
	float sr, sp, sy, cr, cp, cy;
	
	angle = angles[1] * (M_PI*2 / 360);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles[0] * (M_PI*2 / 360);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles[2] * (M_PI*2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	v_forward[0] = cp*cy;
	v_forward[1] = cp*sy;
	v_forward[2] = -sp;

	v_right[0] = (-1*sr*sp*cy+-1*cr*-sy);
	v_right[1] = (-1*sr*sp*sy+-1*cr*cy);
	v_right[2] = -1*sr*cp;

	v_up[0] = (cr*sp*cy+-sr*-sy);
	v_up[1] = (cr*sp*sy+-sr*cy);
	v_up[2] = cr*cp;
}

class CUI3DItem:CUIWidget
{
    // 3D Item Model entity.
    entity m_eModel;
    int initialized;        // Was a static, now a class member.

    // 3D Rendering configuration.
	vector m_vecSize;
	vector m_vec3DPos;
	vector m_vec3DAngles;
	float m_flFOV;
    
    // Item data.
    int m_iItemID;
    int m_iItemAmount;
    
    // Widget Functions.
	void(void) CUI3DItem;
	virtual void(float, float, float, float) m_vInputFunc = 0;
	virtual vector() GetSize;
	virtual vector() Get3DPos;
	virtual vector() Get3DAngles;
	virtual void(vector) SetSize;
	virtual void(vector) Set3DPos;
	virtual void(vector) Set3DAngles;
	virtual void(void(float, float, float, float)) SetInputFunc;
	virtual void(float, float, float, float) Input;
    virtual void(void) Draw;

    // Item related widget functions.
    virtual void(int) SetItemID;
    virtual void(int) SetItemAmount;
};

//=======================
// void CUI3DItem::CUI3DItem(void)
//
// Constructor.
//=======================
void
CUI3DItem::CUI3DItem(void)
{
    // 3D Property defaults.
	m_flFOV = 90;
	m_vecSize = [96,96];
	m_vec3DPos = m_vec3DAngles = [0,0,0];
	m_iFlags = VIEW_VISIBLE;

    // Spawn model entity.
    m_eModel = spawn();

    // Setup default amount.
    m_iItemID = 0;
    m_iItemAmount = 0;
}

//=======================
// void CUI3DItem::SetSize(void)
//
// Set size.
//=======================
void
CUI3DItem::SetSize(vector vecSize)
{
	m_vecSize = vecSize;
}

//=======================
// void CUI3DItem::GetSize(void)
//
// Get size.
//=======================
vector
CUI3DItem::GetSize(void)
{
	return m_vecSize;
}

//=======================
// void CUI3DItem::Set3DAngles(vector vecAngles)
//
// Set the camera view direction angle.
//=======================
void
CUI3DItem::Set3DAngles(vector vecAngles)
{
	m_vec3DAngles = vecAngles;
}

//=======================
// void CUI3DItem::Get3DAngles(void)
//
// Get the camera view direction angle.
//=======================
vector
CUI3DItem::Get3DAngles(void)
{
	return m_vec3DAngles;
}

//=======================
// void CUI3DItem::Set3DPos(vector vecPos)
//
// Set the camera view position.
//=======================
void
CUI3DItem::Set3DPos(vector vecPos)
{
	m_vec3DPos = vecPos;
}

//=======================
// void CUI3DItem::Get3DPos(void)
//
// Set the camera view position.
//=======================
vector
CUI3DItem::Get3DPos(void)
{
	return m_vec3DPos;
}

//=======================
// void CUI3DItem::SetInputFunc(...)
//
// Set designated input function.
//=======================
void
CUI3DItem::SetInputFunc(void(float, float, float, float) vFunc)
{
	m_vInputFunc = vFunc;
}

//=======================
// void CUI3DItem::Draw(void)
//
// Draw the 3D item.
//=======================
void
CUI3DItem::Draw(void)
{
    static vector vecDistance = [ 20, 0, 0 ];

	clearscene();
	setproperty(VF_VIEWPORT, m_vecOrigin + m_parent.m_vecOrigin, m_vecSize);
	setproperty(VF_DRAWWORLD, 0);
    setproperty(VF_AFOV, m_flFOV);
	setproperty(VF_ORIGIN, m_vec3DPos);
	setproperty(VF_ANGLES, m_vec3DAngles);

	if ( !initialized ) {
	  	initialized = TRUE;
        setmodel(m_eModel, g_inventory_items[m_iItemID].wmodel());
	  	AngleVectors( Get3DAngles() );
        Set3DPos( v_forward * -vecDistance[0] + v_right * vecDistance[1] + v_up * vecDistance[2] );
        dprint(sprintf("Initializing item entity with model: %S \n", g_inventory_items[m_iItemID].wmodel()));
	}
    
    m_eModel.angles.y += frametime * 100;
	m_eModel.frame1time += frametime;

	addentity( m_eModel );
	renderscene();

    // Draw item name.
    Font_DrawText(m_parent.m_vecOrigin + m_vecOrigin + [0, 88],
        g_inventory_items[m_iItemID].name, g_fntDefault);

    // Draw item amount.
    Font_DrawText(m_parent.m_vecOrigin + m_vecOrigin + [88, 0],
        sprintf("(%i) x", m_iItemAmount), g_fntDefault);
}

//=======================
// void CUI3DItem::Input(...)
//
// Handle input over to the custom input function.
//=======================
void
CUI3DItem::Input(float flEVType, float flKey, float flChar, float flDevID)
{
	if (!m_vInputFunc) {
		return;
	}

	m_vInputFunc(flEVType, flKey, flChar, flDevID);
}

//=======================
// void CUI3DItem::SetItemID(int itemID)
//
// Set current itemID to be referring to.
//=======================
void
CUI3DItem::SetItemID(int itemID) {
    m_iItemID = itemID;
}

//=======================
// void CUI3DItem::SetItemAmount(int itemAmount)
//
// Set current itemID anount for text rendering.
//=======================
void
CUI3DItem::SetItemAmount(int itemAmount) {
    m_iItemAmount = itemAmount;
}
