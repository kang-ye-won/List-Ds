#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct listNode* listPointer;
typedef struct listNode {
	char model;
	int id;
	listPointer link;
} listNode;
listPointer header = NULL;
listPointer list = NULL;
int checka = 0, checkb = 0, checkc = 0;
int is_empty() {
	return list == NULL;
}
void insert(char model, int id) {
	listPointer new = (listPointer)malloc(sizeof(listNode));
	new->model = model;
	new->id = id;
	new->link = list->link;
	list->link = new;
	list = new;
}
void all(char model) {
	if (is_empty()) {
		printf("list is empty\n");
		return;
	}
	listPointer first = header->link;
	for (; first; first = first->link) {//할당하기
		if (checka == 0 && model == 'A' && first->model == 'A') {
			checka = 1;
			printf("A allocation current order : %d", first->id);
			break;
		}
		else if (checkb == 0 && model == 'B' && first->model == 'B') {
			checkb = 1;
			printf("B allocation current order : % d", first->id);
			break;
		}
		else if (checkc == 0 && model == 'C' && first->model == 'C') {
			checkc = 1;
			printf("C allocation current order : %d", first->id);
			break;
		}
		else {
			if (first->link == header) {
				printf("Already assigned or missing information");
				break;
			}
		}
	}
}
void delete(char model) {
	if (is_empty()) {
		printf("list is empty\n");
		return;
	}
	listPointer current = header->link;
	listPointer pre = header;
	for (; current; current = current->link) {
		if (current->model == model) {
			if (current == list) {
				list = pre;
			}
			pre->link = current->link;
			free(current);
			if (model == 'A')checka = 0;
			else if (model == 'B')checkb = 0;
			else if (model == 'C')checkc = 0;
			break;
		}
		else {
			if (current->link == header) {
				printf("No information found");
				break;
			}
		}
		pre = current;
	}
}
void print() {
	if (is_empty()) {
		printf("List is empty.\n");
		return;
	}
	listPointer current = header->link;
	printf("\nCurrent waiting list:\n");
	while (current != header) {
		printf("Model: %c, Customer ID: %d\n", current->model, current->id);
		current = current->link;
	}
}
int main() {
	int choice;
	char model;
	int id;
	header = (listPointer)malloc(sizeof(listNode));
	header->link = header;
	list = header;
	do {
		printf("\n1. New customer registration\n");
		printf("2. Service ready\n");
		printf("3. Service allocation\n");
		printf("4. Exit the program\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			printf("Enter the model (A, B, C): ");
			scanf(" %c", &model);
			printf("Enter the customer ID: ");
			scanf("%d", &id);
			insert(model, id);
			print();
			break;
		case 2:
			printf("Enter ready model (A, B, C): ");
			scanf(" %c", &model);
			delete(model);
			print();
			break;
		case 3:
			printf("Enter allocation model (A, B, C): ");
			scanf(" %c", &model);
			all(model);
			print();
			break;
		case 4:
			printf("Program exit.\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}
	} while (choice != 4);
	return 0;
}