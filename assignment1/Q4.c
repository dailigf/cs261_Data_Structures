/* CS261- Assignment 1 - Q.4*/
/* Name: Francis C. Dailig
 * Date: 4/15/2018
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}


void camelCase(char* word){
     /*Convert to camelCase*/
	 /*Convert all the characters to lowercase*/
	 int i = 0;
	 do{
		 if((word[i] >= 65 && word[i] <= 90)){
			 word[i] = word[i] + 32;
		 }
		 i++;
	 }while(word[i] != '\n');
	 /*Convert all characters after the underscore to an Uppercase*/
	 i = 0;
	 do{
		 if(word[i] == 95){
			 word[i+1] = toUpperCase(word[i+1]);
		 }
		 i++;
	 }while(word[i] != '\n');
	 /*Shift all values to the right of the underscore to the left*/
	 i = 0;
	 int j = i + 1;
	 do{
		 if(word[i] == 95){
			 int x = i;
			 int y = j;
			 do{
				 word[x] = word[y];
				 x++;
				 y++;
			 }while(word[y] != '\0');
		 }
		 i++;
		 j++;
	 }while(word[j] != '\n');
}

int main(){
    /*Read the string from the keyboard */
	char input[100];
	printf("Please enter a string consisting of the alphabet or underscores: ");
	fgets(input, sizeof(input), stdin);

	/*Verify that only the underscore, uppercase, lowercase are present*/
	/*boolean variable used when determining if input is valid, set to true, 1, as default*/
	int i = 0;
	int isValid = 1;
	do{
		if(!((input[i] >= 65 && input[i] <= 90) || (input[i] >= 97 && input[i] <= 122) || (input[i] == 95))){
			isValid = 0;
		}
		i++;
	}while(input[i] != '\n');
	assert(isValid == 1);
    
    /*Call camelCase*/
	camelCase(input);
    
    /*Print the new the string */
	printf("%s\n", input);
    
    return 0;
}
