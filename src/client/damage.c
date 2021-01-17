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

void
Damage_Draw(void)
{
	vector center;
	vector size_x_spr;		// Size for the sprites on-screen that show top and bottom.
	vector size_y_spr; 	// Size for the sprites on-screen that show left and right.
	vector rel_pos;
	float fw, fw_alpha;
	float rt, rt_alpha;

	if (pSeat->m_flDamageAlpha <= 0.0) {
		return;
	}

	// Screen center.
	center = video_mins + (video_res / 2);

	// The sprites for the sides are 768x2048
	size_y_spr[0] = (video_res[0] >= 1980 ? 768 : 768 / 2);
	size_y_spr[1] = video_res[1];//(video_res[1] >= 2048 ? video_res[1] : 2048);
	/* the pos relative to the player + view_dir determines which
	 * and how bright each indicator is drawn. so first get the relative
	 * position between us and the attacker, then calculate the strength
	 * of each direction based on a dotproduct tested against our
	 * camera direction.
	 */
	rel_pos = normalize(pSeat->m_vecDamagePos - getproperty(VF_ORIGIN));
	makevectors(getproperty(VF_CL_VIEWANGLES));
	fw = dotproduct(rel_pos, v_forward);
	rt = dotproduct(rel_pos, v_right);

	fw_alpha = fabs(fw) * pSeat->m_flDamageAlpha;
	// if (fw > 0.25f) {
	//  	drawpic(center + [-video_res[0] / 2, -size_y_spr[1] / 2], "sprites/pl_dmg_left.tga", 
	//  		[768,size_y_spr[1]], [1,1,1], fw_alpha, DRAWFLAG_NORMAL);
	//  	// drawpic(center + [70,-64], "textures/player/damage_left",
	//  	// 	[768, video_res.y], [1,1,1], rt_alpha, DRAWFLAG_ADDITIVE);
	// } else if (fw < -0.25f) {
	//  	drawpic(center + [-video_res[0] / 2, -size_y_spr[1] / 2], "sprites/pl_dmg_left.tga", 
	//  		[768,size_y_spr[1]], [1,1,1], fw_alpha, DRAWFLAG_NORMAL);
	//  	// drawpic(center + [-64,70], "sprites/640_pain.spr_2.tga",
	//  	// 	[128,48], [1,1,1], fw_alpha, DRAWFLAG_ADDITIVE);
	//  	// drawpic(center + [70,-64], "textures/player/damage_leftx",
	//  	// 	[768, video_res.y], [1,1,1], rt_alpha, DRAWFLAG_ADDITIVE);
	// }

	rt_alpha = fabs(rt) * pSeat->m_flDamageAlpha;
	// if (rt > 0.25f) {
	//  	drawpic(center + [-video_res[0] / 2, -size_y_spr[1] / 2], "sprites/pl_dmg_left.tga", 
	//  		[768,size_y_spr[1]], [1,1,1], fw_alpha, DRAWFLAG_NORMAL);
	//  	// drawpic(center + [102,-64], "sprites/640_pain.spr_4.tga",
	//  	// 	[48,128], [1,1,1], rt_alpha, DRAWFLAG_ADDITIVE);

	//  	// drawpic(center + [70,-64], "textures/player/damage_left",
	//  	// 	[768, video_res.y], [1,1,1], rt_alpha, DRAWFLAG_ADDITIVE);
	// } else if (rt < -0.25f) {
	//  	drawpic(center + [-video_res[0] / 2, -size_y_spr[1] / 2], "sprites/pl_dmg_left.tga", 
	//  		[768,size_y_spr[1]], [1,1,1], fw_alpha, DRAWFLAG_NORMAL);
	//  	// drawpic(center + [-102,-64], "sprites/640_pain.spr_3.tga",
	//  	// 	[48,128], [1,1,1], rt_alpha, DRAWFLAG_ADDITIVE);
	//  	// drawpic(center + [70,-64], "textures/player/damage_left",
	//  	// 	[768, video_res.y], [1,1,1], rt_alpha, DRAWFLAG_ADDITIVE);
	// }
	drawpic([0, 0], "sprites/damage01.tga", video_res, [1,1,1], pSeat->m_flDamageAlpha, DRAWFLAG_NORMAL);
dprint(sprintf("%f\n", pSeat->m_flDamageAlpha));
	pSeat->m_flDamageAlpha -= clframetime * 1.8;
}

/*
 * engine specific callback for when dmg_ fields are set on the client side.
 * might want to replace it at some point? probably not...
 * hence why 'save' and 'take' are unused.
 */
float
CSQC_Parse_Damage(float save, float take, vector abs_pos)
{
	int s = (float)getproperty(VF_ACTIVESEAT);
	pSeat = &g_seats[s];

	/* FIXME: while a player shooting you from [0,0,0] is unlikely, it's
	 * not impossible. we only do this to lazily seperate players from
	 * entities belonging to world
	 */
	if (abs_pos) {
		pSeat->m_vecDamagePos = abs_pos;
		pSeat->m_flDamageAlpha = 1.0f;
	}

	return TRUE;
}
