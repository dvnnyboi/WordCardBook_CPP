//WordCardBookApp.cpp
/************************************************************************************************
파일명칭: WordCardBookApp.cpp
기    능: 단어장
작 성 자: 임다니엘
작성일자: 2022/08/29
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