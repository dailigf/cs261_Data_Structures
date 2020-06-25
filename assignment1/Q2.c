/* CS261- Assignment 1 - Q.2*/
/* Name:  Francis C. Dailig
 * Date:  4/16/2018
 * Solution description:
 */
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /* Increment a */
	(*a)++;
    
    /* Decrement  b */
	(*b)++;
    
    /* Assign a+b to c */
    c = *a + *b;
    /* Return c */
    return c;
}

int main(){
    /* Declare three integers x,y and z and initialize them randomly to values in [0,10] */
	int x = rand() % 11;
	int y = rand() % 11;
	int z = rand() % 11;
	int tmp = 0;
    
    /* Print the values of x, y and z */
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	printf("z: %d\n", z);
    
    /* Call foo() appropriately, passing x,y,z as parameters */
	tmp = foo(&x, &y, z);
    
    /* Print the values of x, y and z */
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	printf("z: %d\n", z);
    
    /* Print the value returned by foo */
	printf("foo: %d", tmp);
    
    return 0;
}
    
    

