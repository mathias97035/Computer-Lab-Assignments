/*
* File:		deque.c
* Creator	Matt Belesiu
* 
* Description: Functions are desgined to create a circular linked list 
* data structure. File will include the following functions: *createDeque
* destroyDeque, numItems, addFirst, addLast, removeFirst, removeLast, 
* getFirst and getLast. These functions are desgined to go along with 
* maze.c and radix.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deque.h"

/*
 * strcut node desgined to hold data and be allocated or removed
 * based on need.
 */
struct node{
	int data;
	struct node *next;
	struct node *prev;
};

/*
 * struct deque holds head, which will point to dummy, and keeps count
 */
struct deque{
	int count;
	struct node *head;
};

/*
 * createDeque is called to create the data structure. It will create
 * the head using struct deque, and a dummy node out of struct node
 * and set the circular list by properly pointing the pointers to the
 * right place
 * O(1)
 */
DEQUE *createDeque(void){
	
	DEQUE  *dp;
	dp = malloc(sizeof(DEQUE));// creates head of list
	assert(dp != NULL);
	
	dp->count = 0;
	dp->head = malloc(sizeof(struct node));// creates "dummy" node
	assert(dp->head != NULL);
	
	/*
 	* Next two lines will set the next and prev pointers of 
	* the "dummy" node to itself, thus creating a linked list 
 	*/
	dp->head->next = dp->head;
	dp->head->prev = dp->head;
	return dp;
}
/*
 * destroyDeque will, when called, remove all the current links in the 
 * circular linked list, freeing the links, "dummmy" and head.
 * O(n)
 */
void destroyDeque(DEQUE *dp){
	
	assert(dp != NULL);

	struct node *sp;
	sp = dp->head->next;
	
	/*
 	* Loop to free all links in the list 
 	*/
	while(sp != dp->head){
		free(sp);
		sp = sp->next;
	}

	free(dp->head);// frees "dummy"
	free(dp);// frees head
}
/*
 * The most complicated function ever created in human computer history.
 * Has the unspeakable power of returning the number of items in the 
 * current linked list.........
 * ...O(1)
 */
int numItems(DEQUE *dp){
	
	assert(dp != NULL);
	return dp->count;
}

/*
 * addFirst will add the newly created link to the begining of the 
 * circular linked list
 * O(1)
 */
void addFirst(DEQUE *dp, int x){
	
	assert(dp != NULL);
	struct node *sp = malloc(sizeof(struct node));//creats node
	assert(sp != NULL);
	
	//Points new node to the begining of the list
	sp->next = dp->head->next;
	sp->prev = dp->head;
	
	//Points head to new begining of the list
	dp->head->next->prev = sp;
	dp->head->next = sp;
	
	sp->data = x;
	dp->count++;
	return;
}
/*
 * addLast will add the newly created link to the end of the 
 * circular linked list
 * O(1)
 */
void addLast(DEQUE *dp, int x){
	
	assert(dp != NULL);
	struct node *sp = malloc(sizeof(struct node));
	assert(sp != NULL);
	
	//Points new node to the end of the list
	sp->next = dp->head;
	sp->prev = dp->head->prev;
	
	//Points heads prev to the new end of the list
	dp->head->prev->next = sp;
	dp->head->prev = sp;

	sp->data = x;
	dp->count++;
	return;
}

/*
 * removeFirst will remove the fisrt item on the list, and porperly
 * move the relevent pointers to the right place. Returns that data's
 * value
 * O(1)
 */
int removeFirst(DEQUE *dp){

	int x;
	assert(dp->count > 0);
	struct node *sp;

	// sets pointer to desired node to remove
	sp = dp->head->next;
	x = sp->data;

	//moves pointers around node to remove
	dp->head->next = sp->next;
	sp->next->prev = dp->head;
	
	free(sp);
	dp->count--;
	return x;
}

/*
 * removeLast will remove the last item on the list, and properly
 * move the relevent pointers to the right place. Returns that data's
 * value
 * O(1) 
 */
int removeLast(DEQUE *dp){

	int x;
	assert(dp->count > 0);
	struct node *sp;

	// sets pointer to desired node to remove
	sp = dp->head->prev;
	x = sp->data;

	//moves pointers around node to remove
	dp->head->prev = sp->prev;
	sp->prev->next = dp->head;
	
	free(sp);
	dp->count--;
	return x;
}

/*
 * getFirst looks up the first element in the circular linked list
 * and reports the value back
 * O(1)
 */
int getFirst(DEQUE *dp){

	assert(dp->count > 0);
	return dp->head->next->data;
}

/*
 * getLast looks up the last element in the cicular linked list and 
 * reports the value back
 * O(1)
 */
int getLast(DEQUE *dp){

	assert(dp->count > 0);
	return dp->head->prev->data;
}
