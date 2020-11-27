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

/*QUAKED scene_cameraview (1 0 0) (-8 -8 -8) (8 8 8)

SCHIZOMANIA ENTITY

Causes the activators first-person camera to switch to the view of 
this entity.
- targetname: The entity trigger targetname.
- angles:     Sets the pitch, yaw and roll angles of the camera.
- moveto:     Overrides angles, and moves the camera view angle to 
              the given target.
- wait:       How long to hold on a target.
- delay:      The amount of time to wait before triggering 
*/

class scene_cameraview:CBaseTrigger
{
	string m_strMoveTo;
	float m_flDelay;
	float m_flWait;

	void(void) scene_cameraview;
	virtual void(entity, int) Trigger;
	virtual void(string, string) SpawnKey;
};

//=======================
// void Trigger(entity act, int state)
//
// Trigger functionality.
//=======================
void
scene_cameraview::Trigger(entity act, int state)
{
	UseTargets(act, TRIG_TOGGLE, m_flDelay);

	if (m_strMoveTo) {
		entity e = find(world, ::targetname, m_strMoveTo);
		if (e) {
			angles = vectoangles(e.origin - origin);
		}
	}

	Client_TriggerCamera(act, origin, angles, m_flWait);
	//eActivator.view2 = this;

    // Supposedly, we need this, otherwise it goes haywire..
    Client_FixAngle(act, act.angles);

	dprint(sprintf("^scene_cameraview::^3Trigger^7: Camera at %v, %v, for %f sec/s requested\n", 
		origin, angles, m_flWait));
}

//=======================
// void SpawnKey(string strKey, string strValue)
//
// SpawnKey.
//=======================
void
scene_cameraview::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "angles":
		angles = stov(strValue);
		break;
	case "wait":
		m_flWait = stof(strValue);
		break;
	case "moveto":
		m_strMoveTo = strValue;
		break;
	default:
		CBaseTrigger::SpawnKey(strKey, strValue);
	}
}

//=======================
// void scene_cameraview(vod)
//
// Constructor.
//=======================
void
scene_cameraview::scene_cameraview(void)
{
	CBaseTrigger::CBaseTrigger();
    classname = "scene_cameraview";
}
