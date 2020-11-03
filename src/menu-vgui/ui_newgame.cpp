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

int g_iNewGameInitialized;

void UI_NewGame_Show ( void )
{
	static CUIWindow winNewGame;
	static CUIButton btnPlay;
	static CUIButton btnCancel;
	static CUILabel	lblSelectChapter;
	static CUIRadio radChapter1;
	static CUIRadio radChapter2;
	static CUIRadio radChapter3;

	static void NewGame_Play ( void ) {	
		// TODO: Load in the proper chapter map.
		localcmd("stopmusic\n");
		//localcmd("set skill 1; maxplayers 1\n");
		localcmd( "maxplayers 1\ncoop 0\n"); 
		localcmd( "map test_item_inventory\n" );
		winNewGame.Hide();
	}
	static void NewGame_Cancel ( void ) {
		winNewGame.Hide();
	}
	static void NewGame_Check_Chapter1 ( void ) {
		radChapter1.SetValue( TRUE );
		radChapter2.SetValue( FALSE );
		radChapter3.SetValue( FALSE );
	}
	static void NewGame_Check_Chapter2 ( void ) {
		radChapter1.SetValue( FALSE );
		radChapter2.SetValue( TRUE );
		radChapter3.SetValue( FALSE );
	}
	static void NewGame_Check_Chapter3 ( void ) {
		radChapter1.SetValue( FALSE );
		radChapter2.SetValue( FALSE );
		radChapter3.SetValue( TRUE );
	}

	if ( !g_iNewGameInitialized ) {
		g_iNewGameInitialized = TRUE;
		winNewGame = spawn( CUIWindow );
		winNewGame.SetTitle( "New Game" );
		winNewGame.SetSize( '192 168' );
		winNewGame.SetIcon( "textures/ui/icons/desktop" );
		g_uiDesktop.Add( winNewGame );

		btnPlay = spawn( CUIButton );
		btnPlay.SetTitle( "Play" );
		btnPlay.SetSize( '64 24' );
		btnPlay.SetPos( winNewGame.GetSize() - '152 32' );
		btnPlay.SetFunc( NewGame_Play );

		btnCancel = spawn( CUIButton );
		btnCancel.SetTitle( "Cancel" );
		btnCancel.SetSize( '64 24' );
		btnCancel.SetPos( winNewGame.GetSize() - '80 32' );
		btnCancel.SetFunc( NewGame_Cancel );

		lblSelectChapter = spawn ( CUILabel );
		lblSelectChapter.SetTitle( "Select a chapter to play:" );
		lblSelectChapter.SetSize( '128 16' );
		lblSelectChapter.SetPos( '32 32' );

		radChapter1 = spawn( CUIRadio );
		radChapter1.SetTitle( "Chapter 1" );
		radChapter1.SetSize( '96 16' );
		radChapter1.SetPos( '32 56' );

		radChapter2 = spawn( CUIRadio );
		radChapter2.SetTitle( "Chapter 2" );
		radChapter2.SetSize( '96 16' );
		radChapter2.SetPos( '32 80' );

		radChapter3 = spawn( CUIRadio );
		radChapter3.SetTitle( "Chapter 3" );
		radChapter3.SetSize( '96 16' );
		radChapter3.SetPos( '32 104' );
		radChapter3.SetValue( TRUE );

		radChapter1.SetFunc( NewGame_Check_Chapter1 );
		radChapter2.SetFunc( NewGame_Check_Chapter2 );
		radChapter3.SetFunc( NewGame_Check_Chapter3 );

		winNewGame.Add( btnPlay );
		winNewGame.Add( btnCancel );
		winNewGame.Add( radChapter1 );
		winNewGame.Add( radChapter2 );
		winNewGame.Add( radChapter3 );
		winNewGame.Add( lblSelectChapter );
	}

	winNewGame.Show();
	winNewGame.SetPos( ( video_res / 2 ) - ( winNewGame.GetSize() / 2 ) );
}
