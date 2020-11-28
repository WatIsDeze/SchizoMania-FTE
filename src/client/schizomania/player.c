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

void
Player_PreDraw(base_player pl, int thirdperson)
{
	/* Handle the flashlights... */
	if (pl.gflags & GF_FLASHLIGHT) {
		vector src;
		vector ang;
		
		if (pl.entnum != player_localentnum) {
			src = pl.origin + pl.view_ofs;
			ang = [pl.pitch, pl.angles[1], pl.angles[2]];
		} else {
			src = pSeat->m_vecPredictedOrigin + [0,0,-8];
			ang = view_angles;
		}

		makevectors(ang);
		traceline(src, src + (v_forward * 8096), MOVE_NORMAL, pl);

		if (serverkeyfloat("*bspversion") == 30) {
			dynamiclight_add(trace_endpos + (v_forward * -2), 128, [1,1,1]);
		} else {
			float p = dynamiclight_add(src, 512, [1,0.8,0.6], 0, "textures/flashlight");
			dynamiclight_set(p, LFIELD_ANGLES, ang);
			dynamiclight_set(p, LFIELD_FLAGS, LFLAG_NORMALMODE | LFLAG_REALTIMEMODE);
			dynamiclight_set(p, LFIELD_STYLESTRING, "kkkkiiikklllklliikllll");
		}
	}
}

void
Player_ReceiveEntity(float new)
{
	float fl;
	player pl = (player)self;

	if (new == TRUE) {
		spawnfunc_player();
		pl.classname = "player";
		pl.solid = SOLID_SLIDEBOX;
		pl.drawmask = MASK_ENGINE;
		pl.customphysics = Empty;
		setsize(pl, VEC_HULL_MIN, VEC_HULL_MAX);
	} else {
		/* Go through all the physics code between the last received frame
		 * and the newest frame and keep the changes this time around instead
		 * of rolling back, because we'll apply the new server-verified values
		 * right after anyway. */
		/* FIXME: splitscreen */
		if (pl.entnum == player_localentnum) {
			/* FIXME: splitscreen */
			pSeat = &g_seats[0];

			for (int i = pl.sequence+1; i <= servercommandframe; i++) {
				/* ...maybe the input state is too old? */
				if (!getinputstate(i)) {
					break;
				}
				input_sequence = i;
				PMove_Run();
			}

			/* any differences in things that are read below are now
			 * officially from prediction misses. */
		}
	}

	/* seed for our prediction table */
	pl.sequence = servercommandframe;

	fl = readfloat();

	/* HACK: we need to make this more reliable */
	if (fl == UPDATE_ALL) {
		/* we respawned */
		pl.gravity = __NULL__;
	}

	if (fl & PLAYER_MODELINDEX)
		pl.modelindex = readshort();

	if (fl & PLAYER_ORIGIN) {
		pl.origin[0] = readcoord();
		pl.origin[1] = readcoord();
	}

	if (fl & PLAYER_ORIGIN_Z)
		pl.origin[2] = readcoord();
	if (fl & PLAYER_ANGLES_X)
		pl.pitch = readfloat();
	if (fl & PLAYER_ANGLES_Y)
		pl.angles[1] = readfloat();
	if (fl & PLAYER_ANGLES_Z)
		pl.angles[2] = readfloat();

	if (fl & PLAYER_VELOCITY) {
		pl.velocity[0] = readcoord();
		pl.velocity[1] = readcoord();
	}

	if (fl & PLAYER_VELOCITY_Z)
		pl.velocity[2] = readcoord();
	if (fl & PLAYER_FLAGS) {
		pl.flags = readfloat();
		pl.gflags = readfloat();
	}
	if (fl & PLAYER_WEAPON)
		pl.activeweapon = readbyte();
	if (fl & PLAYER_ITEMS)
		pl.g_items = (__variant)readfloat();
	if (fl & PLAYER_HEALTH)
		pl.health = readbyte();
	if (fl & PLAYER_ARMOR)
		pl.armor = readbyte();
	if (fl & PLAYER_MOVETYPE)
		pl.movetype = readbyte();
	if (fl & PLAYER_VIEWOFS)
		pl.view_ofs[2] = readfloat();
	if (fl & PLAYER_BASEFRAME)
		pl.baseframe = readbyte();
	if (fl & PLAYER_FRAME) {
		pl.frame = readbyte();
		pl.frame1time = 0.0f;
		pl.frame2time = 0.0f;
	}
	if (fl & PLAYER_AMMO1)
		pl.a_ammo1 = readbyte();
	if (fl & PLAYER_AMMO2)
		pl.a_ammo2 = readbyte();
	if (fl & PLAYER_AMMO3)
		pl.a_ammo3 = readbyte();


	// <WatIs>
	if (fl & PLAYER_CSSHOT)
		pl.scma_shotmultiplier = readbyte();
	if (fl & PLAYER_CSSHOTTIME)
		pl.scma_shottime = readfloat();
	
	// </SCMA>

	setorigin(pl, pl.origin);
}
