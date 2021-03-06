#ifndef __QUEUE_H_
#define __QUEUE_H_

#include "Node.h"

template <typename T>
class Queue
{
private :
	
	Node<T>* backPtr=nullptr;
	Node<T>* frontPtr= nullptr;
public :
	Queue();	
	bool isEmpty() const ;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);  
	bool peekFront(T& frntEntry)  const;
	
	//toArray function to be used ONLY when drawing the queue items
	 T* toArray(int& count);	//returns array of T (array of items)

	~Queue();
};

template <typename T>
Queue<T>::Queue()
{
	backPtr=nullptr;
	frontPtr=nullptr;

}
template <typename T>
bool Queue<T>::isEmpty() const
{
	if(frontPtr==nullptr)
		return true;
	else
		return false;
}

template <typename T>
bool Queue<T>::enqueue( const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty
	backPtr = newNodePtr; // New node is at back
	return true ;
} // end enqueue


template <typename T>
bool Queue<T>:: dequeue(T& frntEntry)  
{
	if(isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr ;	
		
	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;

}

template <typename T>
bool Queue<T>:: peekFront(T& frntEntry) const 
{
	if(isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
Queue<T>::~Queue()
{
	Node<T>* crnNode = frontPtr;
	while (frontPtr )
	{
		crnNode = frontPtr->getNext();
		delete frontPtr;
		frontPtr = crnNode;
	}
	T temp;
	while(dequeue(temp));

}
////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
 T* Queue<T>::toArray(int& count)
{

	//IMPORTANT:
	//toArray function to be used ONLY when drawing the queue items

	count=0;

	if(!frontPtr)
		return nullptr;
	//counting the no. of items in the Queue
	Node<T>* p = frontPtr;
	while(p)
	{
		count++;
		p = p->getNext();
        if (p==frontPtr)
            break;
	}


	T* Arr= new T[count];
	p = frontPtr;
	for(int i=0; i<count;i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
	//IMPORTANT:
	//toArray function to be used ONLY when drawing the queue items

}

#endif
