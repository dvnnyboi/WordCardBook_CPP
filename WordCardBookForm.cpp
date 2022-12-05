//WordCardBookForm.cpp
/************************************************************************************************
���ϸ�Ī: WordCardBookForm.cpp
��    ��: �ܾ��� ������
�� �� ��: �ӴٴϿ�
�ۼ�����: 2022/08/29
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
��    Ī: WordCardBookForm
��    ��: ������
*************************************************************************************************/
WordCardBookForm::WordCardBookForm(CWnd* parent)
	:CDialog(WordCardBookForm::IDD, parent) {
	this->wordCardBook = NULL;
}
/************************************************************************************************
��    Ī: Load
��    ��: �����Ѵ�.
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
��    Ī: Save
��    ��: �����Ѵ�.
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
��    Ī: GetCode
��    ��: �ڵ带 ���Ѵ�. (Primary Key)
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
��    Ī: Insert
��    ��: �����Ѵ�.
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
��    Ī: Modify
��    ��: �����Ѵ�.
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
��    Ī: Delete
��    ��: �����Ѵ�.
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
��    Ī: OnInitDialog
��    ��: ������ ���� �� �ó�����
*************************************************************************************************/
BOOL WordCardBookForm::OnInitDialog() {
	CDialog::OnInitDialog();
	this->wordCardBook = new WordCardBook;
	this->Load();
	TCHAR wordClasses[][8] = { "���", "����", "����", "�����", "�λ�", "���ӻ�", "��ġ��", "��ź��" };
	Long i = 0;
	while (i < sizeof(wordClasses) / sizeof(wordClasses[0])) {
		((CComboBox*)this->GetDlgItem(IDC_COMBOBOX_WORDCLASS))->AddString(wordClasses[i]);
		i++;
	}
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertColumn(0, "��ȣ", LVCFMT_CENTER, 40);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertColumn(1, "ö��", LVCFMT_CENTER, 70);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertColumn(2, "ǰ��", LVCFMT_CENTER, 60);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertColumn(3, "��", LVCFMT_CENTER, 60);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_WORDS))->InsertColumn(4, "����", LVCFMT_CENTER, 180);
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
��    Ī: OnRecordButtonClicked
��    ��: �����ϱ� ��ư�� Ŭ������ �� �ó�����.
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
��    Ī: OnFindButtonClicked
��    ��: ã�� ��ư�� Ŭ������ �� �ó�����.
*************************************************************************************************/
void WordCardBookForm::OnFindButtonClicked() {
	FindingForm findingForm;

	findingForm.DoModal();
}
/************************************************************************************************
��    Ī: OnCorrectButtonClicked
��    ��: ��ġ�� ��ư�� Ŭ������ �� �ó�����.
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
��    Ī: OnEraseButtonClicked
��    ��: ����� ��ư�� Ŭ������ �� �ó�����.
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
��    Ī: OnArrangeButtonClicked
��    ��: �����ϱ� ��ư�� Ŭ������ �� �ó�����.
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
��    Ī: OnListViewItemDoubleClicked
��    ��: ����Ʈ �� ��Ʈ���� �׸��� ����Ŭ������ �� �ó�����.
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
��    Ī: OnSpellingKillFocus
��    ��: ö���� ��Ŀ���� �Ҿ��� �� �ó�����.
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
��    Ī: OnClose
��    ��: �ݱ� ��ư�� Ŭ������ �� �ó�����.
*************************************************************************************************/
void WordCardBookForm::OnClose() {
	this->Save();
	if (this->wordCardBook != NULL) {
		delete this->wordCardBook;
	}
	this->EndDialog(0);
}