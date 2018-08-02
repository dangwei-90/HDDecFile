// HDEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "HDDecFile.h"
#include "HDEdit.h"


// CHDEdit

IMPLEMENT_DYNAMIC(CHDEdit, CEdit)

CHDEdit::CHDEdit()
{

}

CHDEdit::~CHDEdit()
{
}


BEGIN_MESSAGE_MAP(CHDEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CHDEdit 消息处理程序


void CHDEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	return CEdit::OnChar(nChar, nRepCnt, nFlags);

	CString strValue;
	GetWindowText(strValue);
	if (nChar == 8 || strValue.GetLength() == 0)
	{
		return CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else
	{
		return;
	}
}
