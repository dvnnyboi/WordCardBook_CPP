//WordCardBook.h
/************************************************************************************************
파일명칭: WordCardBook.h
기    능: 단어장 클래스 선언
작 성 자: 임다니엘
작성일자: 2022/08/25
*************************************************************************************************/
#ifndef _WORDCARDBOOK_H
#define _WORDCARDBOOK_H
#include "WordCard.h"
#include "Array.h"
#include <string>
using namespace std;

typedef signed long int Long;
class WordCardBook {
public:
	WordCardBook(Long capacity = 256);
	WordCardBook(const WordCardBook& source);
	~WordCardBook();
	Long Record(string spelling, string wordClass, string meaning, string exampleSentence);
	void FindBySpelling(string spelling, Long* (*indexes), Long* count);
	void FindByMeaning(string meaning, Long* (*indexes), Long* count);
	Long Correct(Long index, string wordClass, string meaning, string exampleSentence);
	Long Erase(Long index);
	void Arrange();
	WordCard& GetAt(Long index);
	WordCardBook& operator=(const WordCardBook& source);
	WordCard& operator[](Long index);
	Long GetCapacity() const;
	Long GetLength() const;
private:
	Array<WordCard> wordCards;
	Long capacity;
	Long length;
};
inline Long WordCardBook::GetCapacity() const {
	return this->capacity;
}
inline Long WordCardBook::GetLength() const {
	return this->length;
}

int CompareSpelling(void* one, void* other);
int CompareMeaning(void* one, void* other);
int CompareWords(void* one, void* other);


#endif //_WORDCARDBOOK_H