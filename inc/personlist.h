#ifndef PERSON_LIST_H
#define PERSON_LIST_H

#include <stdbool.h>
#include <stddef.h>

#include "person.h"

struct PersonList_t;

typedef struct PersonList_t PersonList;

PersonList *person_list_init(void);

size_t person_list_size(const PersonList *list);

Person *person_list_get(const PersonList *list, int index);

int person_list_find(const PersonList *list, const Person *person);

Person *person_list_find_if(const PersonList *list, const bool (*condition)(Person*));

int person_list_find_if_index(const PersonList *list, const bool (*condition)(Person*));

void person_list_push_back(PersonList *list, Person *person);

bool person_list_insert(PersonList *list, Person *person, int index);

bool person_list_remove(PersonList *list, int index);

size_t person_list_print(const PersonList *list);

void person_list_free(PersonList **list_ptr);

#endif