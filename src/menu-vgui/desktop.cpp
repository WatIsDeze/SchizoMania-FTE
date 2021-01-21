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
static CUIMenuButton btnNewgame;
static CUIMenuButton btnLoadgame;
static CUIMenuButton btnFindserver;
static CUIMenuButton btnCreateserver;
static CUIMenuButton btnOptions;
static CUIMenuButton btnQuit;
static CUIMenuButton btnMPlayer;
static CUIMenuButton btnMViewer;
static CUIMenuButton btnResume;
static CUIMenuButton btnDisconnect;

static CUIMenuButton lblGameVersion;

static void Desktop_ResumeGame ( void ) {
	m_toggle( 0 );
}
static void Desktop_DisconnectGame ( void ) {
	localcmd( "disconnect\nmap_background mainmenu\n" );
}

static void Desktop_PositionButtons( void ) {
	vector buttonPos = video_res;
	buttonPos.x = 32;
	buttonPos.y -= 384;

	buttonPos.y += 32;
	btnNewgame.SetPos( buttonPos );
		buttonPos.y += 32;
	btnDisconnect.SetPos( buttonPos  );
		buttonPos.y += 32;
	btnLoadgame.SetPos( buttonPos );
		buttonPos.y += 32;
	btnFindserver.SetPos( buttonPos );
		buttonPos.y += 32;
	btnCreateserver.SetPos( buttonPos );
		buttonPos.y += 32;
	btnOptions.SetPos( buttonPos );
		buttonPos.y += 32;
	btnQuit.SetPos(  buttonPos );
		buttonPos.y += 32;
	btnMPlayer.SetPos(  buttonPos );
		buttonPos.y += 32;
	btnMViewer.SetPos(  buttonPos );
		buttonPos.y += 32;
	btnResume.SetPos(  buttonPos  );

	// It serves as a label but whatever.
	lblGameVersion.SetPos( video_res - [333, 332, 0] );
	
}

void Desktop_Init ( void )
{
	g_uiDesktop = spawn( CUIWidget );
	g_uiDesktop.SetPos( '0 0');
	g_uiDesktop.FlagAdd( 1 );

	btnNewgame = spawn( CUIMenuButton );
	btnNewgame.SetTitle( "New Game" );
	btnNewgame.SetSize( '200 24' );

	btnNewgame.SetFunc( UI_NewGame_Show );
	btnNewgame.FlagRemove( MBUTTON_SHOWSP | MBUTTON_SHOWMP );
	btnNewgame.FlagAdd( MBUTTON_TEXTONLY );

	btnDisconnect = spawn( CUIMenuButton );
	btnDisconnect.SetTitle( "Disconnect" );
	btnDisconnect.SetSize( '200 24' );
	btnDisconnect.SetFunc( Desktop_DisconnectGame );
	btnDisconnect.FlagRemove( MBUTTON_SHOWOFFLINE );
	btnDisconnect.FlagAdd( MBUTTON_TEXTONLY );

	btnLoadgame = spawn( CUIMenuButton );
	btnLoadgame.SetTitle( "Load Game" );
	btnLoadgame.SetSize( '200 24' );

	btnLoadgame.FlagAdd( MBUTTON_TEXTONLY );

	btnFindserver = spawn( CUIMenuButton );
	btnFindserver.SetTitle( "Find Servers" );
	btnFindserver.SetSize( '200 24' );
	btnFindserver.SetFunc( UI_FindServers_Show );
	btnFindserver.FlagAdd( MBUTTON_TEXTONLY );

	btnCreateserver = spawn( CUIMenuButton );
	btnCreateserver.SetTitle( "Create Server" );
	btnCreateserver.SetSize( '200 24' );
	btnCreateserver.SetFunc( UI_CreateServer_Show );
	btnCreateserver.FlagAdd( MBUTTON_TEXTONLY );

	btnOptions = spawn( CUIMenuButton );
	btnOptions.SetTitle( "Options" );
	btnOptions.SetSize( '200 24' );
	btnOptions.SetFunc( UI_Options_Show );
	btnOptions.FlagAdd( MBUTTON_TEXTONLY );

	btnQuit = spawn( CUIMenuButton );
	btnQuit.SetTitle( "Quit Game" );
	btnQuit.SetSize( '200 24' );
	btnQuit.SetFunc( UI_QuitGame_Show );
	btnQuit.FlagAdd( MBUTTON_TEXTONLY );

	btnMPlayer = spawn( CUIMenuButton );
	btnMPlayer.SetTitle( "Music Player" );
	btnMPlayer.SetSize( '200 24' );
	btnMPlayer.SetFunc( UI_MusicPlayer_Show );
	btnMPlayer.FlagAdd( MBUTTON_TEXTONLY );

	btnMViewer = spawn( CUIMenuButton );
	btnMViewer.SetTitle( "Model Viewer" );
	btnMViewer.SetSize( '200 24' );
	btnMViewer.SetFunc( UI_ModelViewer_Show );
	btnMViewer.FlagAdd( MBUTTON_TEXTONLY );

	btnResume = spawn( CUIMenuButton );
	btnResume.SetTitle( "Resume Game" );
	btnResume.SetSize( '200 24' );
	btnResume.SetFunc( Desktop_ResumeGame );
	btnResume.FlagRemove( MBUTTON_SHOWOFFLINE );
	btnResume.FlagAdd( MBUTTON_TEXTONLY );

	lblGameVersion = spawn( CUIMenuButton );
	lblGameVersion.SetTitle("SchizoMania - build: (0.0.1)");
	lblGameVersion.SetSize( '200 24');
	lblGameVersion.FlagAdd( MBUTTON_TEXTONLY );

	g_uiDesktop.Add( btnNewgame );
	g_uiDesktop.Add( btnLoadgame );
	g_uiDesktop.Add( btnFindserver );
	g_uiDesktop.Add( btnCreateserver );
	g_uiDesktop.Add( btnOptions );
	g_uiDesktop.Add( btnQuit );
	// g_uiDesktop.Add( btnMPlayer );
	// g_uiDesktop.Add( btnMViewer );
	g_uiDesktop.Add( btnResume );
	g_uiDesktop.Add( btnDisconnect );
	g_uiDesktop.Add( lblGameVersion );
}

void Desktop_Draw ( void )
{
	g_uiDesktop.Draw();
	Desktop_PositionButtons();
}
