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

/*QUAKED func_door (0 .5 .8) ? SF_MOV_OPEN x SF_MOV_UNLINK SF_MOV_PASSABLE x SF_MOV_TOGGLE x x SF_MOV_USE
"targetname"    Name
"target"        Target when triggered.
"killtarget"    Target to kill when triggered.
"angle"			Direction in which this door has to move.
"speed"         Movement speed in game-units per second.
"lip"           Sets how many units are still visible after a door moved.
"delay"         Time until triggering target.
"wait"          When to move back.
"netname"       Target to trigger when door returns to its initial position.
"dmg"           Damage to inflict upon anything blocking the way.
"noise1"        Path to sound sample to play when the door is moving.
"noise2"        Path to sound sample to play when the door stops moving.
"movesnd"       Legacy integer value pointing to a predefined move sound.
"stopsnd"       Legacy integer value pointing to a predefined stop sound.

This sliding door entity has the ability to slide forth and back on any
axis. It is often used for primitive elevators as well.

The keys "movesnd" and "stopsnd" are obsolete. Their values point towards
the samples doors/doormoveX.wav and doors/doorstopX.wav respectively, where
X is the integer value set in "movesnd" and "stopsnd".

When SF_MOV_OPEN is set, the door starts 'open'. This helps getting the surface
of the door lit properly before hiding it away somewhere.

The spawnflag SF_MOV_UNLINK is currently unimplemented.

When SF_MOV_PASSABLE is set, the door won't have any collision.

When SF_MOV_TOGGLE is set, the door cannot be opened by any conventional means.
It will have to be triggered by another map entity.

When SF_MOV_USE is set, the door can be triggered by a player using the 'use'
key/button. Not every game may implement such a function.
*/

enumflags {
	SF_MOV_OPEN,
	SF_MOV_RESERVED1,
	SF_MOV_UNLINK, /* TODO: implement this */
	SF_MOV_PASSABLE,
	SF_MOV_RESERVED2,
	SF_MOV_TOGGLE,
	SF_MOV_RESERVED3,
	SF_MOV_RESERVED4,
	SF_MOV_USE
};

enum
{
	DOORSTATE_RAISED,
	DOORSTATE_LOWERED,
	DOORSTATE_UP,
	DOORSTATE_DOWN
};

class func_door:CBaseTrigger
{
	string targetClose;
	vector m_vecPos1;
	vector m_vecPos2;
	vector m_vecDest;
	vector m_vecMoveDir;
	float m_flSpeed;
	float m_flLip;
	float m_iState;
	float m_flNextTrigger;
	float m_flWait;
	float m_flDelay;
	int m_iDamage;
	int m_iLocked;

	string m_strSndMove;
	string m_strSndStop;

	void(void) func_door;
	virtual void(void) SetMovementDirection;
	virtual void(vector, void(void) func) MoveToDestination;
	virtual void(void) MoveAway;
	virtual void(void) MoveBack;
	virtual void(void) Arrived;
	virtual void(void) Returned;
	virtual void(void) Respawn;
	virtual void(entity, int) Trigger;
	virtual void(void) Blocked;
	virtual void(void) Touch;
	virtual void(void) Use;
	virtual void(string, string) SpawnKey;
};

void
func_door::Use(void)
{
	eActivator.gflags &= ~GF_USE_RELEASED;
	Trigger(eActivator, TRIG_TOGGLE);
}

void
func_door::Arrived(void)
{
	SetOrigin(m_vecDest);
	velocity = [0,0,0];
	nextthink = 0.0f;

	m_iState = DOORSTATE_RAISED;

	if (m_strSndStop) {
		Sound_Play(this, CHAN_VOICE, m_strSndStop);
	} else {
		sound(this, CHAN_VOICE, "common/null.wav", 1.0f, ATTN_NORM);
	}

	if (targetClose)
	for (entity f = world; (f = find(f, ::targetname, targetClose));) {
		CBaseTrigger trigger = (CBaseTrigger)f;
		if (trigger.Trigger != __NULL__) {
			trigger.Trigger(this, TRIG_TOGGLE);
		}
	}

	if (!(spawnflags & SF_MOV_USE)) {
		touch = Touch;
	}
	if (m_flWait < 0) {
		return;
	}

	if (!(spawnflags & SF_MOV_TOGGLE)) {
		think = MoveBack;
		nextthink = (ltime + m_flWait);
	}
}

void
func_door::Returned(void)
{
	SetOrigin(m_vecDest);
	velocity = [0,0,0];
	nextthink = 0.0f;

	if (m_strSndStop) {
		Sound_Play(this, CHAN_VOICE, m_strSndStop);
	} else {
		sound(this, CHAN_VOICE, "common/null.wav", 1.0f, ATTN_NORM);
	}

	if (!(spawnflags & SF_MOV_USE)) {
		touch = Touch;
	}

	m_iState = DOORSTATE_LOWERED;
}

void
func_door::MoveBack(void)
{
	if (m_strSndMove) {
		Sound_Play(this, CHAN_VOICE, m_strSndMove);
	} else {
		sound(this, CHAN_VOICE, "common/null.wav", 1.0f, ATTN_NORM);
	}

	if (!(spawnflags & SF_MOV_USE)) {
		touch = __NULL__;
	}

	m_iValue = 0;
	m_iState = DOORSTATE_DOWN;
	MoveToDestination(m_vecPos1, Returned);
}

void
func_door::MoveAway(void)
{
	if (m_iState == DOORSTATE_UP) {
		return;
	}

	if (m_strSndMove) {
		Sound_Play(this, CHAN_VOICE, m_strSndMove);
	} else {
		sound(this, CHAN_VOICE, "common/null.wav", 1.0f, ATTN_NORM);
	}

	if (!(spawnflags & SF_MOV_TOGGLE)) {
		if (m_iState == DOORSTATE_RAISED) {
			nextthink = (ltime + m_flWait);
			return;
		}
	}

	m_iValue = 1;
	m_iState = DOORSTATE_UP;
	MoveToDestination(m_vecPos2, Arrived);
}

void
func_door::Trigger(entity act, int state)
{
	if (GetMaster() == 0)
		return;

	if (m_flNextTrigger > time) {
		if (!(spawnflags & SF_MOV_TOGGLE)) {
			return;
		}
	}
	m_flNextTrigger = time + m_flWait;

	/* only trigger stuff once we are done moving */
	if ((m_iState == DOORSTATE_RAISED) || (m_iState == DOORSTATE_LOWERED)) {
		UseTargets(act, TRIG_TOGGLE, m_flDelay);
	}

	if (state == TRIG_OFF) {
		MoveBack();
	} else if (state == TRIG_ON) {
		MoveAway();
	} else {
		if ((m_iState == DOORSTATE_UP) || (m_iState == DOORSTATE_RAISED)){
			MoveBack();
		} else {
			MoveAway();
		}
	}
}

void
func_door::Touch(void)
{
	if (spawnflags & SF_MOV_TOGGLE) {
		return;
	}

	if (m_iLocked) {
		return;
	}

	if (other.movetype == MOVETYPE_WALK) {
		if (other.absmin[2] <= maxs[2] - 2) {
			Trigger(other, TRIG_TOGGLE);
		}
	}
}

void
func_door::Blocked(void)
{
	if (m_iDamage) {
		Damage_Apply(other, this, m_iDamage, 0, DMG_CRUSH);
	}

	if (m_flWait >= 0) {
		if (m_iState == DOORSTATE_DOWN) {
			MoveAway();
		} else {
			MoveBack();
		}
	}
}

void
func_door::SetMovementDirection(void)
{
	if (m_oldAngle == [0,-1,0]) {
		m_vecMoveDir = [0,0,1];
	} else if (m_oldAngle == [0,-2,0]) {
		m_vecMoveDir = [0,0,-1];
	} else {
		makevectors(m_oldAngle);
		m_vecMoveDir = v_forward;
	}
}

void
func_door::MoveToDestination(vector vecDest, void(void) func)
{
	vector vecDifference;
	float flTravel;
	float fTravelTime;

	if (!m_flSpeed) {
		objerror("func_door: No speed defined!");
		return;
	}

	m_vecDest = vecDest;
	think = func;

	if (vecDest == origin) {
		velocity = [0,0,0];
		nextthink = (ltime + 0.1f);
		return;
	}

	vecDifference = (vecDest - origin);
	flTravel = vlen(vecDifference);
	fTravelTime = (flTravel / m_flSpeed);

	if (fTravelTime < 0.1) {
		velocity = [0,0,0];
		nextthink = ltime + 0.1f;
		return;
	}

	nextthink = (ltime + fTravelTime);
	velocity = (vecDifference * (1.0f / fTravelTime));
}

void
func_door::Respawn(void)
{
	/* reset */
	m_vecPos1 = [0,0,0];
	m_vecPos2 = [0,0,0];
	m_vecDest = [0,0,0];
	m_vecMoveDir = [0,0,0];

	/* angles to vecMoveDir */
	SetMovementDirection();

	if (spawnflags & SF_MOV_PASSABLE)
		SetSolid(SOLID_NOT);
	else
		SetSolid(SOLID_BSP);

	SetMovetype(MOVETYPE_PUSH);
	SetModel(m_oldModel);
	SetOrigin(m_oldOrigin);
	blocked = Blocked;
	think = __NULL__;
	nextthink = 0.0f;

	/* FIXME: Is this correct? */
	if (m_flWait == -1) {
		spawnflags |= SF_MOV_TOGGLE;
	}

	if (!m_flSpeed) {
		m_flSpeed = 100.0f;
	}

	if (!m_iDamage) {
		m_iDamage = 2;
	}

	if (spawnflags & SF_MOV_USE) {
		touch = __NULL__;
		PlayerUse = Use;
	} else {
		touch = Touch;
		PlayerUse = __NULL__;
	}

	m_iValue = 0;
	m_iState = DOORSTATE_LOWERED;
	m_vecPos1 = m_oldOrigin;
	m_vecPos2 = (m_vecPos1 + m_vecMoveDir * (fabs(m_vecMoveDir * size) - m_flLip));

	if (spawnflags & SF_MOV_OPEN) {
		SetOrigin(m_vecPos2);
		m_vecPos2 = m_vecPos1;
		m_vecPos1 = origin;
		m_iValue = 1;
	}

	if (targetname) {
		m_iLocked = TRUE;
	}

	SetAngles([0,0,0]);
}

void
func_door::SpawnKey(string strKey, string strValue)
{
	int x;

	switch (strKey) {
	case "speed":
		m_flSpeed = stof(strValue);
		break;
	case "lip":
		m_flLip = stof(strValue);
		break;
	case "wait":
		m_flWait = stof(strValue);
		break;
	case "netname":
		targetClose = strValue;
		netname = __NULL__;
		break;
	case "dmg":
		m_iDamage = stoi(strValue);
		break;
	case "noise1":
		m_strSndMove = strValue;
		break;
	case "noise2":
		m_strSndStop = strValue;
		break;
	/* GoldSrc compat */
	case "movesnd":
		x = stoi(strValue);
		m_strSndMove = sprintf("func_door.move_%i", x);
		break;
	case "stopsnd":
		x = stoi(strValue);
		m_strSndStop = sprintf("func_door.stop_%i", x);
		break;
	default:
		CBaseTrigger::SpawnKey(strKey, strValue);
	}
}

void
func_door::func_door(void)
{
	CBaseTrigger::CBaseTrigger();

	if (m_strSndMove)
		Sound_Precache(m_strSndMove);
	if (m_strSndStop)
		Sound_Precache(m_strSndStop);
}

void
func_water(void)
{
	spawnfunc_func_door();
	self.classname = "func_water";
	self.solid = SOLID_BSP;
	self.skin = CONTENT_WATER;
	self.effects |= EF_FULLBRIGHT;
	self.spawnflags |= SF_MOV_TOGGLE;
	setorigin(self, self.origin); // relink. have to do this.
}
