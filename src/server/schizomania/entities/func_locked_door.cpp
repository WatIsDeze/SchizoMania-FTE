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

/*QUAKED func_locked_door (0 .5 .8) ? SF_BTT_NOMOVE x x x x SF_BTT_TOGGLE SF_BTT_SPARKS x SF_BTT_TOUCH_ONLY
"targetname"    Name
"target"        Target when triggered.
"killtarget"    Target to kill when triggered.
"snd_locked"    The sound shader to play when tried to open.
"delay"         Delay until the Target gets triggered.

Outputs:
Don't think we need these.
                
A locked door entity, useful for locked doors in streets, and corridors.
Will play the designated sound when used/touched.

TODO - IMPLEMENT THESE !!!!!!!!!!!!!!!!!

When SF_LOCKEDDOOR_CHANGETEX is set, the only visual indicator you'll get is a possible
change of texture of door.

When SF_LOCKEDDOOR_SPARKS is set, the button will create a bunch of sparks when used.

When SF_LOCKEDDOOR_TOUCH_ONLY is set, the use key cannot be used to interact
with the door, it has to collide against a player.
*/

enumflags
{
	SF_LOCKEDDOOR_CHANGETEX,
	SF_LOCKEDDOOR_SPARKS,
	SF_LOCKEDDOOR_TOUCH_ONLY,
};

enum
{
	FRAME_OFF,
	FRAME_ON
};

class func_locked_door:CBaseTrigger
{
	float m_flSpeed;
	float m_flLip;
	int m_iDamage;
	int m_iState;

	float m_flNextTrigger;
	float m_flWait;
	float m_flDelay;

	string m_strSndUse;

	virtual void(void) Respawn;
	virtual void(void) Touch;
	virtual void(entity, int) Trigger;
	virtual void(void) Use;
	
	virtual void(string, string) SpawnKey;
};

/* TODO: Handle state */
void
func_locked_door::Trigger(entity act, int state)
{
	if (m_strSndUse)
		Sound_Play(this, CHAN_VOICE, m_strSndUse);

	UseTargets(act, TRIG_TOGGLE, m_flDelay);
}

void
func_locked_door::Touch(void)
{
	if (other.movetype == MOVETYPE_WALK) {
		Trigger(other, TRIG_TOGGLE);
    
		if (!(spawnflags & SF_LOCKEDDOOR_TOUCH_ONLY)) {
			touch = __NULL__;
		}
	}
}

void
func_locked_door::Use(void)
{
	Trigger(eActivator, TRIG_TOGGLE);
}

void
func_locked_door::Respawn(void)
{
	SetSolid(SOLID_BSP);
	SetMovetype(MOVETYPE_PUSH);
	SetOrigin(m_oldOrigin);
	SetModel(m_oldModel);

	velocity = [0,0,0];
	nextthink = -1;

	if (spawnflags & SF_LOCKEDDOOR_TOUCH_ONLY) {
		touch = Touch;
		PlayerUse = __NULL__;
	} else {
		touch = __NULL__;
		PlayerUse = Use;
	}

	SetAngles([0,0,0]);
}

void
func_locked_door::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "snd_use":
		m_strSndUse = strValue;
		break;
	case "wait":
		m_flWait = stof(strValue);
		break;
	default:
		CBaseTrigger::SpawnKey(strKey, strValue);
	}
}

void
func_locked_door::func_locked_door(void)
{
	CBaseTrigger::CBaseTrigger();

   	if (!m_strSndUse)
        m_strSndUse = "func_locked_door.wood01";

	/* sounds */
	Sound_Precache(m_strSndUse);
}

CLASSEXPORT(func_locked_door, func_locked_door);