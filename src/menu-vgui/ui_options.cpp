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
    static CUITabArea tabAreaVideo;
    static CUITabArea tabAreaAudio;
    static CUITabArea tabAreaInput;
    static CUITabArea tabAreaOther;

    //
    // Game Options Controls.
    //

    //
    // Video Options Controls.
    //
    static CUIList lsbResolutions;
    static CUIButton btnTestVideo;
    static CUIButton btnTestAudio;
    static CUIButton btnTestInput;
    static CUIButton btnTestOther;

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

    //=====================================================
    // VIDEO OPTIONS MENU CONTROLS.
    //=====================================================
    static void CreateVideoOptions() {
        btnTestVideo = spawn( CUIButton );
        btnTestVideo.SetSize('96 24');
        // TODO: Let CUIWidget have a GetChildrenOffset function, 
        // which will add itself to the result in GetAbsolutePositions
        // this way we'll never have to bother doing these things by hand again.
        //
        // It'll add the offset by itself when calculating render/input phases,
        // as a result we can just write SetPos('10 10') instead.
        btnTestVideo.SetPos('10 10' + [0, tabAreaVideo.GetButtonSizeHeight()]);
        btnTestVideo.SetTitle("Testing...");

        tabAreaVideo.Add(btnTestVideo);
	   	// searchhandle shMaps = search_begin( "maps/*.bsp", TRUE, TRUE );
		// lsbMaps = spawn( CUIList );
		// lsbMaps.SetSize( '10 10' );
		// lsbMaps.SetPos( '100 220 ' );
		// // lsbMaps.SetItemCount( search_getsize( shMaps ) );
        // lsbMaps.SetItemCount(3);
		// //lsbMaps.CallOnScroll( CreateServer_Scrolled );
		// lsbMaps.SetSelected( 0 );

		// lsbMaps.AddItem( "Item 1" );
        // lsbMaps.AddItem( "Item 2" );
        // lsbMaps.AddItem( "Item 3" );
    }

    //=====================================================
    // AUDIO OPTIONS MENU CONTROLS.
    //=====================================================
    static void CreateAudioOptions() {
        btnTestAudio = spawn( CUIButton );
        btnTestAudio.SetSize('96 24');
        btnTestAudio.SetPos('67 54' + [0, tabAreaAudio.GetButtonSizeHeight()]);
        btnTestAudio.SetTitle("Testing Audio Options :D !!..");
        tabAreaAudio.Add(btnTestAudio);
    }

    //=====================================================
    // INPUT OPTIONS MENU CONTROLS.
    //=====================================================
    static void CreateInputOptions() {
        btnTestInput = spawn( CUIButton );
        btnTestInput.SetSize('96 24');
        btnTestInput.SetPos('47 110' + [0, tabAreaInput.GetButtonSizeHeight()]);
        btnTestInput.SetTitle("Input's gonna suck :D !!..");
        tabAreaInput.Add(btnTestInput);
    }

    //=====================================================
    // AUDIO OPTIONS MENU CONTROLS.
    //=====================================================
    static void CreateOtherOptions() {
        btnTestOther = spawn( CUIButton );
        btnTestOther.SetSize('96 24');
        btnTestOther.SetPos('35 144' + [0, tabAreaOther.GetButtonSizeHeight()]);
        btnTestOther.SetTitle("w00t Other Options xD !!..");
        tabAreaOther.Add(btnTestOther);
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

        tabOptions = spawn( CUITabView );
        tabOptions.SetSize('400 240');
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
		g_uiDesktop.Add( winOptions );

        tabAreaVideo = tabOptions.AddTabButton("Video", Options_Tab_Video_Show);
        tabAreaAudio = tabOptions.AddTabButton("Audio", Options_Tab_Audio_Show);
        tabAreaInput = tabOptions.AddTabButton("Input", Options_Tab_Input_Show);
        tabAreaOther = tabOptions.AddTabButton("Other", Options_Tab_Other_Show);
        tabOptions.SwitchActiveTab(tabAreaVideo);
        
        CreateVideoOptions();
        CreateAudioOptions();
        CreateInputOptions();
        CreateOtherOptions();
    }

	winOptions.Show();
	winOptions.SetPos( ( video_res / 2 ) - ( winOptions.GetSize() / 2 ) );
}
