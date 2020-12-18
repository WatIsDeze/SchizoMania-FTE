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

int g_iOptionsInitialized;

//=========================================================================
// A big ass Options menu function, oh lawd, holy QC.
//=========================================================================
void UI_Options_Show ( void )
{
    //
    // Main Options Window UI.
    //
	static CUIWindow winOptions;
    static CUITabView tabOptions;
	static CUIButton btnApply;
	static CUIButton btnCancel;

    //
    // Tab Area Buttons.
    //
    static CUITabButton tabBtnVideo;
    static CUITabButton tabBtnAudio;
    static CUITabButton tabBtnInput;
    static CUITabButton tabBtnOther;

    //
    // Game Options Controls.
    //

    //
    // Video Options Controls.
    //

    //
    // Audio Options Controls.
    //

    //
    // Input Options Controls.
    //

    //
    // Other Options Controls.
    //

	// static CUILabel	lblSelectChapter;
	// static CUIRadio radChapter1;
	// static CUIRadio radChapter2;
	// static CUIRadio radChapter3;

	static void Options_Apply ( void ) {	
		// if (radChapter1.GetValue() != TRUE) {
		// 	localcmd("stopmusic\n");
		// 	//localcmd("set skill 1; maxplayers 1\n");
		// 	localcmd( "maxplayers 1\ncoop 0\n"); 
		// 	localcmd( "map test_prototype_outdoor\n" );
		// 	return;
		// }
		// if (radChapter2.GetValue() != TRUE) {
		// 	localcmd("stopmusic\n");
		// 	//localcmd("set skill 1; maxplayers 1\n");
		// 	localcmd( "maxplayers 1\ncoop 0\n"); 
		// 	localcmd( "map test_prototype_indoor\n" );
		// 	return;
		// }
		winOptions.Hide();
	}
	static void Options_Cancel ( void ) {
		winOptions.Hide();
	}

    //-----------------------------------------------------
    // Options Hide Tab Funcs.
    //-----------------------------------------------------
    static void Options_Tab_Video_Hide( void ) {

    }
    static void Options_Tab_Audio_Hide( void ) {

    }
    static void Options_Tab_Input_Hide( void ) {

    }
    static void Options_Tab_Other_Hide( void ) {

    }

    //-----------------------------------------------------
    // Options Show Tab Funcs.
    //-----------------------------------------------------
    static void Options_Tab_Video_Show( void ) {
        // Hide other option tabs first.
        Options_Tab_Audio_Hide();
        Options_Tab_Input_Hide();
        Options_Tab_Other_Hide();

        // Controls show flag add.
        dprint("Video Tab - Visible\n");
    }
    static void Options_Tab_Audio_Show( void ) {
        // Hide other option tabs first.
        Options_Tab_Video_Hide();
        Options_Tab_Input_Hide();
        Options_Tab_Other_Hide();

        // Controls show flag add.
        dprint("Audio Tab - Visible\n");
    }
    static void Options_Tab_Input_Show( void ) {
        // Hide other option tabs first.
        Options_Tab_Video_Hide();
        Options_Tab_Audio_Hide();
        Options_Tab_Other_Hide();

        // Controls show flag add.
        dprint("Input Tab - Visible\n");
    }
    static void Options_Tab_Other_Show( void ) {
        // Hide other option tabs first.
        Options_Tab_Video_Hide();
        Options_Tab_Audio_Hide();
        Options_Tab_Input_Hide();

        // Controls show flag add.
        dprint("Options Tab - Visible\n");
    }

    //-----------------------------------------------------
    // Initialize.
    //-----------------------------------------------------
	if ( !g_iOptionsInitialized ) {
		g_iOptionsInitialized = TRUE;
		winOptions = spawn( CUIWindow );
		winOptions.SetTitle( "Options" );
		winOptions.SetSize( '420 320' );
		winOptions.SetIcon( "textures/ui/icons/gear" );
		g_uiDesktop.Add( winOptions );
	winOptions.SetPos( ( video_res / 2 ) - ( winOptions.GetSize() / 2 ) );
        tabOptions = spawn( CUITabView );
        tabOptions.SetSize('340 240');
        tabOptions.SetPos(winOptions.GetSize() - '410 290');

		btnApply = spawn( CUIButton );
		btnApply.SetTitle( "Apply" );
		btnApply.SetSize( '64 24' );
		btnApply.SetPos( winOptions.GetSize() - '152 32' );
		btnApply.SetFunc( Options_Apply );

		btnCancel = spawn( CUIButton );
		btnCancel.SetTitle( "Cancel" );
		btnCancel.SetSize( '64 24' );
		btnCancel.SetPos( winOptions.GetSize() - '80 32' );
		btnCancel.SetFunc( Options_Cancel );

        winOptions.Add(btnApply);
        winOptions.Add(btnCancel);
        winOptions.Add(tabOptions);

        tabBtnVideo = tabOptions.AddTabButton("Video", Options_Tab_Video_Show);
        tabBtnAudio = tabOptions.AddTabButton("Audio", Options_Tab_Audio_Show);
        tabBtnInput = tabOptions.AddTabButton("Input", Options_Tab_Input_Show);
        tabBtnOther = tabOptions.AddTabButton("Other", Options_Tab_Other_Show);

	}

	winOptions.Show();
	winOptions.SetPos( ( video_res / 2 ) - ( winOptions.GetSize() / 2 ) );
}
