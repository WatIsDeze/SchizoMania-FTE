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
//=======================================================================//
//
// CLIENT SIDE HUD EVENT IMPLEMENTATIONS.
//
//=======================================================================//
//=======================
// void HUD_Event_Message(void) 
//
// Parses the EV_ITEM_PICKUP message. Adds items to client inventory and
// informs the client about the picked up item.
//=======================
void 
HUD_Event_Message(void) 
{
	int chan = readbyte();
	
    g_hudchannels[chan].m_strMessage = Titles_ParseFunString(readstring());
    // TODO: Do we still need these if we set them by default?
    g_hudchannels[chan].m_flPosX = readfloat();
	g_hudchannels[chan].m_flPosY = readfloat();
    g_hudchannels[chan].m_flPosX = -1.0f;
	g_hudchannels[chan].m_flPosY = 0.8f;
	g_hudchannels[chan].m_iEffect = readbyte();
	g_hudchannels[chan].m_vecColor1[0] = readbyte() / 255;
	g_hudchannels[chan].m_vecColor1[1] = readbyte() / 255;
	g_hudchannels[chan].m_vecColor1[2] = readbyte() / 255;
	g_hudchannels[chan].m_vecColor2[0] = readbyte() / 255;
	g_hudchannels[chan].m_vecColor2[1] = readbyte() / 255;
	g_hudchannels[chan].m_vecColor2[2] = readbyte() / 255;
	g_hudchannels[chan].m_flFadeIn = readfloat();
	g_hudchannels[chan].m_flFadeOut = readfloat();
	g_hudchannels[chan].m_flHoldTime = readfloat();
	g_hudchannels[chan].m_flFXTime = readfloat();
	g_hudchannels[chan].m_flTime = 0.0f;
}