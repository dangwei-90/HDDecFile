#pragma once


// CHDEdit

class CHDEdit : public CEdit
{
	DECLARE_DYNAMIC(CHDEdit)

public:
	CHDEdit();
	virtual ~CHDEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


