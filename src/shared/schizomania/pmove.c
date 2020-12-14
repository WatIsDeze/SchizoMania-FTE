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

// Custom SchizoMania fine tuned.
#define PMOVE_STEPHEIGHT 18
#define PMOVE_AIRSTEPHEIGHT 18
#define PMOVE_FRICTION 4
#define PMOVE_EDGEFRICTION 1
#define PMOVE_STOPSPEED 75
#define PMOVE_GRAVITY 800
#define PMOVE_AIRACCELERATE 10
#define PMOVE_WATERACCELERATE 8
#define PMOVE_ACCELERATE 8
#define PMOVE_MAXSPEED 270
#define PMOVE_STEP_WALKSPEED 125
#define PMOVE_STEP_RUNSPEED 220

// #define PMOVE_STEPHEIGHT 18
// #define PMOVE_AIRSTEPHEIGHT 18
// #define PMOVE_FRICTION 4
// #define PMOVE_EDGEFRICTION 1
// #define PMOVE_STOPSPEED 75
// #define PMOVE_GRAVITY 800
// #define PMOVE_AIRACCELERATE 10
// #define PMOVE_WATERACCELERATE 8
// #define PMOVE_ACCELERATE 8
// #define PMOVE_MAXSPEED 270
// #define PMOVE_STEP_WALKSPEED 135
// #define PMOVE_STEP_RUNSPEED 220

.float waterlevel;
.float watertype;

float GamePMove_Maxspeed(player target)
{
	// Taken from the CStrike code.
	float spd = serverkeyfloat("phy_maxspeed");//serverkeyfloat("phy_maxspeed");

	
	// switch (target.activeweapon)
	// {
	// case WEAPON_XX:
	// 	spd *= 144/165;
	// 	break;
	// default:
	// }

	if (target.flags & FL_CROUCHING) {
		spd = 55;
	}

	return spd;
}

void GamePMove_Fall(player target, float impactspeed)
{
	// Taken from the CStrike code.
	if (impactspeed > 580) {
#ifdef SERVER
		float fFallDamage = (impactspeed - 580) * (100 / (1024 - 580)) * 1.75f;
		Damage_Apply(target, world, fFallDamage, 0, DMG_FALL);

		if (random() < 0.5)
			sound(target, CHAN_AUTO, "player/pl_pain2.wav", 1.0, ATTN_NORM);
		else
			sound(target, CHAN_AUTO, "player/pl_pain4.wav", 1.0, ATTN_NORM);
#endif
	}

// 	if (impactspeed > 580) {
// #ifdef SERVER
// 		float fFallDamage = (impactspeed - 580) * (100 / (1024 - 580));
// 		Damage_Apply(target, world, fFallDamage, 0, DMG_FALL);
// 		Sound_Play(target, CHAN_VOICE, "player.fall");
// #endif
// 		target.punchangle += [15,0,(input_sequence & 1) ? 15 : -15];
// 	} else if (impactspeed > 400) {
// 		target.punchangle += [15,0,0];
// #ifdef SERVER
// 		Sound_Play(target, CHAN_VOICE, "player.lightfall");
// #endif
// 	}
}

void GamePMove_Jump(player target)
{
	// Taken from the CStrike code.
	if (target.waterlevel >= 2) {
		if (target.watertype == CONTENT_WATER) {
			target.velocity[2] = 100;
		} else if (target.watertype == CONTENT_SLIME) {
			target.velocity[2] = 80;
		} else {
			target.velocity[2] = 50;
		}
	} else {
		/* slow the player down a bit to prevent bhopping like crazy */
		target.velocity *= 0.80f;
		target.velocity[2] += 220;
	}
}
