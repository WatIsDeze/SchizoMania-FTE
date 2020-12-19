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
CUITabArea::CUITabArea(void)
{
	CUIWidget::CUIWidget();
	m_vecColor = UI_MAINCOLOR;
	m_flAlpha = 1.0f;
	m_vecButtonSize = [96,24];
	m_iFlags = TABAREA_VISIBLE;
}

void
CUITabArea::Add(CUIWidget wNew)
{
	// TODO: Maybe make a get/set for this.
	wNew.m_strGroupName = m_strChildrenGroupName;
	
	g_vguiGroupList.Add(m_strChildrenGroupName);
	dprint("===============");
	dprint(sprintf("wNew.m_strGroupName = %s\n", wNew.m_strGroupName));
	CUIWidget::Add(wNew);
}

void
CUITabArea::SetSize(vector vecSize)
{
	m_vecAreaSize = vecSize;
}

vector
CUITabArea::GetButtonSize(void)
{
	return m_vecButtonSize;
}

int
CUITabArea::GetButtonSizeWidth(void)
{
	return m_vecButtonSize[0];
}

int CUITabArea::GetButtonSizeHeight(void)
{
	return m_vecButtonSize[1];
}

vector
CUITabArea::GetAreaSize(void)
{
	return m_vecAreaSize;
}

int
CUITabArea::GetAreaSizeWidth(void)
{
	return m_vecAreaSize[0];
}

int
CUITabArea::GetAreaSizeHeight(void)
{
	return m_vecAreaSize[1];
}

void
CUITabArea::SetTitle(string strName)
{
	vector newsize;
	int scale;

	m_strTitle = strName;
	m_strTitleActive = sprintf("^xFFF%s", m_strTitle);
	drawfont = g_fntDefault.iID;

	scale = g_fntDefault.iScale;
	m_vecButtonSize[0] = stringwidth(m_strTitle, TRUE, [scale, scale]) + 16;
	m_vecButtonSize[1] = 24;

	// Generate unique group name for this tab. (No need to repeat this if a title changes.)
	m_strChildrenGroupName = strcat("tab_", m_strTitle, sprintf("_%i", frametime));
}
void
CUITabArea::SetIcon(string strName)
{
	m_strIcon = strName;
}
void
CUITabArea::SetFunc(void(void) vFunc)
{
	m_vFunc = vFunc;
}

void
CUITabArea::Draw(void)
{
	if (g_vguiGroupList.IsVisible(m_strGroupName)) {
		FlagAdd(TABAREA_ACTIVE);
	} else {
		FlagRemove(TABAREA_ACTIVE);
	}
#ifndef CLASSIC_VGUI
	drawfill(m_parent.m_parent.m_vecOrigin + m_vecOrigin, m_vecSize, m_vecColor, m_flAlpha);

	if (m_iFlags & TABAREA_DOWN) {
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
	// Background.
	if (m_iFlags & TABAREA_DOWN) {
		drawfill(GetAbsolutePos(), m_vecButtonSize, m_vecColor, 0.35f);
	} else if (m_iFlags & TABAREA_ACTIVE) {
    	drawfill(GetAbsolutePos(), m_vecButtonSize - [0, 1], m_vecColor, 0.55f);	
    } else {
		drawfill(GetAbsolutePos(), m_vecButtonSize - [0, 1], m_vecColor, 0.15f);	
	}
    
	drawfill(GetAbsolutePos(), [m_vecButtonSize[0], 1], m_vecColor, 1.0f);
    if (!(m_iFlags & TABAREA_ACTIVE)) {
        drawfill(GetAbsolutePos() + [0, m_vecButtonSize[1] - 1], [m_vecButtonSize[0], 1], m_vecColor, 1.0f);
    }
	drawfill(GetAbsolutePos() + [0, 1], [1, m_vecButtonSize[1] - 2], m_vecColor, 1.0f);
	drawfill(GetAbsolutePos() + [m_vecButtonSize[0] - 1, 1], [1, m_vecButtonSize[1] - 2], m_vecColor, 1.0f);
#endif

	if (m_strTitle) {
		if (m_iFlags & TABAREA_ACTIVE) {
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
CUITabArea::Input(float flEVType, float flKey, float flChar, float flDevID)
{
	if (flEVType == IE_KEYDOWN) {
		if (flKey == K_MOUSE1) {
			// Only remove if the mouse is out of bounds.
			// FlagRemove(TABAREA_ACTIVE);
			if (Util_MouseAbove(getmousepos(), GetAbsolutePos(), m_vecButtonSize)) {
				FlagAdd(TABAREA_DOWN);
			}
		}
	} else if (flEVType == IE_KEYUP) {
		if (flKey == K_MOUSE1) {
			if (m_iFlags & TABAREA_DOWN && Util_MouseAbove(getmousepos(), GetAbsolutePos(), m_vecButtonSize)) {
				// FlagAdd(TABAREA_ACTIVE);

				// We're gonna inform the parent TabView that this button got activated.
				// It'll hide all others.
				CUITabView parent = (CUITabView)m_parent;
				parent.SwitchActiveTab(this);

                if (m_vFunc) {
					m_vFunc();
				}
			}
			FlagRemove(TABAREA_DOWN);
		}
	}
}
