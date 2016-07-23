// E:\GitHub\GameLib\Tools\src\RobotCtrl\src\ListCtrlEx.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RobotCtrl.h"
#include "ListBoxEx.h"
#include "DlgRobotCtrl.h"


// CListCtrlEx

IMPLEMENT_DYNAMIC(CListBoxEx, CListBox)

CListBoxEx::CListBoxEx()
{

}

CListBoxEx::~CListBoxEx()
{
}


BEGIN_MESSAGE_MAP(CListBoxEx, CListBox)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// CListCtrlEx ��Ϣ�������




void CListBoxEx::OnRButtonDown(UINT nFlags, CPoint point)
{

	POINT   pt;
	GetCursorPos(&pt);
	int nCount = GetCount();
	ScreenToClient(&pt);
	//ʵ���Ҽ����ѡ��Ŀ��
	for (int i = 0; i < nCount; i++)
	{
		CRect rc;
		GetItemRect(i, &rc);
		if (rc.PtInRect(pt))
		{
			SetCurSel(i);
			CMenu temp, *pSubMenu;
			temp.LoadMenu(IDR_MENU_ROBOT_SERVER);
			pSubMenu = temp.GetSubMenu(0);
			ClientToScreen(&pt);
			pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, pt.x, pt.y, GetParent());

			CDlgRobotCtrl* pDlg = dynamic_cast<CDlgRobotCtrl*>(GetParent());
			if (pDlg)
			{
				pDlg->OnSelchangeListCtrlServer();
			}
			break;
		}
	}

	CListBox::OnRButtonDown(nFlags, point);
}