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

enum
{ 
	USE_TOGGLE,
	USE_CONTINOUS
};

enum
{
	TRIG_OFF,
	TRIG_ON,
	TRIG_TOGGLE
};

class CBaseTrigger:CBaseEntity
{
	int m_strGlobalState;
	string m_strKillTarget;
	string m_strMessage;
	string m_strMaster;
	float m_flDelay;
	int m_iUseType;
	int m_iTeam;
	int m_iValue;

	void(void) CBaseTrigger;

	virtual void(entity, int) Trigger;
	virtual void(entity, int) UseTargets;
	virtual void(entity, int, float) UseTargets_Delay;
	virtual int(void) GetValue;
	virtual int(void) GetMaster;
	virtual void(void) InitBrushTrigger;
	virtual void(void) InitPointTrigger;
	virtual void(string, string) SpawnKey;
};

void
CBaseTrigger::UseTargets(entity act, int state)
{
	for (entity f = world; (f = find(f, ::targetname, target));) {
		CBaseTrigger trigger = (CBaseTrigger)f;
		dprint(sprintf("^2%s::^3UseTargets^7: Triggering %s `%s` from %s\n", 
			this.classname, f.classname, trigger.targetname, act.classname));
		if (trigger.Trigger != __NULL__) {
			trigger.Trigger(act, state);
		}
	}

	/* hack: check to see if this is a sound file */
	/*if (whichpack(m_strMessage)) {
		print(m_strMessage);
		print("\n");
	} else {
		if (m_strMessage && act.flags & FL_CLIENT) {
			centerprint(act, m_strMessage);
		}
	}*/

	if (m_strKillTarget) {
		entity eKill = find(world, ::targetname, m_strKillTarget);
		if (eKill) {
			remove(eKill);
		}
	}
}

void
CBaseTrigger::UseTargets_Delay(entity act, int state, float fDelay)
{
	static void Entities_UseTargets_Delay_Think(void) {
		CBaseTrigger::UseTargets(self.owner, self.health); /* ugly */
		remove(self);
	}

	dprint(sprintf("^2%s::^3UseTargets_Delay^7: Triggering `%s`\n", 
		this.classname, target));

	CBaseTrigger eTimer = spawn(CBaseTrigger);
	eTimer.owner = act;
	eTimer.think = Entities_UseTargets_Delay_Think;
	eTimer.target = target;
	eTimer.nextthink = time + fDelay;
	eTimer.health = state;  /* ugly */
}

int
CBaseTrigger::GetValue(void)
{
	return m_iValue;
}

int
CBaseTrigger::GetMaster(void)
{
	CBaseTrigger t;

	/* default to success */
	if (!m_strMaster) {
		/*dprint(sprintf("^2%s::^3GetMaster^7: No master, return success\n", 
		this.classname));*/
		return TRUE;
	}

	t = (CBaseTrigger)find(world, ::target, m_strMaster);

	/* we couldn't find it, so let's not even bother going further */
	if (!t) {
		/*dprint(sprintf("^2%s::^3GetMaster^7: Invalid master, return success\n", 
		this.classname));*/
		return TRUE;
	}

	/*if (t.GetValue() == 1)
		dprint(sprintf("^2%s::^3GetMaster^7: %s learns %s ^2POSITIVE\n", 
		this.classname, targetname, m_strMaster));
	else
		dprint(sprintf("^2%s::^3GetMaster^7: %s learns %s ^1NEGATIVE\n", 
		this.classname, targetname, m_strMaster));*/
	
	return t.GetValue();
}

void
CBaseTrigger::Trigger(entity act, int state)
{
	
}

void
CBaseTrigger::InitPointTrigger(void)
{
	setsize(this, VEC_HULL_MIN, VEC_HULL_MAX);
	solid = SOLID_TRIGGER;
}

void
CBaseTrigger::InitBrushTrigger(void)
{
	SetModel(m_oldModel);
	SetMovetype(MOVETYPE_NONE);
	SetSolid(SOLID_BSPTRIGGER);
	SetRenderMode(RM_TRIGGER);
}

void
CBaseTrigger::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "killtarget":
		m_strKillTarget = strValue;
		break;
	case "message":
		m_strMessage = strValue;
		break;
	case "master":
		m_strMaster = strValue;
		break;
	case "team_no":
		m_iTeam = stoi(strValue);
		break;
	default:
		CBaseEntity::SpawnKey(strKey, strValue);
		break;
	}
}

void
CBaseTrigger::CBaseTrigger(void)
{
	CBaseEntity::CBaseEntity();
}
