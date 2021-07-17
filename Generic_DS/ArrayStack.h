//	This is an updated version of code originally
//  created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#ifndef ARRAY_STACK_
#define ARRAY_STACK_

#include "StackADT.h"

template<typename T>
class ArrayStack : public StackADT<T>
{
private:
	T *items;		// Array of pointers to items
	int top;                   // Index to top of stack
	 int STACK_SIZE;
	
public:

    T* CopyArray(int Eff_Size)
    {
        T* copy = new T[Eff_Size];
        for(int i = 0; i < Eff_Size; ++i)
            copy[i] = items[i];
        return copy;
    }

	ArrayStack(int MaxSize) : STACK_SIZE(MaxSize)
	{
		items = new T[STACK_SIZE];
		top = -1;
	}  // end default constructor

	bool isEmpty() const
	{
		return top == -1;	
	}  // end isEmpty

	bool push(const T& newEntry)
	{
		if( top == STACK_SIZE-1 ) return false;	//Stack is FULL

		top++;
		items[top] = newEntry;   
		return true;
	}  // end push

	bool pop(T& TopEntry)
	{
		if (isEmpty()) return false;
		
		TopEntry = items[top];		 
		top--;
		return true;
	}  // end pop
	
	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;
		
		TopEntry = items[top];		 
		return true;
	}  // end peek

}; // end ArrayStack

#endif
