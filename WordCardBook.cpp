//WordCardBook.cpp
/************************************************************************************************
파일명칭: WordCardBook.cpp
기    능: 단어장 클래스 정의
작 성 자: 임다니엘
작성일자: 2022/08/25
*************************************************************************************************/
#include"WordCardBook.h"

/************************************************************************************************
명    칭: WordCardBook (default(w/ parameters))
기    능: 디폴트 생성자 (매개변수를 갖는)
*************************************************************************************************/
WordCardBook::WordCardBook(Long capacity)
	:wordCards(capacity) {
	this->capacity = capacity;
	this->length = 0;
}
/************************************************************************************************
명    칭: WordCardBook (copy))
기    능: 복사 생성자
*************************************************************************************************/
WordCardBook::WordCardBook(const WordCardBook& source)
	:wordCards(source.wordCards) {
	this->capacity = source.capacity;
	this->length = source.length;
}
/************************************************************************************************
명    칭: ~WordCardBook 
기    능: 소멸자
*************************************************************************************************/
WordCardBook::~WordCardBook() {}
/************************************************************************************************
명    칭: Record
기    능: 단어장에서 기재한다.
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
명    칭: FindBySpelling
기    능: 단어장에서 철자로 찾는다.
*************************************************************************************************/
void WordCardBook::FindBySpelling(string spelling, Long* (*indexes), Long* count) {
	this->wordCards.LinearSearchDuplicate(&spelling, indexes, count, CompareSpelling);
}
/************************************************************************************************
명    칭: FindByMeaning
기    능: 단어장에서 뜻으로 찾는다.
*************************************************************************************************/
void WordCardBook::FindByMeaning(string meaning, Long* (*indexes), Long* count) {
	this->wordCards.LinearSearchDuplicate(&meaning, indexes, count, CompareMeaning);
}
/************************************************************************************************
명    칭: Correct
기    능: 단어장에서 고친다.
*************************************************************************************************/
Long WordCardBook::Correct(Long index, string wordClass, string meaning, string exampleSentence) {
	WordCard wordCard = this->wordCards.GetAt(index);

	wordCard = WordCard(wordCard.GetSpelling(), wordClass, meaning, exampleSentence);
	index = this->wordCards.Modify(index, wordCard);

	return index;
}
/************************************************************************************************
명    칭: Erase
기    능: 단어장에서 지운다.
*************************************************************************************************/
Long WordCardBook::Erase(Long index) {
	index = this->wordCards.Delete(index);
	this->capacity--;
	this->length--;

	return index;
}
/************************************************************************************************
명    칭: Arrange
기    능: 단어장에서 정리한다.
*************************************************************************************************/
void WordCardBook::Arrange() {
	this->wordCards.SelectionSort(CompareWords);
}
/************************************************************************************************
명    칭: GetAt
기    능: 단어장에서 읽어온다.
*************************************************************************************************/
WordCard& WordCardBook::GetAt(Long index) {
	return this->wordCards.GetAt(index);
}
/************************************************************************************************
명    칭: operator =
기    능: 치환연산자
*************************************************************************************************/
WordCardBook& WordCardBook::operator=(const WordCardBook& source) {
	this->wordCards = source.wordCards;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}
/************************************************************************************************
명    칭: operator []
기    능: 첨자연산자 
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

//테스트시나리오
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

	//기재한다.
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
	//철자로 찾는다.
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
	//뜻으로 찾는다.
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
	//고친다.
	cout << "==============Modify================" << endl;
	index = wordCardBook.Correct(1, "Adv.", "m_now", "I have to do it right now.");
	wordCard = wordCardBook.GetAt(index);
	cout << wordCard.GetSpelling() << endl
		<< wordCard.GetWordClass() << endl
		<< wordCard.GetMeaning() << endl
		<< wordCard.GetExampleSentence() << endl;
	cout << "******************************" << endl;
	//지운다.
	cout << "===============Erase================" << endl;
	index = wordCardBook.Erase(1);
	if (index < 0) {
		cout << "Erased!" << endl;
	}
	//정리한다.
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
	//복사생성자, 첨자연산자, 치환연산자.
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