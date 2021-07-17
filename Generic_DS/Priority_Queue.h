#pragma once
#include "Generic_DS/Node.h"

template<class T>
class Priority_Queue
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	Priority_Queue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry, const int& priority=1);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
	 T* toArray(int& count);	//returns array of T (array of items)
	~Priority_Queue();
};
////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Priority_Queue<T>::Priority_Queue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}

/////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool Priority_Queue<T>::isEmpty() const
{
	if (frontPtr == nullptr)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool Priority_Queue<T>::enqueue(const T& newEntry, const int& priority)
{
	bool is_important =  true ;
	Node<T>* NewNode = new Node<T>(newEntry, priority);
	// Insert the new node
    if (isEmpty())
	{
		// if The queue is empty
		frontPtr = NewNode;
		backPtr = NewNode;
	}
	else //if priority is lowest
	    if (backPtr->GetPriority() >= priority)
        {
	        backPtr->setNext(NewNode);
	        backPtr= NewNode;
        }
	else //if priority is highest
	    if (priority >= frontPtr->GetPriority())
        {
	        NewNode->setNext(frontPtr);
	        frontPtr = NewNode;
        }
	    else
	    {
            Node<T>* higher = frontPtr;
            Node<T>* lower = frontPtr;
            while (NewNode->GetPriority() <= lower->GetPriority())
            {
                higher = lower;
                lower = lower->getNext();
//                is_important = false;
                if (!lower) // the end of the queue
                {
                    higher->setNext(NewNode);
                    backPtr = NewNode;
                    break;
                }
            }
            higher->setNext(NewNode);
            NewNode ->setNext(lower);
//            if (is_important == true)
//            {
//                frontPtr = NewNode;
//            }
	    }
	return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
bool Priority_Queue<T>::dequeue(T& frntEntry)
{
	//Removes the front of this queue

	if (isEmpty())
	{
		return false;
	}


	else {

		Node<T>* NodeToDelete = frontPtr;   //  remove front
		frntEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		if (NodeToDelete == backPtr)	 //  last node in the queue
			backPtr = nullptr;

		delete NodeToDelete;

		return true;
	}
}



/////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
bool Priority_Queue<T>::peekFront(T& frntEntry) const 
// copy the first element 
{
	if (isEmpty())
	{
		return false;
	}
	else {
		frntEntry = frontPtr->getItem();
		return true;
	}
}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
Priority_Queue <T>::~Priority_Queue()
{
	
	Node<T>* crnNode = frontPtr;
	while (frontPtr)
	{
		crnNode = frontPtr->getNext();
		delete frontPtr;
		frontPtr = crnNode;
	}
}


template <typename T>
 T* Priority_Queue<T>::toArray(int& count)
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

