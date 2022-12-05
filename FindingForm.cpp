//FindingForm.cpp
/************************************************************************************************
파일명칭: FindingForm.cpp
기    능: 단어장 찾기 윈도우
작 성 자: 임다니엘
작성일자: 2022/08/29
*************************************************************************************************/
#include "FindingForm.h"
#include "WordCardBookForm.h"
#include "WordCardBook.h"
#include <afxcmn.h>

/************************************************************************************************/
BEGIN_MESSAGE_MAP(FindingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FINDBY, OnFindButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_WORDS, OnListViewItemDoubleClicked)
	ON_BN_CLICKED(IDC_RADIO_SPELLING, OnSpellingRadioButtonClicked)
	ON_BN_CLICKED(IDC_RADIO_MEANING, OnMeaningRadioButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()
/************************************************************************************************
명    칭: FindingForm
기    능: 생성자
*************************************************************************************************/
FindingForm::FindingForm(CWnd* parent)
	: CDialog(FindingForm::IDD, parent) {
	this->indexes = NULL;
	this->count = 0;
}
/************************************************************************************************
명    칭: OnInitDialog
기    능: 윈도우가 생성될 때 시나리오.
*************************************************************************************************/
BOOL FindingForm::OnInitDialog() {
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertColumn(0, "번호", LVCFMT_CENTER, 40);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertColumn(1, "철자", LVCFMT_CENTER, 70);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertColumn(2, "품사", LVCFMT_CENTER, 60);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertColumn(3, "뜻", LVCFMT_CENTER, 60);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertColumn(4, "예문", LVCFMT_CENTER, 150);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	((CButton*)this->GetDlgItem(IDC_RADIO_SPELLING))->SetCheck(BST_CHECKED);
	this->GetDlgItem(IDC_EDIT_MEANING)->EnableWindow(FALSE);

	return FALSE;
}
/************************************************************************************************
명    칭: OnFindButtonClicked
기    능: 찾기 버튼을 클릭했을 때 시나리오.
*************************************************************************************************/
void FindingForm::OnFindButtonClicked() {
	CString spelling;
	CString meaning;
	CString number;
	Long spellingRadio;
	Long meaningRadio;
	WordCard wordCard;
	WordCardBookForm* wordCardBookForm;

	spellingRadio = ((CButton*)this->GetDlgItem(IDC_RADIO_SPELLING))->GetCheck();
	this->GetDlgItem(IDC_EDIT_SPELLING)->GetWindowText(spelling);
	meaningRadio = ((CButton*)this->GetDlgItem(IDC_RADIO_MEANING))->GetCheck();
	this->GetDlgItem(IDC_EDIT_MEANING)->GetWindowText(meaning);
	wordCardBookForm = (WordCardBookForm*)CWnd::FindWindowA("#32770", "단어장");
	if (this->indexes != NULL) {
		delete[]this->indexes;
	}
	if (spellingRadio == BST_CHECKED) {
		wordCardBookForm->wordCardBook->FindBySpelling((LPCTSTR)spelling, &(this->indexes), &(this->count));
	}
	else if(meaningRadio == BST_CHECKED){
		wordCardBookForm->wordCardBook->FindByMeaning((LPCTSTR)meaning, &(this->indexes), &(this->count));
	}
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->DeleteAllItems();
	Long i = 0;
	while (i < this->count) {
		wordCard = wordCardBookForm->wordCardBook->GetAt(this->indexes[i]);
		number.Format("%d", i + 1);
		((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertItem(i, (LPCTSTR)number);
		((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 1, wordCard.GetSpelling().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 2, wordCard.GetWordClass().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 3, wordCard.GetMeaning().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 4, wordCard.GetExampleSentence().c_str());
		i++;
	}
}
/************************************************************************************************
명    칭: OnListViewItemDoubleClicked
기    능: 리스트 뷰 항목을 더블클릭 했을 때 시나리오.
*************************************************************************************************/
void FindingForm::OnListViewItemDoubleClicked(NMHDR* pNotifyStruct, LRESULT* result) {
	CString spelling;
	CString wordClass;
	CString meaning;
	CString exampleSentence;
	Long index;
	WordCardBookForm* wordCardBookForm;

	index = ((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	spelling = ((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 1);
	wordClass = ((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 2);
	meaning = ((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 3);
	exampleSentence = ((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 4);
	wordCardBookForm = (WordCardBookForm*)CWnd::FindWindowA("#32770", "단어장");
	((CListCtrl*)wordCardBookForm->GetDlgItem(IDC_LIST_WORDS))->SetSelectionMark(this->indexes[index]);
	((CListCtrl*)wordCardBookForm->GetDlgItem(IDC_LIST_WORDS))->SetItemState(this->indexes[index],
		LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	wordCardBookForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText((LPCTSTR)spelling);
	wordCardBookForm->GetDlgItem(IDC_COMBOBOX_WORDCLASS)->SetWindowText((LPCTSTR)wordClass);
	wordCardBookForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText((LPCTSTR)meaning);
	wordCardBookForm->GetDlgItem(IDC_EDIT_EXAMPLESENTENCE)->SetWindowText((LPCTSTR)exampleSentence);
	if (this->indexes != NULL) {
		delete[]this->indexes;
	}
	this->EndDialog(0);
	wordCardBookForm->GetDlgItem(IDC_LIST_WORDS)->SetFocus();
}
/************************************************************************************************
명    칭: OnSpellingRadioButtonClicked
기    능: 철자 라디오버튼을 클릭 했을 때 시나리오.
*************************************************************************************************/
void FindingForm::OnSpellingRadioButtonClicked() {
	this->GetDlgItem(IDC_EDIT_SPELLING)->EnableWindow(TRUE);
	((CButton*)this->GetDlgItem(IDC_RADIO_MEANING))->SetCheck(BST_UNCHECKED);
	this->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
	this->GetDlgItem(IDC_EDIT_MEANING)->EnableWindow(FALSE);
}
/************************************************************************************************
명    칭: OnMeaningRadioButtonClicked
기    능: 뜻 라디오버튼을 클릭 했을 때 시나리오.
*************************************************************************************************/
void FindingForm::OnMeaningRadioButtonClicked() {
	this->GetDlgItem(IDC_EDIT_MEANING)->EnableWindow(TRUE);
	((CButton*)this->GetDlgItem(IDC_RADIO_SPELLING))->SetCheck(BST_UNCHECKED);
	this->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText("");
	this->GetDlgItem(IDC_EDIT_SPELLING)->EnableWindow(FALSE);
}
/************************************************************************************************
명    칭: OnClose
기    능: 닫기 버튼을 클릭했을 때 시나리오.
*************************************************************************************************/
void FindingForm::OnClose() {
	if (this->indexes != NULL) {
		delete[]this->indexes;
	}
	this->EndDialog(0);
}