/*
 * File:	radix.c
 * Creator:	Matthew Belesiu
 *
 * Description: Main body of the radix sort, which will sort a list of
 * random numbers into their correct order from accending to decending
 * and display them. The function calls the implementation of deque.c
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "deque.h"

#define SIZE 10
#define RADIX 10

DEQUE *sp;
int max = 0;
int count = 0;
/*
 * radix will return the nth place of the number that has been subimited.
 * ex. If 123 was passed in and I was looking for the 10th place, 
 * m = 10, and the formula will find the mod of 123/10, which in this 
 * case would give us 2. Then 2 is returned
 */
int radix(int x, int m){
	int r;
	
		r = (x / m) % RADIX;
	return r;

}
/*
 * This drives the prgram forward. This is where all the initializations,
 * inserts, and displays will occur. Implementation will be called here 
 * as well to assist in the orginization of the elements.
 */
int main(void){

	DEQUE* slots[RADIX];
	int i, x, r, m = 1;

	sp = createDeque();

	printf("\n\n\n\n\n\n\nInsert postive numbers\n\nTo finish, type a char\n");
	// scans in number of elts, stopping when elt is not a number
	while(scanf("%d",&x) == 1){
		if(x > max)
			max = x;
		addFirst(sp, x);
		count++;
	}

	// creates array of linked list
	for(i = 0; i < RADIX; i++){
		slots[i] = createDeque();
	}
	// this will calculate the total number of passes needed total
	// given by teacher... 
	// ...lesson learned, use the material Dr Atkinson gives us...
	int numPasses = ceil(log(max + 1.0)/log(RADIX));

	while (numPasses -- > 0) {


		for(i = 0; i < count; i++){

			//removes elts from linked list
			x = removeFirst(sp);
			// finds thier approprite postion in the array 
			// of linked list, and adds it there
			r = radix(x, m);
			addLast(slots[r], x);

		}
		//Will now check the next ith's place
		//i.e. 1's place, 10's place, 100 place ...
		m = m * 10;
		
		// puts elts back into the circular linked list	
		for(i = 0; i < RADIX; i++){
			//checks to see if the slot even has elts
			while(numItems(slots[i]) != 0){

				x = removeFirst(slots[i]);
				addLast(sp, x);	
			}
			
		}
			
	}
	/*Once function is sorted, it will remove each elt, destroying 
 	* node, but printing its contents out as it goes, to nicely 
 	* display the elts in order and free spaces simultaneously
 	*/
	while (numItems(sp) != 0){
		x = removeFirst(sp);
		printf("%d ", x);
	}
	printf("\n\n");

	// frees pointers and list
	destroyDeque(sp);

	return 0;
}
