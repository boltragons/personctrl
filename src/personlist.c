#include "personlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

typedef struct PersonListNode_t {
     Person* person;
     LIST_ENTRY(PersonListNode_t) links;
} PersonListNode;

typedef LIST_HEAD(PersonList_t, PersonListNode_t) PersonList;

PersonList* person_list_init(void) {
     PersonList* personList = malloc(sizeof(PersonList));
     LIST_INIT(personList);
     return personList;
}

size_t person_list_size(const PersonList* list) {
     size_t listSize = 0;
     PersonListNode* iterator = NULL;
     LIST_FOREACH(iterator, list, links) {
          listSize++;
     }
     return listSize;
}

Person* person_list_get(const PersonList* list, int index) {
     if (!list || index < 0) {
          return NULL;
     }
     PersonListNode* iterator = NULL;
     size_t listCounter = 0;
     LIST_FOREACH(iterator, list, links) {
          if (index == listCounter++) {
               break;
          }
     }
     return (iterator)? iterator->person : NULL;
}

int person_list_find(const PersonList* list, const Person* person) {
     if (!list) {
          return -1;
     }
     int index = -1;
     bool searchStatus = false;
     PersonListNode* iterator = NULL;
     LIST_FOREACH(iterator, list, links) {
          index++;
          searchStatus = person_equals(iterator->person, person);
          if (searchStatus) {
               break;
          }
     }
     return (searchStatus) ? index : -1;
}

int person_list_find_if_index(const PersonList* list, const bool (*condition)(Person*)) {
     if (!list || !condition) {
          return -1;
     }
     int index = -1;
     bool searchStatus = false;
     PersonListNode* iterator = NULL;
     LIST_FOREACH(iterator, list, links) {
          index++;
          searchStatus = condition(iterator->person);
          if (searchStatus) {
               break;
          }
     }
     return (searchStatus) ? index : -1;
}

Person* person_list_find_if(const PersonList* list, const bool (*condition)(Person*)) {
     if (!list || !condition) {
          return NULL;
     }
     PersonListNode* iterator = NULL;
     LIST_FOREACH(iterator, list, links) {
          if (condition(iterator->person)) {
               break;
          }
     }
     return (iterator)? iterator->person : NULL;
}

void person_list_push_back(PersonList* list, Person* person) {
     if (!list) {
          return;
     }
     PersonListNode* iterator = NULL;
     LIST_FOREACH(iterator, list, links) {
          if (iterator->links.le_next == NULL) {
               break;
          }
     }
     PersonListNode* personNode = malloc(sizeof(PersonListNode));
     personNode->person = person;
     if (iterator != NULL) {
          LIST_INSERT_AFTER(iterator, personNode, links);

     }
     else {
          LIST_INSERT_HEAD(list, personNode, links);
     }
}

bool person_list_insert(PersonList* list, Person* person, int index) {
     if (!list || index < 0) {
          return false;
     }
     size_t listCounter = 0;
     PersonListNode* personNode = malloc(sizeof(PersonListNode));
     personNode->person = person;
     PersonListNode* iterator = NULL;
     LIST_FOREACH(iterator, list, links) {
          if (index == listCounter++) {
               LIST_INSERT_BEFORE(iterator, personNode, links);
               return true;
          }
     }
     if (!iterator && listCounter == 0) {
          LIST_INSERT_HEAD(list, personNode, links);
          return true;
     }
     return false;
}

bool person_list_remove(PersonList* list, int index) {
     if (!list || index < 0) {
          return false;
     }
     size_t listCounter = 0;
     PersonListNode* iterator = NULL;
     LIST_FOREACH(iterator, list, links) {
          if (index == listCounter++) {
               LIST_REMOVE(iterator, links);
               return true;
          }
     }
     return false;
}

size_t person_list_print(const PersonList* list) {
     if (!list) {
          return 0;
     }
     size_t index = 1;
     PersonListNode* iterator = NULL;
     LIST_FOREACH(iterator, list, links) {
          printf("ID #%ld\n", index++);
          person_print(iterator->person);
     }
     return index - 1;
}

void person_list_free(PersonList** list_ptr) {
     if (!list_ptr || !(*list_ptr)) {
          return;
     }
     PersonList* list = *list_ptr;

     PersonListNode* iterator = list->lh_first;
     while (iterator) {
          PersonListNode* currentNode = iterator;
          person_free(&currentNode->person);
          iterator = iterator->links.le_next;
          free(currentNode);
     }
     free(list);
     *list_ptr = NULL;
}
