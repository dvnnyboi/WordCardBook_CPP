//WordCard.cpp
/************************************************************************************************
파일명칭: WordCard.cpp
기    능: 단어카드 클래스 정의
작 성 자: 임다니엘
작성일자: 2022/08/25
*************************************************************************************************/
#include "WordCard.h"

/************************************************************************************************
명    칭: WordCard (default)
기    능: 디폴트 생성자
*************************************************************************************************/
WordCard::WordCard()
	:spelling(""), wordClass(""), meaning(""), exampleSentence("") {
}
/************************************************************************************************
명    칭: WordCard (parameters)
기    능: 매개변수를 갖는 생성자
*************************************************************************************************/
WordCard::WordCard(string spelling, string wordClass, string meaning, string exampleSentence)
	:spelling(spelling), wordClass(wordClass), meaning(meaning), exampleSentence(exampleSentence) {
}
/************************************************************************************************
명    칭: WordCard (copy)
기    능: 복사 생성자
*************************************************************************************************/
WordCard::WordCard(const WordCard& source)
	:spelling(source.spelling), wordClass(source.wordClass), meaning(source.meaning), exampleSentence(source.exampleSentence) {
}
/************************************************************************************************
명    칭: ~WordCard
기    능: 소멸자
*************************************************************************************************/
WordCard::~WordCard(){
}
/************************************************************************************************
명    칭: IsEqual
기    능: 같은지 확인한다.
*************************************************************************************************/
bool WordCard::IsEqual(const WordCard& other) {
	bool ret = false;

	if (this->spelling.compare(other.spelling) == 0 && this->wordClass.compare(other.wordClass) == 0 &&
		this->meaning.compare(other.meaning) == 0 && this->exampleSentence.compare(other.exampleSentence) == 0) {
		ret = true;
	}
	return ret;
}
/************************************************************************************************
명    칭: IsNotEqual
기    능: 다른지 확인한다.
*************************************************************************************************/
bool WordCard::IsNotEqual(const WordCard& other) {
	bool ret = false;

	if (this->spelling.compare(other.spelling) != 0 || this->wordClass.compare(other.wordClass) != 0 ||
		this->meaning.compare(other.meaning) != 0 || this->exampleSentence.compare(other.exampleSentence) != 0) {
		ret = true;
	}
	return ret;
}
/************************************************************************************************
명    칭: operator ==
기    능: 등가비교 연산자
*************************************************************************************************/
bool WordCard::operator==(const WordCard& other) {
	bool ret = false;

	if (this->spelling.compare(other.spelling) == 0 && this->wordClass.compare(other.wordClass) == 0 &&
		this->meaning.compare(other.meaning) == 0 && this->exampleSentence.compare(other.exampleSentence) == 0) {
		ret = true;
	}
	return ret;
}
/************************************************************************************************
명    칭: operator !=
기    능: 등가비교 연산자
*************************************************************************************************/
bool WordCard::operator!=(const WordCard& other) {
	bool ret = false;

	if (this->spelling.compare(other.spelling) != 0 || this->wordClass.compare(other.wordClass) != 0 ||
		this->meaning.compare(other.meaning) != 0 || this->exampleSentence.compare(other.exampleSentence) != 0) {
		ret = true;
	}
	return ret;
}
/************************************************************************************************
명    칭:  operator =
기    능: 치환연산자
*************************************************************************************************/
WordCard& WordCard::operator=(const WordCard& source) {
	this->spelling = source.spelling;
	this->wordClass = source.wordClass;
	this->meaning = source.meaning;
	this->exampleSentence = source.exampleSentence;

	return *this;
}


#if 0
//테스트시나리오
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	WordCard one;
	WordCard two("apple", "Noun", "k_apple", "I'm allergic to apple.");
	WordCard three(two);

	cout << two.GetSpelling() << endl
		<< two.GetWordClass() << endl
		<< two.GetMeaning() << endl
		<< two.GetExampleSentence() << endl;
	cout << "******************************" << endl;

	cout << three.GetSpelling() << endl
		<< three.GetWordClass() << endl
		<< three.GetMeaning() << endl
		<< three.GetExampleSentence() << endl;
	cout << "******************************" << endl;

	one = two;
	cout << one.GetSpelling() << endl
		<< one.GetWordClass() << endl
		<< one.GetMeaning() << endl
		<< one.GetExampleSentence() << endl;
	cout << "******************************" << endl;
	
	if (one.IsEqual(two) == true) {
		cout << "EQUAL" << endl;
		cout << "******************************" << endl;
	}
	if (one == two) {
		cout << "EQUAL" << endl;
		cout << "******************************" << endl;
	}

	one = WordCard(one.GetSpelling(), one.GetWordClass(), one.GetMeaning(), "Someone took the apple.");
	if (one.IsNotEqual(two) == true) {
		cout << "NOT EQUAL" << endl;
		cout << "******************************" << endl;
	}
	if (one != two) {
		cout << "NOT EQUAL" << endl;
		cout << "******************************" << endl;
	}
	
	return 0;
}
#endif