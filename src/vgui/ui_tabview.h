enumflags
{
	TABVIEW_VISIBLE = UI_VISIBLE
};
class CUITabView:CUIWidget
{
	vector m_vecSize;
	vector m_vecColor;
	string m_strTitle;
	
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