//WordCard.h
/************************************************************************************************
���ϸ�Ī: WordCard.h
��    ��: �ܾ�ī�� Ŭ���� ����
�� �� ��: �ӴٴϿ�
�ۼ�����: 2022/08/25
*************************************************************************************************/
#ifndef _WORDCARD_H
#define _WORDCARD_H
#include <string>
using namespace std;

class WordCard {
public:
	WordCard();
	WordCard(string spelling, string wordClass, string meaning, string exampleSentence);
	WordCard(const WordCard& source);
	~WordCard();
	bool IsEqual(const WordCard& other);
	bool IsNotEqual(const WordCard& other);
	bool operator==(const WordCard& other);
	bool operator!=(const WordCard& other);
	WordCard& operator=(const WordCard& source);
	string& GetSpelling() const;
	string& GetWordClass() const;
	string& GetMeaning() const;
	string& GetExampleSentence() const;
private:
	string spelling;
	string wordClass;
	string meaning;
	string exampleSentence;
};
inline string& WordCard::GetSpelling() const {
	return const_cast<string&>(this->spelling);
}
inline string& WordCard::GetWordClass() const {
	return const_cast<string&>(this->wordClass);
}
inline string& WordCard::GetMeaning() const {
	return const_cast<string&>(this->meaning);
}
inline string& WordCard::GetExampleSentence() const {
	return const_cast<string&>(this->exampleSentence);
}


#endif	//_WORDCARD_H