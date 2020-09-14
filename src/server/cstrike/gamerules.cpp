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

var int autocvar_sv_playerkeepalive = TRUE;

void
CSGameRules::PlayerDeath(base_player pl)
{
}

void
CSGameRules::PlayerPain(base_player pl)
{
}

int
CSGameRules::BuyingPossible(base_player pl)
{
	return FALSE;
}

/* we check what fields have changed over the course of the frame and network
 * only the ones that have actually changed */
void
CSGameRules::PlayerPostFrame(base_player pp)
{
	player pl = (player)pp;

	Animation_PlayerUpdate();

	if (autocvar_sv_playerkeepalive)
		pl.SendFlags |= PLAYER_KEEPALIVE;

	if (pl.old_modelindex != pl.modelindex)
		pl.SendFlags |= PLAYER_MODELINDEX;

	if (pl.old_origin[0] != pl.origin[0])
		pl.SendFlags |= PLAYER_ORIGIN;

	if (pl.old_origin[1] != pl.origin[1])
		pl.SendFlags |= PLAYER_ORIGIN;

	if (pl.old_origin[2] != pl.origin[2])
		pl.SendFlags |= PLAYER_ORIGIN_Z;

	if (pl.old_angles[0] != pl.v_angle[0])
		pl.SendFlags |= PLAYER_ANGLES_X;

	if (pl.old_angles[1] != pl.angles[1])
		pl.SendFlags |= PLAYER_ANGLES_Y;

	if (pl.old_angles[2] != pl.angles[2])
		pl.SendFlags |= PLAYER_ANGLES_Z;

	if (pl.old_velocity[0] != pl.velocity[0])
		pl.SendFlags |= PLAYER_VELOCITY;

	if (pl.old_velocity[1] != pl.velocity[1])
		pl.SendFlags |= PLAYER_VELOCITY;

	if (pl.old_velocity[2] != pl.velocity[2])
		pl.SendFlags |= PLAYER_VELOCITY_Z;

	if (pl.old_flags != pl.flags)
		pl.SendFlags |= PLAYER_FLAGS;

	if (pl.old_activeweapon != pl.activeweapon)
		pl.SendFlags |= PLAYER_WEAPON;

	if (pl.old_items != pl.g_items)
		pl.SendFlags |= PLAYER_ITEMS;

	if (pl.old_health != pl.health)
		pl.SendFlags |= PLAYER_HEALTH;

	if (pl.old_armor != pl.armor)
		pl.SendFlags |= PLAYER_ARMOR;

	if (pl.old_movetype != pl.movetype)
		pl.SendFlags |= PLAYER_MOVETYPE;

	if (pl.old_viewofs != pl.view_ofs[2])
		pl.SendFlags |= PLAYER_VIEWOFS;

	if (pl.old_baseframe != pl.baseframe)
		pl.SendFlags |= PLAYER_BASEFRAME;

	if (pl.old_frame != pl.frame)
		pl.SendFlags |= PLAYER_FRAME;

	if (pl.old_a_ammo1 != pl.a_ammo1)
		pl.SendFlags |= PLAYER_AMMO1;

	if (pl.old_a_ammo2 != pl.a_ammo2)
		pl.SendFlags |= PLAYER_AMMO2;

	if (pl.old_a_ammo3 != pl.a_ammo3)
		pl.SendFlags |= PLAYER_AMMO3;

	pl.old_modelindex = pl.modelindex;
	pl.old_origin = pl.origin;
	pl.old_angles = pl.angles;
	pl.old_angles[0] = pl.v_angle[0];
	pl.old_velocity = pl.velocity;
	pl.old_flags = pl.flags;
	pl.old_activeweapon = pl.activeweapon;
	pl.old_items = pl.g_items;
	pl.old_health = pl.health;
	pl.old_armor = pl.armor;
	pl.old_movetype = pl.movetype;
	pl.old_viewofs = pl.view_ofs[2];
	pl.old_baseframe = pl.baseframe;
	pl.old_frame = pl.frame;
	pl.old_a_ammo1 = pl.a_ammo1;
	pl.old_a_ammo2 = pl.a_ammo2;
	pl.old_a_ammo3 = pl.a_ammo3;
	pl.old_cs_shotmultiplier = pl.cs_shotmultiplier;
	pl.old_cs_shottime = pl.cs_shottime;

	if (g_cs_gamestate != GAME_FREEZE) {
		if (pl.progress <= 0.0f)
			pl.flags &= ~FL_FROZEN;
	} 
}

void
CSGameRules::LevelDecodeParms(base_player pp)
{
	player pl = (player)pp;
	g_landmarkpos[0] = parm1;
	g_landmarkpos[1] = parm2;
	g_landmarkpos[2] = parm3;
	pl.angles[0] = parm4;
	pl.angles[1] = parm5;
	pl.angles[2] = parm6;
	pl.velocity[0] = parm7;
	pl.velocity[1] = parm8;
	pl.velocity[2] = parm9;
	pl.g_items = parm10;
	pl.activeweapon = parm11;
	pl.flags = parm64;

	pl.ammo_50ae = parm12;
	pl.ammo_762mm = parm13;
	pl.ammo_556mm = parm14;
	pl.ammo_556mmbox = parm15;
	pl.ammo_338mag = parm16;
	pl.ammo_9mm = parm17;
	pl.ammo_buckshot = parm18;
	pl.ammo_45acp = parm19;
	pl.ammo_357sig = parm20;
	pl.ammo_57mm = parm21;
	pl.ammo_hegrenade = parm22;
	pl.ammo_fbgrenade = parm23;
	pl.ammo_smokegrenade = parm24;
	pl.usp45_mag = parm25;
	pl.glock18_mag = parm26;
	pl.deagle_mag = parm27;
	pl.p228_mag = parm28;
	pl.elites_mag = parm29;
	pl.fiveseven_mag = parm30;
	pl.m3_mag = parm31;
	pl.xm1014_mag = parm32;
	pl.mp5_mag = parm33;
	pl.p90_mag = parm34;
	pl.ump45_mag = parm35;
	pl.mac10_mag = parm36;
	pl.tmp_mag = parm37;
	pl.ak47_mag = parm38;
	pl.sg552_mag = parm39;
	pl.m4a1_mag = parm40;
	pl.aug_mag = parm41;
	pl.scout_mag = parm42;
	pl.awp_mag = parm43;
	pl.g3sg1_mag = parm44;
	pl.sg550_mag = parm45;
	pl.para_mag = parm46;

	if (pl.flags & FL_CROUCHING) {
		setsize(pl, VEC_CHULL_MIN, VEC_CHULL_MAX);
	} else {
		setsize(pl, VEC_HULL_MIN, VEC_HULL_MAX);
	}
}

void
CSGameRules::LevelChangeParms(base_player pp)
{
	player pl = (player)pp;
	parm1 = g_landmarkpos[0];
	parm2 = g_landmarkpos[1];
	parm3 = g_landmarkpos[2];
	parm4 = pl.angles[0];
	parm5 = pl.angles[1];
	parm6 = pl.angles[2];
	parm7 = pl.velocity[0];
	parm8 = pl.velocity[1];
	parm9 = pl.velocity[2];
	parm64 = pl.flags;
	parm10 = pl.g_items;
	parm11 = pl.activeweapon;

	parm12 = pl.ammo_50ae;
	parm13 = pl.ammo_762mm;
	parm14 = pl.ammo_556mm;
	parm15 = pl.ammo_556mmbox;
	parm16 = pl.ammo_338mag;
	parm17 = pl.ammo_9mm;
	parm18 = pl.ammo_buckshot;
	parm19 = pl.ammo_45acp;
	parm20 = pl.ammo_357sig;
	parm21 = pl.ammo_57mm;
	parm22 = pl.ammo_hegrenade;
	parm23 = pl.ammo_fbgrenade;
	parm24 = pl.ammo_smokegrenade;
	parm25 = pl.usp45_mag;
	parm26 = pl.glock18_mag;
	parm27 = pl.deagle_mag;
	parm28 = pl.p228_mag;
	parm29 = pl.elites_mag;
	parm30 = pl.fiveseven_mag;
	parm31 = pl.m3_mag;
	parm32 = pl.xm1014_mag;
	parm33 = pl.mp5_mag;
	parm34 = pl.p90_mag;
	parm35 = pl.ump45_mag;
	parm36 = pl.mac10_mag;
	parm37 = pl.tmp_mag;
	parm38 = pl.ak47_mag;
	parm39 = pl.sg552_mag;
	parm40 = pl.m4a1_mag;
	parm41 = pl.aug_mag;
	parm42 = pl.scout_mag;
	parm43 = pl.awp_mag;
	parm44 = pl.g3sg1_mag;
	parm45 = pl.sg550_mag;
	parm46 = pl.para_mag;
}

void
CSGameRules::LevelNewParms(void)
{
	parm1 = parm2 = parm3 = parm4 = parm5 = parm6 = parm7 =
	parm8 = parm9 = parm10 = parm11 = parm12 = parm13 = parm14 =
	parm15 = parm16 = parm17 = parm18 = parm19 = parm20 = parm21 =
	parm22 = parm23 = parm24 = parm25 = parm26 = parm27 = parm28 =
	parm29 = parm30 = parm31 = parm32 = parm33 = parm34 = parm35 =
	parm36 = parm37 = parm38 = parm39 = parm40 = parm41 = parm42 =
	parm43 = parm44 = parm45 = parm46 = 0;
	parm64 = FL_CLIENT;
}

void
CSGameRules::PlayerConnect(entity pl)
{
	entity a;
	bprint(PRINT_HIGH, sprintf("%s connected\n", pl.netname));

	int playercount = 0;
	for (a = world; (a = find(a, ::classname, "player"));) {
		playercount++;
	}

	/* we're the first. respawn all entities? */
	if (playercount == 0) {
		for (a = world; (a = findfloat(a, ::gflags, GF_CANRESPAWN));) {
			CBaseEntity caw = (CBaseEntity)a;
			caw.Respawn();
		}
		Nodes_Init();
	}
}

void
CSGameRules::PlayerDisconnect(entity pl)
{
	bprint(PRINT_HIGH, sprintf("%s disconnected\n", pl.netname));

	/* Make this unusable */
	pl.solid = SOLID_NOT;
	pl.movetype = MOVETYPE_NONE;
	pl.modelindex = 0;
	pl.health = 0;
	pl.takedamage = 0;
	pl.SendFlags = PLAYER_MODELINDEX;
}

void
CSGameRules::PlayerKill(base_player pl)
{
	Damage_Apply(pl, pl, pl.health, WEAPON_NONE, DMG_SKIP_ARMOR);
}
