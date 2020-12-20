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

#ifdef MENU
enumflags
{
	// Button states.
	MBUTTON_VISIBLE = UI_VISIBLE,
	MBUTTON_HOVER,
	MBUTTON_DOWN,

	// Show flags.
	MBUTTON_TEXTONLY,
	MBUTTON_SHOWOFFLINE,
	MBUTTON_SHOWSP,
	MBUTTON_SHOWMP,
};

class CUIMenuButton:CUIWidget
{
	vector m_vecColor;
	float m_flAlpha;
	vector m_vecSize;
	string m_strTitle;
	string m_strIcon;
	
	void(void) CUIMenuButton;
	virtual void(void) m_vFunc = 0;
	virtual void(void) Draw;
	virtual void(vector) SetSize;
	virtual void(string) SetTitle;
	virtual void(string) SetIcon;
	virtual void(void(void)) SetFunc;
	virtual void(float, float, float, float) Input;
};

void CUIMenuButton::CUIMenuButton(void)
{
	m_vecColor = UI_MAINCOLOR;
	m_flAlpha = 1.0f;
	m_vecSize = [96,24];
	m_iFlags = MBUTTON_VISIBLE | MBUTTON_SHOWOFFLINE | MBUTTON_SHOWSP | MBUTTON_SHOWMP;
}

void CUIMenuButton::Draw(void)
{
	// If we're not ingame
	if (clientstate() == 2 && !g_background) {
		if (!(m_iFlags & MBUTTON_SHOWSP)) {
			return;
		}
	} else {
		if (!(m_iFlags & MBUTTON_SHOWOFFLINE)) {
			return;
		}
	}
	
	if (!(m_iFlags & MBUTTON_TEXTONLY)) {
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
			drawfill(GetAbsolutePos() + [0, m_vecSize[1] - 1], [m_vecSize[0], 1], m_vecColor, 1.0f);
			drawfill(GetAbsolutePos(), [m_vecSize[0], 1], m_vecColor, 1.0f);
			drawfill(GetAbsolutePos() + [0, 1], [1, m_vecSize[1] - 2], m_vecColor, 1.0f);
			drawfill(GetAbsolutePos() + [m_vecSize[0] - 1, 1], [1, m_vecSize[1] - 2], m_vecColor, 1.0f);
		#endif

			
			if (m_strIcon) {
				drawpic(GetAbsolutePos() + [4, 4], m_strIcon, [16,16], [1,1,1], 1.0f);
				if (m_strTitle) {
					Font_DrawText(GetAbsolutePos() + [26, 8], m_strTitle, g_fntDefault);
				}
			} else {
				if (m_strTitle) {
					Font_DrawText(GetAbsolutePos() + [8, 8], m_strTitle, g_fntDefault);
				}
			}
	} else {
		if (m_iFlags & MBUTTON_HOVER) {
			if (m_strTitle) {
				Font_DrawText(GetAbsolutePos() + [8, 8], strcat("^xF00", m_strTitle), g_fntDefault);
				//Font_DrawText(m_parent.m_vecOrigin + m_vecOrigin + [8, 256], "^xF00 One, ^2 Two, ^3 Three, ^4 Four, ^5 Five, ^6 Six, ^7 Seven", g_fntDefault);
			}
		} else {
			if (m_strTitle) {
				Font_DrawText(GetAbsolutePos() + [8, 8], m_strTitle, g_fntDefault);
			}
		}
	}
}

void CUIMenuButton::Input (float flEVType, float flKey, float flChar, float flDevID)
{
	// If we're not ingame
	if (clientstate() == 2 && !g_background) {
		if (!(m_iFlags & MBUTTON_SHOWSP)) {
			return;
		}
	} else {
		if (!(m_iFlags & MBUTTON_SHOWOFFLINE)) {
			return;
		}
	}

	// Set the hover flag, in case, we hover...
	if (Util_MouseAbove(getmousepos(), GetAbsolutePos(), m_vecSize)) {
		if (!(m_iFlags & MBUTTON_HOVER))
			m_iFlags |= MBUTTON_HOVER;
	} else {
		if (m_iFlags & MBUTTON_HOVER)
			m_iFlags &= ~MBUTTON_HOVER;
	}

	// Handle mouse button down on hover, and if released within button, execute a click event.
	if (flEVType == IE_KEYDOWN) {
		if (flKey == K_MOUSE1) {
			if (Util_MouseAbove(getmousepos(), GetAbsolutePos(), m_vecSize)) {
				m_iFlags |= MBUTTON_DOWN;
			}
		}
	} else if (flEVType == IE_KEYUP) {
		if (flKey == K_MOUSE1) {
			if (m_iFlags & MBUTTON_DOWN && Util_MouseAbove(getmousepos(), GetAbsolutePos(), m_vecSize)) {
				if (m_vFunc) {
					m_vFunc();
				}
			}
			m_iFlags -= (m_iFlags & MBUTTON_DOWN);
		}
	}
}

void CUIMenuButton::SetSize (vector vecSize)
{
	m_vecSize = vecSize;
}
void CUIMenuButton::SetTitle (string strName)
{
	m_strTitle = strName;
}
void CUIMenuButton::SetIcon (string strName)
{
	m_strIcon = strName;
}
void CUIMenuButton::SetFunc (void(void) vFunc)
{
	m_vFunc = vFunc;
}
#endif
