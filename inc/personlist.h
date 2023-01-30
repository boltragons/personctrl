#ifndef PERSON_LIST_H
#define PERSON_LIST_H

#include <stdbool.h>
#include <stddef.h>

#include "person.h"

struct PersonList_t;

typedef struct PersonList_t PersonList;

PersonList *person_list_init(void);

size_t person_list_size(PersonList *list);

Person *person_list_get(PersonList *list, int index);

int person_list_find(PersonList *list, Person *person);

Person *person_list_find_if(PersonList *list, bool (*condition)(Person*));

int person_list_find_if_index(PersonList *list, bool (*condition)(Person*));

void person_list_push_back(PersonList *list, Person *person);

bool person_list_insert(PersonList *list, Person *person, int index);

bool person_list_remove(PersonList *list, int index);

void person_list_print(PersonList *list);

void person_list_free(PersonList *list);

#endif