//WordCardBookForm.cpp
/************************************************************************************************
파일명칭: WordCardBookForm.cpp
기    능: 단어장 윈도우
작 성 자: 임다니엘
작성일자: 2022/08/29
*************************************************************************************************/
#include "WordCardBookForm.h"
#include "FindingForm.h"
#include "WordCardBook.h"
#include <afxcmn.h>
#include <afxdb.h>

/************************************************************************************************/
BEGIN_MESSAGE_MAP(WordCardBookForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, OnEraseButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_WORDS, OnListViewItemDoubleClicked)
	ON_EN_KILLFOCUS(IDC_EDIT_SPELLING, OnSpellingKillFocus)
	ON_WM_CLOSE()
END_MESSAGE_MAP()
/************************************************************************************************
명    칭: WordCardBookForm
기    능: 생성자
*************************************************************************************************/
WordCardBookForm::WordCardBookForm(CWnd* parent)
	:CDialog(WordCardBookForm::IDD, parent) {
	this->wordCardBook = NULL;
}
/************************************************************************************************
명    칭: Load
기    능: 적재한다.
*************************************************************************************************/
void WordCardBookForm::Load() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT WordCard.spelling, WordCard.wordClass, WordCard.meaning, WordCard.exampleSentence "
		"FROM WordCard;";

	db.OpenEx("DSN=WordCardBook;UID=root;PWD=Dlaeksldpf1!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString spelling;
	CString wordClass;
	CString meaning;
	CString exampleSentence;
	while (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, spelling);
		rs.GetFieldValue((short)1, wordClass);
		rs.GetFieldValue((short)2, meaning);
		rs.GetFieldValue((short)3, exampleSentence);
		this->wordCardBook->Record((LPCTSTR)spelling, (LPCTSTR)wordClass, (LPCTSTR)meaning, (LPCTSTR)exampleSentence);
		rs.MoveNext();
	}
	rs.Close();
	db.Close();
}
/************************************************************************************************
명    칭: Save
기    능: 저장한다.
*************************************************************************************************/
void WordCardBookForm::Save() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT WordCard.code FROM WordCard;";
	CString code;
	WordCard wordCard;
	Long i = 0;

	db.OpenEx("DSN=WordCardBook;UID=root;PWD=Dlaeksldpf1!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	sql = "DELETE FROM WordCard;";
	db.ExecuteSQL(sql);
	while (!rs.IsEOF() && i < this->wordCardBook->GetLength()) {
		rs.GetFieldValue((short)0, code);
		wordCard = this->wordCardBook->GetAt(i);
		sql.Format("INSERT INTO WordCard(code, spelling, wordClass, meaning, exampleSentence) "
			"VALUES('%s', '%s', '%s', '%s', '%s');", (LPCTSTR)code, wordCard.GetSpelling().c_str(),
			wordCard.GetWordClass().c_str(), wordCard.GetMeaning().c_str(), wordCard.GetExampleSentence().c_str());
		db.ExecuteSQL(sql);
		rs.MoveNext();
		i++;
	}
	rs.Close();
	db.Close();
}
/************************************************************************************************
명    칭: GetCode
기    능: 코드를 구한다. (Primary Key)
*************************************************************************************************/
CString WordCardBookForm::GetCode() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT WordCard.code FROM WordCard ORDER BY code DESC;";
	CString code;
	Long number = 0;

	db.OpenEx("DSN=WordCardBook;UID=root;PWD=Dlaeksldpf1!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, code);
		number = _ttoi(code.Right(5));
	}
	code.Format("P%05d", number + 1);
	rs.Close();
	db.Close();

	return code;
}
/************************************************************************************************
명    칭: Insert
기    능: 삽입한다.
*************************************************************************************************/
void WordCardBookForm::Insert(Long index) {
	CDatabase db;
	CString sql;
	WordCard wordCard = this->wordCardBook->GetAt(index);

	sql.Format("INSERT INTO WordCard(code, spelling, wordClass, meaning, exampleSentence) "
		"VALUES('%s', '%s', '%s', '%s', '%s');", (LPCTSTR)this->GetCode(), wordCard.GetSpelling().c_str(),
		wordCard.GetWordClass().c_str(), wordCard.GetMeaning().c_str(), wordCard.GetExampleSentence().c_str());
	db.OpenEx("DSN=WordCardBook;UID=root;PWD=Dlaeksldpf1!");
	db.ExecuteSQL(sql);
	db.Close();
}
/************************************************************************************************
명    칭: Modify
기    능: 수정한다.
*************************************************************************************************/
void WordCardBookForm::Modify(Long index) {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT WordCard.code FROM WordCard;";
	CString code;
	WordCard wordCard = this->wordCardBook->GetAt(index);
	Long i = 0;

	db.OpenEx("DSN=WordCardBook;UID=root;PWD=Dlaeksldpf1!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	while (!rs.IsEOF() && i <= index) {
		rs.GetFieldValue((short)0, code);
		rs.MoveNext();
		i++;
	}
	sql.Format("UPDATE WordCard SET wordClass='%s', meaning='%s', exampleSentence='%s' "
		"WHERE WordCard.code='%s';", wordCard.GetWordClass().c_str(), wordCard.GetMeaning().c_str(), wordCard.GetExampleSentence().c_str(),
		(LPCTSTR)code);
	db.ExecuteSQL(sql);
	rs.Close();
	db.Close();
}
/************************************************************************************************
명    칭: Delete
기    능: 삭제한다.
*************************************************************************************************/
void WordCardBookForm::Delete(Long index) {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT WordCard.code FROM WordCard;";
	CString code;
	WordCard wordCard = this->wordCardBook->GetAt(index);
	Long i = 0;

	db.OpenEx("DSN=WordCardBook;UID=root;PWD=Dlaeksldpf1!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	while (!rs.IsEOF() && i <= index) {
		rs.GetFieldValue((short)0, code);
		rs.MoveNext();
		i++;
	}
	sql.Format("DELETE FROM WordCard WHERE WordCard.code='%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);
	rs.Close();
	db.Close();
}
/************************************************************************************************
명    칭: OnInitDialog
기    능: 윈도우 생성 시 시나리오
*************************************************************************************************/
BOOL WordCardBookForm::OnInitDialog() {
	CDialog::OnInitDialog();
	this->wordCardBook = new WordCardBook;
	this->Load();
	TCHAR wordClasses[][8] = { "명사", "대명사", "동사", "형용사", "부사", "접속사", "전치사", "감탄사" };
	Long i = 0;
	while (i < sizeof(wordClasses) / sizeof(wordClasses[0])) {
		((CComboBox*)this->GetDlgItem(IDC_COMBOBOX_WORDCLASS))->AddString(wordClasses[i]);
		i++;
	}
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertColumn(0, "번호", LVCFMT_CENTER, 40);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertColumn(1, "철자", LVCFMT_CENTER, 70);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertColumn(2, "품사", LVCFMT_CENTER, 60);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertColumn(3, "뜻", LVCFMT_CENTER, 60);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertColumn(4, "예문", LVCFMT_CENTER, 180);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	WordCard wordCard;
	CString number;
	i = 0;
	while (i < this->wordCardBook->GetLength()) {
		wordCard = this->wordCardBook->GetAt(i);
		number.Format("%d", i + 1);
		((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertItem(i, (LPCTSTR)number);
		((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 1, wordCard.GetSpelling().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 2, wordCard.GetWordClass().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 3, wordCard.GetMeaning().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetItemText(i, 4, wordCard.GetExampleSentence().c_str());
		i++;
	}

	return FALSE;
}
/************************************************************************************************
명    칭: OnRecordButtonClicked
기    능: 기재하기 버튼을 클릭했을 때 시나리오.
*************************************************************************************************/
void WordCardBookForm::OnRecordButtonClicked() {
	CString spelling;
	CString wordClass;
	CString meaning;
	CString exampleSentence;
	CString number;
	WordCard wordCard;
	Long index;
	
	this->GetDlgItem(IDC_EDIT_SPELLING)->GetWindowText(spelling);
	this->GetDlgItem(IDC_COMBOBOX_WORDCLASS)->GetWindowText(wordClass);
	this->GetDlgItem(IDC_EDIT_MEANING)->GetWindowText(meaning);
	this->GetDlgItem(IDC_EDIT_EXAMPLESENTENCE)->GetWindowText(exampleSentence);
	index = this->wordCardBook->Record((LPCTSTR)spelling, (LPCTSTR)wordClass, (LPCTSTR)meaning, (LPCTSTR)exampleSentence);
	this->Insert(index);
	wordCard = this->wordCardBook->GetAt(index);
	number.Format("%d", index + 1);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertItem(index, (LPCTSTR)number);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 1, wordCard.GetSpelling().c_str());
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 2, wordCard.GetWordClass().c_str());
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 3, wordCard.GetMeaning().c_str());
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 4, wordCard.GetExampleSentence().c_str());
}
/************************************************************************************************
명    칭: OnFindButtonClicked
기    능: 찾기 버튼을 클릭했을 때 시나리오.
*************************************************************************************************/
void WordCardBookForm::OnFindButtonClicked() {
	FindingForm findingForm;

	findingForm.DoModal();
}
/************************************************************************************************
명    칭: OnCorrectButtonClicked
기    능: 고치기 버튼을 클릭했을 때 시나리오.
*************************************************************************************************/
void WordCardBookForm::OnCorrectButtonClicked(){
	CString wordClass;
	CString meaning;
	CString exampleSentence;
	Long index;
	WordCard wordCard;

	index = ((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	this->GetDlgItem(IDC_COMBOBOX_WORDCLASS)->GetWindowText(wordClass);
	this->GetDlgItem(IDC_EDIT_MEANING)->GetWindowText(meaning);
	this->GetDlgItem(IDC_EDIT_EXAMPLESENTENCE)->GetWindowTextA(exampleSentence);
	index = this->wordCardBook->Correct(index, (LPCTSTR)wordClass, (LPCTSTR)meaning, (LPCTSTR)exampleSentence);
	this->Modify(index);
	wordCard = this->wordCardBook->GetAt(index);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 2, wordCard.GetWordClass().c_str());
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 3, wordCard.GetMeaning().c_str());
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetItemText(index, 4, wordCard.GetExampleSentence().c_str());
}
/************************************************************************************************
명    칭: OnEraseButtonClicked
기    능: 지우기 버튼을 클릭했을 때 시나리오.
*************************************************************************************************/
void WordCardBookForm::OnEraseButtonClicked() {
	CString number;
	Long index;
	Long i;

	index = ((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	this->wordCardBook->Erase(index);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->DeleteItem(index);
	this->Delete(index);
	i = index;
	while (i < this->wordCardBook->GetLength()) {
		number.Format("%d", i + 1);
		((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->SetItemText(i,0, (LPCTSTR)number);
		i++;
	}
}
/************************************************************************************************
명    칭: OnArrangeButtonClicked
기    능: 정리하기 버튼을 클릭했을 때 시나리오.
*************************************************************************************************/
void WordCardBookForm::OnArrangeButtonClicked() {
	CString number;
	WordCard wordCard;
	Long index;
	Long i;

	this->wordCardBook->Arrange();
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->DeleteAllItems();
	i = 0;
	while (i < this->wordCardBook->GetLength()) {
		wordCard = this->wordCardBook->GetAt(i);
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
기    능: 리스트 뷰 컨트롤의 항목을 더블클릭했을 때 시나리오.
*************************************************************************************************/
void WordCardBookForm::OnListViewItemDoubleClicked(NMHDR* pNotifyStruct, LRESULT* result) {
	CString spelling;
	CString wordClass;
	CString meaning;
	CString exampleSentence;
	Long index;

	index = ((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->GetSelectionMark();
	spelling = ((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 1);
	wordClass = ((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 2);
	meaning = ((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 3);
	exampleSentence = ((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->GetItemText(index, 4);
	this->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText((LPCTSTR)spelling);
	this->GetDlgItem(IDC_COMBOBOX_WORDCLASS)->SetWindowText((LPCTSTR)wordClass);
	this->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText((LPCTSTR)meaning);
	this->GetDlgItem(IDC_EDIT_EXAMPLESENTENCE)->SetWindowText((LPCTSTR)exampleSentence);
}
/************************************************************************************************
명    칭: OnSpellingKillFocus
기    능: 철자의 포커스를 잃었을 때 시나리오.
*************************************************************************************************/
void WordCardBookForm::OnSpellingKillFocus() {
	CString spelling;
	WordCard wordCard;
	Long(*indexes) = NULL;
	Long count = 0;

	this->GetDlgItem(IDC_EDIT_SPELLING)->GetWindowText(spelling);
	this->wordCardBook->FindBySpelling((LPCTSTR)spelling, &indexes, &count);
	if (count > 0) {
		wordCard = this->wordCardBook->GetAt(indexes[0]);
		this->GetDlgItem(IDC_COMBOBOX_WORDCLASS)->SetWindowText(wordCard.GetWordClass().c_str());
		this->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(wordCard.GetMeaning().c_str());
		this->GetDlgItem(IDC_EDIT_EXAMPLESENTENCE)->SetWindowText(wordCard.GetExampleSentence().c_str());
	}
	if (indexes != NULL) {
		delete[]indexes;
	}
}
/************************************************************************************************
명    칭: OnClose
기    능: 닫기 버튼을 클릭했을 때 시나리오.
*************************************************************************************************/
void WordCardBookForm::OnClose() {
	this->Save();
	if (this->wordCardBook != NULL) {
		delete this->wordCardBook;
	}
	this->EndDialog(0);
}