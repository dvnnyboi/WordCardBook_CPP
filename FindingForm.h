//FindingForm.h
/************************************************************************************************
파일명칭: FindingForm.h
기    능: 단어장 찾기 윈도우
작 성 자: 임다니엘
작성일자: 2022/08/29
*************************************************************************************************/
#ifndef _FINDINGFORM_H
#define _FINDINGFORM_H
#include <afxwin.h>
#include "resource.h"

typedef signed long int Long;
class FindingForm : public CDialog {
public:
	enum { IDD = IDD_FINDINGFORM };
public:
	FindingForm(CWnd* parent = NULL);
	virtual BOOL OnInitDialog();
public:
	Long(*indexes);
	Long count;
protected:
	afx_msg void OnFindButtonClicked();
	afx_msg void OnListViewItemDoubleClicked(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnSpellingRadioButtonClicked();
	afx_msg void OnMeaningRadioButtonClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif //_FINDINGFORM_H