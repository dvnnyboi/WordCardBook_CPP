//WordCardBookForm.h
/************************************************************************************************
���ϸ�Ī: WordCardBookForm.h
��    ��: �ܾ��� ������
�� �� ��: �ӴٴϿ�
�ۼ�����: 2022/08/29
*************************************************************************************************/
#ifndef _WORDACRDBOOKFORM_H
#define _WORDCARDBOOKFORM_H
#include <afxwin.h>
#include "resource.h"

typedef signed long int Long;
class WordCardBook;
class WordCardBookForm : public CDialog {
public:
	enum { IDD = IDD_WORDCARDBOOKFORM };
public:
	WordCardBookForm(CWnd* parent = NULL);
	virtual BOOL OnInitDialog();
	void Load();
	void Save();
	void Insert(Long index);
	void Modify(Long index);
	void Delete(Long index);
	CString GetCode();
public:
	WordCardBook* wordCardBook;
protected:
	afx_msg void OnRecordButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnCorrectButtonClicked();
	afx_msg void OnEraseButtonClicked();
	afx_msg void OnArrangeButtonClicked();
	afx_msg void OnListViewItemDoubleClicked(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnSpellingKillFocus();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};


#endif //_WORDCARDBOOKFORM_H