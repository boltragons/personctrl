#include "person.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person_t {
     char* firstName;
     char* secondName;
     char* cpf;
     int age;
};

Person* person_init(const char* firstName, const char* secondName, const char* cpf, int age) {
     if (!firstName || !secondName || !cpf || !person_validate_cpf(cpf) || age < 0) {
          return NULL;
     }
     Person* person = malloc(sizeof(Person));
     person->firstName = malloc(strlen(firstName) * sizeof(char) + 1);
     person->secondName = malloc(strlen(secondName) * sizeof(char) + 1);
     person->cpf = malloc(strlen(cpf) * sizeof(char) + 1);
     person->age = age;
     strcpy(person->firstName, firstName);
     strcpy(person->secondName, secondName);
     strcpy(person->cpf, cpf);
     return person;
}

void person_set_first_name(Person* person, const char* firstName) {
     if (!person || !firstName) {
          return;
     }
     person->firstName = realloc(person->firstName, strlen(firstName));
     strcpy(person->firstName, firstName);
}

void person_set_second_name(Person* person, const char* secondName) {
     if (!person || !secondName) {
          return;
     }
     person->secondName = realloc(person->secondName, strlen(secondName));
     strcpy(person->secondName, secondName);
}

void person_set_cpf(Person* person, const char* cpf) {
     if (!person || !cpf || !person_validate_cpf(cpf)) {
          return;
     }
     strcpy(person->cpf, cpf);
}

void person_set_age(Person* person, int age) {
     if (!person || age < 0) {
          return;
     }
     person->age = age;
}

char* person_get_first_name(const Person* person) {
     return (person) ? person->firstName : NULL;
}

char* person_get_second_name(const Person* person) {
     return (person) ? person->secondName : NULL;
}

char* person_get_cpf(const Person* person) {
     return (person) ? person->cpf : NULL;
}

int person_get_age(const Person* person) {
     return (person) ? person->age : 0;
}

bool person_equals(const Person* person01, const Person* person02) {
     return (person01) && (person02) && (strcmp(person01->firstName, person02->firstName) == 0) && (strcmp(person01->secondName, person02->secondName) == 0) && (person01->age == person02->age);
}

Person* person_copy(const Person* personFrom) {
     if (!personFrom) {
          return NULL;
     }
     return person_init(personFrom->firstName, personFrom->secondName, personFrom->cpf, personFrom->age);
}

void person_print(const Person* person) {
     if (!person) {
          return;
     }
     printf("NAME: %s %s\nAGE: %d\nCPF: %s\n\n", person->firstName, person->secondName, person->age, person->cpf);
}

void person_free(Person** person_ptr) {
     if (!person_ptr || !(*person_ptr)) {
          return;
     }
     Person* person = *person_ptr;
     free(person->firstName);
     free(person->secondName);
     free(person->cpf);
     free(person);
     person->firstName = NULL;
     person->secondName = NULL;
     person->cpf = NULL;
     *person_ptr = NULL;
}

bool person_validate_cpf(const char* cpf) {
     return (cpf) && (strlen(cpf) == 14);
}
