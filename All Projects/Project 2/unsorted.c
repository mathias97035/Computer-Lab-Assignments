/*
 * File:	unsorted.c
 * Creator:	Matthew Belesiu
 *
 * Description: *** Functions designed for unsorted arrays. ***
 * 		File will include the following functions: hasElement, 
 * 		addElement, removeElement and the static function 
 * 		findElement.
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
 * Finds element location and returns that vaule. Note this is static to keep keep 
 * function localized
 * O(n)
 */
static int findElement(SET *sp, char *elt)
{

	int i;

	for(i = 0; i < sp->count; i++) 
	{
		if( strcmp(sp->elts[i], elt) == 0)
			return i;
	}
	
	return (-1);
}
/*
 * checks to see if the element is actually in the set and returns true(1) or false(0)
 * O(n)
 */
bool hasElement(SET *sp, char *elt)
{
	if( findElement(sp , elt) >= 0) // findElement will conduct same search
		return true;
	return false;
}
/*
 * adds element to the set. Will add to the end of the set.
 * O(n)
 */
bool addElement(SET *sp, char *elt) //adds element to the end of the list
{
		if(findElement(sp, elt) != -1)
			return false;

		if(sp->count < sp->length) 
		{
		//elt = strdup(elt); // this solved a lot of problems. 
		sp->elts[sp->count] = strdup(elt);
			sp->count++;
			return true;
		}
	
	return false;
}
/*
 * remvoes element from list. Then moves the last element to the open spot
 * O(n)
 */
bool removeElement(SET *sp, char *elt)
{
	int r; //variable to hold vaule give by findElement
	if( (r = findElement(sp, elt)) >= 0)
	{
		free(sp->elts[r]);
		sp->elts[r] = sp->elts[sp->count-1];
		sp->count--;
		return true;
	}
	
	return false;
}

