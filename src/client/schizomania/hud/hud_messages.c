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
typedef struct
{
	string m_strMessage;
	float m_flPosX;
	float m_flPosY;
	int m_iEffect;
	vector m_vecColor1;
	vector m_vecColor2;
	float m_flFadeIn;
	float m_flFadeOut;
	float m_flHoldTime;
	float m_flFXTime;
	float m_flTime;
} hudmessage_t;
hudmessage_t g_hudchannels[5];

/* for effect 2 */
int
HUDMessage_CharCount(float fadein, float timer, string msg)
{
	float len = (timer / fadein);

	if (!fadein || len > strlen(msg))
		return strlen(msg);
	else 
		return len;
}

/* the engine its drawstring doesn't like newlines that much */
void
HUDMessage_DrawString(vector pos, string msg, vector col, float alpha)
{
	vector rpos;
	int c = tokenizebyseparator(msg, "\n");
	
	for (int i = 0; i < c; i++) {
		float strwidth = stringwidth(argv(i), TRUE, [20,20]);

		if (pos[0] == -1) {
			rpos[0] = g_hudmins[0] + (g_hudres[0] / 2) - (strwidth/2);
		} else {
			rpos[0] = g_hudmins[0] + g_hudres[0] * pos[0];

			if (pos[0] >= 0.5) {
				rpos[0] -= strwidth;
			}
		}

		if (pos[1] == -1) {
			rpos[1] = g_hudmins[1] + (g_hudres[1] / 2) - 6;
		} else {
			rpos[1] = g_hudmins[1] + ((g_hudres[1] - 12) * pos[1]);
		}
		rpos[1] += 20 * i;
		rpos[1] -= (20 * c) / 2;
		drawstring(rpos, argv(i), '20 20', col, alpha,
			DRAWFLAG_ADDITIVE);
	}
}

void
HUDMessage_DrawMessage(int i, float timer, int highlight, int drawbg)
{
	float a = 0.0f;
	vector rpos;
	float mtime;
	float btime;
	string finalstring;

	if (g_hudchannels[i].m_iEffect == 2) {
		/* scan out */
		finalstring = substring(g_hudchannels[i].m_strMessage, 0,
			HUDMessage_CharCount(g_hudchannels[i].m_flFadeIn, timer,
				g_hudchannels[i].m_strMessage));
	} else {
		finalstring = g_hudchannels[i].m_strMessage;
	}

	timer = max(0, timer);

	if (highlight) {
		btime = g_hudchannels[i].m_flFadeIn * strlen(g_hudchannels[i].m_strMessage);
		mtime = btime + g_hudchannels[i].m_flFadeOut;
	} else {
		mtime = g_hudchannels[i].m_flFadeIn + g_hudchannels[i].m_flHoldTime + g_hudchannels[i].m_flFadeOut;
		btime = g_hudchannels[i].m_flFadeIn + g_hudchannels[i].m_flHoldTime;
	}

	if (timer > mtime) {
		return;
	}

	if (timer < g_hudchannels[i].m_flFadeIn) {
		a = (timer / g_hudchannels[i].m_flFadeIn);
	} else if (timer < btime) {
		a = 1.0f;
	} else if (timer < mtime) {
		if (g_hudchannels[i].m_flFadeOut) {
			a = 1 - (timer - btime) / g_hudchannels[i].m_flFadeOut;
		}
	}

	rpos[0] = g_hudchannels[i].m_flPosX;
	rpos[1] = g_hudchannels[i].m_flPosY;

    // // Draw background.
    // vector bgPos;

    // if (rpos[0] == -1) {
	// 	bgPos[0] = g_hudmins[0] + (g_hudres[0] / 2);
    // } else {

    // }

    // if (rpos[1] == -1) {
    //     bgPos[1] = g_hudmins[1] + (g_hudres[1] / 2);
    // } else {

    // }

    // // Positions.
    // vector leftPos;
    // vector centerPos;
    // vector centerSize;
    // vector rightPos;

    // // Get string width.
    // float strWidth = stringwidth(finalstring, TRUE, [20,20]);

    // // Is string smaller than 256?
    // if (strWidth < 256) {
    //     leftPos[0] = bgPos[0] - 192;
    //     leftPos[1] = bgPos[1] - 64;

    //     centerPos[0] = bgPos[0] - 32;
    //     centerPos[1] = bgPos[1] - 64;
    //     centerSize[0] = 512;
    //     centerSize[1] = 128;
        
    //     rightPos[0] = bgPos[0] + 192;
    //     rightPos[1] = bgPos[1] - 64;
    // } else {
    //     float strHalfWidth = strWidth / 2;
        
    //     leftPos[0] = bgPos[0] - strHalfWidth - 128;
    //     leftPos[1] = bgPos[1] - 64;

    //     centerPos[0] = bgPos[0] - strHalfWidth;
    //     centerPos[1] = bgPos[1] - 64;
    //     centerSize[0] = strWidth;
    //     centerSize[1] = 128;
        
    //     rightPos[0] = bgPos[0] + strHalfWidth;
    //     rightPos[1] = bgPos[1] - 64;

    // }

    // // Left
    
    // // Center.
    // if (drawbg){
    //     drawpic(leftPos, "textures/hud/hud_message_left.tga", [128,128], [1,1,1], a, 0);
    //     drawpic(centerPos, "textures/hud/hud_message_center.tga", centerSize, [1,1,1], a, 0);
    //     drawpic(rightPos, "textures/hud/hud_message_right.tga", [128,128], [1,1,1], a, 0);
    // }

	if (highlight) {
		HUDMessage_DrawString(rpos, finalstring, g_hudchannels[i].m_vecColor2, a);
	} else {
		HUDMessage_DrawString(rpos, finalstring, g_hudchannels[i].m_vecColor1, a);
	}
}

void
HUDMessage_Draw(void)
{
	drawfont = FONT_HUD_MESSAGES;
	for (int i = 0; i < 5; i++) {
		HUDMessage_DrawMessage(i, g_hudchannels[i].m_flTime - g_hudchannels[i].m_flFXTime, 0, 1);
		HUDMessage_DrawMessage(i, g_hudchannels[i].m_flTime, 1, 0);
		g_hudchannels[i].m_flTime += clframetime;
	}

	drawfont = FONT_CON;
}
