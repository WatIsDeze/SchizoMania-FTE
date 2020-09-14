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

CWidget fn_multiplayer;
CMainButton mp_btnQuickstart;
CMainButton mp_btnInternet;
CMainButton mp_btnSpectate;
CMainButton mp_btnChat;
CMainButton mp_btnLAN;
CMainButton mp_btnCustomize;
CMainButton mp_btnControls;
CMainButton mp_btnDone;

CDialog mp_dgConnect;
int g_connected;
int g_connectstatus;
float g_connecttimer;

enum
{
	CONNECT_NONE,
	CONNECT_INTERNET,
	CONNECT_CHAT
};

void
mp_btndone_start(void)
{
	static void mp_btndone_end(void) {
		g_menupage = PAGE_MAIN;
	}
	localsound("../media/launch_dnmenu1.wav");
	header.SetStartEndPos(45,45,70,320);
	header.SetStartEndSize(460,80,156,26);
	header.m_lerp = 0.0f;
	header.m_visible = TRUE;
	header.SetHeader(HEAD_MULTI);
	header.SetExecute(mp_btndone_end);
}

void
mp_btninet_start(void)
{
	static void mp_btninet_end(void) {
		g_menupage = PAGE_INTERNETGAMES;
	}

	cvar_set("sv_public", "1");
	localsound("../media/launch_upmenu1.wav");
	
	if (g_connected == TRUE) {
		header.SetStartEndPos(50,172,45,45);
		header.SetStartEndSize(156,26,460,80);
		header.m_lerp = 0.0f;
		header.m_visible = TRUE;
		header.SetHeader(HEAD_INETGAMES);
		header.SetExecute(mp_btninet_end);
	} else {
		Master_GetInternetList();
		g_connectstatus = CONNECT_INTERNET;
		g_connecttimer = 8.0f;
	}
}

/* this is from m_chatrooms.cpp */
void
cr_btnservers_start(void)
{
	static void cr_btnservers_end(void) {
		g_menupage = PAGE_INTERNETGAMES;
	}

	/* hack - jump to here so we draw the connection thing */
	g_menupage = PAGE_MULTIPLAYER;
	cvar_set("sv_public", "1");
	localsound("../media/launch_upmenu1.wav");

	if (g_connected == TRUE) {
		header.SetStartEndPos(252,70,45,45);
		header.SetStartEndSize(156,26,460,80);
		header.m_lerp = 0.0f;
		header.m_visible = TRUE;
		header.SetHeader(HEAD_INETGAMES);
		header.SetExecute(cr_btnservers_end);
	} else {
		Master_GetInternetList();
		g_connectstatus = CONNECT_INTERNET;
		g_connecttimer = 8.0f;
	}
}

void
mp_btnlan_start(void)
{
	static void mp_btnlan_end(void) {
		g_menupage = PAGE_LANGAMES;
	}
	cvar_set("sv_public", "0");
	Master_GetLANList();
	localsound("../media/launch_upmenu1.wav");
	header.SetStartEndPos(50,268,45,45);
	header.SetStartEndSize(156,26,460,80);
	header.m_lerp = 0.0f;
	header.m_visible = TRUE;
	header.SetHeader(HEAD_LAN);
	header.SetExecute(mp_btnlan_end);
}

void
mp_btnchatrooms_start(void)
{
	static void mp_btnchatrooms_end(void) {
		g_menupage = PAGE_CHATROOMS;
	}
	localsound("../media/launch_upmenu1.wav");
	header.SetStartEndPos(50,239,45,45);
	header.SetStartEndSize(156,26,460,80);
	header.m_lerp = 0.0f;
	header.m_visible = TRUE;
	header.SetHeader(HEAD_ROOMS);
	header.SetExecute(mp_btnchatrooms_end);
}

void
mp_btncustomize_start(void)
{
	static void mp_btncustomize_end(void) {
		g_menupage = PAGE_CUSTOMIZE;
	}
	localsound("../media/launch_upmenu1.wav");
	header.SetStartEndPos(50,300,45,45);
	header.SetStartEndSize(156,26,460,80);
	header.m_lerp = 0.0f;
	header.m_visible = TRUE;
	header.SetHeader(HEAD_CUSTOMIZE);
	header.SetExecute(mp_btncustomize_end);
}

void
menu_multiplayer_init(void)
{
	fn_multiplayer = spawn(CWidget);
	mp_dgConnect = spawn(CDialog);
	
	mp_btnQuickstart = spawn(CMainButton);
	mp_btnQuickstart.SetImage(BTN_QUICKSTART);
	//mp_btnQuickstart.SetExecute(btn_console);
	mp_btnQuickstart.SetPos(50,140);
	Widget_Add(fn_multiplayer, mp_btnQuickstart);
	
	mp_btnInternet = spawn(CMainButton);
	mp_btnInternet.SetImage(BTN_INTERNET);
	mp_btnInternet.SetExecute(mp_btninet_start);
	mp_btnInternet.SetPos(50,172);
	Widget_Add(fn_multiplayer, mp_btnInternet);
	
	mp_btnSpectate = spawn(CMainButton);
	mp_btnSpectate.SetImage(BTN_SPECTATEGAMES);
	//mp_btnSpectate.SetExecute(btn_console);
	mp_btnSpectate.SetPos(50,204);
	Widget_Add(fn_multiplayer, mp_btnSpectate);
	
	mp_btnChat = spawn(CMainButton);
	mp_btnChat.SetImage(BTN_CHATROOMS);
	mp_btnChat.SetExecute(mp_btnchatrooms_start);
	mp_btnChat.SetPos(50,236);
	Widget_Add(fn_multiplayer, mp_btnChat);
	
	mp_btnLAN = spawn(CMainButton);
	mp_btnLAN.SetImage(BTN_LAN);
	mp_btnLAN.SetExecute(mp_btnlan_start);
	mp_btnLAN.SetPos(50,268);
	Widget_Add(fn_multiplayer, mp_btnLAN);
	
	mp_btnCustomize = spawn(CMainButton);
	mp_btnCustomize.SetImage(BTN_CUSTOMIZE);
	mp_btnCustomize.SetExecute(mp_btncustomize_start);
	mp_btnCustomize.SetPos(50,300);
	Widget_Add(fn_multiplayer, mp_btnCustomize);
	
	mp_btnControls = spawn(CMainButton);
	mp_btnControls.SetImage(BTN_CONTROLS);
	//mp_btnControls.SetExecute(btn_console);
	mp_btnControls.SetPos(50,332);
	Widget_Add(fn_multiplayer, mp_btnControls);

	mp_btnDone = spawn(CMainButton);
	mp_btnDone.SetImage(BTN_DONE);
	mp_btnDone.SetExecute(mp_btndone_start);
	mp_btnDone.SetPos(50,364);
	Widget_Add(fn_multiplayer, mp_btnDone);

	Master_UpdateCache();
}

void
menu_multiplayer_draw(void)
{
	Widget_Draw(fn_multiplayer);
	drawpic([g_menuofs[0]+45,g_menuofs[1]+45], g_bmp[HEAD_MULTI],[460,80], [1,1,1], 1.0f, 1);

	WLabel_Static(215, 148, m_reslbl[IDS_MAIN_QUICKHELP], 10, 10, col_help,
					1.0f, 0, font_label);
	WLabel_Static(215, 180, m_reslbl[IDS_MULTI_BROWSEHELP], 10, 10, col_help,
					1.0f, 0, font_label);
	WLabel_Static(215, 212, "Spectate internet games.", 10, 10, col_help,
					1.0f, 0, font_label);
	WLabel_Static(215, 244, m_reslbl[IDS_MULTI_CHATHELP], 10, 10, col_help,
					1.0f, 0, font_label);
	WLabel_Static(215, 276, m_reslbl[IDS_MULTI_LANHELP], 10, 10, col_help,
					1.0f, 0, font_label);
	WLabel_Static(215, 308, m_reslbl[IDS_MULTI_CUSTOMIZEHELP], 10, 10, col_help,
					1.0f, 0, font_label);
	WLabel_Static(215, 340, m_reslbl[IDS_CFG_CONTROLHELP], 10, 10, col_help,
					1.0f, 0, font_label);
	WLabel_Static(215, 372, m_reslbl[IDS_MULTI_DONEHELP], 10, 10, col_help,
					1.0f, 0, font_label);

	if (g_connectstatus) {
		if (Master_GetTotalServers() || g_connecttimer <= 0) {
			g_connected = TRUE;
			g_connectstatus = CONNECT_NONE;
			mp_btninet_start();
		}
		mp_dgConnect.Draw();
		WField_Static(162, 180, m_reslbl[IDS_WON_LOGIN], 320, 260,
						col_prompt_text, 1.0f, 2, font_label_p);
		WField_Static(162, 280, sprintf(m_reslbl[IDS_QUICK_REQUEST],g_connecttimer), 320, 260,
						col_prompt_title, 1.0f, 2, font_label);
		g_connecttimer -= frametime;
		Master_ResortCache();
	}
}

void
menu_multiplayer_input(float evtype, float scanx, float chary, float devid)
{
	if (!g_connectstatus) {
		Widget_Input(fn_multiplayer, evtype, scanx, chary, devid);
	}
}
