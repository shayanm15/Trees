	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "tree.h"



struct Performance *newPerformance() {

	struct Performance *newNode;
	newNode = (struct Performance*)malloc(sizeof(struct Performance)); /* Allocating mmemory for struct performance pointer */

	newNode -> reads = 0;
	newNode -> writes = 0;
	newNode -> mallocs = 0;		/* Assigning number of reads, writes, mallocs, frees to zero  */
	newNode -> frees = 0;

	if (newNode == NULL) {
		printf("Malloc has failed\n"); /* Error checking if malloc failed if pointer is null*/
		exit(0);
	} 

	return newNode;

}

void attachNode (struct Performance *performance, struct Node **node_ptr, void *src, unsigned int width) {

	 struct Node* newNode = (struct Node*) malloc(sizeof(struct Node)); /* Created a newNode */
	 
	 newNode ->data = malloc(width);
	 memcpy(newNode->data,src,width); /* Copy the data from src to newNode data */
	 
	 (*node_ptr) = newNode;
	 
	 newNode -> lt = NULL; /* Set the lt branch to be NULL*/
	 newNode -> gte = NULL; /* Set the gte branch to be NULL */

	 if (newNode == NULL) {
		
		printf("Malloc has failed\n"); /* Error checking if malloc failed if pointer is null*/
		
		exit(0);
	} 

	
	performance -> writes = performance -> writes +1;
	performance -> mallocs = performance -> mallocs +1;


}

int comparNode(struct Performance *performance, struct Node**node_ptr, int (*compar)(const void *, const void *), void *target) {
	
	struct Node *newNode = *node_ptr; /* Created a newNode that points to the node_ptr that is passed */
	
	performance ->reads = performance ->reads +1;
	
	return (compar(target, (newNode) ->data ) ); /* Return the value that is returned from the compar function to see if target and newNode data are a match */

}


struct Node **next (struct Performance *performance, struct Node **node_ptr, int direction) {

	if (*node_ptr == NULL) {

		printf("Empty list\n"); /*Error checking to see if tree empty*/
		exit(0);
	}

		if (direction < 0) {

			performance->reads = performance->reads + 1;
			 return &(*node_ptr) -> lt; /*Return the node_ptr to the lt branch*/

		} else  {

			performance->reads = performance->reads + 1;
			return &(*node_ptr) -> gte;  /*Return the node_ptr to the gte branch*/


		}

	

}


void readNode (struct Performance *performance, struct Node **node_ptr, void *dest, unsigned int width) {

	if (*node_ptr == NULL) {

		printf("Empty list\n"); /*Error checking to see if tree empty*/
		
		exit(0);
	}


	memcpy(dest, (*node_ptr)->data, width);  /* Copy the data from node_ptr to dest*/
	performance ->reads = performance ->reads +1;


}


void detachNode (struct Performance *performance, struct Node **node_ptr) {

	if (*node_ptr == NULL) {

		printf("Empty list\n"); /*Error checking to see if tree empty*/
		
		exit(0);
	}


	performance ->frees = performance ->frees +1;

	struct Node *detachNode = *node_ptr;  /* Create a detach node pointing to the branch of node_ptr*/

	
	detachNode-> lt = NULL;  /* Set the lt branch to be NULL*/
	
	detachNode-> gte = NULL;  /* Set the gte branch to be NULL*/

	free(detachNode->data);
	
	free(detachNode);  /* Free deatchNode*/


}


int isEmpty(struct Performance *performance, struct Node **node_ptr) {

	if (*node_ptr == NULL) {

		return 1; /*If tree empty return 1*/

	} else {

		return 0; /*Else return 0*/
	}


}


void addItem(struct Performance *performance, struct Node**node_ptr, int (*compar)(const void *, const void *), void *src, unsigned int width) {

	
	int i;

	int (*func_ptrCompar)(const void*, const void*);

	func_ptrCompar = compar;

	for (i =0; (*node_ptr != NULL); i++) {


		node_ptr = next(performance, node_ptr,comparNode(performance, node_ptr, func_ptrCompar,src));  /* Go through the tree until the bottom hwere its NULL*/
	

		}


		attachNode(performance, node_ptr, src, width);  /* Attach a new node where its NULL*/


	

}


void freeTree(struct Performance *performance, struct Node**node_ptr) {

if (node_ptr == NULL){

	return;
}

if (*node_ptr) {

	
	freeTree(performance, next(performance, node_ptr, 1));  /* Recursively call freeTree for all the gte branchs*/
	
	freeTree(performance, next(performance, node_ptr, -1)); /* Recursively call freeTree for all the lt branchs*/
	
	detachNode(performance, node_ptr); /* Call the detachNode fucntion to detach the node*/
	

} else {

	free(*node_ptr); /* Once tree is freed, free node_ptr*/
}




}

	




int searchItem(struct Performance *performance, struct Node**node_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width) {



	 int similarity;
	 similarity = 0;

	 int match;
	 match = 1;

	 int (*func_ptrCompar)(const void*, const void*);

	 func_ptrCompar = compar;

	int i;

	int searched;
	

	
	for ( i = 0; ((compar(target, (*node_ptr) ->data) != similarity) ); i++ ) { 

	 		
	node_ptr = next(performance, node_ptr, comparNode(performance, node_ptr, func_ptrCompar, target)); /* Go through the tree until the target is found in the tree*/

		if ( (*node_ptr) == NULL) {

			return similarity; /* If node_ptr is NULL return 0*/
		}


}

searched = comparNode(performance,node_ptr,func_ptrCompar,target);

if (searched != match) { /* Once a target is found after leaving the for loop*/

		readNode(performance, node_ptr, target, width);

		return match; /* Return 1 if the target and node_ptr are the same*/

		} else {

			
		return similarity; /* Return 0 if the target */
		
	}



}




