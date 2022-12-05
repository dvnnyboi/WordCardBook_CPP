//WordCardBook.cpp
/************************************************************************************************
���ϸ�Ī: WordCardBook.cpp
��    ��: �ܾ��� Ŭ���� ����
�� �� ��: �ӴٴϿ�
�ۼ�����: 2022/08/25
*************************************************************************************************/
#include"WordCardBook.h"

/************************************************************************************************
��    Ī: WordCardBook (default(w/ parameters))
��    ��: ����Ʈ ������ (�Ű������� ����)
*************************************************************************************************/
WordCardBook::WordCardBook(Long capacity)
	:wordCards(capacity) {
	this->capacity = capacity;
	this->length = 0;
}
/************************************************************************************************
��    Ī: WordCardBook (copy))
��    ��: ���� ������
*************************************************************************************************/
WordCardBook::WordCardBook(const WordCardBook& source)
	:wordCards(source.wordCards) {
	this->capacity = source.capacity;
	this->length = source.length;
}
/************************************************************************************************
��    Ī: ~WordCardBook 
��    ��: �Ҹ���
*************************************************************************************************/
WordCardBook::~WordCardBook() {}
/************************************************************************************************
��    Ī: Record
��    ��: �ܾ��忡�� �����Ѵ�.
*************************************************************************************************/
Long WordCardBook::Record(string spelling, string wordClass, string meaning, string exampleSentence) {
	WordCard wordCard(spelling, wordClass, meaning, exampleSentence);
	Long index;

	if (this->length < this->capacity) {
		index = this->wordCards.Store(this->length, wordCard);
	}
	else {
		index = this->wordCards.AppendFromRear(wordCard);
		this->capacity++;
	}
	this->length++;

	return index;
}
/************************************************************************************************
��    Ī: FindBySpelling
��    ��: �ܾ��忡�� ö�ڷ� ã�´�.
*************************************************************************************************/
void WordCardBook::FindBySpelling(string spelling, Long* (*indexes), Long* count) {
	this->wordCards.LinearSearchDuplicate(&spelling, indexes, count, CompareSpelling);
}
/************************************************************************************************
��    Ī: FindByMeaning
��    ��: �ܾ��忡�� ������ ã�´�.
*************************************************************************************************/
void WordCardBook::FindByMeaning(string meaning, Long* (*indexes), Long* count) {
	this->wordCards.LinearSearchDuplicate(&meaning, indexes, count, CompareMeaning);
}
/************************************************************************************************
��    Ī: Correct
��    ��: �ܾ��忡�� ��ģ��.
*************************************************************************************************/
Long WordCardBook::Correct(Long index, string wordClass, string meaning, string exampleSentence) {
	WordCard wordCard = this->wordCards.GetAt(index);

	wordCard = WordCard(wordCard.GetSpelling(), wordClass, meaning, exampleSentence);
	index = this->wordCards.Modify(index, wordCard);

	return index;
}
/************************************************************************************************
��    Ī: Erase
��    ��: �ܾ��忡�� �����.
*************************************************************************************************/
Long WordCardBook::Erase(Long index) {
	index = this->wordCards.Delete(index);
	this->capacity--;
	this->length--;

	return index;
}
/************************************************************************************************
��    Ī: Arrange
��    ��: �ܾ��忡�� �����Ѵ�.
*************************************************************************************************/
void WordCardBook::Arrange() {
	this->wordCards.SelectionSort(CompareWords);
}
/************************************************************************************************
��    Ī: GetAt
��    ��: �ܾ��忡�� �о�´�.
*************************************************************************************************/
WordCard& WordCardBook::GetAt(Long index) {
	return this->wordCards.GetAt(index);
}
/************************************************************************************************
��    Ī: operator =
��    ��: ġȯ������
*************************************************************************************************/
WordCardBook& WordCardBook::operator=(const WordCardBook& source) {
	this->wordCards = source.wordCards;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}
/************************************************************************************************
��    Ī: operator []
��    ��: ÷�ڿ����� 
*************************************************************************************************/
WordCard& WordCardBook::operator[](Long index) {
	return this->wordCards[index];
}

/************************************************************************************************/
int CompareSpelling(void* one, void* other) {
	WordCard* one_ = static_cast<WordCard*>(one);
	string* other_ = static_cast<string*>(other);

	return one_->GetSpelling().compare(*other_);
}
int CompareMeaning(void* one, void* other) {
	WordCard* one_ = static_cast<WordCard*>(one);
	string* other_ = static_cast<string*>(other);

	return one_->GetMeaning().compare(*other_);
}
int CompareWords(void* one, void* other) {
	WordCard* one_ = static_cast<WordCard*>(one);
	WordCard* other_ = static_cast<WordCard*>(other);

	return one_->GetSpelling().compare(other_->GetSpelling());
}
/************************************************************************************************/

//�׽�Ʈ�ó�����
#if 0
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	WordCardBook wordCardBook(3);
	WordCard wordCard;
	Long index;
	Long(*indexes);
	Long count;
	Long i;

	//�����Ѵ�.
	cout << "===============Record===============" << endl;
	index = wordCardBook.Record("apple", "Noun", "m_apple", "I'm allergic to apple.");
	wordCard = wordCardBook.GetAt(index);
	cout << wordCard.GetSpelling() << endl
		<< wordCard.GetWordClass() << endl
		<< wordCard.GetMeaning() << endl
		<< wordCard.GetExampleSentence() << endl;
	cout << "******************************" << endl;
	index = wordCardBook.Record("right", "Adj.", "m_right", "That's not in th right place.");
	wordCard = wordCardBook.GetAt(index);
	cout << wordCard.GetSpelling() << endl
		<< wordCard.GetWordClass() << endl
		<< wordCard.GetMeaning() << endl
		<< wordCard.GetExampleSentence() << endl;
	cout << "******************************" << endl;
	index = wordCardBook.Record("general", "Adj.", "m_normal", "I don't use it for general occasions.");
	wordCard = wordCardBook.GetAt(index);
	cout << wordCard.GetSpelling() << endl
		<< wordCard.GetWordClass() << endl
		<< wordCard.GetMeaning() << endl
		<< wordCard.GetExampleSentence() << endl;
	cout << "******************************" << endl;
	index = wordCardBook.Record("proper", "Adj.", "m_right", "He is not in the proper uniform.");
	wordCard = wordCardBook.GetAt(index);
	cout << wordCard.GetSpelling() << endl
		<< wordCard.GetWordClass() << endl
		<< wordCard.GetMeaning() << endl
		<< wordCard.GetExampleSentence() << endl;
	cout << "******************************" << endl;
	index = wordCardBook.Record("general", "Noun", "m_general", "The general was a good leader.");
	wordCard = wordCardBook.GetAt(index);
	cout << wordCard.GetSpelling() << endl
		<< wordCard.GetWordClass() << endl
		<< wordCard.GetMeaning() << endl
		<< wordCard.GetExampleSentence() << endl;
	cout << "******************************" << endl;
	//ö�ڷ� ã�´�.
	cout << "===========FindBySpelling===========" << endl;
	wordCardBook.FindBySpelling("general", &indexes, &count);
	i = 0;
	while (i < count) {
		wordCard = wordCardBook.GetAt(indexes[i]);
		cout << wordCard.GetSpelling() << endl
			<< wordCard.GetWordClass() << endl
			<< wordCard.GetMeaning() << endl
			<< wordCard.GetExampleSentence() << endl;
		cout << "******************************" << endl;
		i++;
	}
	if (indexes != 0) {
		delete[]indexes;
	}
	//������ ã�´�.
	cout << "===========FindByMeaning============" << endl;
	wordCardBook.FindByMeaning("m_right", &indexes, &count);
	i = 0;
	while (i < count) {
		wordCard = wordCardBook.GetAt(indexes[i]);
		cout << wordCard.GetSpelling() << endl
			<< wordCard.GetWordClass() << endl
			<< wordCard.GetMeaning() << endl
			<< wordCard.GetExampleSentence() << endl;
		cout << "******************************" << endl;
		i++;
	}
	if (indexes != 0) {
		delete[]indexes;
	}
	//��ģ��.
	cout << "==============Modify================" << endl;
	index = wordCardBook.Correct(1, "Adv.", "m_now", "I have to do it right now.");
	wordCard = wordCardBook.GetAt(index);
	cout << wordCard.GetSpelling() << endl
		<< wordCard.GetWordClass() << endl
		<< wordCard.GetMeaning() << endl
		<< wordCard.GetExampleSentence() << endl;
	cout << "******************************" << endl;
	//�����.
	cout << "===============Erase================" << endl;
	index = wordCardBook.Erase(1);
	if (index < 0) {
		cout << "Erased!" << endl;
	}
	//�����Ѵ�.
	cout << "=============Arrange================" << endl;
	wordCardBook.Arrange();
	i = 0;
	while (i < wordCardBook.GetLength()) {
		wordCard = wordCardBook.GetAt(i);
		cout << wordCard.GetSpelling() << endl
			<< wordCard.GetWordClass() << endl
			<< wordCard.GetMeaning() << endl
			<< wordCard.GetExampleSentence() << endl;
		cout << "******************************" << endl;
		i++;
	}
	//���������, ÷�ڿ�����, ġȯ������.
	cout << "==========CopyConstructor===========" << endl;
	cout << "============Operator[]==============" << endl;
	WordCardBook copy(wordCardBook);
	i = 0;
	while (i < copy.GetLength()) {
		wordCard = copy[i];
		cout << wordCard.GetSpelling() << endl
			<< wordCard.GetWordClass() << endl
			<< wordCard.GetMeaning() << endl
			<< wordCard.GetExampleSentence() << endl;
		cout << "******************************" << endl;
		i++;
	}
	cout << "============Operator = =============" << endl;
	WordCardBook another = copy;
	i = 0;
	while (i < another.GetLength()) {
		wordCard = another[i];
		cout << wordCard.GetSpelling() << endl
			<< wordCard.GetWordClass() << endl
			<< wordCard.GetMeaning() << endl
			<< wordCard.GetExampleSentence() << endl;
		cout << "******************************" << endl;
		i++;
	}

	return 0;
}
#endif