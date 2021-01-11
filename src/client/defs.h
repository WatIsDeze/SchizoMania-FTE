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

#include "textmenu.h"

/* flags for 2d drawing */
#define DRAWFLAG_NORMAL		0
#define DRAWFLAG_ADDITIVE	1
#define DRAWFLAG_MODULATE	2
#define DRAWFLAG_2XMODULATE	3

/* undocumented printcall types */
#define PRINT_LOW		0
#define PRINT_MEDIUM	1
#define PRINT_HIGH		2
#define PRINT_CHAT		3

/* fonts */
var float FONT_16;
var float FONT_20;
var float FONT_CON;

/* clientside cvars */
var float autocvar_cl_bob = 0;
var float autocvar_v_bob = 0.01;
var float autocvar_v_bobcycle = 0.8;
var float autocvar_v_bobup = 0.5;
var float autocvar_zoom_sensitivity = 1.0f;
var int autocvar_cl_smoothstairs = TRUE;
var int autocvar_cl_thirdperson = FALSE;
var int autocvar_v_bobclassic = TRUE;
var int autocvar_v_lefthanded = FALSE;
var string autocvar_cl_logofile = "lambda";
var vector autocvar_cl_logocolor = [255,0,0];
var vector autocvar_con_color = [255,150,0];
var vector autocvar_vgui_color = [255,170,0];
var vector autocvar_v_gunofs = [0,0,0];
var int autocvar_r_viewmodelpass = 0;
var float autocvar_r_viewmodelfov = 90.0f;
var float autocvar_r_viewmodelscale = 1.0f;
var float autocvar_cl_hudaspect = 0.0f;

/* particle descriptors */
var float PART_DUSTMOTE;

/* muzzleflash indices */
var int MUZZLE_SMALL;
var int MUZZLE_RIFLE;
var int MUZZLE_WEIRD;

/* misc globals */
vector video_mins;
vector video_res;
vector mouse_pos;
int g_iIntermission;

int g_iWorldInitialized;

/* this actually belongs in builtins.h since its an undocumented global */
float clframetime;

/* prototypes */
void Damage_Draw(void);

string(string modelname, int frame, float frametime) spriteframe = #0;

void
drawstring_r(vector p, string t, vector s, vector c, float a, float f)
{
	p[0] -= stringwidth(t, TRUE, s);
	drawstring(p, t, s, c, a, f);
}

void GameMessage_Setup(string, int);
void Game_Input(void);
void View_SetMuzzleflash(int);
void View_PlayAnimation(int);
void View_PlayAnimation(int);
void Vox_Play(string);
void Event_ProcessModel(float, int, string);
void Game_ClientModelEvent(float, int, string);

/*
=======================
CROSSHAIR API
=======================
*/
void SCMA_DrawGunCrosshair(void);
void SCMA_DrawSimpleCrosshair(void);
void SCMA_DrawScope(void);

/* this really should be done in-engine */

__wrap float(vector pos, string pic, vector size, vector rgb, float alpha, optional float drawflag) drawpic =
{
	return prior([(int)pos[0],(int)pos[1]], pic, size, rgb, alpha, drawflag);
};
__wrap void(vector pos, vector sz, string pic, vector srcpos, vector srcsz, vector rgb, float alpha, optional float drawflag) drawsubpic =
{
	return prior([(int)pos[0],(int)pos[1]], sz, pic, srcpos, srcsz, rgb, alpha, drawflag);
};
