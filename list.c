#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* your list function definitions */

void print_list(struct linkedlist *head)  {

	while(head != NULL)
	{
		printf("%d\n", head->number);
		head = head->next;
	}
}

void insert_sort(int num, struct linkedlist **head) {
	struct linkedlist *newentry = malloc(sizeof(struct linkedlist));
	if (newentry == NULL)
	{
		fprintf(stderr, "Problem with malloc, exiting now");
		exit(1);

	}
	newentry->number = num;
	newentry->next = NULL;
	struct linkedlist *placer;
	//First entry into list?
     	if(*head==NULL)
	{
		*head = newentry;
	}
	//Number should go in first spot?
	else if((newentry->number) <= ((*head)->number))
	{
		newentry->next = (*head);
		(*head) = newentry;
	}
	//not in first spot
	else {
		placer = (*head);
		while(placer->next != NULL)
		{
			if((newentry->number) <= ((placer->next)->number))
			{
                     		newentry->next = placer->next;
              		       	placer->next = newentry;
				break;
			}
			placer = placer->next;
              	}
		//Last entry in list? Need to check again because
		//of break from previous while
		if(placer->next==NULL)
		{
			placer->next = newentry;
		}
	}
}

void clear_list(struct linkedlist *head)  {

	struct linkedlist *tmp;
        while(head != NULL)
        {
               	tmp = head;
                head = head->next;
		free(tmp);
        }
}

