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
	TABBUTTON_VISIBLE,
	TABBUTTON_HOVER,
	TABBUTTON_DOWN,
	TABBUTTON_ACTIVE
};

class CUITabButton:CUIWidget
{
	vector m_vecColor;
	float m_flAlpha;
	vector m_vecSize;
	string m_strTitle;
	string m_strTitleActive;
	string m_strIcon;

	void(void) CUITabButton;
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
CUITabButton::CUITabButton(void)
{
	m_vecColor = UI_MAINCOLOR;
	m_flAlpha = 1.0f;
	m_vecSize = [96,24];
	m_iFlags = TABBUTTON_VISIBLE;
}

void
CUITabButton::SetSize(vector vecSize)
{
	m_vecSize = vecSize;
}

vector
CUITabButton::GetSize(void)
{
	return m_vecSize;
}

int
CUITabButton::GetSizeWidth(void)
{
	return m_vecSize[0];
}

int
CUITabButton::GetSizeHeight(void)
{
	return m_vecSize[1];
}

void
CUITabButton::SetTitle(string strName)
{
	vector newsize;
	int scale;

	m_strTitle = strName;
	m_strTitleActive = sprintf("^xFFF%s", m_strTitle);
	drawfont = g_fntDefault.iID;

	scale = g_fntDefault.iScale;
	newsize[0] = stringwidth(m_strTitle, TRUE, [scale, scale]) + 16;
	newsize[1] = 24;
	SetSize(newsize);
}
void
CUITabButton::SetIcon(string strName)
{
	m_strIcon = strName;
}
void
CUITabButton::SetFunc(void(void) vFunc)
{
	m_vFunc = vFunc;
}

void
CUITabButton::Draw(void)
{
#ifndef CLASSIC_VGUI
	drawfill(m_parent.m_parent.m_vecOrigin + m_vecOrigin, m_vecSize, m_vecColor, m_flAlpha);

	if (m_iFlags & TABBUTTON_DOWN) {
	//	drawfill(m_parent.m_vecOrigin + m_vecOrigin + [0, m_vecSize[1] - 1], [m_vecSize[0], 1], [1,1,1], 0.5f);
		drawfill(m_parent.m_vecOrigin + m_vecOrigin, [m_vecSize[0], 1], [0,0,0], 0.5f);
		drawfill(m_parent.m_vecOrigin + m_vecOrigin + [0, 1], [1, m_vecSize[1] - 2], [0,0,0], 0.5f);
		drawfill(m_parent.m_vecOrigin + m_vecOrigin + [m_vecSize[0] - 1, 1], [1, m_vecSize[1] - 2], [1,1,1], 0.5f);
	} else {
	//	drawfill(m_parent.m_vecOrigin + m_vecOrigin + [0, m_vecSize[1] - 1], [m_vecSize[0], 1], [0,0,0], 0.5f);
		drawfill(m_parent.m_vecOrigin + m_vecOrigin, [m_vecSize[0], 1], [1,1,1], 0.5f);
		drawfill(m_parent.m_vecOrigin + m_vecOrigin + [0, 1], [1, m_vecSize[1] - 2], [1,1,1], 0.5f);
		drawfill(m_parent.m_vecOrigin + m_vecOrigin + [m_vecSize[0] - 1, 1], [1, m_vecSize[1] - 2], [0,0,0], 0.5f);
	}
#else
	if (m_iFlags & TABBUTTON_DOWN) {
		drawfill(GetAbsolutePos(), m_vecSize, m_vecColor, 0.25f);
	}
    if (m_iFlags & TABBUTTON_ACTIVE) {
    	drawfill(GetAbsolutePos(), m_vecSize - [0, 1], m_vecColor, 0.75f);	
        //drawfill(m_parent.m_parent.m_vecOrigin + m_vecOrigin + [0, m_vecSize[1] - 1], [m_vecSize[0], 1], m_vecColor, 1.0f);
    }
    if (!(m_iFlags & TABBUTTON_ACTIVE)) {
        drawfill(GetAbsolutePos() + [0, m_vecSize[1] - 1], [m_vecSize[0], 1], m_vecColor, 1.0f);
    }
    
	drawfill(GetAbsolutePos(), [m_vecSize[0], 1], m_vecColor, 1.0f);
	drawfill(GetAbsolutePos() + [0, 1], [1, m_vecSize[1] - 2], m_vecColor, 1.0f);
	drawfill(GetAbsolutePos() + [m_vecSize[0] - 1, 1], [1, m_vecSize[1] - 2], m_vecColor, 1.0f);
#endif

	if (m_strTitle) {
		if (m_iFlags & TABBUTTON_ACTIVE) {
			Font_DrawText(GetAbsolutePos() + [8, 8], m_strTitleActive, g_fntDefault);
		} else {
			Font_DrawText(GetAbsolutePos() + [8, 8], m_strTitle, g_fntDefault);
		}
	}
	if (m_strIcon) {
		drawpic(GetAbsolutePos() + [2,2], m_strIcon, [16,16], [1,1,1], 1.0f, 0);
	}
    Font_DrawText([8, video_res[1] - 42], sprintf("Mouse Position: %d, %d\n", getmousepos()[0], getmousepos()[1]), g_fntDefault);
}

void
CUITabButton::Input(float flEVType, float flKey, float flChar, float flDevID)
{
	if (flEVType == IE_KEYDOWN) {
		if (flKey == K_MOUSE1) {
			FlagRemove(TABBUTTON_ACTIVE);
			if (Util_MouseAbove(getmousepos(), GetAbsolutePos(), m_vecSize)) {
				FlagAdd(TABBUTTON_DOWN);
			}
		}
	} else if (flEVType == IE_KEYUP) {
		if (flKey == K_MOUSE1) {
			if (m_iFlags & TABBUTTON_DOWN && Util_MouseAbove(getmousepos(), GetAbsolutePos(), m_vecSize)) {
				FlagAdd(TABBUTTON_ACTIVE);
                if (m_vFunc) {
					m_vFunc();
				}
			}
			FlagRemove(TABBUTTON_DOWN);
		}
	}
}
