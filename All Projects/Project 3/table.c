/*
 * File		table.c
 * Creator:	Matthew Belesiu
 *
 * Description: Functions are desined to use a hash table, using linear
 * probing. File will include the following functions: createSet, 
 * destroySet, numElement, hashString, findElement, hasElements, 
 * addElement removeElement. The overall goal is to use hashing to 
 * improve the O() of uniquie, bincount and parity
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "set.h"

#define EMPTY 0
#define FILLED 1
#define DELETED 2

struct set{
	int count;
	int length;
	char **elts;
	char *flags;// neseccary for parrelle array
};
/*
 * create set allocates memory and sets up the pointer. For flags, it 
 * sets the array values to EMPTY. O(n)
 */
SET *createSet(int maxElts)
{
	int i;

	SET *sp = malloc(sizeof(SET)); 
	assert(sp != NULL);
	
	sp->count = 0;
	sp->length = maxElts;

	sp->elts = malloc(sizeof(char*)*maxElts);
	assert(sp->elts != NULL);

	sp->flags = malloc(sizeof(char)*maxElts);
	assert(sp->flags != NULL);

	for (i = 0; i < sp->length; i++)// sets flags to EMPTY
		sp->flags[i] = EMPTY;

	return sp;
}
/*
 * destroy set frees memory allocated by createSet
 * O(n)
 */
void destroySet(SET *sp)
{
	int i;

	assert(sp != NULL);

	for(i = 0; i < sp->length; i++)
	{
		if(sp->flags[i] == FILLED)
		{
			free(sp->elts[i]);
		}

	}
	
	free(sp->flags);
	free(sp->elts);
	free(sp);

}
/*
 * numElements returns the number of elements
 * yea... it is stuipd simple
 * O(1)
 */
int numElements(SET *sp)
{
	assert(sp != NULL);
	return (sp->count);
}
/*
 * hashString returns an unsigned vaule that will be used in findElement
 * to locate a address in the array 
 * O(1)
 */
static unsigned hashString(char *s) 
{
	unsigned hash = 0;
	
	while (*s != '\0')
		hash = 31 * hash + *s ++; //Linear probing
	
	return hash;
}
/*
 * uses the hash function hashString key to locate an elt or, if one is not found,
 * a spot to place an elt.O(n) at worst case, expect however is O(1).
 */
static int findElement (SET *sp, char *elt, bool *found)
{	
	int key;
	int i;
	int remember = -1;

	assert(sp != NULL);
	assert(elt != NULL);
	
	key = (hashString(elt)) % sp->length; // retrives location

	/*
 	* for loop will traverse array searching for desired elt.
 	* if not found and not empty, search will continue
 	*/
	for (i = 0; i < sp->length; i++)
	{
		/*
 		* if spot is filled and elt matches, then value will return
 		*/
		if(sp->flags[(key + i) % sp->length] == FILLED && strcmp(elt, sp->elts[(key + i) % sp->length]) == 0)
			{
				*found = true;
				return ((key + i) % sp->length);
			}

 	/*if deleted, function will remember first delete and continue*/
		else if(sp->flags[(key + i) % sp->length] == DELETED)
			{
				if(remember == -1)
					remember = ((key + i) % sp-> length);
			}

 	/* if empty, function stops and returns remember or locn*/
		else if(sp->flags[(key + i) % sp->length] == EMPTY)
			{
				if(remember == -1)
				{	
					*found = false;
					return ((key + i) %sp->length);
				}
					*found = false;
					return remember;
			}
	}
	
	
	*found = false;
	return remember;

}
// hasElement searches for the existance of elt in hash table. 
// O(n) at worst case, expect however is O(1).

bool hasElement(SET *sp, char *elt)
{
	bool found;
	
	assert(sp != NULL);
	assert(elt != NULL);
	findElement (sp, elt, &found);

return found;
}
/* addElement uses findElement to get the locn of the nearest empty
 * spot to the home locn O(n) at worst case,
 * expect however is O(1). */
bool addElement(SET *sp, char *elt)
{
	bool found;
	int locn;
	
	assert(sp != NULL);
	assert(elt != NULL);
	locn = findElement(sp, elt, &found);
	/* if elt already exist in array, 
 	* we do not want to put another one in*/
	if(found)
		return false;
	
	sp->flags[locn] = FILLED;
	sp->elts[locn] = strdup(elt);
	sp->count++;
	return true;
}
/* removeElement uses findElement to locate the postion of the
 * desired elt,  and removes it from the array
 O(n) at worst case, expect however is O(1).
*/
bool removeElement(SET *sp, char *elt)
{
	bool found;
	int locn;
	
	assert(sp != NULL);
	assert(elt != NULL);
	
	locn = findElement(sp, elt, &found);
	
	if(!found)// if elt is not found, the it can not be deleted
		return false;
	
	sp->flags[locn] = DELETED;
	free(sp->elts[locn]);
	sp->count--;
	return true;
}
