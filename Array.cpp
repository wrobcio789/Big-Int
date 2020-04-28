#include "Array.h"
#include "Array.h"


template <typename Type>
Array<Type>::Array()
	:	data(nullptr),
		count(0)
{
}

template<typename Type>
Array<Type>::Array(const std::initializer_list<Type> values)
	:	Array(values.size())
{
	int index = 0;
	for (const Type & value : values)
		data[index++] = value;
}

template<typename Type>
Array<Type>::Array(Type * data, unsigned int count)
	:	data(data),
		count(count)
{
}

template<typename Type>
void Array<Type>::free()
{
	if (data == nullptr)
		delete[] data;
	count = 0;
}

template<typename Type>
void Array<Type>::allocate(unsigned int newCount)
{
	free();
	count = newCount;
	data = new Type[count];
}

template<typename Type>
void Array<Type>::rellocate(unsigned int newCount)
{
	Type* newData = new Type[newCount];

	unsigned int limit = std::min(newCount, count);
	for (unsigned int i = 0; i < limit; i++)
		newData[i] = data[i];
	free();
	data = newData;
	count = newCount;
}

template<typename Type>
Type & Array<Type>::operator[](unsigned int index)
{
	if (index >= count || index < 0)
		__debugbreak();
	return data[index];
}

template<typename Type>
const Type & Array<Type>::operator[](unsigned int index) const
{
	if (index >= count || index < 0)
		__debugbreak();
	return data[index];
}

template<typename Type>
Type * Array<Type>::begin()
{
	return data;
}

template<typename Type>
Type * Array<Type>::end()
{
	return data + count;
}

template<typename Type>
const Type * Array<Type>::begin() const
{
	return cbegin();
}

template<typename Type>
const Type * Array<Type>::end() const
{
	return cend();
}

template<typename Type>
const Type * Array<Type>::cbegin() const
{
	return data;
}

template<typename Type>
const Type * Array<Type>::cend() const
{
	return data + count;
}

template<typename Type>
const Type & Array<Type>::back() const
{
	return data[count - 1];
}

template<typename Type>
Type * Array<Type>::ptr() const
{
	return data;
}

template<typename Type>
unsigned int Array<Type>::size() const
{
	return count;
}

template<typename Type>
void Array<Type>::shrink(int shrinkingCount)
{
	if (count < shrinkingCount)
		__debugbreak();
	count -= shrinkingCount;
}

template<typename Type>
//Use only after shallow copy contructor to prevent memory leaks
void Array<Type>::forget()
{
	data = nullptr;
	count = 0;
}

template <typename Type>
Array<Type>::~Array()
{
	free();
}
