/* Author: Francis C. Dailig
 * Date: 4/23/2018
 * stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */		
	/* Algorithm Description:
	 * If '(', '{', '[' is encountered push onto a stack
	 * If ')', '}', ']' is encountered pop the opening matching pair from the stack
	 * If a closing bracket is encountered and the stack is empty, string is not balanced return 0 - false
	 * If closing bracket is encountered, and there is opening bracket on stack, pop the stack.
	 * Check to see if the stack is empty.  If stack is not empty, then there is an opening bracket without a matching closing bracket,
	 * return 0 - false.  If stack is empty, string is balanced, return 1 - true.
	 */

	/* Create a temporary stack */
	DynArr *temp;
	temp = newDynArr(100);

	/* create a temp char variable */
	char tempChar = nextChar(s);

	while(tempChar != '\0'){
		if(tempChar == '{' || tempChar == '(' || tempChar == '[' ){
			pushDynArr(temp, tempChar);
		}

		if(tempChar == '}' || tempChar == ')' || tempChar == ']'){
			/* return false if temp stack is empty */
			if(isEmptyDynArr(temp)){
				return 0;
				/* If the opening is not the same type of bracket as the closing type return false */
			}else if((topDynArr(temp) == '{' && tempChar != '}') || (topDynArr(temp) == '(' && tempChar != ')') || (topDynArr(temp) == '[' && tempChar != ']')){
				return 0;
			}else{ popDynArr(temp); }
		}
		tempChar = nextChar(s);

	}

	if(isEmptyDynArr(temp)){
		return 1;
	}else{ return 0; }
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

