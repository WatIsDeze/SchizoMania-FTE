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

/*QUAKED func_brush (0 .5 .8) ?
"targetname"        Name

"Solidity"          Mode for choosing solidity:
                    0 - Toggle
                    1 - Not solid
                    2 - Solid
"StartDisabled"     Only valid when Solidity is 0. Will make it spawn invisible
                    and without collision.
"solidbsp"          Type of collision model to choose
"excludednpc"       Name of the NPC classname that will not collide with this
                    entity
"invert_exclusion"  Set to 1 if you want the 'excludednpc' key to act inverted

Description:
Combination of func_illusionary, func_wall, func_wall_toggle.
Triggering it causes to become invisible if the key 'Solidity' is set to 0 as
well as lose its collision.


Trivia:
This entity was introduced in Half-Life 2 (2004).
*/

class func_brush:CBaseTrigger
{
	int m_iSolidity;
	int m_iStartOff;

	void(void) func_brush;

	virtual void(entity,int) Trigger;
	virtual void(string,string) SpawnKey;
	virtual void(void) Respawn;
};

void
func_brush::Trigger(entity act, int state)
{
	switch (state) {
	case TRIG_OFF:
		SetSolid(SOLID_NOT);
		break;
	case TRIG_ON:
		SetSolid(SOLID_BSP);
		break;
	default:
		SetSolid(solid == SOLID_BSP ? SOLID_NOT : SOLID_BSP);
	}

	/* toggle appareance */
	if (m_iSolidity == 0) {
		if (solid == SOLID_NOT)
			SetModelindex(0);
		else
			SetModel(m_oldModel);
	}
}

void
func_brush::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "Solidity":
		m_iSolidity = stoi(strValue);
		break;
	case "StartDisabled":
		m_iStartOff = stoi(strValue);
		break;
	/* TODO: implement these */
	case "solidbsp":
		break;
	case "excludednpc":
		break;
	case "invert_exclusion":
		break;
	}
}

void
func_brush::Respawn(void)
{
	SetMovetype(MOVETYPE_PUSH);
	SetModel(m_oldModel);
	SetOrigin(m_oldOrigin);

	switch (m_iSolidity) {
	case 1:
		SetSolid(SOLID_NOT);
		break;
	case 2:
		SetSolid(SOLID_BSP);
		break;
	default:
		if (m_iStartOff) {
			SetSolid(SOLID_NOT);
			SetModelindex(0);
		} else {
			SetSolid(SOLID_BSP);
		}
	}
}

void
func_brush::func_brush(void)
{
	CBaseTrigger::CBaseTrigger();
}
