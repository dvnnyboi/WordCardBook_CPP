//Array.h
/************************************************************************************************
���ϸ�Ī: Array.h
��    ��: �迭 ���̺귯�� Ŭ���� ���� �� ����
�� �� ��: �ӴٴϿ�
�ۼ�����: 2022/08/03
*************************************************************************************************/
#ifndef _ARRAY_H
#define _ARRAY_H

typedef signed long int Long;
template <typename T>
class Array {
public:
	Array(Long capacity = 256);		//Default Constructor
	Array(const Array& source);		//Copy Constructor
	~Array();						//Destructor
	Long Store(Long index, T object);
	Long Insert(Long index, T object);
	Long AppendFromFront(T object);
	Long AppendFromRear(T object);
	Long Delete(Long index);
	Long DeleteFromFront();
	Long DeleteFromRear();
	void Clear();
	Long Modify(Long index, T object);
	Long LinearSearchUnique(void* key, int(*compare)(void*, void*));
	void LinearSearchDuplicate(void* key, Long* (*indexes), Long* count, int(*compare)(void*, void*));
	Long BinarySearchUnique(void* key, int(*compare)(void*, void*));
	void BinarySearchDuplicate(void* key, Long* (*indexes), Long* count, int(*compare)(void*, void*));
	void SelectionSort(int(*compare)(void*, void*));
	void BubbleSort(int(*compare)(void*, void*));
	void InsertionSort(int(*compare)(void*, void*));
	void Merge(const Array& one, const Array& other, int(*compare)(void*, void*));
	T& GetAt(Long index);
	Long GetCapacity() const;
	Long GetLength() const;
	Array& operator=(const Array& source);
	T& operator[](Long index);
	T* operator+(Long index);
private:
	T(*front);
	Long capacity;
	Long length;
};
template <typename T>
inline Long Array<T>::GetCapacity()const {
	return this->capacity;
}
template <typename T>
inline Long Array<T>::GetLength()const {
	return this->length;
}

/************************************************************************************************
��    Ī: Array (default)
��    ��: ����Ʈ ������
��    ��: �Ҵ緮
��    ��: ����
*************************************************************************************************/
template <typename T>
Array<T>::Array(Long capacity) {
	this->front = new T[capacity];
	this->capacity = capacity;
	this->length = 0;
}
/************************************************************************************************
��    Ī: Array (copy)
��    ��: ���� ������
��    ��: �迭
��    ��: ����
*************************************************************************************************/
template <typename T>
Array<T>::Array(const Array& source) {
	Long i = 0;

	this->front = new T[source.capacity];
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}
/************************************************************************************************
��    Ī: ~Array
��    ��: �Ҹ���
��    ��: ����
��    ��: ����
*************************************************************************************************/
template <typename T>
Array<T>::~Array() {
	if (this->front != 0) {
		delete[]this->front;
		this->front = 0;
	}
}
/************************************************************************************************
��    Ī: Store
��    ��: �迭�� �׸��� �����Ѵ�.
��    ��: ��ġ, �׸�
��    ��: ��ġ
*************************************************************************************************/
template <typename T>
Long Array<T>:: Store(Long index, T object) {
	this->front[index] = object;
	this->length++;

	return index;
}
/************************************************************************************************
��    Ī: Insert
��    ��: �迭�� �׸��� �����Ѵ�.
��    ��: ��ġ, �׸�
��    ��: ��ġ
*************************************************************************************************/
template <typename T>
Long Array<T>::Insert(Long index, T object) {
	T(*temp) = 0;
	Long i = 0;

	temp = new T[this->capacity + 1];
	while (i < index) {
		temp[i] = this->front[i];
		i++;
	}
	while (i < this->length) {
		temp[i+1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[]this->front;
	}
	this->front = temp;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}
/************************************************************************************************
��    Ī: AppendFromFront
��    ��: �迭�� �׸��� �߰��Ѵ�.
��    ��: �׸�
��    ��: ��ġ
*************************************************************************************************/
template <typename T>
Long Array<T>::AppendFromFront(T object) {
	T(*temp);
	Long index = 0;
	Long i = 0;

	temp = new T[this->capacity + 1];
	while (i < this->length) {
		temp[i+1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[]this->front;
	}
	this->front = temp;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}
/************************************************************************************************
��    Ī: AppendFromRear
��    ��: �迭�� �׸��� �����Ѵ�.
��    ��: �׸�
��    ��: ��ġ
*************************************************************************************************/
template <typename T>
Long Array<T>::AppendFromRear(T object) {
	T(*temp);
	Long index;
	Long i = 0;

	temp = new T[this->capacity + 1];
	while (i < this->length) {
		temp[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[]this->front;
	}
	this->front = temp;
	this->capacity++;
	index = this->capacity - 1;
	this->front[index] = object;
	this->length++;

	return index;
}
/************************************************************************************************
��    Ī: Delete
��    ��: �迭�� �׸��� �����.
��    ��: ����
��    ��: ��ġ
*************************************************************************************************/
template <typename T>
Long Array<T>::Delete(Long index) {
	T(*temp) = 0;
	Long i = 0;
	if (this->capacity > 1) {
		temp = new T[this->capacity];
	}
	while (i < index) {
		temp[i] = this->front[i];
		i++;
	}
	i++;
	while (i < this->length) {
		temp[i - 1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[]this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = temp;
	}
	this->length--;
	this->capacity--;
	index = -1;

	return index;
}
/************************************************************************************************
��    Ī: DeleteFromFront
��    ��: �迭�� ù �׸��� �����.
��    ��: ����
��    ��: ��ġ
*************************************************************************************************/
template <typename T>
Long Array<T>::DeleteFromFront() {
	T(*temp) = 0;
	Long index;
	Long i = 1;
	
	if (this->capacity > 1) {
		temp = new T[this->capacity - 1];
	}
	while (i < this->length) {
		temp[i - 1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[]this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = temp;
	}
	this->length--;
	this->capacity--;
	index = -1;

	return index;
}
/************************************************************************************************
��    Ī: DeleteFromRear
��    ��: �迭�� ������ �׸��� �����.
��    ��: ����
��    ��: ��ġ
*************************************************************************************************/
template <typename T>
Long Array<T>::DeleteFromRear() {
	T(*temp) = 0;
	Long index;
	Long i = 0;

	if (this->capacity > 1) {
		temp = new T[this->capacity - 1];
	}
	while (i < this->capacity - 1) {
		temp[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[]this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = temp;
	}
	this->length--;
	this->capacity--;
	index = -1;

	return index;
}
/************************************************************************************************
��    Ī: Clear
��    ��: �迭�� ��� �׸��� �����.
��    ��: ����
��    ��: ����
*************************************************************************************************/
template <typename T>
void Array<T>::Clear() {
	if (this->front != 0) {
		delete[]this->front;
		this->front = 0;
	}
	this->length = 0;
	this->capacity = 0;
}
/************************************************************************************************
��    Ī: Modify
��    ��: �迭�� �׸��� ��ģ��.
��    ��: ��ġ, �׸�
��    ��: ��ġ
*************************************************************************************************/
template <typename T>
Long Array<T>::Modify(Long index, T object) {
	this->front[index] = object;

	return index;
}
/************************************************************************************************
��    Ī: LinearSearchUnique
��    ��: �迭���� ã�´�
��    ��: ����
��    ��: ��ġ
*************************************************************************************************/
template <typename T>
Long Array<T>::LinearSearchUnique(void* key, int(*compare)(void*, void*)) {
	Long index = -1;
	Long i = 0;
	
	while (i < this->length && compare(this->front + i, key) != 0) {
		i++;
	}
	if (i < this->length) {
		index = i;
	}

	return index;
}
/************************************************************************************************
��    Ī: LinearSearchDuplicate
��    ��: �迭���� ã�´�
��    ��: ����
��    ��: ��ġ��, ����
*************************************************************************************************/
template <typename T>
void Array<T>::LinearSearchDuplicate(void* key, Long*(*indexes), Long*count, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;

	*count = 0;
	*indexes = new Long[this->length];
	while (i < this->length) {
		if (compare(this->front + i, key) == 0) {
			(*indexes)[j] = i;
			(*count)++;
			j++;
		}
		i++;
	}
}
/************************************************************************************************
��    Ī: BinarySearchUnique
��    ��: �迭���� ã�´�
��    ��: ����
��    ��: ��ġ
*************************************************************************************************/
template <typename T>
Long Array<T>::BinarySearchUnique(void* key, int(*compare)(void*, void*)) {
	Long index = -1;
	Long low = 0;
	Long high = this->length - 1;
	Long middle = (low + high) / 2;

	while (low <= high && compare(this->front + middle, key) != 0) {
		if (compare(this->front + middle, key) < 0) {
			low = middle + 1;
		}
		else {
			high = middle - 1;
		}
		middle = (low + high) / 2;
	}
	if (low <= high) {
		index = middle;
	}
	return index;
}
/************************************************************************************************
��    Ī: BinarySearchDuplicate
��    ��: �迭���� ã�´�
��    ��: ����
��    ��: ��ġ��, ����
*************************************************************************************************/
template <typename T>
void Array<T>::BinarySearchDuplicate(void* key, Long *(*indexes), Long *count, int(*compare)(void*, void*)) {
	Long low = 0;
	Long high = this->length - 1;
	Long middle = (low + high) / 2;
	Long i;
	Long j = 0;

	*count = 0;
	*indexes = new Long[this->length];
	while (low <= high && compare(this->front + middle, key) != 0) {
		if (compare(this->front + middle, key) < 0) {
			low = middle + 1;
		}
		else {
			high = middle - 1;
		}
		middle = (low + high) / 2;
	}
	i = middle - 1;
	while (i >= low && compare(this->front + i, key) == 0) {
		i--;
	}
	i++;
	while (i <= high && compare(this->front + i, key) == 0) {
		(*indexes)[j] = i;
		(*count)++;
		j++;
		i++;
	}
}
/************************************************************************************************
��    Ī: SelectionSort
��    ��: �迭�� ������������ �����Ѵ�. (��������)
��    ��: ����
��    ��: ����
*************************************************************************************************/
template <typename T>
void Array<T>::SelectionSort(int(*compare)(void*, void*)) {
	T temp;
	Long i = 0;
	Long j;
	Long smallest;

	while (i < this->length - 1) {
		smallest = i;
		j = i + 1;
		while (j < this->length) {
			if (compare(this->front + smallest, this->front + j) > 0) {
				smallest = j;
			}
			j++;
		}
		temp = this->front[smallest];
		this->front[smallest] = this->front[i];
		this->front[i] = temp;
		i++;
	}
}
/************************************************************************************************
��    Ī: BubbleSort
��    ��: �迭�� ������������ �����Ѵ�. ( ��������)
��    ��: ����
��    ��: ����
*************************************************************************************************/
template <typename T>
void Array<T>::BubbleSort(int (*compare)(void*, void*)) {
	T temp;
	Long i = this->length - 2;
	Long j;
	Long count = 1;

	while (i >= 0 && count > 0) {
		count = 0;
		j = 0;
		while (j <= i) {
			if (compare(this->front + j, this->front + (j + 1)) > 0) {
				temp = this->front[j];
				this->front[j] = this->front[j + 1];
				this->front[j + 1] = temp;
				count++;
			}
			j++;
		}
		i--;
	}
}
/************************************************************************************************
��    Ī: BubbleSort
��    ��: �迭�� ������������ �����Ѵ�. ( ��������)
��    ��: ����
��    ��: ����
*************************************************************************************************/
template <typename T>
void Array<T>::InsertionSort(int(*compare)(void*, void*)) {
	T temp;
	Long i = 1;
	Long j;

	while (i < this->length) {
		temp = this->front[i];
		j = i - 1;
		while (j >= 0 && compare(this->front + j, &temp) > 0) {
			this->front[j + 1] = this->front[j];
			j--;
		}
		this->front[j + 1] = temp;
		i++;
	}
}
/************************************************************************************************
��    Ī: Merge
��    ��: �� �迭�� �����Ѵ�.
��    ��: �迭1, �迭2
��    ��: ����
*************************************************************************************************/
template <typename T>
void Array<T>::Merge(const Array& one, const Array& other, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	Long k = 0;
	
	if (this->front != 0) {
		delete[]this->front;
	}
	this->front = new T[one.length + other.length];
	this->capacity = one.length + other.length;
	while (i < one.length && j < other.length) {
		if (compare(one.front + i, other.front + j) <= 0) {
			this->front[k] = one.front[i];
			k++;
			i++;
		}
		else {
			this->front[k] = other.front[j];
			k++;
			j++;
		}
	}
	while (i < one.length) {
		this->front[k] = one.front[i];
		k++;
		i++;
	}
	while (j < other.length) {
		this->front[k] = other.front[j];
		k++;
		j++;
	}
	this->length = one.length + other.length;
}
/************************************************************************************************
��    Ī: GetAt
��    ��: �׸��� �о�´�
��    ��: ��ġ
��    ��: �׸�
*************************************************************************************************/
template <typename T>
T& Array<T>::GetAt(Long index) {
	return this->front[index];
}
/************************************************************************************************
��    Ī: Operator=
��    ��: ġȯ������
��    ��: ��ġ, �׸�
��    ��: ��ġ
*************************************************************************************************/
template <typename T>
Array<T>& Array<T>::operator=(const Array& source) {
	Long i = 0;

	if (this->front != 0) {
		delete[]this->front;
	}
	this->front = new T[source.capacity];
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}
/************************************************************************************************
��    Ī: Operator[]
��    ��: ÷�ڿ�����
��    ��: ��ġ, �׸�
��    ��: ��ġ
*************************************************************************************************/
template <typename T>
T& Array<T>::operator[](Long index) {
	return this->front[index];
}
/************************************************************************************************
��    Ī: Operator+
��    ��: �ּ� ������
��    ��: ��ġ, �׸�
��    ��: ��ġ
*************************************************************************************************/
template <typename T>
T* Array<T>::operator+(Long index) {
	return this->front + index;
}


#endif //_ARRAY_H