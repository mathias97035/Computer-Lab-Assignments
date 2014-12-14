/*
 * File:	deque.h
 * Description: Header file which will include the class for the deque.cpp file.
 * Contatins a prtive implementation and public functions
*/
class Deque{
	int count;
	struct node *head;

public:
	Deque();
	~Deque();
	int size();
	void addFirst(int x);
	void addLast(int x);
	int removeFirst();
	int removeLast();
	int getFirst();
	int getLast();
};

