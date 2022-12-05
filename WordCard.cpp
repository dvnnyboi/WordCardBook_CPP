//WordCard.cpp
/************************************************************************************************
���ϸ�Ī: WordCard.cpp
��    ��: �ܾ�ī�� Ŭ���� ����
�� �� ��: �ӴٴϿ�
�ۼ�����: 2022/08/25
*************************************************************************************************/
#include "WordCard.h"

/************************************************************************************************
��    Ī: WordCard (default)
��    ��: ����Ʈ ������
*************************************************************************************************/
WordCard::WordCard()
	:spelling(""), wordClass(""), meaning(""), exampleSentence("") {
}
/************************************************************************************************
��    Ī: WordCard (parameters)
��    ��: �Ű������� ���� ������
*************************************************************************************************/
WordCard::WordCard(string spelling, string wordClass, string meaning, string exampleSentence)
	:spelling(spelling), wordClass(wordClass), meaning(meaning), exampleSentence(exampleSentence) {
}
/************************************************************************************************
��    Ī: WordCard (copy)
��    ��: ���� ������
*************************************************************************************************/
WordCard::WordCard(const WordCard& source)
	:spelling(source.spelling), wordClass(source.wordClass), meaning(source.meaning), exampleSentence(source.exampleSentence) {
}
/************************************************************************************************
��    Ī: ~WordCard
��    ��: �Ҹ���
*************************************************************************************************/
WordCard::~WordCard(){
}
/************************************************************************************************
��    Ī: IsEqual
��    ��: ������ Ȯ���Ѵ�.
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
��    Ī: IsNotEqual
��    ��: �ٸ��� Ȯ���Ѵ�.
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
��    Ī: operator ==
��    ��: ��� ������
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
��    Ī: operator !=
��    ��: ��� ������
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
��    Ī:  operator =
��    ��: ġȯ������
*************************************************************************************************/
WordCard& WordCard::operator=(const WordCard& source) {
	this->spelling = source.spelling;
	this->wordClass = source.wordClass;
	this->meaning = source.meaning;
	this->exampleSentence = source.exampleSentence;

	return *this;
}


#if 0
//�׽�Ʈ�ó�����
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