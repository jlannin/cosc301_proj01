#ifndef __LIST_H__
#define __LIST_H__

/* your list data structure declarations */

struct linkedlist {
	int number;
	struct linkedlist *next;
};

/* your function declarations associated with the list */

void print_list(struct linkedlist *);
void insert_sort(int, struct linkedlist **);
void clear_list(struct linkedlist *);

#endif // __LIST_H__
