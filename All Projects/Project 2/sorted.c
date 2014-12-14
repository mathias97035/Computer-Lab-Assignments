/*
 * File:	sorted.c
 * Creator:	Matthew Belesiu
 *
 * Description: *** Funstions designed for sorted arrays. ***
 * 		File will include the following functions, hasElement
 * 		addElement, removeElement and bsearch. The overall 
 * 		goal is to order the arrays first, then using a binary
 * 		search, speed up the programs O().
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "set.h"
struct set
{
	int count;
	int length;
	char **elts;
};
/*
 * create set allocates memory and sets up the pointer to nothing.
 * O(1)
 */
SET *createSet(int maxElts) // passing in Size of element
{
	SET *sp = malloc(sizeof(SET)); // allocation for Struct
	assert (sp != NULL); // assert is cool function that checks statement and reports accurate error message if false
	
	sp->count = 0;
	sp->elts = malloc(sizeof(char*)*maxElts); // allocating array
	assert (sp->elts != NULL);
	sp-> length = maxElts;
	return sp;
}
/*
 * frees up memory that was allocated by createSet.
 * O(n)
 */
void destroySet (SET *sp)
{
	int i;
	
	for(i = 0; i < sp->count; i++)
	{
		free(sp->elts[i]); 
	}
	
	free(sp->elts);
	free(sp);
	return;
}
/*
 * returns the number of elements in the set
 * O(1)
 */
int numElements(SET *sp)
{
	return (sp->count);
}

/*
 * Will search by elimnating half of number options on each loop.
 * This gives us a O(log(n)). 
 */
static int xbsearch(SET *sp, char *elt, bool *found)
{
	int lo, hi, mid;
	lo = 0;
	hi = sp->count - 1;
	while (lo <= hi) // breaks when element is not here i.e lo is greater than hi
	{
		mid = (lo + hi)/2;
		if (strcmp(elt, sp->elts[mid]) < 0) // element is less than mid
		{	
			hi = mid - 1;
		}
		
		else if(strcmp(elt, sp->elts[mid]) > 0) // element is greater than mid
		{
			lo = mid + 1;
		}
		else // Found mid!!! 
		{
			*found = true;
			return mid;
		}
	}
	*found = false;
	return lo;
}
/*
 *Program is created to search to see if the element in question exists.
 *This gives us a O(log(n)).
 */
bool hasElement (SET *sp, char *elt)
{
	bool found;

	xbsearch(sp, elt, &found);

	return found;
}
/*
 * Program adds elements into array in order from greatest to least. 
 * This function gives us a O(n) + O(log(n)) which is effectivly O(n). 
 */ 
bool addElement (SET *sp, char *elt)
{
	bool found;
	int x, i;
	
	if(sp->count == sp->length) // Checks to see if there is enough room in length
	{
		return false;
	}
		x = xbsearch(sp, elt, &found);
	if (!found )
	{
		/*
 		* shifts all elements right of x to the right. X will be 
		* the desired postion where I want to add the element 	
 		*/
		for( i = sp->count; i > x; i--) 
		{	
			sp->elts[i] = sp->elts[i-1];
		}
		sp->elts[x] = strdup(elt);
		sp->count++;
		return true;
	}
	
	return false;
}
/*
 * Finds element using xbsearch, frees the element up, then shifts all 
 * all elements to the left of the newly freed element down to the left.
 * Has O(n) + O(logn) = O(n)
 */
bool removeElement(SET *sp, char *elt)
{
	bool found;
	int x, i;

	x = xbsearch(sp, elt, &found);

	if(found)
	{	
		free(sp->elts[x]); // free elt found
		/*
 		* shifts elements right of X to the left. X is the psotion
 		* of the element removed 
 		*/
		for (i = x; i < sp->count; i++)
		{	
			sp->elts[i] = sp->elts[i + 1];
		}
		
		sp->count--;
		return true;
	
	}
	
	return false;
}
