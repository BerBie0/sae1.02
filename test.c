#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// Max size of the table
#define MAX_SIZE 4000000

// Person struct to store person data
typedef struct person {
	char sex[2];
	char fName[26];
	char yearOfBirth[5];
	int frequency;
} Person;

void clearStdin(){
	scanf("%*[^\n]");
	scanf("%*c");
}

// extracting persons data from readed line from file
Person getData(char* line) {
	Person p;
	// tokenizing the string by semicolon(;)
	strcpy(p.sex, strtok(line, ";"));
	strcpy(p.fName, strtok(NULL, ";"));
	strcpy(p.yearOfBirth, strtok(NULL, ";"));
	strtok(NULL, ";");
	p.frequency = atoi(strtok(NULL, ";"));
	// returning the person object
	return p;
}

// Clearing the dynamically allocated memory from the list
void clearList(Person* table, long int totalCount) {
	free(table);
}

// Loading data from file dpt2020.csv
void loadInfo(Person* table, long int* count, long int* nbrBirth, char fileName[]) {
	// opening the file
	FILE* file = fopen(fileName, "r");
	// if file opening failed, exit the program with error message
	if (!file) {
		printf("Unable to open file...\n");
		exit(1);
	}
	printf("Loading data! Please wait a second...\n");
	char line[50] = { 0 };
	// ignoring the headings
	fgets(line, 50, file);
	// reading data line by line from the file
	while (fgets(line, 50, file)) {
		// ignoring the next line char from the end of the line
		line[strlen(line) - 1] = '\0';
		// inserting data into the list
		table[*count] = getData(line);
		// count number of birth
		*nbrBirth += table[*count].frequency;
		(*count)++;
	}
	// closing the file
	fclose(file);
	// clearing the console
	system("clear");
}

// counting the first names by distinguishing the gender
void fnamesSeparate(Person* table, long int totalCount) {
	long int boys = 0, girls = 0;
	char sex[2] = { 0 };
	char n[26] = { 0 };
	for (long int i = 0; i < totalCount; i++) {
		if (strcmp(table[i].sex, "1") == 0) {
			boys++;
		}
		// else the person would be female
		else {
			girls++;
		}
		strcpy(n, table[i].fName);
		strcpy(sex, table[i].sex);
		while (i + 1 < totalCount && strcmp(n, table[i + 1].fName) == 0 && strcmp(sex, table[i + 1].sex) == 0) {
			i++;
		}
	}

	// display results
	printf("The file covers %ld male names and %ld female names.\n", boys, girls);
}

// check if the name exists more than once.
// return 1 if name is distinct, 0 otherwise
int checkDistinct(Person* table, long int totalCount, char* name) {
	for (long int i = 0; i < totalCount; i++) {
		if (strcmp(table[i].fName, name) == 0)
			return 0;
	}
	// return 1 otherwise
	return 1;
}

// counting the first names without distinguishing the gender
void fNames(Person* table, long int totalCount) {
	long int names = 0;
	char n[26] = { 0 };
	Person* temp = (Person*)calloc(totalCount, sizeof(Person));
	for (long int i = 0; i < totalCount; i++) {
		if (checkDistinct(temp, names, table[i].fName)) {
			// inserting the person data into a new list of distinct names
			temp[names] = table[i];
			names++;
		}
		strcpy(n, table[i].fName);
		while (i + 1 < totalCount && strcmp(n, table[i + 1].fName) == 0) {
			i++;
		}
	}
	// display results
	printf("The file contains %ld first names.\n", names);

	// clearing the distinct list dynamic memory
	clearList(temp, names);
}

// generating statistics by distinguishing the gender
void statsSeparate(Person* table, long int totalCount, char* name) {
	int boys = 0, girls = 0;
	int min = 2020;
	int max = 1900;
	int change = 0;

	for (long int i = 0; i < totalCount; i++) {
		// if name matched by the given name
		if (strcmp(table[i].fName, name) == 0) {
			// check for male and female
			if (strcmp(table[i].sex, "1") == 0) {
				boys+=table[i].frequency;
			}
			else {
				girls+=table[i].frequency;
			}
			// getting the first and last appearance of the name
			if (strcmp(table[i].yearOfBirth, "XXXX") != 0 && min > atoi(table[i].yearOfBirth)) {
				min = atoi(table[i].yearOfBirth);
				change = 1;
			}
			if (strcmp(table[i].yearOfBirth, "XXXX") != 0 && max < atoi(table[i].yearOfBirth)) {
				max = atoi(table[i].yearOfBirth);
				change = 1;
			}
		}
	}
	// printing the results
	printf("The first name %s was given to %d boys and %d girls.\n", name, boys, girls);
	switch (change){
		case 0 : printf("We don't know the year of first and last appearance.\n");break;
		case 1 : printf("Year of first appearance %d.\n", min);printf("Year of last appearance %d.\n", max);break;
	}
}

// generating statistics without distinguishing the gender
void stats(Person* table, long int totalCount, char* name) {
	int count = 0;
	int max = 1900;
	int min = 2020;
	int change = 0;

	for (long int i = 0; i < totalCount; i++) {
		// if name matched by the given name
		if (strcmp(table[i].fName, name) == 0) {
			count+=table[i].frequency;
			// getting the first and last appearance of the name
			if (strcmp(table[i].yearOfBirth, "XXXX") != 0 && min > atoi(table[i].yearOfBirth)) {
				min = atoi(table[i].yearOfBirth);
				change = 1;
			}
			if (strcmp(table[i].yearOfBirth, "XXXX") != 0 && max < atoi(table[i].yearOfBirth)) {
				max = atoi(table[i].yearOfBirth);
				change = 1;
			}
		}
	}
	// printing the results
	printf("The first name %s was given to %d children.\n", name, count);
	switch(change){
		case 0 : printf("We don't know the year of first and last appearance.\n");break;
		case 1 : printf("Year of first appearance %d.\n", min);printf("Year of last appearance %d.\n", max);break;
	}

}

// Display menu function
void menu() {
	printf(" - 0 : This menu\n");
	printf(" - 1 : The number of births\n");
	printf(" - 2 : Number of first names\n");
	printf(" - 3 : Statistics on first name\n");
	printf(" - 4 : Quit\n");
}

// processing user inputs against menu
void menuProcessing(Person* table, long int* totalCount, long int* nbrBirth) {
	int choice = 0;
	char distinguish = '\0';
	char name[26] = { 0 };
	menu();
	do {
		printf("What do you want to display? (0 for the menu) > ");
		// input choice from the user
		if (scanf("%d", &choice)) {
			clearStdin();
			// display menu for 0
			if (choice == 0) {
				menu();
			}
			// display number of births for 1
			else if (choice == 1) {
				// number of births
				printf("The file covers %ld births.\n", *nbrBirth);
			}
			// display numbe of first names on 2
			else if (choice == 2) {
				// Number of first names
				// getc(stdin);
				printf("Do you want to distinguish the gender (Y/N) > ");
				scanf("%c", &distinguish);

				// if user wants to distiguish the gender
				if (distinguish == 'Y' || distinguish == 'y') {
					fnamesSeparate(table, *totalCount);
				}

				// if user doesn't wants to distiguish the gender
				else {
					fNames(table, *totalCount);
				}
				clearStdin();
			}
			// display stats for a given first name
			else if (choice == 3) {
				// Statistics on first names
				// input first name from the user
				printf("Enter firstname: ");
				scanf("%s", name);
				//getc(stdin);

				for (int i = 0; name[i]!='\0'; i++){
					name[i] = toupper(name[i]);
				}
				clearStdin();
				
				printf("Do you want to distinguish the gender (Y/N) > ");
				scanf("%c", &distinguish);
				// if user wants to distiguish the gender
				if (distinguish == 'Y' || distinguish == 'y') {
					statsSeparate(table, *totalCount, name);
				}
				// if user doesn't wants to distiguish the gender
				else {
					stats(table, *totalCount, name);
				}
				clearStdin();
			}
			// exiting the program for 4
			else if (choice == 4) {
				return;
			}
			// invalid choice message for wrong choice
			else {
				printf("Invalid choice. Enter again...\n");
			}
		}
		else {
			printf("Invalid choice. Enter again...\n");
			clearStdin();
		}
	} while (choice != 4);
}

int main(int argc, char *argv[]) {
	// tracking the total count of persons
	long int totalCount = 0;
	long int nbrBirth = 0;
	Person* table = (Person*)calloc(MAX_SIZE, sizeof(Person));
	// loading data from file
	loadInfo(table, &totalCount, &nbrBirth, argv[1]);
	// processing user inputs against menu
	menuProcessing(table, &totalCount, &nbrBirth);
	// clearing the dynamically allocated memory to the list
	clearList(table, totalCount);

	return 0;
}
