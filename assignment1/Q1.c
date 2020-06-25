/* CS261- Assignment 1 - Q.1*/
/* Name: Francis C. Dailig
 * Date: 4/11/2018
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
	 struct student *studentArr = (struct student*)malloc(sizeof(struct student) * 10);
     
     /*return the pointer*/
	 return studentArr;

}

void generate(struct student* students){
     /*Generate random and unique ID and random scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
	 /*create an array of 10 integers for the student IDs*/
	 int numArray[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	 for(int i = 0; i < 10; i++){
		 do{
			 int tmp = rand() % 10;
			 students[i].id = numArray[tmp];
			 students[i].score = rand() % 100 + 1;
			 numArray[tmp] = 0;
		 }while(students[i].id == 0);
	 }
     
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	for(int i = 0; i < 10; i++){
		printf("%d %d\n", students[i].id, students[i].score);
	}
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
	 int min = students[0].score, max = students[0].score;
	 double avg = 0.0;

	 for(int i = 1; i < 10; i++){
		 if(students[i].score < min){
			 min = students[i].score;
		 }

		 if(students[i].score > max){
			 max = students[i].score;
		 }

		 avg += students[i].score;

	 }
		 avg = avg / 10;

		 printf("The minimum is: %d\n", min);
		 printf("The maximum is: %d\n", max);
		 printf("The average is: %lf\n", avg);
     
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
	 assert(stud != NULL);
	 free(stud);
	 stud = NULL;
}

int main(){
	/*See the random number generator*/
	srand(time(0));
    struct student* stud = NULL;
    
    /*call allocate*/
    stud = allocate();
    
    /*call generate*/
    generate(stud);
    
    /*call output*/
    output(stud);
    
    /*call summary*/
    summary(stud);
    
    /*call deallocate*/
    deallocate(stud);

    return 0;
}
