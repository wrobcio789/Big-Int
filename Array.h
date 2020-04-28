#pragma once
#include <algorithm>

template <typename Type>
class Array
{
private:
	Type* data;
	unsigned int count;

public:
	Array();
	Array(unsigned int n);
	Array(const std::initializer_list<Type> values);
	Array(Type* data, unsigned int count);	//Shallow copy constructor

	void free();
	void allocate(unsigned int newSize);
	void rellocate(unsigned int newSize);

	Type& operator[](unsigned int index);
	const Type& operator[](unsigned int index) const;

	Type* begin();
	Type* end();
	const Type* begin() const;
	const Type* end() const;
	const Type* cbegin() const;
	const Type* cend() const;

	const Type& back() const;

	Type* ptr() const;
	unsigned int size() const;
	void shrink(int shrinkingCount);
	void forget();

	~Array();
};

#include "Array.cpp"

template<typename Type>
inline Array<Type>::Array(unsigned int n)
	:	count(n),
		data(new Type[n])
{
}
