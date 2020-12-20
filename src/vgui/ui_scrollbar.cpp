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
	SCROLLBAR_VISIBLE = UI_VISIBLE,
	SCROLLBAR_UP_DOWN,
	SCROLLBAR_DN_DOWN,
	SCROLLBAR_SLIDER_DOWN
};

class CUIScrollbar:CUIWidget
{
	vector m_vecColor;
	float m_flAlpha;
	
	int m_iLength;
	
	float m_flMin;
	float m_flMax;
	float m_flStep;
	float m_flValue;
	
	void(void) CUIScrollbar;
	virtual void(void) m_vChangedCB = 0;
	
	virtual void(int) SetLength;
	virtual int(void) GetLength;
	virtual void(float) SetMin;
	virtual float() GetMin;
	virtual void(float) SetMax;
	virtual float() GetMax;
	virtual void(float) SetStep;
	virtual float() GetStep;
	virtual void(float, int) SetValue;
	virtual float() GetValue;
	
	virtual void(void(void)) CallOnChange;
	
	virtual void(float, float, float, float) Input;
	virtual void(void) Draw;
};

void CUIScrollbar::CUIScrollbar(void)
{
	m_vecColor = UI_MAINCOLOR;
	m_flAlpha = 1.0f;
	m_iFlags = SCROLLBAR_VISIBLE;
}

void CUIScrollbar::Draw(void)
{
	vector vecSize = [20, m_iLength];

#ifndef CLASSIC_VGUI
	drawfill(GetAbsolutePos(), vecSize, m_vecColor, m_flAlpha);

	if (m_iFlags & BUTTON_DOWN) {
		drawfill(GetAbsolutePos() + [0, vecSize[1] - 1], [vecSize[0], 1], [1,1,1], 0.5f);
		drawfill(GetAbsolutePos(), [vecSize[0], 1], [0,0,0], 0.5f);
		drawfill(GetAbsolutePos() + [0, 1], [1, vecSize[1] - 2], [0,0,0], 0.5f);
		drawfill(GetAbsolutePos() + [vecSize[0] - 1, 1], [1, vecSize[1] - 2], [1,1,1], 0.5f);
	} else {
		drawfill(GetAbsolutePos() + [0, vecSize[1] - 1], [vecSize[0], 1], [0,0,0], 0.5f);
		drawfill(GetAbsolutePos(), [vecSize[0], 1], [1,1,1], 0.5f);
		drawfill(GetAbsolutePos() + [0, 1], [1, vecSize[1] - 2], [1,1,1], 0.5f);
		drawfill(GetAbsolutePos() + [vecSize[0] - 1, 1], [1, vecSize[1] - 2], [0,0,0], 0.5f);
	}
#else
	drawfill(GetAbsolutePos() + [0, vecSize[1] - 1], [vecSize[0], 1], m_vecColor, 1.0f);
	drawfill(GetAbsolutePos(), [vecSize[0], 1], m_vecColor, 1.0f);
	drawfill(GetAbsolutePos() + [0, 1], [1, vecSize[1] - 2], m_vecColor, 1.0f);
	drawfill(GetAbsolutePos() + [vecSize[0] - 1, 1], [1, vecSize[1] - 2], m_vecColor, 1.0f);
#endif

	vector vecUpPos = GetAbsolutePos();
	vector vecDownPos = GetAbsolutePos() + [0, m_iLength - 20];
	vector vecSliderPos = GetAbsolutePos() + [0, 20];
	
	vecSliderPos[1] += (m_iLength - 60) * (m_flValue / m_flMax);
	
	// Slider Button
	drawfill(vecSliderPos, [20,20], m_vecColor, m_flAlpha);
	if (m_iFlags & SCROLLBAR_SLIDER_DOWN) {
		drawfill(vecSliderPos, [20, 1], [0,0,0], 0.5f);
		drawfill(vecSliderPos + [0, 19], [20, 1], [1,1,1], 0.5f);
		drawfill(vecSliderPos + [0, 1], [1, 18], [0,0,0], 0.5f);
		drawfill(vecSliderPos + [19, 1], [1, 18], [1,1,1], 0.5f);
	} else {
		drawfill(vecSliderPos, [20, 1], [1,1,1], 0.5f);
		drawfill(vecSliderPos + [0, 19], [20, 1], [0,0,0], 0.5f);
		drawfill(vecSliderPos + [0, 1], [1, 18], [1,1,1], 0.5f);
		drawfill(vecSliderPos + [19, 1], [1, 18], [0,0,0], 0.5f);
	}

	// Button UP
#ifndef CLASSIC_VGUI
	drawfill(vecUpPos, [20,20], m_vecColor, m_flAlpha);
	if (m_iFlags & SCROLLBAR_UP_DOWN) {
		drawfill(vecUpPos, [20, 1], [0,0,0], 0.5f);
		drawfill(vecUpPos + [0, 19], [20, 1], [1,1,1], 0.5f);
		drawfill(vecUpPos + [0, 1], [1, 18], [0,0,0], 0.5f);
		drawfill(vecUpPos + [19, 1], [1, 18], [1,1,1], 0.5f);
	} else {
		drawfill(vecUpPos, [20, 1], [1,1,1], 0.5f);
		drawfill(vecUpPos + [0, 19], [20, 1], [0,0,0], 0.5f);
		drawfill(vecUpPos + [0, 1], [1, 18], [1,1,1], 0.5f);
		drawfill(vecUpPos + [19, 1], [1, 18], [0,0,0], 0.5f);
	}
	drawpic(vecUpPos + [2,2], "textures/ui/steam/icon_up", [16,16], [1,1,1], 1.0f, 0);
#else
	if (m_iFlags & SCROLLBAR_UP_DOWN) {
		drawfill(vecUpPos, [20,20], m_vecColor, 0.25f);
		drawfill(vecUpPos, [20, 1], m_vecColor, 1.0f);
		drawfill(vecUpPos + [0, 19], [20, 1], m_vecColor, 1.0f);
		drawfill(vecUpPos + [0, 1], [1, 18], m_vecColor, 1.0f);
		drawfill(vecUpPos + [19, 1], [1, 18], m_vecColor, 1.0f);
	} else {
		drawfill(vecUpPos, [20, 1], [1,1,1], 0.5f);
		drawfill(vecUpPos + [0, 19], [20, 1], m_vecColor, 1.0f);
		drawfill(vecUpPos + [0, 1], [1, 18], m_vecColor, 1.0f);
		drawfill(vecUpPos + [19, 1], [1, 18], m_vecColor, 1.0f);
	}
	drawpic(vecUpPos + [2,2], "textures/ui/steam/icon_up", [16,16], m_vecColor, 1.0f, 0);
#endif
	// Button DOWN
#ifndef CLASSIC_VGUI
	drawfill(vecDownPos, [20,20], m_vecColor, m_flAlpha);
	if (m_iFlags & SCROLLBAR_DN_DOWN) {
		drawfill(vecDownPos, [20, 1], [0,0,0], 0.5f);
		drawfill(vecDownPos + [0, 19], [20, 1], [1,1,1], 0.5f);
		drawfill(vecDownPos + [0, 1], [1, 18], [0,0,0], 0.5f);
		drawfill(vecDownPos + [19, 1], [1, 18], [1,1,1], 0.5f);
	} else {
		drawfill(vecDownPos, [20, 1], [1,1,1], 0.5f);
		drawfill(vecDownPos+ [0, 19], [20, 1], [0,0,0], 0.5f);
		drawfill(vecDownPos + [0, 1], [1, 18], [1,1,1], 0.5f);
		drawfill(vecDownPos + [19, 1], [1, 18], [0,0,0], 0.5f);
	}
	drawpic(vecDownPos + [2,2], "textures/ui/steam/icon_down", [16,16], [1,1,1], 1.0f, 0);
#else
	if (m_iFlags & SCROLLBAR_DN_DOWN) {
		drawfill(vecDownPos, [20,20], m_vecColor, 0.25f);
		drawfill(vecDownPos, [20, 1], m_vecColor, 1.0f);
		drawfill(vecDownPos + [0, 19], [20, 1], m_vecColor, 1.0f);
		drawfill(vecDownPos + [0, 1], [1, 18], m_vecColor, 1.0f);
		drawfill(vecDownPos + [19, 1], [1, 18], m_vecColor, 1.0f);
	} else {
		drawfill(vecDownPos, [20, 1], m_vecColor, 1.0f);
		drawfill(vecDownPos+ [0, 19], [20, 1], m_vecColor, 1.0f);
		drawfill(vecDownPos + [0, 1], [1, 18], m_vecColor, 1.0f);
		drawfill(vecDownPos + [19, 1], [1, 18], m_vecColor, 1.0f);
	}
	drawpic(vecDownPos + [2,2], "textures/ui/steam/icon_down", [16,16], m_vecColor, 1.0f, 0);
#endif
}

void CUIScrollbar::Input (float flEVType, float flKey, float flChar, float flDevID)
{
	vector vecUpPos = GetAbsolutePos();
	vector vecDownPos = GetAbsolutePos() + [0, m_iLength - 20];
	
	if (flEVType == IE_KEYDOWN) {
		if (flKey == K_MOUSE1) {
			if (Util_MouseAbove(getmousepos(), vecUpPos, [20,20])) {
				m_iFlags |= SCROLLBAR_UP_DOWN;
			} else if (Util_MouseAbove(getmousepos(), vecDownPos, [20,20])) {
				m_iFlags |= SCROLLBAR_DN_DOWN;
			}
		}
	} else if (flEVType == IE_KEYUP) {
		if (flKey == K_MOUSE1) {
			if (m_iFlags & SCROLLBAR_UP_DOWN && Util_MouseAbove(getmousepos(), vecUpPos, [20,20])) {
				SetValue(GetValue() - GetStep(), TRUE);
			} else if (m_iFlags & SCROLLBAR_DN_DOWN && Util_MouseAbove(getmousepos(), vecDownPos, [20,20])) {
				SetValue(GetValue() + GetStep(), TRUE);
			}
			m_iFlags -= (m_iFlags & SCROLLBAR_UP_DOWN);
			m_iFlags -= (m_iFlags & SCROLLBAR_DN_DOWN);
		} else if (flKey == K_MWHEELDOWN && Util_MouseAbove(getmousepos(), GetAbsolutePos(), [20, m_iLength])) {
			SetValue(GetValue() + GetStep(), TRUE);
		} else if (flKey == K_MWHEELUP && Util_MouseAbove(getmousepos(), GetAbsolutePos(), [20, m_iLength])) {
			SetValue(GetValue() - GetStep(), TRUE);
		}
	}
}

void CUIScrollbar::SetLength (int iLength)
{
	m_iLength = iLength;
}
int CUIScrollbar::GetLength(void)
{
	return m_iLength;
}

void CUIScrollbar::SetMin (float flVal)
{
	m_flMin = flVal;
}
float CUIScrollbar::GetMin(void)
{
	return m_flMin;
}

void CUIScrollbar::SetMax (float flVal)
{
	m_flMax = flVal;
}
float CUIScrollbar::GetMax(void)
{
	return m_flMax;
}

void CUIScrollbar::SetStep (float flVal)
{
	m_flStep = flVal;
}
float CUIScrollbar::GetStep(void)
{
	return m_flStep;
}

void CUIScrollbar::SetValue (float flVal, int iCallBack)
{
	m_flValue = bound(m_flMin, flVal, m_flMax);
	
	if (m_vChangedCB && iCallBack) {
		m_vChangedCB();
	}
}
float CUIScrollbar::GetValue(void)
{
	return m_flValue;
}

void CUIScrollbar::CallOnChange (void(void) vFunc)
{
	m_vChangedCB = vFunc;
}
