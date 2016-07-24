#pragma once
#include "CRobot.h"

using namespace Robot;
// CRobotBtn

class CRobotBtn : public CButton
{
	DECLARE_DYNAMIC(CRobotBtn)

public:
	CRobotBtn(CRobot * pRobot = NULL);
	virtual ~CRobotBtn();

protected:
	virtual void				DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg BOOL				OnEraseBkgnd(CDC* pDC);
	afx_msg void				OnPaint();
	afx_msg HBRUSH				OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void				OnBnClicked();

	DECLARE_MESSAGE_MAP()
	
public: 

public:
	INT64						GetRobotIndex() const { return m_nRobotIndex; }
	void						SetRobotIndex(INT64 val) { m_nRobotIndex = val; }
	CRect						GetRectPos() const { return m_rectPos; }
	void						SetRectPos(CRect val) { m_rectPos = val; }
	void						SetBtnColor(COLORREF colorRef) { m_btnColor = colorRef; }
	CRobot				*		GetRobot() const { return m_pRobot; }
	void						SetRobot(CRobot * val) { m_pRobot = val; }

protected:
	CRect						m_rectPos;
	INT64						m_nRobotIndex;		//5 ������Ҫ������Robot��Index
	CRobot				*		m_pRobot;
	COLORREF					m_btnColor;

};


