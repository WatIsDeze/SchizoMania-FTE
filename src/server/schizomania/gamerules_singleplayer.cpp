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
HLSingleplayerRules::PlayerDeath(base_player pl)
{
	/* obituary networking */
	WriteByte(MSG_MULTICAST, SVC_CGAMEPACKET);
	WriteByte(MSG_MULTICAST, EV_OBITUARY);
	if (g_dmg_eAttacker.netname)
		WriteString(MSG_MULTICAST, g_dmg_eAttacker.netname);
	else
		WriteString(MSG_MULTICAST, g_dmg_eAttacker.classname);
	WriteString(MSG_MULTICAST, pl.netname);
	WriteByte(MSG_MULTICAST, g_dmg_iWeapon);
	WriteByte(MSG_MULTICAST, 0);
	msg_entity = world;
	multicast([0,0,0], MULTICAST_ALL);

	/* death-counter */
	pl.deaths++;
	forceinfokey(pl, "*deaths", ftos(pl.deaths));

	/* update score-counter */
	if (pl.flags & FL_CLIENT || pl.flags & FL_MONSTER)
	if (g_dmg_eAttacker.flags & FL_CLIENT) {
		if (pl == g_dmg_eAttacker)
			g_dmg_eAttacker.frags--;
		else
			g_dmg_eAttacker.frags++;
	}

	/* in DM we only care about the frags */
	if (cvar("mp_fraglimit"))
	if (g_dmg_eAttacker.frags >= cvar("mp_fraglimit")) {
		IntermissionStart();
	}

	weaponbox_spawn((player)pl);
	pl.movetype = MOVETYPE_NONE;
	pl.solid = SOLID_NOT;
	pl.takedamage = DAMAGE_NO;
	pl.flags &= ~FL_FLASHLIGHT;
	pl.armor = pl.activeweapon = pl.g_items = pl.weapon = 0;
	pl.health = 0;
	Sound_Play(pl, CHAN_AUTO, "player.die");

	// For now automatically respawn. (Later on we'll restart the map.)
	pl.think = PutClientInServer;
	pl.nextthink = time + 4.0f;

	if (pl.health < -50) {
		pl.health = 0;
		FX_GibHuman(pl.origin);
		return;
	}

	pl.health = 0;

	/* Let's handle corpses on the clientside */
	entity corpse = spawn();
	setorigin(corpse, pl.origin + [0,0,32]);
	setmodel(corpse, pl.model);
	setsize(corpse, VEC_HULL_MIN, VEC_HULL_MAX);
	corpse.movetype = MOVETYPE_TOSS;
	corpse.solid = SOLID_TRIGGER;
	corpse.modelindex = pl.modelindex;
	corpse.frame = ANIM_DIESIMPLE;
	corpse.angles = pl.angles;
	corpse.velocity = pl.velocity;
}

/*
============================
SpawnInGamePlayer

Spawn the client's player entity.
============================
*/
void
HLSingleplayerRules::SpawnInGamePlayer(base_player pp) {
	// Cast.
	player pl = (player)pp;
	
	pl.classname = "player";
	pl.health = pl.max_health = 100;
	pl.takedamage = DAMAGE_YES;
	pl.solid = SOLID_SLIDEBOX;
	pl.movetype = MOVETYPE_WALK;
	pl.flags = FL_CLIENT;
	pl.viewzoom = 1.0;
	pl.model = "models/player.mdl";
	string mymodel = infokey(pl, "model");

	if (mymodel) {
		mymodel = sprintf("models/player/%s/%s.mdl", mymodel, mymodel);
		if (whichpack(mymodel)) {
			pl.model = mymodel;
		}
	}
	setmodel(pl, pl.model);

	setsize(pl, VEC_HULL_MIN, VEC_HULL_MAX);
	pl.view_ofs = VEC_PLAYER_VIEWPOS;
	pl.velocity = [0,0,0];
	pl.gravity = __NULL__;
	pl.frame = 1;
	pl.SendEntity = Player_SendEntity;
	pl.SendFlags = UPDATE_ALL;
	pl.customphysics = Empty;
	pl.iBleeds = TRUE;
	forceinfokey(pl, "*spec", "0");
	forceinfokey(pl, "*deaths", ftos(pl.deaths));

	// Setp new level params and decode em.
	LevelNewParms();
	LevelDecodeParms(pl);
	pl.g_items = ITEM_CROWBAR | ITEM_GLOCK | ITEM_SUIT;
	pl.activeweapon = WEAPON_GLOCK;
	pl.glock_mag = 18;
	pl.ammo_9mm = 44;

	/* this is where the mods want to deviate */
	entity spot;

	if (startspot != "") {
		dprint(sprintf("^3Gamerules_Spawn^7: Startspot is %s\n", startspot));
		LevelDecodeParms(pl);
		setorigin(pl, Landmark_GetSpot());
	} else {
		LevelNewParms();
		spot = find(world, ::classname, "info_player_start");
		setorigin(pl, spot.origin);
		pl.angles = spot.angles;
	}

	Weapons_RefreshAmmo(pl);
	Client_FixAngle(pl, pl.angles);
}

/*
============================
SpawnInMenuCameraPlayer

Spawn the client's camera player entity, used for the mainmenu where we
don't want the player to use userinput.
============================
*/
void
HLSingleplayerRules::SpawnInMenuCameraPlayer(base_player pp, entity eMainmenu) {
	// Cast.
	player pl = (player)pp;

	pl.classname = "spectator";
	pl.health = 0;
	pl.armor = 0;
	pl.takedamage = DAMAGE_NO;
	pl.solid = SOLID_NOT;
	pl.movetype = MOVETYPE_NONE;
	pl.SendEntity = Player_SendEntity;
	pl.flags = FL_CLIENT;
	pl.weapon = 0;
	pl.viewzoom = 1.0f;
	pl.model = 0;
	pl.gravity = __NULL__;
	setsize (pl, [-16,-16,-16], [16,16,16]);
	pl.view_ofs = pl.velocity = [0,0,0];

	// Ensure empty inventory.
	pl.items = 0x0;
	pl.activeweapon = 0;

	// Set the origin of the player at the menu entity.
	setorigin(pl, eMainmenu.origin);
	
	// Find the mainmenu camera its target.
	if (eMainmenu.target) {
		entity eTarget = find(world, ::targetname, eMainmenu.target);
		dprint("Found etarget\n");
		// Found the target, adjust player angles.
		if (eTarget) {
			dprint("Found etarget\n");
			pl.angles = vectoangles(eTarget.origin - eMainmenu.origin);
			//pl.angles[0] *= -1;
		}
	}

	// Fix angle.
	Client_FixAngle(pl, pl.angles);
}

/*
============================
PlayerSpawn

Determine whether to spawn the player entity, or a camera menu entity 
for use in the mainmenu.bsp map.
============================
*/
void
HLSingleplayerRules::PlayerSpawn(base_player pp)
{
	// Cast.
	player pl = (player)pp;

	// Is there a mainmenu entity?
	entity eMainmenu = find(world, ::classname, "egui_mainmenu");

	// Spawn menu if egui_mainmenu was found. Otherwise, spawn the player as per usual.
	if (eMainmenu) {
		dprint("HLSingleplayerRules::PlayerSpawn - Spawning player menu camera\n");
		SpawnInMenuCameraPlayer(pl, eMainmenu);
	} else {
		dprint("HLSingleplayerRules::PlayerSpawn - Spawning player entity.\n");
		SpawnInGamePlayer(pl);
	}
} 
