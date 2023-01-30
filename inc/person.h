#ifndef PERSON_H
#define PERSON_H

#include <stdbool.h>
#include <stddef.h>

struct Person_t;

typedef struct Person_t Person;

Person* person_init(char* firstName, char* secondName, char* cpf, int age);

void person_print(Person *person);

bool person_equals(Person *person01, Person *person02);

Person* person_copy(Person* personFrom);

void person_free(Person *person);

void person_set_first_name(Person *person, char *firstName);

void person_set_second_name(Person *person, char *secondName);

void person_set_cpf(Person* person, char* cpf);

void person_set_age(Person *person, int age);

char *person_get_first_name(Person *person);

char *person_get_second_name(Person *person);

char* person_get_cpf(Person* person);

int person_get_age(Person *person);

bool person_validate_cpf(char *cpf);

#endif