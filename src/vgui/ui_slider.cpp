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

enumflags
{
	SLIDER_VISIBLE = UI_VISIBLE,
	SLIDER_HOVER,
	SLIDER_DOWN,
};

class CUISlider:CUIWidget
{
	float m_flAlpha;
	vector m_vecSize;
	vector m_vecColor;

	void(void) CUISlider;
	virtual void(void) Draw;
	virtual void(float, float, float, float) Input;
	virtual void(vector) SetSize;
	virtual void(string) SetTitle;
};

void CUISlider::CUISlider(void)
{
	m_vecColor = [76,88,68] / 255;
	m_flAlpha = 1.0f;
	m_vecSize = [96,24];
	m_iFlags = BUTTON_VISIBLE;
}

void CUISlider::Draw(void)
{
	drawfill(GetAbsolutePos(), m_vecSize, m_vecColor, m_flAlpha);
	
	if (m_iFlags & BUTTON_DOWN) {
		drawfill(GetAbsolutePos(), [m_vecSize[0], 1], [0,0,0], 0.5f);
		drawfill(GetAbsolutePos() + [0, m_vecSize[1] - 1], [m_vecSize[0], 1], [1,1,1], 0.5f);
		drawfill(GetAbsolutePos() + [0, 1], [1, m_vecSize[1] - 2], [0,0,0], 0.5f);
		drawfill(GetAbsolutePos() + [m_vecSize[0] - 1, 1], [1, m_vecSize[1] - 2], [1,1,1], 0.5f);
	} else {
		drawfill(GetAbsolutePos(), [m_vecSize[0], 1], [1,1,1], 0.5f);
		drawfill(GetAbsolutePos() + [0, m_vecSize[1] - 1], [m_vecSize[0], 1], [0,0,0], 0.5f);
		drawfill(GetAbsolutePos() + [0, 1], [1, m_vecSize[1] - 2], [1,1,1], 0.5f);
		drawfill(GetAbsolutePos() + [m_vecSize[0] - 1, 1], [1, m_vecSize[1] - 2], [0,0,0], 0.5f);
	}
	
	if (m_strTitle) {
		Font_DrawText(GetAbsolutePos() + [8, 8], m_strTitle, g_fntDefault);
	}
	if (m_strIcon) {
		drawpic(GetAbsolutePos() + [2,2], m_strIcon, [16,16], [1,1,1], 1.0f);
	}
}

void CUISlider::Input (float flEVType, float flKey, float flChar, float flDevID)
{

}

void CUISlider::SetSize (vector vecSize)
{
	m_vecSize = vecSize;
}
void CUISlider::SetTitle (string strName)
{
	m_strTitle = strName;
}
