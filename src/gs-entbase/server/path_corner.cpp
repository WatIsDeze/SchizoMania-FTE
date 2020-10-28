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

/*QUAKED path_corner (1 0 0) (-8 -8 -8) (8 8 8) PC_WAIT PC_TELEPORT PC_FIREONCE
"targetname"    Name
"target"        Next node.
"message"       Target to trigger when a train passes this node.
"speed"         New speed for passing train.
"yaw_speed"     New yaw rotation for passing train. Currently unused.
"wait"          Waiting time until we go to the next node.

Node entities used for func_trains and func_guntargets.

When the PC_WAIT flag is set, the train will stop moving once it's passed this
node. The train will have to be triggered again for it to continue moving.
This is useful for elevators.

When the PC_TELEPORT flag is set, the train passing this node will immediately
teleport to the position of the next node (target).

With the PC_FIREONCE flag set, it'll only fire its target (message) once.

Trivia:
This entity was introduced in Quake (1996).
*/

#ifdef DEVELOPER
var int autocvar_dev_cornerspeed = 0;
#endif

enumflags
{
	PC_WAIT,
	PC_TELEPORT,
	PC_FIREONCE
};

class path_corner:CBaseTrigger
{
	int m_iFired;
	float m_flSpeed;
	float m_flYawSpeed;
	float m_flWait;

	void(void) path_corner;
	virtual void(entity, int) Trigger;
	virtual void(void) Respawn;
	virtual void(string, string) SpawnKey;
};

void
path_corner::Trigger(entity act, int state)
{
	entity a;

	if ((spawnflags & PC_FIREONCE) && (m_iFired)) {
		return;
	}

	for (a = world; (a = find(a, ::targetname, m_strMessage));) {
		CBaseTrigger trigger = (CBaseTrigger)a;
		trigger.Trigger(act, state);
		m_iFired = TRUE;
	}
}

void
path_corner::Respawn(void)
{
#ifdef DEVELOPER
	if (autocvar_dev_cornerspeed != 0) {
		m_flSpeed = autocvar_dev_cornerspeed;
	}
#endif

	m_iFired = FALSE;
}

void
path_corner::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "speed":
		m_flSpeed = stof(strValue);
		break;
	case "yaw_speed":
		m_flYawSpeed = stof(strValue);
		break;
	case "wait":
		m_flWait = stof(strValue);
		break;
	case "message":
		m_strMessage = strValue;
		break;
	default:
		CBaseTrigger::SpawnKey(strKey, strValue);
	}
}

void
path_corner::path_corner(void)
{
	m_flWait = 1.0f;
	CBaseTrigger::CBaseTrigger();
}
