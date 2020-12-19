
enumflags
{
	TABBUTTON_VISIBLE = UI_VISIBLE,
	TABBUTTON_HOVER,
	TABBUTTON_DOWN,
	TABBUTTON_ACTIVE
};

class CUITabArea:CUIWidget
{
	vector m_vecColor;
	float m_flAlpha;
	
	vector m_vecAreaSize;
	vector m_vecButtonSize;

	string m_strTitle;
	string m_strTitleActive;
	string m_strIcon;

	void(void) CUITabArea;
	virtual void(void) m_vFunc = 0;
	virtual void(void) Draw;

	virtual vector() GetButtonSize;
	virtual int(void) GetButtonSizeWidth;
	virtual int(void) GetButtonSizeHeight;

	virtual vector() GetAreaSize;
	virtual int(void) GetAreaSizeWidth;
	virtual int(void) GetAreaSizeHeight;

	virtual void(vector) SetSize;
	virtual void(string) SetTitle;
	virtual void(string) SetIcon;
	virtual void(void(void)) SetFunc;

	virtual void(float, float, float, float) Input;
};