/*-- LQueue.h -------------------------------------------------------------

 This header file defines a Queue data type.
 Basic operations:
 constructor:  Constructs an empty queue
 empty:        Checks if a queue is empty
 enqueue:      Modifies a queue by adding a value at the back
 front:        Accesses the top queue value; leaves queue unchanged
 dequeue:      Modifies queue by removing the value at the front
 display:      Displays all the queue elements
 Note: Execution terminates if memory isn't available for a queue element.
 ---------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

//(1) - After defining this class as a template there will be no use for the following line
//typedef int QueueElement;

//(2) - Define here the class TQueue as a template class that takes the type of its elements
//from the main function in a type def named QueueElement
template<class QueueElement>
class TQueue
{
public:
	/***** Function Members *****/
	//(3) - Apply the required changes to each function definition from the following


	/***** Constructors *****/
	TQueue();
	/*-----------------------------------------------------------------------
	 Construct a Queue object.

	 Precondition:  None.
	 Postcondition: An empty Queue object has been constructed.
	 (myFront and myBack are initialized to null pointers).
	 -----------------------------------------------------------------------*/

	TQueue(const TQueue& original);
	/*-----------------------------------------------------------------------
	 Copy Constructor

	 Precondition:  original is the queue to be copied and is received
	 as a const reference parameter.
	 Postcondition: A copy of original has been constructed.
	 -----------------------------------------------------------------------*/

	 /***** Destructor *****/
	~TQueue();
	/*-----------------------------------------------------------------------
	 Class destructor

	 Precondition:  None.
	 Postcondition: The linked list in the queue has been deallocated.
	 -----------------------------------------------------------------------*/

	 /***** Assignment *****/
	const TQueue& operator= (const TQueue& rightHandSide);
	/*-----------------------------------------------------------------------
	 Assignment Operator

	 Precondition:  rightHandSide is the queue to be assigned and is
	 received as a const reference parameter.
	 Postcondition: The current queue becomes a copy of rightHandSide
	 and a reference to it is returned.
	 -----------------------------------------------------------------------*/

	bool empty() const;
	/*-----------------------------------------------------------------------
	 Check if queue is empty.

	 Precondition:  None.
	 Postcondition: Returns true if queue is empty and false otherwise.
	 -----------------------------------------------------------------------*/

	void enqueue(const QueueElement& value);
	/*-----------------------------------------------------------------------
	 Add a value to a queue.

	 Precondition:  value is to be added to this queue.
	 Postcondition: value is added at back of queue.
	 -----------------------------------------------------------------------*/

	void display(ostream& out) const;
	/*-----------------------------------------------------------------------
	 Display values stored in the queue.

	 Precondition:  ostream out is open.
	 Postcondition: Queue's contents, from front to back, have been
	 output to out.
	 -----------------------------------------------------------------------*/

	QueueElement front() const;
	/*-----------------------------------------------------------------------
	 Retrieve value at front of queue (if any).

	 Precondition:  Queue is nonempty.
	 Postcondition: Value at front of queue is returned, unless the queue
	 is empty; in that case, an error message is displayed.
	 -----------------------------------------------------------------------*/

	void dequeue();
	/*-----------------------------------------------------------------------
	 Remove value at front of queue (if any).

	 Precondition:  Queue is nonempty.
	 Postcondition: Value at front of queue has been removed, unless
	 queue is empty; in that case, an error message is displayed
	 and execution allowed to proceed.
	 -----------------------------------------------------------------------*/

private:

	//(4) - The member variable here will be a Vector from the Standard Template Library in C++
	// Therefore, you need to remove the LinkedList used and replace it with this Vector that you'll create
	//Hint: use #include <vector> at the begining of the file


		/*** Node class ***/
	class Node
	{
	public:
		QueueElement data;
		Node* next;
		//--- Node constructor
		Node(QueueElement value)
			/*-------------------------------------------------------------------
			 Precondition:  value and link are received
			 Postcondition: A Node has been constructed with value in its
			 data part and its next part set to link (default 0).
			 ------------------------------------------------------------------*/
		{
			data = value; next = 0;
		}

	};

	typedef Node* NodePointer;

	/***** Data Members *****/
	NodePointer myFront,      // pointer to front of queue
		myBack;       // pointer to back of queue

}; // end of class declaration

//(5) - You'll implement the above functions all in here, no separate cpp file is needed

//The following is an example of function definition using templates, you should follow the same pattern 
//while implementing the rest of the functions.

template <class QueueElement>
TQueue<QueueElement>::TQueue() 
{
	myFront = myBack = 0;
}

template<class QueueElement>
inline TQueue<QueueElement>::TQueue(const TQueue& original)
{
	NodePointer origPtr, lastPtr;
	myFront = new Node(original.myFront->data); // copy first node

	// set pointers to point to the first nodes in both lists respectively
	lastPtr = myFront;
	origPtr = original.myFront->next; // makes origPtr leading by one node

	while (origPtr != original.myBack) //as long as the original list isn't at the end
	{
		// intitializes the next node by the data in origPtr
		lastPtr->next = new Node(origPtr->data);

		// traverses through list
		origPtr = origPtr->next;
		lastPtr = lastPtr->next;
	}
	myBack = lastPtr;
}

template<class QueueElement>
inline TQueue<QueueElement>::~TQueue()
{
	NodePointer prev = myFront,
				ptr;
	while (prev != myBack)
	{
		ptr = prev->next; // pointer catches the next node in the list
		delete prev; // delete current node
		prev = ptr; // set the current node to next
	}
	myBack = myFront;
}

template<class QueueElement>
inline bool TQueue<QueueElement>::empty() const
{
	return myBack == myFront;
}

template<class QueueElement>
inline void TQueue<QueueElement>::enqueue(const QueueElement& value)
{
	NodePointer temp = new Node(value);

	if (myBack == NULL) 
	{
		myFront = myBack = temp;
		return;
	}
		myBack->next = temp;
		myBack = temp;
}

template<class QueueElement>
inline void TQueue<QueueElement>::dequeue()
{
	// If queue is empty, return NULL.
	if (front == NULL)
		return;

	// Store previous front and
	// move front one node ahead
	NodePointer temp = myFront;
	myFront = myFront->next;

	// If front becomes NULL, then
	// change rear also as NULL
	if (myFront == NULL)
		myBack = NULL;

	delete temp;
}
