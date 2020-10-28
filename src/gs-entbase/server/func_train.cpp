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

/*QUAKED func_train (0 .5 .8) ? TRAIN_WAIT x x TRAIN_NOTSOLID
"targetname"    Name
"target"        First node.
"killtarget"    Target to kill when triggered.
"dmg"           Damage to inflict upon a person blocking the way.
"snd_move"      Path to sound sample which plays when it's moving.
"snd_stop"      Path to sound sample which plays when it stops moving.

Moving platform following along path_corner entities, aka nodes.
Most of its behaviour is controlled by the path_corner entities it passes over.
See the entity definition for path_corner to find out more.

Upon level entry, the func_train will spawn right where its first path_corner
node is. This is so you can light the func_train somewhere else - like a lonely
box somewhere outside the playable area.

Marking the func_train with the flag TRAIN_NOTSOLID will make entities not
collide with the train. This is best used for things in the distance or for
when lasers are following this train as a sort of guide.

Trivia:
This entity was introduced in Quake (1996).
*/

enumflags
{
	TRAIN_WAIT,
	TRAIN_UNUSED1,
	TRAIN_UNUSED2,
	TRAIN_NOTSOLID
};

class func_train:CBaseTrigger
{
	float m_flWait;
	float m_flSpeed;
	float m_flDamage;
	string m_strMoveSnd;
	string m_strStopSnd;

	void(void) func_train;
	virtual void(void) NextPath;
	virtual void(void) GoToTarget;
	virtual void(entity, int) Trigger;
	virtual void(void) Respawn;
	virtual void(void) Blocked;
	virtual void(string, string) SpawnKey;
};

void
func_train::Blocked(void)
{
	/* HACK: Make corpses gib instantly */
	if (other.solid == SOLID_CORPSE) {
		Damage_Apply(other, this, 500, 0, DMG_EXPLODE);
		return;
	}

	if (other.takedamage != DAMAGE_NO) {
		Damage_Apply(other, this, m_flDamage, 0, DMG_CRUSH);
	} else {
		remove(other);
	}
}

void
func_train::GoToTarget(void)
{
	entity eNode;
	float flTravelTime;
	vector vecVelocity;
	vector vecWorldPos;

	eNode = find(world, ::targetname, target);

	if (!eNode) {
		return;
	}

	vecWorldPos[0] = absmin[0] + (0.5 * (absmax[0] - absmin[0]));
	vecWorldPos[1] = absmin[1] + (0.5 * (absmax[1] - absmin[1]));
	vecWorldPos[2] = absmin[2] + (0.5 * (absmax[2] - absmin[2]));

	vecVelocity = (eNode.origin - vecWorldPos);
	flTravelTime = (vlen(vecVelocity) / m_flSpeed);

	if (!flTravelTime) {
		print("^1func_train::^3GoToTarget^7: Distance short, going next\n");
		think = NextPath;
		nextthink = ltime;
		return;
	}

	/* more stuff for the ears */
	if (m_strMoveSnd) {
		Sound_Play(this, CHAN_VOICE, m_strMoveSnd);
	}

	velocity = (vecVelocity * (1 / flTravelTime));
	think = NextPath;
	nextthink = (ltime + flTravelTime);
}

void
func_train::NextPath(void)
{
	path_corner eNode;
	eNode = (path_corner)find(world, ::targetname, target);

	if (!eNode) {
		return;
	}

	/* fire the path_corners' target */
	if (eNode.m_strMessage) {
		eNode.Trigger(this, TRIG_TOGGLE);
	}

	/* stuff for the ears */
	if (m_strStopSnd) {
		Sound_Play(this, CHAN_BODY, m_strStopSnd);
	}
	/* make the loopy noise stop */
	if (m_strMoveSnd) {
		sound(this, CHAN_VOICE, "common/null.wav", 1.0, ATTN_NORM);
	}

	SetOrigin(eNode.origin - (mins + maxs) * 0.5);

	/* if speed is 0, retain current speed */
	if (eNode.m_flSpeed > 0)
		m_flSpeed = eNode.m_flSpeed;

	m_flWait = eNode.m_flWait;
	target = eNode.target;
	velocity = [0,0,0];

	/* warp next frame */
	if (eNode.spawnflags & PC_TELEPORT) {
		print(sprintf("^1func_train::^3NextPath^7: Node %s wants %s to teleport\n", eNode.targetname, targetname));
		think = NextPath;
		nextthink = ltime;
		return;
	}

	/* stop until triggered again */
	if (eNode.spawnflags & PC_WAIT || spawnflags & TRAIN_WAIT) {
		return;
	}

	if (m_flWait > 0) {
		think = GoToTarget;
		nextthink = ltime + m_flWait;
	} else {
		GoToTarget();
	}
}

/* TODO: Handle state? */
void
func_train::Trigger(entity act, int state)
{
	GoToTarget();
}

void
func_train::Respawn(void)
{
	solid = spawnflags & TRAIN_NOTSOLID ? SOLID_NOT : SOLID_BSP;
	movetype = MOVETYPE_PUSH;
	blocked = Blocked;
	SetModel(m_oldModel);
	SetOrigin(m_oldOrigin);

	/* let's wait 1/4 a second to give the path_corner entities a chance to
	 * spawn in case they're after us in the ent lump */
	target = m_oldstrTarget;
	think = NextPath;
	nextthink = ltime + 0.25f;
}

void
func_train::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "dmg":
		m_flDamage = stof(strValue);
		break;
	case "snd_move":
		m_strMoveSnd = strValue;
		break;
	case "snd_stop":
		m_strStopSnd = strValue;
		break;
	/* compatibility */
	case "movesnd":
		m_strMoveSnd = sprintf("func_train.move_%i", stoi(strValue) + 1i);
		break;
	case "stopsnd":
		m_strStopSnd = sprintf("func_train.stop_%i", stoi(strValue) + 1i);
		break;
	default:
		CBaseTrigger::SpawnKey(strKey, strValue);
	}
}

void
func_train::func_train(void)
{
	/* FIXME: This is all decided by the first path_corner pretty much */
	m_flSpeed = 100;
	CBaseTrigger::CBaseTrigger();

	if (m_strMoveSnd)
		Sound_Precache(m_strMoveSnd);

	if (m_strStopSnd)
		Sound_Precache(m_strStopSnd);
}
