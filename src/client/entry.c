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

/* This file houses all of the callbacks and entry points the engine
   calls by itself */

void
CSQC_Init(float apilevel, string enginename, float engineversion)
{
	Sound_Init();
	pSeat = &g_seats[0];

	registercommand("getpos");
	registercommand("callvote");
	registercommand("dev_sentence");
	registercommand("titles_test");
	registercommand("vox_test");
	registercommand("+attack2");
	registercommand("-attack2");
	registercommand("+reload");
	registercommand("-reload");
	registercommand("+use");
	registercommand("-use");
	registercommand("+duck");
	registercommand("-duck");
	registercommand("vote");

	/* Requested by Slacer */
	registercommand("+zoomin");
	registercommand("-zoomin");

	registercommand("slot1");
	registercommand("slot2");
	registercommand("slot3");
	registercommand("slot4");
	registercommand("slot5");
	registercommand("slot6");
	registercommand("slot7");
	registercommand("slot8");
	registercommand("slot9");
	registercommand("slot10");
	registercommand("lastinv");
	registercommand("invnext");
	registercommand("invprev");
	registercommand("+showscores");
	registercommand("-showscores");
	registercommand("buildcubemaps");
	registercommand("_fnchat_msg");
	registercommand("dev_sunpos");
	registercommand("dev_measure");
	registercommand("way_menu");

	// precache_model("sprites/muzzleflash1.spr");
	// precache_model("sprites/muzzleflash2.spr");
	// precache_model("sprites/muzzleflash3.spr");
	precache_model("models/weapons/muzzleflashes/muzzleflash1.vvm");
	precache_model("models/weapons/shells/small.vvm");

	/* VOX */
	Vox_Init();

	/* VGUI */
	VGUI_Init();

	/* Game specific inits */
	Client_Init(apilevel, enginename, engineversion);
	DSP_Init();
	CSQC_RendererRestarted("init");
	Titles_Init();
	Sentences_Init();
	Decals_Init();
	Way_Init();
}

/* Rendering Caches */
void
CSQC_RendererRestarted(string rstr)
{
	/* Fonts */
	FONT_16 = loadfont("16", "fonts/default", "16", -1);
	FONT_20 = loadfont("cr", "creditsfont?fmt=h", "20", -1);
	FONT_CON = loadfont("font", "", "12", -1);
	drawfont = FONT_CON;

	/* Particles */
	PART_DUSTMOTE = particleeffectnum("volume.dustmote");

	/* 2D Pics */
	precache_pic("gfx/vgui/icntlk_sv");
	precache_pic("gfx/vgui/icntlk_pl");

	/* View */
	Items_Init();
	Weapons_Init();
	Scores_Init();
	View_Init();
	Game_RendererRestarted(rstr);
	HUD_Init();

	/* GS-Entbase */
	Fade_Init();
	Sky_Update();
	Decal_Reload();
	FX_Init();
}

/* this is so that profile_csqc reports more accurate statistics as to
   what causes computation time */
void
CSQC_RenderScene(void)
{
	renderscene();
}

void
CSQC_UpdateView(float w, float h, float focus)
{
	player pl;
	int s;

	if (w == 0 || h == 0) {
		return;
	} else {
		/* First time we can effectively call VGUI
		*  because until now we don't know the video res.
		*/
		if (!video_res[0] && !video_res[1]) {
			video_res[0] = w;
			video_res[1] = h;
			Client_InitDone();
		}
	}

	/* While the init above may have already happened,
	   people are able to resize windows dynamically too. */
	video_res[0] = w;
	video_res[1] = h;

	cvar_set("_background", serverkey("background"));

	if (serverkeyfloat("background") == 1) {
		setpause(FALSE);
	}

	if (g_iCubeProcess == TRUE) {
		clearscene();
		setproperty(VF_DRAWWORLD, TRUE);
		setproperty(VF_DRAWENGINESBAR, FALSE);
		setproperty(VF_DRAWCROSSHAIR, FALSE);
		setproperty(VF_ENVMAP, "$whiteimage");
		setproperty(VF_ORIGIN, g_vecCubePos);
		setproperty(VF_AFOV, 90);
		SkyCamera_Setup(g_vecCubePos);
		renderscene();
		return;
	}

	clearscene();
	setproperty(VF_DRAWENGINESBAR, 0);
	setproperty(VF_DRAWCROSSHAIR, 0);

	//just in case...
	if (numclientseats > g_seats.length) {
		numclientseats = g_seats.length;
	}

	for (s = g_seats.length; s-- > numclientseats;) {
		pSeat = &g_seats[s];
		pSeat->m_ePlayer = world;
	}

	for (s = numclientseats; s-- > 0;) {
		pSeat = &g_seats[s];

		View_CalcViewport(s, w, h);
		setproperty(VF_ACTIVESEAT, (float)s);

		setproperty(VF_MIN, video_mins);
		setproperty(VF_SIZE, video_res);

		pSeat->m_ePlayer = self = findfloat(world, entnum, player_localentnum);

		if (!self) {
			continue;
		}

		pl = (player)self;

		Predict_PreFrame((player)self);

		pSeat->m_vecPredictedOrigin = pl.origin;
		pSeat->m_vecPredictedVelocity = pl.velocity;
		pSeat->m_flPredictedFlags = pl.flags;

		/* Don't hide the player entity */
		if (autocvar_cl_thirdperson == TRUE && pl.health) {
			setproperty(VF_VIEWENTITY, (float)0);
		} else {
			setproperty(VF_VIEWENTITY, (float)player_localentnum);
		}

		float oldzoom = pl.viewzoom;
		if (pl.viewzoom == 1.0f) {
			pl.viewzoom = 1.0 - (0.5 * pSeat->m_flZoomTime);

			/* +zoomin requested by Slacer */
			if (pSeat->m_iZoomed) {
				pSeat->m_flZoomTime += clframetime * 15;
			} else {
				pSeat->m_flZoomTime -= clframetime * 15;
			}
			pSeat->m_flZoomTime = bound(0, pSeat->m_flZoomTime, 1);
		}

		setproperty(VF_AFOV, cvar("fov") * pl.viewzoom);

		if (autocvar_zoom_sensitivity && pl.viewzoom < 1.0f) {
			setsensitivityscaler(pl.viewzoom * autocvar_zoom_sensitivity);
		} else {
			setsensitivityscaler(pl.viewzoom);
		}

		if (pl.viewzoom <= 0.0f) {
			setsensitivityscaler(1.0f);
		}

		pl.viewzoom = oldzoom;

		View_Stairsmooth();

		if (pSeat->m_pWeaponFX) {
			CBaseFX p = (CBaseFX)pSeat->m_pWeaponFX;
			p.Draw();
		}

		addentities(MASK_ENGINE);

		if (pSeat->m_flCameraTime > time) {
			view_angles = pSeat->m_vecCameraAngle;

			setproperty(VF_ORIGIN, pSeat->m_vecCameraOrigin);
			setproperty(VF_CL_VIEWANGLES, view_angles);
			setproperty(VF_ANGLES, view_angles);
		} else {
			if (pl.health) {
				if (autocvar_cl_thirdperson == TRUE) {
					makevectors(view_angles);
					vector vStart = [pSeat->m_vecPredictedOrigin[0], pSeat->m_vecPredictedOrigin[1], pSeat->m_vecPredictedOrigin[2] + 16] + (v_right * 4);
					vector vEnd = vStart + (v_forward * -48) + [0,0,16] + (v_right * 4);
					traceline(vStart, vEnd, FALSE, self);
					setproperty(VF_ORIGIN, trace_endpos + (v_forward * 5));
				} else {
					setproperty(VF_ORIGIN, pSeat->m_vecPredictedOrigin + pl.view_ofs);
				}
			} else {
				setproperty(VF_ORIGIN, pSeat->m_vecPredictedOrigin);
			}

			if (g_iIntermission) {
				view_angles = pSeat->m_vecCameraAngle;
				view_angles += [sin(time), sin(time * 2)] * 5;
				setproperty(VF_ORIGIN, pSeat->m_vecCameraOrigin);
				setproperty(VF_CL_VIEWANGLES, view_angles);
			}
			if (pSeat->m_flShakeDuration > 0.0) {
				vector vecShake = [0,0,0];
				vecShake[0] += random() * 3;
				vecShake[1] += random() * 3;
				vecShake[2] += random() * 3;
				pl.punchangle += (vecShake * pSeat->m_flShakeAmp) * (pSeat->m_flShakeDuration / pSeat->m_flShakeTime);
				pSeat->m_flShakeDuration -= clframetime;
			}
			setproperty(VF_ANGLES, view_angles + pl.punchangle);
		}

		setproperty(VF_DRAWWORLD, 1);
		SkyCamera_Setup(getproperty(VF_ORIGIN));

		/* draw the viewmodel in a second pass if desired */
		if (autocvar_r_viewmodelpass) {
			renderscene();
			clearscene();
			setproperty(VF_MIN, video_mins);
			setproperty(VF_SIZE, video_res);
			setproperty(VF_ANGLES, view_angles + pl.punchangle);
			setproperty(VF_DRAWWORLD, 0);
			setproperty(VF_AFOV, autocvar_r_viewmodelfov);
			setproperty(VF_ORIGIN, pSeat->m_vecPredictedOrigin + pl.view_ofs);
			View_DrawViewModel();
			CSQC_RenderScene();
		} else {
			View_DrawViewModel();
			CSQC_RenderScene();
		}

		RenderTarget_Monitor_Update();

		for (entity b = world; (b = findfloat(b, ::isCSQC, 1));) {
			CBaseEntity pf = (CBaseEntity) b;
			pf.postdraw();
		}

		Fade_Update((int)video_mins[0],(int)video_mins[1], (int)w, (int)h);

#if 0
		Cstrike_PostDraw((int)video_mins[0],(int)video_mins[1], (int)w, (int)h);
#endif
		View_PostDraw();

		if (g_iIntermission) {
			Scores_Draw();
		} else if (focus == TRUE) {
			GameText_Draw();
			PointMessage_Draw();

			if (getplayerkeyvalue(player_localnum, "*spec") != "0") {
				HUD_DrawSpectator();
			} else {
				HUD_Draw();
			}

			Voice_DrawHUD();
			Chat_Draw();
			Print_Draw();

			/* no prints overlapping scoreboards */
			if (pSeat->m_iScoresVisible == TRUE) {
				Scores_Draw();
			} else {
				VGUI_Draw();
				Print_DrawCenterprint();
			}
		}

		Predict_PostFrame((player)self);
	}

	DSP_UpdateListener();
	pSeat = (void*)0x70000000i;

	Vox_Update();
}

/*
=================
CSQC_InputEvent

Updates all our input related globals for use in other functions
=================
*/
float
CSQC_InputEvent(float fEventType, float fKey, float fCharacter, float fDeviceID)
{
	int s = (float)getproperty(VF_ACTIVESEAT);
	pSeat = &g_seats[s];

	switch (fEventType) {
	case IE_KEYDOWN:
		break;
	case IE_KEYUP:
		break;
	case IE_MOUSEABS:
		mouse_pos[0] = fKey;
		mouse_pos[1] = fCharacter;
		break;
	case IE_MOUSEDELTA:
		mouse_pos[0] += fKey;
		mouse_pos[1] += fCharacter;

		if (mouse_pos[0] < 0) {
			mouse_pos[0] = 0;
		} else if (mouse_pos[0] > video_res[0]) {
			mouse_pos[0] = video_res[0];
		}

		if (mouse_pos[1] < 0) {
			mouse_pos[1] = 0;
		} else if (mouse_pos[1] > video_res[1]) {
			mouse_pos[1] = video_res[1];
		}
		break;
	default:
		return TRUE;
	}

	VGUI_Input(fEventType, fKey, fCharacter, fDeviceID);

	if (g_vguiWidgetCount) {
		setcursormode(TRUE, "gfx/cursor", [0,0,0], 1.0f);
	} else {
		setcursormode(FALSE, "gfx/cursor", [0,0,0], 1.0f);
	}

	return FALSE;
}

/*
=================
CSQC_Input_Frame

Hijacks and controls what input globals are being sent to the server
=================
*/
void
CSQC_Input_Frame(void)
{
	int s = (float)getproperty(VF_ACTIVESEAT);
	pSeat = &g_seats[s];

	/* If we are inside a VGUI, don't let the client do stuff outside */
	if (g_vguiWidgetCount > 0) {
		input_impulse = 0;
		input_buttons = 0;
		return;
	}

	/* background maps have no input */
	if (serverkeyfloat("background") == 1)
		return;

	/* The HUD needs more time */
	if ((pSeat->m_iHUDWeaponSelected) && (input_buttons & INPUT_BUTTON0)) {
		HUD_DrawWeaponSelect_Trigger();
		input_buttons = 0;
		pSeat->m_flInputBlockTime = time + 0.2;
	}

	/* prevent accidental input packets */
	if (pSeat->m_flInputBlockTime > time) {
		input_impulse = 0;
		input_buttons = 0;
		return;
	}

	/* compat*/
	if (input_impulse == 201) {
		sendevent("Spraylogo", "");
	}

	if (pSeat->m_iInputAttack2 == TRUE) {
		input_buttons |= INPUT_BUTTON3;
	}

	if (pSeat->m_iInputReload == TRUE) {
		input_buttons |= INPUT_BUTTON4;
	}

	if (pSeat->m_iInputUse == TRUE) {
		input_buttons |= INPUT_BUTTON5;
	}

	if (pSeat->m_iInputDuck == TRUE) {
		input_buttons |= INPUT_BUTTON8;
	}

	if (pSeat->m_flCameraTime > time) {
		/* TODO: Supress the changing of view_angles/input_angles. */
	}
}


/*
=================
CSQC_Parse_Event

Whenever we call a SVC_CGAMEPACKET on the SSQC, this is being run
=================
*/
void
CSQC_Parse_Event(void)
{
	/* always 0, unless it was sent with a MULTICAST_ONE or MULTICAST_ONE_R to p2+ */
	int s = (float)getproperty(VF_ACTIVESEAT);
	pSeat = &g_seats[s];

	float fHeader = readbyte();

	switch (fHeader) {
	case EV_INTERMISSION:
		int cam;
		vector pos, ang;

		cam = (int)readbyte();

		if (cam) {
			ang[0] = readfloat();
			ang[1] = readfloat();
			ang[2] = readfloat();

			pos[0] = readcoord();
			pos[1] = readcoord();
			pos[2] = readcoord();
		} else {
			pos = getproperty(VF_ORIGIN);
			ang = getproperty(VF_ANGLES);
		}

		pSeat->m_vecCameraOrigin = pos;
		pSeat->m_vecCameraAngle = ang;
		g_iIntermission = TRUE;
		break;
	case EV_MUSICTRACK:
		Music_ParseTrack();
		break;
	case EV_MUSICLOOP:
		Music_ParseLoop();
		break;
	case EV_SPEAK:
		string msg;
		float pit;
		entity t = findfloat(world, entnum, readentitynum());
		msg = readstring();
		pit = readfloat();
		sound(t, CHAN_VOICE, msg, 1.0, ATTN_NORM, pit);
		break;
	case EV_SENTENCE:
		CBaseEntity_ParseSentence();
		break;
	case EV_HUDHINT:
		string hint;
		hint = readstring();
		/* TODO: Handle the event properly */
		Chat_Parse(sprintf("Hint: %s", hint));
		break;
	case EV_FADE:
		Fade_Parse();
		break;
	case EV_SPRITE:
		EnvSprite_ParseEvent();
		break;
	case EV_TEXT:
		GameText_Parse();
		break;
	case EV_MESSAGE:
		GameMessage_Parse();
		break;
	case EV_CAMERATRIGGER:
		vector cam_newpos;

		cam_newpos[0] = readcoord();
		cam_newpos[1] = readcoord();
		cam_newpos[2] = readcoord();

		pSeat->m_vecCameraAngle[0] = readcoord();
		pSeat->m_vecCameraAngle[1] = readcoord();
		pSeat->m_vecCameraAngle[2] = readcoord();

		pSeat->m_flCameraTime = time + readfloat();

		/* if the same camera as last-time (hack) is still active,
		   then make sure it becomes inactive... */
		if (pSeat->m_vecCameraOrigin == cam_newpos) {
			pSeat->m_flCameraTime = 0.0f;
		} else {
			pSeat->m_vecCameraOrigin = cam_newpos;
		}
		break;
	case EV_ANGLE:
		vector a;
		a[0] = readfloat();
		a[1] = readfloat();
		a[2] = readfloat();
		setproperty(VF_CL_VIEWANGLES, a);
		setproperty(VF_ANGLES, a);
		break;
	case EV_SHAKE:
		pSeat->m_flShakeFreq = readfloat();
		pSeat->m_flShakeDuration = readfloat();
		pSeat->m_flShakeAmp = readfloat();
		pSeat->m_flShakeTime = pSeat->m_flShakeDuration;
	default:
		Game_Parse_Event(fHeader);
	}
}

float
CSQC_ConsoleCommand(string sCMD)
{
	/* the engine will hide the p1 etc commands... which is fun... */
	int s = (float)getproperty(VF_ACTIVESEAT);
	pSeat = &g_seats[s];

	tokenize(sCMD);

	switch (argv(0)) {
	case "dev_sunpos":
		vector sunpos;
		vector sunang;
		vector a = getproperty(VF_ANGLES);
		makevectors(getproperty(VF_ANGLES));
		sunpos = v_forward * -1;
		sunang = vectoangles(sunpos);
		localcmd(sprintf("r_shadows_throwdirection %v\n", sunpos));
		print(sprintf("env_sun: pitch: %d; angle: %d\n", sunang[0], sunang[1]));
		print(sprintf("light_environment: pitch %d; sunangle %d\n", a[0], a[1]));
		break;
	case "dev_measure":
		static vector measurepos;
		if (!vlen(measurepos)) {
			measurepos = getproperty(VF_ORIGIN);
			CSQC_Parse_CenterPrint(sprintf( "First marker set at\n%v", measurepos));
		} else {
			CSQC_Parse_CenterPrint(sprintf("Distance: %d\n", vlen(measurepos - getproperty(VF_ORIGIN))));
			measurepos = [0,0,0];
		}
		break;
	case "dev_sentence":
		static CBaseEntity foo;
		if (!foo) {
			foo = spawn(CBaseEntity);
			foo.drawmask = MASK_ENGINE;
			//setmodel(foo, "sprites/muzzleflash1.spr");
		}
		setorigin(foo, getproperty(VF_ORIGIN));
		foo.Sentence(argv(1));
		break;
	case "vote":
		if (argv(1) == "yes") {
			sendevent("VoteY", "");
		} else if (argv(1) == "no") {
			sendevent("VoteN", "");
		}
		break;
	case "getpos":
		print(sprintf("setpos %v;setang -%v\n", getproperty(VF_ORIGIN), getproperty(VF_ANGLES)));
		break;
	case "callvote":
		sendevent("CallVote", "s", substring(sCMD, 9, strlen(sCMD)-9));
		break;
	case "+zoomin":
		pSeat->m_iZoomed = TRUE;
		break;
	case "-zoomin":
		pSeat->m_iZoomed = FALSE;
		break;
	case "buildcubemaps":
		CMap_Build();
		break;
	case "titles_test":
		GameMessage_Setup(argv(1), 0);
		break;
	case "vox_test":
		Vox_Play(sCMD);
		break;
	case "+attack2":
		pSeat->m_iInputAttack2 = TRUE;
		break;
	case "-attack2":
		pSeat->m_iInputAttack2 = FALSE;
		break;
	case "+reload":
		pSeat->m_iInputReload = TRUE;
		break;
	case "-reload":
		pSeat->m_iInputReload = FALSE;
		break;
	case "+use":
		pSeat->m_iInputUse = TRUE;
		break;
	case "-use":
		pSeat->m_iInputUse = FALSE;
		break;
	case "+duck":
		pSeat->m_iInputDuck = TRUE;
		break;
	case "-duck":
		pSeat->m_iInputDuck = FALSE;
		break;
	case "invnext":
		HUD_DrawWeaponSelect_Back();
		break;
	case "invprev":
		HUD_DrawWeaponSelect_Forward();
		break;
	case "lastinv":
		HUD_DrawWeaponSelect_Last();
		break;
	case "+showscores":
		pSeat->m_iScoresVisible = TRUE;
		break;
	case "-showscores":
		pSeat->m_iScoresVisible = FALSE;
		break;
	case "slot1":
		HUD_SlotSelect(0);
		break;
	case "slot2":
		HUD_SlotSelect(1);
		break;
	case "slot3":
		HUD_SlotSelect(2);
		break;
	case "slot4":
		HUD_SlotSelect(3);
		break;
	case "slot5":
		HUD_SlotSelect(4);
		break;
	case "slot6":
		HUD_SlotSelect(5);
		break;
	case "slot7":
		HUD_SlotSelect(6);
		break;
	case "slot8":
		HUD_SlotSelect(7);
		break;
	case "slot9":
		HUD_SlotSelect(8);
		break;
	case "slot10":
		HUD_SlotSelect(9);
		break;
	case "way_menu":
		Textmenu_Call("WAY_MENU");
		break;
	case "_fnchat_msg":
		CSQC_Parse_Print(argv(1), PRINT_CHAT);
		break;
	default:
		return Game_ConsoleCommand();
	}
	return TRUE;
}

void
CSQC_Parse_Print(string sMessage, float fLevel)
{
	int s = (float)getproperty(VF_ACTIVESEAT);
	pSeat = &g_seats[s];

	/* This gives messages other than chat an orange tint */
	if (fLevel == PRINT_CHAT) {
		Chat_Parse(sMessage);
		return;
	}

	if (pSeat->m_iPrintLines < 4) {
		pSeat->m_strPrintBuffer[pSeat->m_iPrintLines + 1] = sMessage;
		pSeat->m_iPrintLines++;
	} else {
		for (int i = 0; i < 4; i++) {
			pSeat->m_strPrintBuffer[i] = pSeat->m_strPrintBuffer[i + 1];
		}
		pSeat->m_strPrintBuffer[4] = sMessage;
	}

	pSeat->m_flPrintTime = time + CHAT_TIME;

	// Log to console
	localcmd(sprintf("echo \"%s\"\n", sMessage));
}


/*
=================
CSQC_Parse_CenterPrint

Catches every centerprint call and allows us to tinker with it.
That's how we are able to add color, alpha and whatnot.
Keep in mind that newlines need to be tokenized
=================
*/
float
CSQC_Parse_CenterPrint(string sMessage)
{
	int s = (float)getproperty(VF_ACTIVESEAT);
	pSeat = &g_seats[s];

	pSeat->m_iCenterprintLines = tokenizebyseparator(sMessage, "\n");

	for (int i = 0; i < (pSeat->m_iCenterprintLines); i++) {
		pSeat->m_strCenterprintBuffer[i] = sprintf("^xF80%s", argv(i));
	}

	pSeat->m_flCenterprintAlpha = 1;
	pSeat->m_flCenterprintTime = time + 3;

	return TRUE;
}

/*
=================
CSQC_Ent_Update

Called whenever an entity is sent manually via .SendFlags and so on
=================
*/
void
CSQC_Ent_Update(float new)
{
	float t;
	t = readbyte();

	switch (t) {
	case ENT_ENTITY:
		CBaseEntity me = (CBaseEntity)self;
		if (new) {
			spawnfunc_CBaseEntity();
		}
		me.ReceiveEntity(readfloat());
		break;
	case ENT_PLAYER:
		Player_ReceiveEntity(new);
		break;
	case ENT_SPRITE:
		env_sprite spr = (env_sprite)self;
		if (new) {
			spawnfunc_env_sprite();
		}
		spr.ReceiveEntity(readfloat());
		break;
		break;
	case ENT_SPRAY:
		Spray_Parse();
		break;
	case ENT_DECAL:
		Decal_Parse();
		break;
	case ENT_AMBIENTSOUND:
		Sound_ParseLoopingEntity(self, new);
		break;
	case ENT_OLDCAMERA:
		trigger_camera tc = (trigger_camera)self;
		if (new) {
			spawnfunc_trigger_camera();
		}
		tc.ReceiveEntity(readfloat());
		break;
	case ENT_MONITOR:
		func_monitor fc = (func_monitor)self;
		if (new) {
			spawnfunc_func_monitor();
		}
		fc.ReceiveEntity(readfloat());
		break;
	case ENT_DLIGHT:
		light_dynamic dl = (light_dynamic)self;
		if (new) {
			spawnfunc_light_dynamic();
		}
		dl.ReceiveEntity(readfloat());
		break;
	case ENT_PROJECTEDTEXTURE:
		env_projectedtexture ept = (env_projectedtexture)self;
		if (new) {
			spawnfunc_env_projectedtexture();
		}
		ept.ReceiveEntity(readfloat());
		break;
	case ENT_ENVLASER:
		env_laser l = (env_laser)self;
		if (new) {
			spawnfunc_env_laser();
		}
		l.ReceiveEntity(readfloat());
		break;
	case ENT_PARTSYSTEM:
		info_particle_system ips = (info_particle_system)self;
		if (new) {
			spawnfunc_info_particle_system();
		}
		ips.ReceiveEntity(readfloat());
		break;
	default:
		if (Game_Entity_Update(t, new) == FALSE) {
			error("Unknown entity type update received.\n");
		}
	}
}

/*
=================
CSQC_WorldLoaded

Whenever the world is fully initialized...
=================
*/
void
CSQC_WorldLoaded(void)
{
	/* Primarily for the flashlight */
	if (serverkeyfloat("*bspversion") != BSPVER_HL) {
		localcmd("r_shadow_realtime_dlight 1\n");
	} else {
		localcmd("r_shadow_realtime_dlight 0\n");
	}

	string strTokenized;
	getentitytoken(0);

	while (1) {
		strTokenized = getentitytoken();
		if (strTokenized == "") {
			break;
		}
		if (strTokenized != "{") {
			print("^1[WARNING] ^7Bad entity data\n");
			return;
		}
		if (!Entities_ParseLump()) {
			print("^1[WARNING] ^7Bad entity data\n");
			return;
		}
	}

	/* we've gone through all ent-lumps, so we can read sky-overrides from
	   worldspawn now. */
	Sky_Update();
}

/*
=================
CSQC_Shutdown

Incase you need to free something
=================
*/
void
CSQC_Shutdown(void)
{
	Decal_Shutdown();
	Sentences_Shutdown();
	Titles_Shutdown();
	Sound_Shutdown();
	Vox_Shutdown();
}
