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
	TABVIEW_VISIBLE = UI_VISIBLE
};
class CUITabView:CUIWidget
{
	vector m_vecSize;
	vector m_vecColor;
	string m_strTitle;
	
	// Reference to currently active tab.
	CUITabArea m_tabActive;

	// A bit of a cheesy hack, but it works.
	int m_iTotalButtonWidth;

	void(void) CUITabView;

	virtual CUITabArea(string title, void(void) vFunc) AddTabButton;
	virtual void(CUITabArea) SwitchActiveTab;

	virtual void(void) Draw;
	virtual void(vector) SetPos;
	virtual void(vector) SetSize;
	virtual void(string) SetTitle;
	virtual void(float, float, float, float) Input;
};

void CUITabView::CUITabView(void)
{
	m_vecColor = UI_MAINCOLOR;
	m_vecSize = [320,240];
	m_iTotalButtonWidth = 0;
	m_iFlags = TABVIEW_VISIBLE;
}

CUITabArea CUITabView::AddTabButton(string title, void(void) vFunc)
{
	// Create our tab widget.
	CUITabArea tabArea = spawn( CUITabArea );
	tabArea.SetTitle(title);
	tabArea.SetPos([m_iTotalButtonWidth, 0]);
	tabArea.SetFunc(vFunc);
	
	// Increment nextbutton pos.
	m_iTotalButtonWidth += tabArea.GetButtonSize()[0] + 1;
	
	// Add as a tab child widget.
	Add(tabArea);

	// Latest added tab is active by default.
	SwitchActiveTab(tabArea);

	// Return.
	return tabArea;
}

void CUITabView::SwitchActiveTab(CUITabArea tabArea)
{
	if (m_tabActive)
		g_vguiGroupList.SetVisible(m_tabActive.m_strChildrenGroupName, 0);
		
	g_vguiGroupList.SetVisible(tabArea.m_strChildrenGroupName, 1);
	m_tabActive = tabArea;
}
void CUITabView::SetPos(vector vecPos)
{
	m_vecOrigin = vecPos;
}
void CUITabView::SetSize (vector vecSize)
{
	m_vecSize = vecSize;
}
void CUITabView::SetTitle (string strName)
{
	// We set the title, but it's not being used for the Tab control.
	m_strTitle = strName;
}

void CUITabView::Draw(void)
{
	CUIWidget::Draw();

	// Draw.
	drawfill(GetAbsolutePos() + [0, m_vecSize[1]], [m_vecSize[0], 1], m_vecColor, 1.0f);
	drawfill(GetAbsolutePos() + [m_iTotalButtonWidth, 23], [m_vecSize[0] - m_iTotalButtonWidth, 1], m_vecColor, 1.0f);
	drawfill(GetAbsolutePos() + [0, 24], [1, m_vecSize[1] - 24], m_vecColor, 1.0f);
	drawfill(GetAbsolutePos() + [m_vecSize[0], 24], [1, m_vecSize[1] - 23], m_vecColor, 1.0f);
}

void CUITabView::Input (float flEVType, float flKey, float flChar, float flDevID)
{
}
