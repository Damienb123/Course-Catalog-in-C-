# Course Catalog in C

## Table of Contents

1. [Overview](#Overview)
2. [Project Structure](#Project-Structure)
3. [Source Files](#Source-Files)
    - assign4.c
    - assign4.h
    - a4Input.txt
    - Makefile
3. [Usage Instructions](#Usage-Instructions)
4. [Compilation and Execution](#Compilation-and-Execution)
5. [Example Commands](#Example-Commands)

## Overiew

This project provides a simple command-line interface (CLI) for managing a course catalog. The catalog supports operations such as creating, reading, updating, and deleting course records stored in a binary file (**courses.dat**).

## Project Structure

- **assign4.c:** Contains the main logic for the course catalog operations.
- **assign4.h:** Header file declaring functions used in assign4.c.
- **a4Input.txt:** Input file containing a series of commands to test the program.
- **Makefile:** Script for compiling the program.

## Source Files

### assign4.c
This file contains the implementation of the main program and the functions for managing course records.
```
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

// Function declarations
void createCourse(FILE *file);
void updateCourse(FILE *file);
void readCourse(FILE *file);
void deleteCourse(FILE *file);

int main() {
	FILE *file = fopen("courses.dat", "rb+");
	if (file == NULL){
		// Create the file if it doesn't exist
		file = fopen("courses.dat", "wb");
		if (file == NULL) {
			perror("Error creating/opening file");
			return -1;
		}
	}
	
	char option;
	while (1){
		printf("\nEnter one of the following actions or press CTRL-D to exit.\n");
		printf("C - create a new course record\n");
		printf("U - update an existing course record\n");
		printf("R - read an existing course record\n");
		printf("D - delete an existing course record\n");

		// Read user option
		if (scanf(" %c", &option) != 1) {
			break; // Exit loop on EOF
		}
		while (getchar() != '\n'); // Clear input buffer

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

void createCourse(FILE *file) {
	COURSE newCourse;

	printf("Enter course number: ");
	int courseNumber;
	scanf("%d", &courseNumber);
	while (getchar() != '\n'); // Clear input buffer

	fseek(file, courseNumber * sizeof(COURSE), SEEK_SET);
	fread(&newCourse, sizeof(COURSE), 1, file);

	// Check if the course already exists
	if (strlen(newCourse.course_Name) > 0) {
		printf("ERROR: course already exists\n");
		return;
	}
	
	printf("Enter course name: ");
	fgets(newCourse.course_Name, sizeof(newCourse.course_Name), stdin);
	newCourse.course_Name[strcspn(newCourse.course_Name, "\n")] = 0; // Remove newline character

	printf("Enter course schedule (MWF or TR): ");
	scanf("%s", newCourse.course_Sched);

	printf("Enter course credit hours: ");
	scanf("%u", &newCourse.course_Hours);

	printf("Enter course enrollment: ");
	scanf("%u", &newCourse.course_Size);

	fseek(file, courseNumber * sizeof(COURSE), SEEK_SET);
	fwrite(&newCourse, sizeof(COURSE), 1, file);

	printf("Course created successfully.\n");
}

void updateCourse(FILE *file) {
	COURSE updatedCourse;

	printf("Enter course number: ");
	int courseNumber;
	scanf("%d", &courseNumber);
	while (getchar() != '\n'); // Clear input buffer

	fseek(file, courseNumber * sizeof(COURSE), SEEK_SET);
	fread(&updatedCourse, sizeof(COURSE), 1, file);

	// Check if the course exists
	if (strlen(updatedCourse.course_Name) == 0) {
		printf("ERROR: course not found\n");
		return;
	}
	
	printf("Enter updated course name (Enter to keep original): ");
	fgets(updatedCourse.course_Name, sizeof(updatedCourse.course_Name), stdin);
	updatedCourse.course_Name[strcspn(updatedCourse.course_Name, "\n")] = 0; // Remove newline character

	printf("Enter updated course schedule (MWF or TR) (Press Enter to keep original): ");
	fgets(updatedCourse.course_Sched, sizeof(updatedCourse.course_Sched), stdin);
	updatedCourse.course_Sched[strcspn(updatedCourse.course_Sched, "\n")] = 0; // Remove newline character

	printf("Enter updated course credit hours (Press 0 to keep original): ");
	scanf("%u", &updatedCourse.course_Hours);

	printf("Enter updated course enrollment (Press 0 to keep original): ");
	scanf("%u", &updatedCourse.course_Size);

	fseek(file, courseNumber * sizeof(COURSE), SEEK_SET);
	fwrite(&updatedCourse, sizeof(COURSE), 1, file);

	printf("Course updated successfully\n");
}

void readCourse(FILE *file) {
	COURSE course; 

	printf("Enter course number: ");
	int courseNumber;
	scanf("%d", &courseNumber);
	while (getchar() != '\n'); // Clear input buffer
	
	fseek(file, courseNumber * sizeof(COURSE), SEEK_SET);
	fread(&course, sizeof(COURSE), 1, file);

	// Check if course exists
	if (strlen(course.course_Name) == 0) {
		printf("ERROR: course not found\n");
		return;
	}
	printf("Course number: %d\n", courseNumber);
	printf("Course name: %s\n", course.course_Name);
	printf("Scheduled days: %s\n", course.course_Sched);
	printf("Credit hours: %u\n", course.course_Hours);
	printf("Enrolled students: %u\n", course.course_Size);
}

void deleteCourse(FILE *file) {
	COURSE emptyCourse = {0};
	
	printf("Enter course number: ");
	int courseNumber;
	scanf("%d", &courseNumber);
	while (getchar() != '\n'); // Clear input buffer

	fseek(file, courseNumber * sizeof(COURSE), SEEK_SET);
	fwrite(&emptyCourse, sizeof(COURSE), 1, file);
	
	printf("Course %d was successfully deleted\n", courseNumber);
}
```

### assign4.h
Header file declaring the functions used in **assign4.c**.
```
#ifndef ASSIGN4_H
#define ASSIGN4_H

#include <stdio.h>

// Function declarations
void createCourse(FILE *file);
void updateCourse(FILE *file);
void readCourse(FILE *file);
void deleteCourse(FILE *file);

#endif /* ASSIGN4_H */
```

### a4Input.txt
Example input file containing a series of commands to test the program.
```
r
1793
r
3443
c
3424
Systems Programming
MWF
3
82
r
3343
c
3793
Artificial Intelligence
MWF
3
40
r
3793
d
1793
u
9999
r
4653
q
r
3424
u
3343
Analysis of Algorithms
TR
3
75
c
4643
cellular and mobile technology
MWF
3
56
u
4643
Cellular and Mobile Technologies
r
4643
u
3424
r
2193
d
2193
r
2193
```

### Makefile
Makefile for compiling the program.
```
CC=gcc
CFLAGS=-Wall -Wextra

assign4: assign4.o
	$(CC) $(CFLAGS) -o assign4 assign4.o

assign4.o: assign4.c assign4.h
	$(CC) $(CFLAGS) -c assign4.c

clean:
	rm -f assign4.o assign4
```

## Usage Instructions
1. **Clone the Repository:** Clone the repository containing the source files to your local machine.

2. **Navigate to the Directory:** Open a terminal and navigate to the directory containing the source files.

3. **Compile the Program:** Use the Makefile to compile the program.
```
make
```

4. **Run the Program:** Execute the compiled binary to start the CLI.
```
./assign4
```

5. **Enter Commands:** Follow the on-screen prompts to enter commands for creating, reading, updating, and deleting course records.

## Compilation and Execution

To compile and execute the program, follow these steps:

1. **Compile:** Use the provided Makefile.
```
make
```

2. **Run:** Execute the binary file generated by the Makefile.
```
./assign4
```

## Example Commands

Here are some example commands to test the program:

1. Create a course:
```
C
3424
Systems Programming
MWF
3
82
```

2. Read a course:
```
R
3424
```

3. Update a course:
```
U
3424
Advanced Systems Programming
TR
4
100
```

4. Delete a course:
```
D
3424
```

5. Exit the program:

Press CTRL-D on your keyboard.
