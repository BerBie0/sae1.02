#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Person struct to store person data
typedef struct person{
	char sex[2];
	char fName[26];
	char yearOfBirth[5];
	char dptOfBirth[3];
	int frequency;
} Person;

// A linked/chained list node
typedef struct node {
	Person data;
	struct node* next;
} Node;

// list head pointer
Node* head;
// tracking the total count of persons
long int totalCount = 0;

// extracting persons data from readed line from file
Person getData(char* line) {
	Person p;
	// tokenizing the string by semicolon(;)
	strcpy(p.sex, strtok(line, ";"));
	strcpy(p.fName, strtok(NULL, ";"));
	strcpy(p.yearOfBirth, strtok(NULL,";"));
	strcpy(p.dptOfBirth, strtok(NULL,";"));
	p.frequency = atoi(strtok(NULL,";"));
	// returning the person object
	return p;
}

// Creating and returning a list node
Node* createNode(char* line) {
	// extracting person data from line
	Person p = getData(line);
	// allocating memomery to new node
	Node* n = (Node*)malloc(sizeof(Node));
	n->data = p;
	n->next = NULL;
	// returning the new list node
	return n;
}

// inserting the data into the list
void insertNode(char* line) {
	// creating a node for the person data
	Node* n = (Node*)malloc(sizeof(Node));
	n = createNode(line);
	// inserting the node into the linked list
	n->next = head;
	head = n;
	// incrementig the total count
	totalCount++;
}

// Clearing the dynamically allocated memory from the list
void clearList(Node** n) {
	Node* temp = *n;
	while (temp != NULL) {
		*n = (*n)->next;
		free(temp);
		temp = NULL;
	}
}

// Loading data from file dpt2020.csv
void loadInfo() {
	// opening the file
	FILE* file = fopen("dpt2020.csv", "r");
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
		insertNode(line);
	}
	// closing the file
	fclose(file);
	// clearing the console
	system("clear");
}

// check if the name exists more than once.
// return 1 if name is distinct, 0 otherwise
int checkDistinct(Node* list, char* name) {
	Node* temp = list;
	while (temp != NULL) {
		// if name found already, return 0
		if (strcmp(temp->data.fName, name) == 0)
			return 0;
		temp = temp->next;
	}
	// return 1 otherwise
	return 1;
}

// counting the first names by distinguishing the gender
void fNamesSeparate() {
	long int boys = 0, girls = 0;
	Node* temp = head;
	char sex[2] = { 0 };
	char n[26] = { 0 };
	while (temp != NULL) {
		// if the person is male
		if (strcmp(temp->data.sex, "1") == 0) {
			boys++;
		}
		// els ethe person would be female
		else {
			girls++;
		}
		
		strcpy(n, temp->data.fName);
		strcpy(sex, temp->data.sex);
		temp = temp->next;
		// ignoring the repeating names
		while (temp != NULL && strcmp(n, temp->data.fName) == 0 && strcmp(sex,temp->data.sex) == 0) {
			temp = temp->next;
		}
	}
	// display results
	printf("The file covers %ld male names and %ld female names.\n", boys, girls);
}

// counting the first names without distinguishing the gender
void fNames() {
	long int names = 0;
	Node* list = NULL;
	Node* temp = head;
	char n[26] = { 0 };
	while (temp != NULL) {
		// if name is not duplicated
		if (checkDistinct(list, temp->data.fName)) {
			// inserting the person data into a new list of distinct names
			Node* n = (Node*)malloc(sizeof(Node));
			*n = *temp;
			n->next = list;
			list = n;
			names++;
		}
		// ignoring the repating names
		strcpy(n, temp->data.fName);
		temp = temp->next;
		while (temp != NULL && strcmp(n, temp->data.fName) == 0) {
			temp = temp->next;
		}
	}
	// display results
	printf("The file contains %ld first names.\n", names);
	// clearing the distinct list dynamic memory
	clearList(&list);
}

// generating statistics by distinguishing the gender
void statsSeparate(char* name) {
	int boys = 0, girls = 0;
	int min = 2020;
	int max = 1900;
	Node* temp = head;
	while (temp != NULL) {
		// if name matched by the given name
		if (strcmp(temp->data.fName, name) == 0) {
			// check for male and female
			if (strcmp(temp->data.sex, "1") == 0) {
				boys++;
			}
			else {
				girls++;
			}
			// getting the first and last appearance of the name
			if (strcmp(temp->data.yearOfBirth, "XXXX") != 0 && min > atoi(temp->data.yearOfBirth)) {
				min = atoi(temp->data.yearOfBirth);
			}
			if (strcmp(temp->data.yearOfBirth, "XXXX") != 0 && max < atoi(temp->data.yearOfBirth)) {
				max = atoi(temp->data.yearOfBirth);
			}
		}
		temp = temp->next;
	}
	// printing the results
	printf("The first name %s was given to %d boys and %d girls.\n", name, boys, girls);
	printf("Year of first appearance %d.\n", min);
	printf("Year of last appearance %d.\n", max);
}

// generating statistics by distinguishing the gender
void stats(char* name) {
	int count = 0;
	Node* temp = head;
	int max = 1900;
	int min = 2020;
	while (temp != NULL) {
		// if name matched by the given name
		if (strcmp(temp->data.fName, name) == 0) {
			count++;
			// getting the first and last appearance of the name
			if (strcmp(temp->data.yearOfBirth, "XXXX") != 0 && min > atoi(temp->data.yearOfBirth)) {
				min = atoi(temp->data.yearOfBirth);
			}
			if (strcmp(temp->data.yearOfBirth, "XXXX") != 0 && max < atoi(temp->data.yearOfBirth)) {
				max = atoi(temp->data.yearOfBirth);
			}
		}
		temp = temp->next;
	}
	// printing the results
	printf("The first name %s was given to %d children.\n", name, count);
	printf("Year of first appearance %d.\n", min);
	printf("Year of last appearance %d.\n", max);

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
void menuProcessing() {
	int choice = 0;
	char distinguish = '\0';
	char name[26] = { 0 };
	menu();
	do {
		printf("What do you want to display? (0 for the menu) > ");
		// input choice from the user
		if (scanf("%d", &choice)) {
			// display menu for 0
			if (choice == 0) {
				menu();
			}
			// display number of births for 1
			else if (choice == 1) {
				// number of births
				printf("The file covers %ld births.\n", totalCount);
			}
			// display numbe of first names on 2
			else if (choice == 2) {
				// Number of first names
				getc(stdin);
				printf("Do you want to distinguish the gender (Y/N) > ");
				scanf("%c", &distinguish);
				// if user wants to distiguish the gender
				if (distinguish == 'Y' || distinguish == 'y') {
					fNamesSeparate();
				}
				// if user doesn't wants to distiguish the gender
				else {
					fNames();
				}
			}
			// display stats for a given first name
			else if (choice == 3) {
				// Statistics on first names
				// input first name from the user
				printf("Enter firstname: ");
				scanf("%s", name);
				getc(stdin);
				printf("Do you want to distinguish the gender (Y/N) > ");
				scanf("%c", &distinguish);
				// if user wants to distiguish the gender
				if (distinguish == 'Y' || distinguish == 'y') {
					statsSeparate(name);
				}
				// if user doesn't wants to distiguish the gender
				else {
					stats(name);
				}
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
		}
	} while (choice != 4);
}

int main() {
	// loading data from file
	loadInfo();
	// processing user inputs against menu
	menuProcessing();
	// clearing the dynamically allocated memory to the list
	clearList(&head);
	return 0;
}