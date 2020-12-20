class CUIGroupList {
    void(void) CUIGroupList;

    hashtable m_hashGroupList;
    virtual int(string) IsVisible;
    virtual void(string) Add;
    virtual void(string, float) SetVisible;
};

void 
CUIGroupList::CUIGroupList(void)
{
    m_hashGroupList = __NULL__;
    m_hashGroupList = hash_createtab(2, HASH_ADD);
}

int
CUIGroupList::IsVisible(string name)
{
    if ((float)hash_get(m_hashGroupList, name) == 1)
        return 1;
    else
        return 0;    
}
void
CUIGroupList::Add(string name)
{

    if (hash_get(m_hashGroupList, name) == 0) {
        hash_add(m_hashGroupList, name, 0.0f, 0);
    }
}

void
CUIGroupList::SetVisible(string name, float visible)
{
    hash_add(m_hashGroupList, name, visible, HASH_REPLACE);
}