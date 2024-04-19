#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assign4.h"

typedef struct {
	char course_Name[84];
	char course_Sched[4];
	unsigned course_Size;
	unsigned course_Hours;
	char padding[20];
} COURSE;

//function declarations
void createCourse(FILE *file);
void updateCourse(FILE *file);
void readCourse(FILE *file);
void deleteCourse(FILE *file);



int main() {
	FILE *file = fopen("courses.dat", "rb+");
	if (file == NULL){
		//create the file if it doesnt exist
		file = fopen("courses.dat", "wb");
		if (file == NULL) {
			perror("Error creating/opening file");
			return -1;
		}
	}
	
	char option;
	while (1){
		printf("\nEnter of the following actions or press CTRL-D to exit.\n");
		printf("C - create a new course record\n");
		printf("U - update an existing course record\n");
		printf("R - read an existing course record\n");
		printf("D - delete an existing course record\n");

		//read user option
		if (scanf(" %c", &option) != 1) {
			break; //exit loop on EOF
	}
	while (getchar() != '\n'); //clear input buffer

	switch (option) {
		case 'C':
		case 'c':
			createCourse(file);
			break;
		case 'U':
		case 'u':
			updateCourse(file);
			break;
		case 'R':
		case 'r':
			readCourse(file);
			break;
		case 'D':
		case 'd':
			deleteCourse(file);
			break;
		default:
			printf("ERROR: invalid option\n");

		}
	}
	
	fclose(file);
	return 0;
}

void createCourse(FILE *file){
	COURSE newCourse;

	printf("Enter course number: ");
	int courseNumber;
	scanf("%d", &courseNumber);
	while (getchar() != '\n'); //clear input buffer

	fseek(file, courseNumber * sizeof(COURSE), SEEK_SET);
	fread(&newCourse, sizeof(COURSE), 1, file);

	//check if the course already exists
	if(strlen(newCourse.course_Name) > 0) {
		printf("ERROR: course already exists\n");
		return;
	}
	
	printf("Enter course name: ");
	fgets(newCourse.course_Name, sizeof(newCourse.course_Name), stdin);
	newCourse.course_Name[strcspn(newCourse.course_Name, "\n")] = 0; //remove newline character

	printf("Enter course schedule (MWF or TR): ");
	scanf("%s", newCourse.course_Sched);

	printf("Enter course credit hours: ");
	scanf("%u", &newCourse.course_Hours);

	printf("Enter course enrollment: ");
	scanf("%u", &newCourse.course_Size);

	fseek(file, courseNumber * sizeof(COURSE), SEEK_SET);
	fwrite(&newCourse, sizeof(COURSE), 1, file);

	printf("Course created successfully. \n");
}

void updateCourse(FILE *file){
	COURSE updatedCourse;

	printf("Enter course number: ");
	int courseNumber;
	scanf("%d", &courseNumber);
	while (getchar() != '\n'); //clear input buffer

	fseek(file, courseNumber * sizeof(COURSE), SEEK_SET);
	fread(&updatedCourse, sizeof(COURSE), 1, file);

	//check if the course exists
	if (strlen(updatedCourse.course_Name) == 0) {
		printf("ERROR: course not found\n");
		return;
	}
	
	printf("Enter updated course name (Enter to keep original): ");
	fgets(updatedCourse.course_Name, sizeof(updatedCourse.course_Name), stdin);
	updatedCourse.course_Name[strcspn(updatedCourse.course_Name, "\n")] = 0; //read newline character

	printf("Enter updated course schedule (MFW or TF) (Press Enter to keep original): ");
	fgets(updatedCourse.course_Sched, sizeof(updatedCourse.course_Name), stdin);
	updatedCourse.course_Sched[strcspn(updatedCourse.course_Sched, "\n")] = 0; //remove newline character

	printf("Enter updated course credit hours (Press 0 to keep original): ");
	scanf("%u", &updatedCourse.course_Hours);

	printf("Enter updated course enrollment (Press 0 to keep original): ");
	scanf("%u", &updatedCourse.course_Size);

	fseek(file, courseNumber * sizeof(COURSE), SEEK_SET);
	fwrite(&updatedCourse, sizeof(COURSE), 1, file);

	printf("Course updated successfully\n");



}

void readCourse(FILE *file){
	COURSE course; 

	printf("Enter course number: ");
	int courseNumber;
	scanf("%d", &courseNumber);
	while (getchar() != '\n'); //clear input buffer
	
	fseek(file, courseNumber * sizeof(COURSE), SEEK_SET);
	fread(&course, sizeof(COURSE), 1, file);

	//check if course exist
	if(strlen(course.course_Name) == 0){
		printf("ERROR: course not found\n");
		return;
	}
	printf("Course number: %d\n", courseNumber);
	printf("Course name: %s\n", course.course_Name);
	printf("Scheduled days: %s\n", course.course_Sched);
	printf("Credit hours: %u\n", course.course_Hours);
	printf("Enrolled students: %u\n", course.course_Size);



}

void deleteCourse(FILE *file){

	COURSE emptyCourse = {0};
	
	printf("Enter course number: ");
	int courseNumber;
	scanf("%d", &courseNumber);
	while (getchar() != '\n'); //clear input buffer

	fseek(file, courseNumber * sizeof(COURSE), SEEK_SET);
	fwrite(&emptyCourse, sizeof(COURSE), 1, file);
	
	printf("Course %d was successfully deleted\n", courseNumber);
}

