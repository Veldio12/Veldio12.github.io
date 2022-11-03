#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient{
	char event[10];
	char name[35];
	char condition[20];
	struct Patient* next, *prev;
}*head = NULL, *tail = NULL;


struct Patent* addNewPatient (char event[],char name[],char condition[]){
	struct Patient* NewPatient = (struct Patient*)malloc(sizeof(struct Patient));
	strcpy(NewPatient->event,event);
	strcpy(NewPatient->name,name);
	strcpy(NewPatient->condition,condition);
	NewPatient->next = NewPatient->prev = NULL;
	return NewPatient;
}

void PushHead (char event[], char name[], char condition[]){
	struct Patient* NewPatient = addNewPatient(event[],name[],condition[]);
	if(head == NULL){
		head = tail = NULL;
	}
	else{
		head->prev = NewPatient;
		NewPatient->next = head;
		NewPatient->prev = NULL;
		head = NewPatient;
	}
}


