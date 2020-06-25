/* CS261- Assignment 1 - Q.0*/
/* Name: Francis C. Dailig
 * Date: 4/15/2018
 * Solution description:
 */
 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int* iptr){
     /*Print the value of iptr*/
	 printf("The value of iptr is: %d\n", *iptr);
     
     /*Print the address pointed to by iptr*/
	 printf("The address pointed to by iptr is: %p\n", iptr);

     /*Print the address of iptr itself*/
	 printf("The address of iptr is: %p\n", (void*)&iptr);
     
     /*Change the value of iptr itself*/
	 *iptr = 100;
         
}

int main(){
    
    /*declare an integer x and initialize it randomly to a value in [0,10] */
	/*seed the random number generator*/
	srand(time(0));
    int x = rand() % 9 + 1;
    /*Print the address of x*/
    printf("The value of x is: %d\n", x);
    printf("The address of x is: %p\n", (void*)&x);
    
    /*Call fooA() with the address of x*/
    fooA(&x);
    
    /*Print the value of x*/
    printf("The value of x is: %d\n", x);

    /*Answer the question */
    /*The value of x is different than what was first printed, the pointer to variable, x, was passed to foo.  When the operation, *iptr = 100
     * was performed, it changed the value of variable that iptr was pointing to, i.e the variable x.
     */
    
    return 0;
   
    
}


