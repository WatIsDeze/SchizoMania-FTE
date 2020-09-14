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

class CLabel:CWidget
{
	string m_label;
	vector m_color;
	int m_sx;
	int m_sy;
	float m_alpha;
	int m_font;

	void(void) CLabel;
	virtual void(void) Draw;
};

void
CLabel::CLabel(void)
{
	m_label = "Label";
	m_color = [1,1,1];
	m_alpha = 1.0f;
	m_sx = m_sy = 8;
}

void
CLabel::Draw(void)
{
	drawfont = m_font;
	drawstring([m_x,m_y], m_label, [m_sx,m_sy], m_color, m_alpha, 0);
}

/* Sometimes all you need is a static label */
void
WLabel_Static(int x, int y, string msg, int sx, int sy, vector col,
				float alpha, float flags, int font)
{
	drawfont = font;
	x += g_menuofs[0];
	y += g_menuofs[1];
	drawstring([x,y], msg, [sx,sy], col, alpha, flags);
}

void
WLabel_StaticR(int x, int y, string msg, int sx, int sy, vector col,
				float alpha, float flags, int font)
{
	drawfont = font;
	x += g_menuofs[0] - stringwidth(msg, TRUE,[sx,sy]);
	y += g_menuofs[1];
	drawstring([x,y], msg, [sx,sy], col, alpha, flags);
}

void
WField_Static(int x, int y, string msg, int sx, int sy, vector col,
				float alpha, float flags, int font)
{
	drawfont = font;
	x += g_menuofs[0];
	y += g_menuofs[1];
	drawtextfield([x,y], [sx,sy], flags, sprintf("%s%s", 
				  Colors_RGB8_to_HEX(col), msg));
}
