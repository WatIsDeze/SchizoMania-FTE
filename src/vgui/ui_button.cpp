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
	BUTTON_VISIBLE = UI_VISIBLE,
	BUTTON_HOVER,
	BUTTON_DOWN,
	BUTTON_HOVER,
	BUTTON_DISABLED,
	BUTTON_LASTACTIVE
};

class CUIButton:CUIWidget
{
	vector m_vecColor;
	float m_flAlpha;
	vector m_vecSize;
	vector m_vecButtonSize;
	string m_strTitle;
	string m_strTitleActive;
	string m_strTitleHover;
	string m_strTitleDisabled;
	string m_strIcon;

	void(void) CUIButton;
	virtual void(void) m_vFunc = 0;
	virtual void(void) Draw;
	virtual vector() GetSize;
	virtual int(void) GetSizeWidth;
	virtual int(void) GetSizeHeight;
	virtual void(vector) SetSize;
	virtual void(string) SetTitle;
	virtual void(string) SetIcon;
	virtual void(void(void)) SetFunc;
	virtual void(float, float, float, float) Input;
};

void
CUIButton::CUIButton(void)
{
	m_vecColor = UI_MAINCOLOR;
	m_flAlpha = 1.0f;
	m_vecSize = [96,24];
	m_iFlags = BUTTON_VISIBLE;
}

void
CUIButton::SetSize(vector vecSize)
{
	m_vecSize = vecSize;
}

vector
CUIButton::GetSize(void)
{
	return m_vecSize;
}

int
CUIButton::GetSizeWidth(void)
{
	return m_vecSize[0];
}

int
CUIButton::GetSizeHeight(void)
{
	return m_vecSize[1];
}

void
CUIButton::SetTitle(string strName)
{
	vector newsize;
	int scale;

	m_strTitle = strName;
	m_strTitleActive = sprintf("^xF00%s", m_strTitle);
	m_strTitleHover = sprintf("^xA10%s", m_strTitle);
	m_strTitleDisabled = sprintf("^x932%s", m_strTitle);
	drawfont = g_fntDefault.iID;

	scale = g_fntDefault.iScale;
	newsize[0] = stringwidth(m_strTitle, TRUE, [scale, scale]) + 16;
	newsize[1] = 24;
	SetSize(newsize);
}
void
CUIButton::SetIcon(string strName)
{
	m_strIcon = strName;
}
void
CUIButton::SetFunc(void(void) vFunc)
{
	m_vFunc = vFunc;
}

void
CUIButton::Draw(void)
{

#ifndef CLASSIC_VGUI
	drawfill(GetAbsolutePos(), m_vecSize, m_vecColor, m_flAlpha);

	if (m_iFlags & BUTTON_DOWN) {
		drawfill(GetAbsolutePos() + [0, m_vecSize[1] - 1], [m_vecSize[0], 1], [1,1,1], 0.5f);
		drawfill(GetAbsolutePos(), [m_vecSize[0], 1], [0,0,0], 0.5f);
		drawfill(GetAbsolutePos() + [0, 1], [1, m_vecSize[1] - 2], [0,0,0], 0.5f);
		drawfill(GetAbsolutePos() + [m_vecSize[0] - 1, 1], [1, m_vecSize[1] - 2], [1,1,1], 0.5f);
	} else {
		drawfill(GetAbsolutePos() + [0, m_vecSize[1] - 1], [m_vecSize[0], 1], [0,0,0], 0.5f);
		drawfill(GetAbsolutePos(), [m_vecSize[0], 1], [1,1,1], 0.5f);
		drawfill(GetAbsolutePos() + [0, 1], [1, m_vecSize[1] - 2], [1,1,1], 0.5f);
		drawfill(GetAbsolutePos() + [m_vecSize[0] - 1, 1], [1, m_vecSize[1] - 2], [0,0,0], 0.5f);
	}
#else
	if (m_iFlags & BUTTON_DOWN) {
		drawfill(GetAbsolutePos(), m_vecSize, m_vecColor, 0.25f);
	}
	if (m_iFlags & BUTTON_DISABLED) {
		drawfill(GetAbsolutePos(), m_vecSize, m_vecColor, 0.15f);
	}
	drawfill(GetAbsolutePos() + [0, m_vecSize[1] - 1], [m_vecSize[0], 1], m_vecColor, 1.0f);
	drawfill(GetAbsolutePos(), [m_vecSize[0], 1], m_vecColor, 1.0f);
	drawfill(GetAbsolutePos() + [0, 1], [1, m_vecSize[1] - 2], m_vecColor, 1.0f);
	drawfill(GetAbsolutePos() + [m_vecSize[0] - 1, 1], [1, m_vecSize[1] - 2], m_vecColor, 1.0f);
#endif

	if (m_strTitle) {
		if (m_iFlags & BUTTON_DISABLED) {
			Font_DrawText(GetAbsolutePos() + [8, 8], m_strTitleDisabled, g_fntDefault);
		} else {
			if (m_iFlags & BUTTON_LASTACTIVE) {
				Font_DrawText(GetAbsolutePos() + [8, 8], m_strTitleActive, g_fntDefault);
			} else if (m_iFlags & BUTTON_HOVER) {
				Font_DrawText(GetAbsolutePos() + [8, 8], m_strTitleHover, g_fntDefault);
			} else {
				Font_DrawText(GetAbsolutePos() + [8, 8], m_strTitle, g_fntDefault);
			}
		}
	}
	if (m_strIcon) {
		drawpic(GetAbsolutePos() + [2,2], m_strIcon, [16,16], [1,1,1], 1.0f, 0);
	}
}

void
CUIButton::Input(float flEVType, float flKey, float flChar, float flDevID)
{
	if (m_iFlags & BUTTON_DISABLED) {
		return;
	}
	// Set the hover flag, in case, we hover...
	if (Util_MouseAbove(getmousepos(), GetAbsolutePos(), m_vecSize)) {
		if (!(m_iFlags & BUTTON_HOVER)) {
			m_iFlags |= BUTTON_HOVER;
	//		localsound("ui/hover.wav");
		}
	} else {
		if (m_iFlags & BUTTON_HOVER)
			m_iFlags &= ~BUTTON_HOVER;
	}
	
	if (flEVType == IE_KEYDOWN) {
		if (flKey == K_MOUSE1) {
			FlagRemove(BUTTON_LASTACTIVE);
			if (Util_MouseAbove(getmousepos(), GetAbsolutePos(), m_vecSize)) {
				FlagAdd(BUTTON_DOWN);
				FlagAdd(BUTTON_LASTACTIVE);
			}
		}
	} else if (flEVType == IE_KEYUP) {
		if (flKey == K_MOUSE1) {
			if (m_iFlags & BUTTON_DOWN && Util_MouseAbove(getmousepos(), GetAbsolutePos(), m_vecSize)) {
				if (m_vFunc) {
					m_vFunc();
				}
			}
			FlagRemove(BUTTON_DOWN);
		}
	}
}
