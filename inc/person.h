#ifndef PERSON_H
#define PERSON_H

#include <stdbool.h>
#include <stddef.h>

struct Person_t;

typedef struct Person_t Person;

Person* person_init(const char* firstName, const char* secondName, const char* cpf, int age);

void person_print(const Person *person);

bool person_equals(const Person *person01, const Person *person02);

Person* person_copy(const Person* personFrom);

void person_free(Person **person);

void person_set_first_name(Person *person, const char *firstName);

void person_set_second_name(Person *person, const char *secondName);

void person_set_cpf(Person* person, const char* cpf);

void person_set_age(Person *person, int age);

char *person_get_first_name(const Person *person);

char *person_get_second_name(const Person *person);

char* person_get_cpf(const Person* person);

int person_get_age(const Person *person_ptr);

bool person_validate_cpf(const char *cpf);

#endif