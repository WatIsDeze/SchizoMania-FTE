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

/*QUAKED light_dynamic (1 0 0) (-8 -8 -8) (8 8 8)
"targetname"        Name
"target"            Name of an entity in the map that light will point at.
"_light"            Color of the spotlight in RGB255 format.
"brightness"        Intensity of the spotlight.
"_inner_cone"       Angles of the inner spotlight beam. 0 = omnidirectional.
"_cone"             Angles of the outer spotlight beam. 0 = omnidirectional.
"distance"          Distance that light is allowed to cast, in inches.
"spotlight_radius"  Radius of the resulting spotlight that's cast at a wall.
"style"             Select one of the hard-coded lightstyles.
"start_active"      Override for if the entity should start on or off.

Inputs:
"TurnOn"            Turns the light on.
"TurnOff"           Turns the light off.
"Toggle"            Toggles the light from an on/off state.
"Color"             Sets the light color in RGB255 format.
"brightness"        Sets the light brightness.
"distance"          Sets the distance of which the light will travel/radius.
"_inner_cone"       Sets the length of the inner light cone.
"_cone"             Sets the length of the light cone.
"spotlight_radius"  Sets the radius of the projected spotlight.
"style"             Sets the light appearance in integer form.

Dynamic light entity. Can be parented to things, it even has some inputs that
may be interesting.

The 'start_active' is a Nuclide specific one. There is no way in Source engine
games to tell the entity to start inactive as far as I can tell.

Trivia:
This entity was introduced in Half-Life 2 (2004).
*/

enumflags
{
	DLIGHTFL_CHANGED_ORIGIN,
	DLIGHTFL_CHANGED_ANGLES,
	DLIGHTFL_CHANGED_LIGHT,
	DLIGHTFL_CHANGED_INTENSITY,
	DLIGHTFL_CHANGED_INNERCONE,
	DLIGHTFL_CHANGED_CONE,
	DLIGHTFL_CHANGED_DISTANCE,
	DLIGHTFL_CHANGED_RADIUS,
	DLIGHTFL_CHANGED_STYLE,
	DLIGHTFL_CHANGED_STATE
};

#ifdef CLIENT
class light_dynamic
#else
class light_dynamic:CBaseTrigger
#endif
{
	vector m_vecLight;
	float m_flIntensity;
	float m_flInnerCone;
	float m_flCone;
	float m_flDistance;
	float m_flRadius;
	float m_flStyle;
	int m_iState;

	void(void) light_dynamic;

#ifdef CLIENT
	virtual void(float) ReceiveEntity;
	virtual float(void) predraw;
#else
	int m_iStartActive;

	virtual void(entity, int) Trigger;
	virtual void(void) Respawn;
	virtual float(entity, float) SendEntity;
	virtual void(string, string) SpawnKey;
	virtual void(entity, string, string) Input;
	virtual void(void) ParentUpdate;
#endif
};

#ifdef CLIENT
float
light_dynamic::predraw(void)
{
	if (!m_iState) {
		return PREDRAW_NEXT;
	}

	/* TODO: We need to handle the second cone light */
	dynamiclight_add(origin, m_flDistance, m_vecLight, m_flStyle);

	addentity(this);
	return PREDRAW_NEXT;
}

void
light_dynamic::ReceiveEntity(float flFlags)
{
	if (flFlags & DLIGHTFL_CHANGED_ORIGIN) {
		origin[0] = readcoord();
		origin[1] = readcoord();
		origin[2] = readcoord();
		setorigin(this, origin);
	}

	if (flFlags & DLIGHTFL_CHANGED_ANGLES) {
		angles[0] = readfloat();
		angles[1] = readfloat();
		angles[2] = readfloat();
	}

	if (flFlags & DLIGHTFL_CHANGED_LIGHT) {
		m_vecLight[0] = readbyte() / 255;
		m_vecLight[1] = readbyte() / 255;
		m_vecLight[2] = readbyte() / 255;
	}

	if (flFlags & DLIGHTFL_CHANGED_INTENSITY)
		m_flIntensity = readfloat();
	if (flFlags & DLIGHTFL_CHANGED_INNERCONE)
		m_flInnerCone = readfloat();
	if (flFlags & DLIGHTFL_CHANGED_CONE)
		m_flCone = readfloat();
	if (flFlags & DLIGHTFL_CHANGED_DISTANCE)
		m_flDistance = readfloat();
	if (flFlags & DLIGHTFL_CHANGED_RADIUS)
		m_flRadius = readfloat();
	if (flFlags & DLIGHTFL_CHANGED_STYLE)
		m_flStyle = readbyte();
	if (flFlags & DLIGHTFL_CHANGED_STATE)
		m_iState = readbyte();

	classname = "light_dynamic";
}
#else
void
light_dynamic::ParentUpdate(void)
{
	if (net_origin != origin) {
		net_origin = origin;
		SendFlags |= DLIGHTFL_CHANGED_ORIGIN;
	}
	if (net_angles != angles) {
		net_angles = angles;
		SendFlags |= DLIGHTFL_CHANGED_ANGLES;
	}

	if (m_parent) {
		entity p = find(world, ::targetname, m_parent);

		if (p)
			SetOrigin(p.origin);
	}
}

void
light_dynamic::Trigger(entity act, int state)
{
	switch (state) {
	case TRIG_OFF:
		m_iState = 0;
		break;
	case TRIG_ON:
		m_iState = 1;
		break;
	default:
		m_iState = 1 - m_iState;
	}

	SendFlags |= DLIGHTFL_CHANGED_STATE;
}

float
light_dynamic::SendEntity(entity ePVSEnt, float flFlags)
{
	WriteByte(MSG_ENTITY, ENT_DLIGHT);
	WriteFloat(MSG_ENTITY, flFlags);

	if (flFlags & DLIGHTFL_CHANGED_ORIGIN) {
		WriteCoord(MSG_ENTITY, origin[0]);
		WriteCoord(MSG_ENTITY, origin[1]);
		WriteCoord(MSG_ENTITY, origin[2]);
	}

	if (flFlags & DLIGHTFL_CHANGED_ANGLES) {
		WriteFloat(MSG_ENTITY, angles[0]);
		WriteFloat(MSG_ENTITY, angles[1]);
		WriteFloat(MSG_ENTITY, angles[2]);
	}

	if (flFlags & DLIGHTFL_CHANGED_LIGHT) {
		WriteByte(MSG_ENTITY, m_vecLight[0]);
		WriteByte(MSG_ENTITY, m_vecLight[1]);
		WriteByte(MSG_ENTITY, m_vecLight[2]);
	}

	if (flFlags & DLIGHTFL_CHANGED_INTENSITY)
		WriteFloat(MSG_ENTITY, m_flIntensity);
	if (flFlags & DLIGHTFL_CHANGED_INNERCONE)
		WriteFloat(MSG_ENTITY, m_flInnerCone);
	if (flFlags & DLIGHTFL_CHANGED_CONE)
		WriteFloat(MSG_ENTITY, m_flCone);
	if (flFlags & DLIGHTFL_CHANGED_DISTANCE)
		WriteFloat(MSG_ENTITY, m_flDistance);
	if (flFlags & DLIGHTFL_CHANGED_RADIUS)
		WriteFloat(MSG_ENTITY, m_flRadius);
	if (flFlags & DLIGHTFL_CHANGED_STYLE)
		WriteByte(MSG_ENTITY, m_flStyle);
	if (flFlags & DLIGHTFL_CHANGED_STATE)
		WriteByte(MSG_ENTITY, m_iState);

	return TRUE;
}

void
light_dynamic::Input(entity eAct, string strInput, string strData)
{
	switch (strInput) {
	case "Color":
		m_vecLight = stov(strData);
		SendFlags |= DLIGHTFL_CHANGED_LIGHT;
		break;
	case "brightness":
		m_flIntensity = stof(strData);
		SendFlags |= DLIGHTFL_CHANGED_INTENSITY;
		break;
	case "distance":
		m_flDistance = stof(strData);
		SendFlags |= DLIGHTFL_CHANGED_DISTANCE;
		break;
	case "_inner_cone":
		m_flInnerCone = stof(strData);
		SendFlags |= DLIGHTFL_CHANGED_INNERCONE;
		break;
	case "_cone":
		m_flCone = stof(strData);
		SendFlags |= DLIGHTFL_CHANGED_CONE;
		break;
	case "spotlight_radius":
		m_flRadius = stof(strData);
		SendFlags |= DLIGHTFL_CHANGED_RADIUS;
		break;
	case "style":
		m_flStyle = stof(strData);
		SendFlags |= DLIGHTFL_CHANGED_STYLE;
		break;
	case "TurnOn":
		Trigger(eAct, TRIG_ON);
		break;
	case "TurnOff":
		Trigger(eAct, TRIG_OFF);
		break;
	case "Toggle":
		Trigger(eAct, TRIG_TOGGLE);
		break;
	default:
		CBaseTrigger::Input(eAct, strInput, strData);
	}
}

void
light_dynamic::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "_light":
		m_vecLight = stov(strValue);
		break;
	case "light":
	case "brightness":
		m_flIntensity = stof(strValue);
		break;
	case "_inner_cone":
		m_flInnerCone = stof(strValue);
		break;
	case "_cone":
		m_flCone = stof(strValue);
		break;
	case "distance":
		m_flDistance = stof(strValue);
		break;
	case "spotlight_radius":
		m_flRadius = stof(strValue);
		break;
	case "style":
		m_flStyle = stof(strValue);
		break;
	/* out-of-spec */
	case "start_active":
		m_iStartActive = stoi(strValue);
		break;
	default:
		CBaseTrigger::SpawnKey(strKey, strValue);
	}
}

void
light_dynamic::Respawn(void)
{
	SetSolid(SOLID_NOT);
	SetSize([-16,-16,-16], [16,16,16]);
	SetOrigin(m_oldOrigin);
	SetAngles(m_oldAngle);

	m_iState = (m_iStartActive == 1) ? 1 : 0;
}
#endif

void
light_dynamic::light_dynamic(void)
{
#ifdef CLIENT
	drawmask = MASK_ENGINE;
#else
	m_vecLight = [255,255,255];
	m_flDistance = 256;
	m_iStartActive = 1;

	CBaseTrigger::CBaseTrigger();
#endif
}

/* workaround for q3map2, as it turns any entity starting with light*
   into a generic static world light. */
#ifndef CLIENT
CLASSEXPORT(dynamic_light, light_dynamic)
#endif
