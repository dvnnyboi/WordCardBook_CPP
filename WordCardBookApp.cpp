//WordCardBookApp.cpp
/************************************************************************************************
���ϸ�Ī: WordCardBookApp.cpp
��    ��: �ܾ���
�� �� ��: �ӴٴϿ�
�ۼ�����: 2022/08/29
*************************************************************************************************/
#include "WordCardBookApp.h"
#include "WordCardBookForm.h"

BOOL WordCardBookApp::InitInstance() {
	WordCardBookForm wordCardBookForm;
	this->m_pMainWnd = &wordCardBookForm;
	wordCardBookForm.DoModal();

	return TRUE;
}
WordCardBookApp wordCardBookApp;