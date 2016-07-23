// RobotButton.cpp : ʵ���ļ�
//

#include "stdafx.h"  

#include "RobotBtn.h"


// CRobotButton

IMPLEMENT_DYNAMIC(CRobotBtn, CButton)

CRobotBtn::CRobotBtn(CRobot * pRobot/* = NULL*/)
	: m_pRobot(pRobot)
	, m_btnColor(RGB(0,255,0))
	, m_nRobotIndex(-1)
{ 
}

CRobotBtn::~CRobotBtn()
{
}


BEGIN_MESSAGE_MAP(CRobotBtn, CButton) 
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_CONTROL_REFLECT(BN_CLICKED, &CRobotBtn::OnBnClicked)
END_MESSAGE_MAP()



// CRobotButton ��Ϣ�������
  
void CRobotBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
}

BOOL CRobotBtn::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

//	return TRUE;
	return CButton::OnEraseBkgnd(pDC);
}

void CRobotBtn::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CButton::OnPaint()

	CRect rect;
	GetClientRect(rect);

	CBrush brush(m_btnColor); 
	dc.FillRect(&rect , &brush);

	CFont * pFont = new CFont;
	pFont->CreatePointFont(70 , _T("΢���ź�"));
	dc.SelectObject(pFont);

	dc.SetBkMode(TRANSPARENT);
 
	CBrush brushPen(RGB(0,0,0)); 
	dc.SelectObject(&brushPen);

	CString str;
	if (m_pRobot)
	{
		str.Format("%s", m_pRobot->GetRobotInfo().strName.c_str());
	}
	else
	{
		str = "None";
	}
	dc.TextOut(0,0, str);


	SAFE_DELETE(pFont);

}

HBRUSH CRobotBtn::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CButton::OnCtlColor(pDC, pWnd, nCtlColor);


	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CRobotBtn::OnBnClicked()
{ 

// 	CollectionRobotInforT::iterator iter = g_RobotData.m_mapRobotInforMgr.find(m_nRobotIndex);
// 
// 	if (iter != g_RobotData.m_mapRobotInforMgr.end())
// 	{
// 		CString str;
// 		str.Format("BaseMapID: %lld \nGameMapID:%lld \n", (iter->second).info.nBaseMapID, (iter->second).info.nGameMapID);
// 		MessageBox(str);

		CString str;
		str.Format("BaseMapID:  \nGameMapID: \n");
		MessageBox(str);
//	} 

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
