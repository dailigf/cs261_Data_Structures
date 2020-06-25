/* CS261- Assignment 1 - Q.3*/
/* Name:
 * Date:
 * Solution description:
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/     
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			int tmpScore = students[i].score;
			int tmpID = students[i].id;
			if(students[j].score < students[i].score){
				students[i].score = students[j].score;
				students[i].id = students[j].id;
				students[j].score = tmpScore;
				students[j].id = tmpID;

			}
		}
	}
}

int main(){
    /*Declare an integer n and assign it a value.*/
	int n = 10;
    
    /*Allocate memory for n students using malloc.*/
	struct student *students = (struct student*)malloc(sizeof(struct student) * 10);
    
    /*Generate random and unique IDs and random scores for the n students, using rand().*/
	int numArray[n];
	for(int i = 0; i < n; i++){
		numArray[i] = i + 1;
	}
	for(int i = 0; i < n; i ++){
		do{
			int tmp = rand() % 10;
			students[i].id = numArray[tmp];
			students[i].score = rand() % 100 + 1;
			numArray[tmp] = 0;
		}while(students[i].id == 0);
	}
    
    /*Print the contents of the array of n students.*/
	for(int i = 0; i < n; i++){
		printf("%d  %d\n", students[i].id, students[i].score);
	}

    /*Pass this array along with n to the sort() function*/
	sort(students, n);
    
    /*Print the contents of the array of n students.*/
	for(int i = 0; i < n; i++){
		printf("%d  %d\n", students[i].id, students[i].score);
	}
    
    return 0;
}
