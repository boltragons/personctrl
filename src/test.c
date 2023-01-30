#include <stdio.h>
#include <string.h>

#include "person.h"
#include "personlist.h"

bool findPedro(Person* person) {
     return (strcmp(person_get_first_name(person), "Pedro") == 0);
}

bool findRubens(Person* person) {
     return (strcmp(person_get_first_name(person), "Rubens") == 0);
}

int main(void) {    
     PersonList *personList = person_list_init();
     printf("TEST [01] : SIZE %ld\n", person_list_size(personList));

     Person *person01 = person_init("Pedro", "Botelho", "111.222.333-00", 21);
     Person *person02 = person_init("David", "Melo", "222.333.444-11", 22);
     Person *person03 = person_init("Felipe", "Ace", "333.444.555-22", 19);

     person_list_push_back(personList, person01);
     printf("TEST [02] : SIZE %ld\n", person_list_size(personList));
     person_list_push_back(personList, person02);
     printf("TEST [03] : SIZE %ld\n", person_list_size(personList));
     person_list_push_back(personList, person03);
     printf("TEST [04] : SIZE %ld\n", person_list_size(personList));

     person_list_print(personList);

     Person *personIndex02 = person_list_get(personList, 2);
     printf("TEST [05] : INDEX 02 ");
     person_print(personIndex02);

     int indexPerson03 = person_list_find(personList, person03);
     printf("TEST [06] : PERSON 03 INDEX (%d)\n", indexPerson03);

     Person *person04 = person_init("Rubens", "Filho", "333.999.666-72", 24);
     person_list_insert(personList, person04, 1);
     printf("TEST [07] : SIZE %ld\n", person_list_size(personList));
     person_list_print(personList);

     person_list_remove(personList, 0);
     printf("TEST [08] : SIZE %ld\n", person_list_size(personList));
     person_list_print(personList);

     person_list_remove(personList, 2);
     printf("TEST [09] : SIZE %ld\n", person_list_size(personList));
     person_list_print(personList);

     int indexPedro = person_list_find_if_index(personList, findPedro);
     printf("TEST [10] : INDEX OF PEDRO %d\n", indexPedro);

     int indexRubens = person_list_find_if_index(personList, findRubens);
     printf("TEST [11] : INDEX OF RUBENS %d\n", indexRubens);

     person_list_free(&personList);

     return 0;
}