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

typedef struct waypoint_s
{
	vector vecOrigin;
	float flRadius;	 /* used for picking the closest waypoint. aka proximity weight. also relaxes routes inside the area. */
	struct wpneighbour_s
	{
		int node;
		float linkcost;
		int iFlags;
	} *neighbour;
	int iNeighbours;
} waypoint_t;

static waypoint_t *g_pWaypoints;
static int g_iWaypoints;

static void
Way_WipeWaypoints(void)
{
	for (int i = 0; i < g_iWaypoints; i++) {
		memfree(g_pWaypoints[i].neighbour);
	}

	memfree(g_pWaypoints);
	g_iWaypoints = 0;
}

void
Way_DumpWaypoints(string filename)
{
	filestream file = fopen(filename, FILE_WRITE);

	if (file < 0) {
		print("RT_DumpWaypoints: unable to open ", filename, "\n");
		return;
	}

	fputs(file, sprintf("%i\n", g_iWaypoints));

	for (int i = 0i; i < g_iWaypoints; i++) {
		fputs(file, sprintf("%v %f %i\n", g_pWaypoints[i].vecOrigin, g_pWaypoints[i].flRadius, g_pWaypoints[i].iNeighbours));
		
		for(int j = 0i; j < g_pWaypoints[i].iNeighbours; j++) {
			fputs(file, sprintf(" %i %f %x\n", g_pWaypoints[i].neighbour[j].node, g_pWaypoints[i].neighbour[j].linkcost, (float)g_pWaypoints[i].neighbour[j].iFlags));
		}
	}

	fclose(file);
}

void
Way_ReadWaypoints(string strFile)
{
	float file = fopen(strFile, FILE_READ);
	if (file < 0) {
		print("Way_DumpWaypoints: unable to open ", strFile, "\n");
		return;
	}

	Way_WipeWaypoints();

	tokenize(fgets(file));
	g_iWaypoints = stoi(argv(0));
	g_pWaypoints = memalloc(sizeof(*g_pWaypoints) * g_iWaypoints);

	for (int i = 0i; i < g_iWaypoints; i++) {
		tokenize(fgets(file));
		g_pWaypoints[i].vecOrigin[0] = stof(argv(0));
		g_pWaypoints[i].vecOrigin[1] = stof(argv(1));
		g_pWaypoints[i].vecOrigin[2] = stof(argv(2));
		g_pWaypoints[i].flRadius = stof(argv(3));
		g_pWaypoints[i].iNeighbours = stoi(argv(4));
		g_pWaypoints[i].neighbour = memalloc(sizeof(*g_pWaypoints[i].neighbour) * g_pWaypoints[i].iNeighbours);
		
		for (int j = 0i; j < g_pWaypoints[i].iNeighbours; j++) {
			tokenize(fgets(file));
			g_pWaypoints[i].neighbour[j].node = stoi(argv(0));
			g_pWaypoints[i].neighbour[j].linkcost = stof(argv(1));
			g_pWaypoints[i].neighbour[j].iFlags = stoh(argv(2));
		}
	}
	fclose(file);
}

static void
Way_LinkWaypoints(waypoint_t *wp, waypoint_t *w2)
{
	int w2n = w2 - g_pWaypoints;

	/* don't bother if we're already linked */
	for (int i = 0i; i < wp->iNeighbours; i++) {
		if (wp->neighbour[i].node == w2n) {
			return;
		}
	}

	int idx = wp->iNeighbours++;
	wp->neighbour = memrealloc(wp->neighbour, sizeof(*wp->neighbour), idx, wp->iNeighbours);
	local struct wpneighbour_s *n = wp->neighbour+idx;
	n->node = w2n;
	n->linkcost = vlen(w2->vecOrigin - wp->vecOrigin);
	n->iFlags = 0;
}

static void
Way_AutoLink(waypoint_t *wp)
{
	int wpidx = wp-g_pWaypoints;

	for (int i = 0i; i < g_iWaypoints; i++) {
		//don't link to ourself...
		if (i == wpidx) {
			continue;
		}

		//autolink distance cutoff.
		if (vlen(wp->vecOrigin - g_pWaypoints[i].vecOrigin) > autocvar(nav_linksize, 256, "Cuttoff distance between links")) {
			continue;
		}

		//not going to use the full player size because that makes steps really messy.
		//however, we do need a little size, for sanity's sake
		tracebox(wp->vecOrigin, '-16 -16 0', '16 16 32', g_pWaypoints[i].vecOrigin, TRUE, world);

		//light of sight blocked, don't try autolinking.
		if (trace_fraction < 1) {
			continue;
		}

		Way_LinkWaypoints(wp, &g_pWaypoints[i]);
		Way_LinkWaypoints(&g_pWaypoints[i], wp);
	}
}

void
Way_Waypoint_Create(entity ePlayer, int iAutoLink)
{
	int iID = g_iWaypoints++;
	g_pWaypoints = memrealloc(g_pWaypoints, sizeof(waypoint_t), iID, g_iWaypoints);
	waypoint_t *n = g_pWaypoints + iID;
	n->vecOrigin = ePlayer.origin;
	n->neighbour = __NULL__;
	n->iNeighbours = 0;

	if (iAutoLink == 1) {
		Way_AutoLink(n);
	} else {
		if (iID != 0) {
			if (iAutoLink == 0) {
				Way_LinkWaypoints(n, &g_pWaypoints[iID-1]);
				Way_LinkWaypoints(&g_pWaypoints[iID-1], n);
			} else if (iAutoLink == -1) {
				Way_LinkWaypoints(&g_pWaypoints[iID-1], n);
			} else if (iAutoLink == -2) {
				Way_LinkWaypoints(n, &g_pWaypoints[iID-1]);
			}
		}
	}
}

void
Way_Waypoint_CreateSpawns()
{
	for (entity a = world; (a = find(a, ::classname, "info_player_deathmatch"));) {
		Way_Waypoint_Create(a, TRUE);
	}
}

void
Way_Waypoint_Delete(int iID)
{
	if (iID < 0i || iID >= g_iWaypoints) {
		print("RT_DeleteWaypoint: invalid waypoint\n");
		return;
	}

	//wipe the waypoint
	memfree(g_pWaypoints[iID].neighbour);
	memcpy(g_pWaypoints + iID, g_pWaypoints + iID + 1, (g_iWaypoints - (iID + 1)) * sizeof(*g_pWaypoints));
	g_iWaypoints--;

	//clean up any links to it.
	for (int i = 0; i < g_iWaypoints; i++) {
		for (int j = 0; j < g_pWaypoints[i].iNeighbours;) {
			int l = g_pWaypoints[i].neighbour[j].node;
			if (l == iID) {
				memcpy(g_pWaypoints[i].neighbour+j, g_pWaypoints[i].neighbour+j+1, (g_pWaypoints[i].iNeighbours-(j+1))*sizeof(*g_pWaypoints[i].neighbour));
				g_pWaypoints[i].iNeighbours--;
				continue;
			} else if (l > iID) {
				g_pWaypoints[i].neighbour[j].node = l-1;
			}
			j++;
		}
	}
}

void
Way_Waypoint_SetRadius(int iID, float flRadValue)
{
	if (iID < 0i || iID >= g_iWaypoints) {
		print("RT_Waypoint_SetRadius: invalid waypoint\n");
		return;
	}
	g_pWaypoints[iID].flRadius = flRadValue;
}

int
Way_FindClosestWaypoint(vector vecOrigin)
{
	
	/* -1 for no nodes anywhere... */
	int r = -1i;
	float flBestDist = COST_INFINITE;

	for (int i = 0i; i < g_iWaypoints; i++) {
		float fDist = vlen(g_pWaypoints[i].vecOrigin - vecOrigin) - g_pWaypoints[i].flRadius;
		if (fDist < flBestDist) {
			/* within the waypoint's radius */
			if (fDist < 0) {
				flBestDist = fDist;
				r = i;
			} else {
				/* outside the waypoint, make sure its valid. */
				traceline(vecOrigin, g_pWaypoints[i].vecOrigin, TRUE, world);
				if (trace_fraction == 1) {
					/* FIXME: sort them frst, to avoid traces? */
					flBestDist = fDist;
					r = i;
				}
			}
		}
	}
	return r;
}

void
Way_Waypoint_LinkJump(void)
{
	static int waylink_status;
	static int way1, way2;
	
	if (waylink_status == 0) {
		way1 = Way_FindClosestWaypoint(self.origin);
		waylink_status = 1;
		centerprint(self, "Selected first waypoint!\n");
	} else if (waylink_status == 1) {
		way2 = Way_FindClosestWaypoint(self.origin);
		waylink_status = 0;

		if (way1 != way2) {
			for (int b = 0i; b < g_pWaypoints[way1].iNeighbours; b++) {
				if (g_pWaypoints[way1].neighbour[b].node == way2) {
					g_pWaypoints[way1].neighbour[b].iFlags |= LF_JUMP;
					env_message_single(self, "Jump-linked the two points!\n");
				}
			}
		} else {
			centerprint(self, "Failed to link, the two points are the same!\n");
		}
	}
}

void
Way_Waypoint_LinkCrouch(void)
{
	static int waylink_status;
	static int way1, way2;
	
	if (waylink_status == 0) {
		way1 = Way_FindClosestWaypoint(self.origin);
		waylink_status = 1;
		centerprint(self, "Selected first waypoint!\n");
	} else if (waylink_status == 1) {
		way2 = Way_FindClosestWaypoint(self.origin);
		waylink_status = 0;

		if (way1 != way2) {
			for (int b = 0i; b < g_pWaypoints[way1].iNeighbours; b++) {
				if (g_pWaypoints[way1].neighbour[b].node == way2) {
					g_pWaypoints[way1].neighbour[b].iFlags |= LF_CROUCH;
					env_message_single(self, "Crouch-linked the two points!\n");
				}
			}
		} else {
			centerprint(self, "Failed to link, the two points are the same!\n");
		}
	}
}

void
Way_Waypoint_LinkWalk(void)
{
	static int waylink_status;
	static int way1, way2;
	
	if (waylink_status == 0) {
		way1 = Way_FindClosestWaypoint(self.origin);
		waylink_status = 1;
		env_message_single(self, "Selected first waypoint!\n");
	} else if (waylink_status == 1) {
		way2 = Way_FindClosestWaypoint(self.origin);
		waylink_status = 0;

		if (way1 != way2) {
			for (int b = 0i; b < g_pWaypoints[way1].iNeighbours; b++) {
				if (g_pWaypoints[way1].neighbour[b].node == way2) {
					g_pWaypoints[way1].neighbour[b].iFlags |= LF_WALK;
					env_message_single(self, "Walk-linked the two points!\n");
				}
			}
		} else {
			env_message_single(self, "Failed to link, the two points are the same!\n");
		}
	}
}

void
Way_GoToPoint(entity pl)
{
	vector vecSrc;
	makevectors(pl.v_angle);
	vecSrc = pl.origin + pl.view_ofs;
	traceline(vecSrc, vecSrc + (v_forward * 4096), FALSE, pl);
	print(sprintf("Telling all bots to go to %v\n", trace_endpos));

	for (entity a = world; ( a = find( a, classname, "player" ) ); ) {
		if ( clienttype(a) != CLIENTTYPE_REAL ) {
			bot targ;
			targ = (bot)a;
			targ.RouteClear();
			route_calculate(targ, pl.origin, 0, Bot_RouteCB);
			print(sprintf("Told bot to go to %v\n", trace_endpos));
		}
	}
}

void
Way_DrawDebugInfo(void)
{
	if (!g_iWaypoints) {
		return;
	}

	int iNearest = Way_FindClosestWaypoint(self.origin);
	makevectors(self.v_angle);
	R_BeginPolygon("textures/dev/info_node", 0, 0);
	
	for (int i = 0i; i < g_iWaypoints; i++) {
		waypoint_t *w = g_pWaypoints + i;
		vector org = w->vecOrigin;
		vector rgb = [1,1,1];

		if (iNearest == i) {
			rgb = [0,1,0];
		}

		R_PolygonVertex(org + v_right * 8 - v_up * 8, '1 1', rgb, 1);
		R_PolygonVertex(org - v_right * 8 - v_up * 8, '0 1', rgb, 1);
		R_PolygonVertex(org - v_right * 8 + v_up * 8, [0,0], rgb,  1);
		R_PolygonVertex(org + v_right * 8 + v_up * 8, '1 0', rgb, 1);
		R_EndPolygon();
	}
	
	R_BeginPolygon("", 0, 0);
	for (int i = 0i; i < g_iWaypoints; i++) {
		waypoint_t *w = g_pWaypoints + i;
		vector org = w->vecOrigin;

		for(int j = 0; j < 16; j++) {
			float theta = 2.0f * M_PI * j / 16;
			R_PolygonVertex(org + [sin(theta), cos(theta)]*w->flRadius, '1 1', '0 0.25 0', 1);

		}
		R_EndPolygon();
	}

	R_BeginPolygon("", 1, 0);
	
	for (int i = 0i; i < g_iWaypoints; i++) {
		waypoint_t *w = g_pWaypoints+i;
		vector org = w->vecOrigin;
		vector rgb = [1,1,1];

		for (int j = 0i; j < w->iNeighbours; j++) {
			int k = w->neighbour[j].node;
			int fl = w->neighbour[j].iFlags;

			if (k < 0i || k >= g_iWaypoints) {
				break;
			}

			waypoint_t *w2 = &g_pWaypoints[k];

			if (fl & LF_JUMP) {
				vector middle;
				middle = (w2->vecOrigin + org) / 2;
				R_PolygonVertex(org + [0,0,1], [0,1], [1,1,0], 1);
				R_PolygonVertex(middle + [0,0,32], [0,1], [0.5,0.5,0], 1);
				R_EndPolygon();
				R_PolygonVertex(middle + [0,0,32], [0,1], [0.5,0.5,0], 1);
				R_PolygonVertex(w2->vecOrigin + [0,0,1], [1,1], [0,0,0], 1);
				R_EndPolygon();
			}

			if (fl & LF_CROUCH) {
				R_PolygonVertex(org + [0,0,-1], [0,1], [0,0,1], 1);
				R_PolygonVertex(w2->vecOrigin + [0,0,-1], [1,1], [0,0,1], 1);
				R_EndPolygon();
			}

			R_PolygonVertex(org, [0,1], [1,0,1], 1);
			R_PolygonVertex(w2->vecOrigin, [1,1], [0,1,0], 1);
			R_EndPolygon();
		}
	}
}

void
Way_ConnectOne(void)
{
	static int waylink_status;
	static int way1, way2;
	
	if (waylink_status == 0) {
		way1 = Way_FindClosestWaypoint(self.origin);
		waylink_status = 1;
		env_message_single(self, "Selected first waypoint!\n");
	} else if (waylink_status == 1) {
		way2 = Way_FindClosestWaypoint(self.origin);
		waylink_status = 0;

		if (way1 != way2) {
			Way_LinkWaypoints(&g_pWaypoints[way1], &g_pWaypoints[way2]);
			env_message_single(self, "Linked first waypoint with second waypoint!\n");
		} else {
			env_message_single(self, "Failed to link, the two points are the same!\n");
		}
	}
}

void
Way_ConnectTwo(void)
{
	static int waylink_status;
	static int way1, way2;
	
	if (waylink_status == 0) {
		way1 = Way_FindClosestWaypoint(self.origin);
		waylink_status = 1;
		env_message_single(self, "Selected first waypoint!\n");
	} else if (waylink_status == 1) {
		way2 = Way_FindClosestWaypoint(self.origin);
		waylink_status = 0;

		if (way1 != way2) {
			Way_LinkWaypoints(&g_pWaypoints[way1], &g_pWaypoints[way2]);
			Way_LinkWaypoints(&g_pWaypoints[way2], &g_pWaypoints[way1]);
			env_message_single(self, "Linked first waypoint with second waypoint!\n");
		} else {
			env_message_single(self, "Failed to link, the two points are the same!\n");
		}
	}
}

void
Way_RadiusDefaults(void)
{
	for (int i = 0i; i < g_iWaypoints; i++) {
		g_pWaypoints[i].flRadius = 48;
	}
}

void
Way_ConnectAuto(void)
{
	Way_AutoLink(Way_FindClosestWaypoint(self.origin));
}

void
Way_Purge(void)
{
	Way_WipeWaypoints();
}

void
Way_Cmd(void)
{
	if (!self) {
		return;
	}

	switch (argv(1)) {
	case "goto":
		Way_GoToPoint( self );
		break;
	case "autolink":
		Way_ConnectAuto();
		break;
	case "connect1":
		Way_ConnectOne();
		break;
	case "connect2":
		Way_ConnectTwo();
		break;
	case "add":
		Way_Waypoint_Create( self, 1 );
		break;
	case "addchain":
		Way_Waypoint_Create( self, 0 );
		break;
	case "addsingle":
		Way_Waypoint_Create( self, -3 );
		break;
	case "addltn":
		Way_Waypoint_Create( self, -1 );
		break;
	case "addntl":
		Way_Waypoint_Create( self, -2 );
		break;
	case "addspawns":
		Way_Waypoint_CreateSpawns();
		break;
	case "delete":
		Way_Waypoint_Delete( Way_FindClosestWaypoint( self.origin ) );
		break;
	case "purge":
		Way_Purge();
		break;
	case "radius":
		Way_Waypoint_SetRadius( Way_FindClosestWaypoint( self.origin ), stof( argv( 2 ) ) );
		break;
	case "radiushack":
		Way_RadiusDefaults();
		break;
	case "linkjump":
		Way_Waypoint_LinkJump();
		break;
	case "linkcrouch":
		Way_Waypoint_LinkCrouch();
		break;
	case "linkwalk":
		Way_Waypoint_LinkWalk();
		break;
	case "save":
		Way_DumpWaypoints( argv( 2 ) );
		break;
	case "load":
		Way_ReadWaypoints( argv( 2 ) );
		break;
	}
}
