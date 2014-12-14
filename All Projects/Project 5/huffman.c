/*
* File:		huffman.c
* Creator:	Matt Belesiu
* Description: 	This program has a two goals. One is to show the user 
*		how the huffman tree is created by making a min heap,
*		then creating a huffman tree, then printing out the 
*		binary repenstation. The second part is to create 
*		the leaves to be compressed by the func pack().
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"
#include "pack.h"

#define p(x) (((x)-1)/2)
#define l(x) ((x)*2+1)
#define r(x) ((x)*2+2)

struct tree *heap[257];
struct tree *leaves[257];
int count[257];
int x;// Total number of elements in my Min Heap
/*
 * read will read in a file, and save the character count for each ASCII
 * value in the array count.
 */
void read(char *filename){
	FILE *fp = fopen (filename, "r");
	int c;
	if(fp == NULL){
		printf("*** FILE IS BLANK ***\n\n");
		return;
	}
	//saves each charater into the array at its ASCII value until EOF
	while((c = fgetc(fp)) != EOF)
		count[c] ++;

	fclose(fp);
	return;
}
/*
 * insert() inserts given leaf into a Min Heap. Inserts into the back 
 * of the array, then shifts up if value is less than parent.
 */
void insert(struct tree *lp){
	
	int i = x;
	struct tree *temp;
	heap[x++] = lp;//Min heap
	while(i > 0){
		//Checks if current value is less than parent
		if(getData(heap[p(i)]) > getData(heap[i])){
			temp = heap[i];
			heap[i] = heap[p(i)];
			heap[p(i)] = temp;
		}else{
			break;
		}
		i = p(i);
	}
		
}
/*
 * delete() removes the first (minimuim) value of the Min Heap, and 
 * returns that leaf. That "deleted" value is then moved to end of the 
 * array and removed.
 */
struct tree *delete(void){
	struct tree *tdelete, *temp;
	int child;
	int i = 0;
	temp = heap[0];
	tdelete = heap[--x];
	while(l(i) < x){//while the left is smaller than count
		child = l(i);
			//checks if right is smaller than left.
		if(r(i) < x){
			if(getData(heap[r(i)]) < getData(heap[l(i)]))
				child = r(i);
		}
		//swapping function
		if(getData(heap[child]) < getData(tdelete)){
			heap[i] = heap[child];
			i = child;
		}else{
			break;
		}
	}
	heap[i] = tdelete;
	return temp;
}
/*
 * print() prints the binary code for each character in the huffman tree.
 * assigns a 0 if right node and a 1 if left node
 */
void print(struct tree *p){

	if(getParent(p) == NULL)
		return;
	
	print(getParent(p));
	if(getLeft(getParent(p)) == p)
		printf("1");
	
	if(getRight(getParent(p)) == p)
		printf("0");
		
		return;

}
/*
 * Driving function of the Huffman code. Calls all main funtions
 * Includes the read in file, the creation of the min  heap,
 * creation of the Huffman tree, the printing of each charaters
 * information, and the final compression, Given by Dr. Atkinson
 */
int main (int argc, char *argv[]){

	int i;
	struct tree *uno, *dos, *temp1;
	
	x = 0;
	if(argc != 3){
		printf("*** FILE IS MISSING ***\n\n");
		return 0;
	}

	for(i = 0; i<257; i++){	
		count[i] = 0;
		leaves[i] = NULL;
		heap[i] = NULL;
	}

	read(argv[1]);

	/*
	* heap sort creation.
	* creates node if count[i] isnt 0
	* inserts into leaves at ASCII value
	* then puts it into min heap
	*/
	for(i = 0; i < 256; i++){
		if(count[i] != 0){
			leaves[i] = createTree (count[i], NULL, NULL);
			insert (leaves[i]);
			}
		}
	leaves[256] = createTree (0, NULL, NULL);
	insert(leaves[i]);
	
	/*
	 * Tree Creation. 
	 * Will remove the last two leaves in the heap
	 * Add their values together, then creates a subtree 
	 * with those two values.
	 */
	while(x > 1){
		uno = delete();
		dos = delete();
		temp1 = createTree ((getData(uno) + getData(dos)), uno, dos);
		insert (temp1);
	}

	//Print block
	//want to print count, ASCII Charater(eithr in Hex or 
	//normal) and the binary repensentation.
	for (i = 0; i < 257; i++){
		if(leaves[i] != NULL){
			//checks if charater is "readable"
			if(!isprint(i))
				printf("%o ",i);

			else
				printf("%c ",i);

			printf("%d ", count[i]);
			print(leaves[i]);
			printf("\n");
		}
	}
	printf("Done\n");
	//Function given by Dr. Atkinson to compress file
	pack(argv[1], argv[2], leaves);
return 0;
}
