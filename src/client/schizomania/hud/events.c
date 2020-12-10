/*
 * Copyright (c) 2020 Mike Poortman <someemail@mail.com>
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
string Titles_ParseFunString(string);

//=======================================================================//
//
// CLIENT SIDE HUD EVENT IMPLEMENTATIONS.
//
//=======================================================================//
//=======================
// void HUD_Event_Message(void) 
//
// Parses the EV_HUD_MESSAGE event appropriately.
//=======================
void 
HUD_Event_Message(void) 
{
	int chan = readbyte();
	
    g_hudmessage_channels[chan].m_strMessage = Titles_ParseFunString(readstring());
    g_hudmessage_channels[chan].m_flPosX = readfloat();
	g_hudmessage_channels[chan].m_flPosY = readfloat();
	g_hudmessage_channels[chan].m_iEffect = readbyte();
	g_hudmessage_channels[chan].m_vecColor1[0] = readbyte() / 255;
	g_hudmessage_channels[chan].m_vecColor1[1] = readbyte() / 255;
	g_hudmessage_channels[chan].m_vecColor1[2] = readbyte() / 255;
	g_hudmessage_channels[chan].m_vecColor2[0] = readbyte() / 255;
	g_hudmessage_channels[chan].m_vecColor2[1] = readbyte() / 255;
	g_hudmessage_channels[chan].m_vecColor2[2] = readbyte() / 255;
	g_hudmessage_channels[chan].m_flFadeIn = readfloat();
	g_hudmessage_channels[chan].m_flFadeOut = readfloat();
	g_hudmessage_channels[chan].m_flHoldTime = readfloat();
	g_hudmessage_channels[chan].m_flFXTime = readfloat();
	g_hudmessage_channels[chan].m_flTime = 0.0f;
}

//=======================
// void HUD_Event_Notification(void) 
//
// Parses the EV_HUD_NOTIFICATION event appropriately.
//=======================
void 
HUD_Event_Notification(void) 
{
	float duration = readfloat();
	string message = strreplace("\\n", "\n", readstring());

	HUDNotification_PushNotification(message, duration, HUD_NOTIFICATION_LARGE);

//	g_hudnotifications[position].m_iPosition = position;
 //   g_hudnotifications[position].m_flDuration = readfloat();
//	g_hudnotifications[position].m_strMessage = strreplace("\\n", "\n", readstring());
	// //g_hudnotifications[position].m_strMessage = "Lorem ipsum dolor \nsit amec avec un grande dildo ich ficke deine mutti mit das groBn dildo ja!";//Titles_ParseFunString(readstring());
	// g_hudnotifications[position].m_flTotalTime = 0;
	// g_hudnotifications[position].m_flFadeTime = 0;
}