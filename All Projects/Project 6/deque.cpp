/*
 * File:	deque.cpp
 *
 * Description: Functions are desgined to create a circular linked list 
 * data structure. File will include the following functions: Deque 
 * constructor and destructor, size(), addFirst(int x), addLast(int x)
 * removeFirst(), removeLast(), getFirst(), and getLast(). These 
 * functions are desgined to work with maze.cpp and radix.cpp. This is
 * my first attempt at a C++ file.
*/
#include "deque.h"
#include <cassert>
/*
 * struct node desgined to hold data and be allocated or removed
 * based on need
 */
struct node{
	int data;
	struct node *next;
	struct node *prev;
};
/*
 * Constructor. Called to create the data structrue. Creates head 
 * pointer and dummy node
 * O(1)
 */
Deque::Deque(){
	count = 0;
	head = new node;//C++ allocation
	
	head->next = head;
	head->prev = head;
}
/*
 * Deconstructor. Called to deallocate memory of circular linked list
 * Ensures all elements are freed
 * O(n)
 */
Deque::~Deque(){
	struct node *dp, *t1;
	dp = head->next;

	while(dp != head){
		t1 = dp;
		delete dp;//deallocator
		t1 = t1->next;
	}
}
/*
 * Returns the number of nodes in Circular linked list. Excludes dummy
 * O(1)
 */
int Deque::size(){
	return count;
}
/*
 * addFirst will add the newly created node to the begining of the list
 * O(1)
 */
void Deque::addFirst(int x){
	struct node *sp = new node;
	//points new node to the begining of the list
	sp->next = head->next;
	sp->prev = head;
	//points head to new begining of the list
	head->next->prev = sp;
	head->next = sp;
	
	sp->data = x;
	count ++;
}
/*
 * addLast will add the newly created node to the end of the list
 * O(1)
 */
void Deque::addLast(int x){
	struct node *sp = new node;
	//points new node to the head of the list
	sp->next = head;
	sp->prev = head->prev;
	//points head's prev to the new node
	head->prev->next = sp;
	head->prev = sp;

	sp->data = x;
	count++;
}
/*
 * removeFirst will remove the first node on the circular linked list
 * O(1)
 */
int Deque::removeFirst(){
	int x;
	assert(count > 0);
	struct node *sp;
	//sets pointer to desired node to remove
	sp = head->next;
	x = sp->data;
	//moves pointers around the node to remove
	head->next = sp->next;
	sp->next->prev = head;

	delete sp;
	count--;
	return x; 
}
/*
 * removeLast will remove the last node on the circular linked list
 * O(1)
 */
int Deque::removeLast(){
	int x;
	assert(count > 0);
	struct node *sp;
	//sets pointer to desired node to remove	
	sp = head->prev;
	x = sp->data;
	//moves pointer around node to remove
	head->prev = sp->prev;
	sp->prev->next = head;

	delete sp;
	count--;
	return x;
}
/*
 * getFirst returns the data of the node being pointed by the head's prev
 * O(1)
 */
int Deque::getFirst(){
	assert(count > 0);
	return head->next->data;
}
/*
 * getFirst returns the data of the node being pointed by the head's prev
 * O(1)
 */
int Deque::getLast(){
	assert(count > 0);
	return head->prev->data;
}

