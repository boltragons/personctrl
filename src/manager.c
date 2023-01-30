#include "manager.h"

#include "person.h"
#include "personlist.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// -----------------------------------------------------------------------------
// GLOBAL VARIABLES
// -----------------------------------------------------------------------------
PersonList *personList = NULL;

// -----------------------------------------------------------------------------
// MENU FUNCTIONS PROTOTYPES
// -----------------------------------------------------------------------------
void systemMenuShow(void);

void systemMenuCreate(void);

void systemMenuRemove(void);

void systemMenuList(void);

void systemMenuUpdate(void);

void systemMenuLoadBackup(void);

void systemMenuSaveBackup(void);

void systemShowMainMenu(void);

// -----------------------------------------------------------------------------
// PRIVATE FUNCTIONS PROTOTYPES
// -----------------------------------------------------------------------------
void systemClearBuffer(void);

void systemCleanConsole(void);

void systemWaitEnter(void);

bool systemLoadBackup(char *filepath);

bool systemSaveBackup(char *filepath);

bool systemGetId(int *id);

bool systemGetFirstName(char *firstName);

bool systemGetSecondName(char *secondName);

bool systemGetCpf(char *cpf);

bool systemGetAge(int *age);

bool systemGetFilePath(char *filePath);

// -----------------------------------------------------------------------------
// PUBLIC FUNCTIONS IMPLEMENTATION
// -----------------------------------------------------------------------------
void systemInit(void) {
     personList = person_list_init();
     if(!personList) {
          exit(EXIT_FAILURE);
     }
}

void systemProcess(void) {
     int option = -1;
     while(option != 0) {
          systemCleanConsole();
          systemShowMainMenu();
          scanf("%d", &option);
          systemClearBuffer();
          switch(option) {
               case 0:
                    break;
               case 1:
                    systemMenuCreate();
                    break;
               case 2:
                    systemMenuList();
                    break;
               case 3:
                    systemMenuRemove();
                    break;
               case 4:
                    systemMenuUpdate();
                    break;
               case 5:
                    systemMenuLoadBackup();
                    break;
               case 6:
                    systemMenuSaveBackup();
                    break;
               default:
                    printf("Invalid option!\n");
                    systemWaitEnter(); 
                    break;
          }
     }
}

void systemShutDown(void) {
     person_list_free(personList);
}

// -----------------------------------------------------------------------------
// MENU FUNCTIONS IMPLEMENTATION
// -----------------------------------------------------------------------------
void systemShowMainMenu(void) {
     puts("=============================================");
     puts("\t\t PERSON Ctrl");
     puts("=============================================");
     puts("Choose an option to continue:");
     puts("1) ADD a person");
     puts("2) LIST all persons");
     puts("3) REMOVE a person");
     puts("4) EDIT a person");
     puts("5) LOAD backup");
     puts("6) SAVE backup");
     puts("0) EXIT manager");
     printf("=============================================\n> ");
}

void systemMenuCreate(void) {
     systemCleanConsole();
     printf(" =============================================\n");
     printf(" \t\t ADD PERSON\n");
     printf(" =============================================\n");

     char firstName[100];
     if(!systemGetFirstName(firstName)) return;
     
     char secondName[100];
     if(!systemGetSecondName(secondName)) return;

     char cpf[15];
     if(!systemGetCpf(cpf)) return;

     int age = 0;
     if(!systemGetAge(&age)) return;

     Person *person = person_init(firstName, secondName, cpf, age);
     person_list_push_back(personList, person);

     printf("\nPerson added with SUCCESS!\n");
     systemWaitEnter();  
}

void systemMenuRemove(void) {
     systemCleanConsole();
     printf(" =============================================\n");
     printf(" \t\t DELETE PERSON\n");
     printf(" =============================================\n");

     int id = 0;
     if(!systemGetId(&id)) return;

     person_list_remove(personList, id - 1);

     printf("\nPerson removed with SUCCESS!\n");
     systemWaitEnter();  
}

void systemMenuList(void) {
     systemCleanConsole();
     printf(" =============================================\n");
     printf(" \t\t LIST PERSON\n");
     printf(" =============================================\n");

     person_list_print(personList);

     systemWaitEnter();  
}

void systemMenuUpdate(void) {
     systemCleanConsole();
     printf(" =============================================\n");
     printf(" \t\t UPDATE PERSON\n");
     printf(" =============================================\n");

     int id = 0;
     if(!systemGetId(&id)) return;
     
     Person *person = person_list_get(personList, id - 1);

     int option = -1;
     while(option != 0) {
          systemCleanConsole();
          printf(" =============================================\n");
          printf(" \t\t UPDATE PERSON\n");
          printf(" =============================================\n");
          puts("Choose a field to update (enter 0 to RETURN):");
          puts("1) FIRST NAME");
          puts("2) SECOND NAME");
          puts("3) CPF");
          puts("4) AGE");
          puts("0) RETURN");
          printf("=============================================\n> ");

          scanf("%d", &option);
          systemClearBuffer();
          switch(option) {
               case 1:{
                    char firstName[100];
                    if(!systemGetFirstName(firstName)) break;
                    person_set_first_name(person, firstName);
                    printf("\nFIRST NAME updated with SUCCESS!\n");
                    systemWaitEnter();  
                    break;
                    }
               case 2:{
                    char secondName[100];
                    if(!systemGetSecondName(secondName)) return;
                    person_set_second_name(person, secondName);
                    printf("\nSECOND NAME updated with SUCCESS!\n");
                    systemWaitEnter();  
                    break;
                    }
               case 3:{
                    char cpf[15];
                    if(!systemGetCpf(cpf)) return;
                    person_set_cpf(person, cpf);
                    printf("\nCPF updated with SUCCESS!\n");
                    systemWaitEnter();  
                    break;
                    }
               case 4:{
                    int age = 0;
                    if(!systemGetAge(&age)) return;
                    person_set_age(person, age);
                    printf("\nAGE updated with SUCCESS!\n");
                    systemWaitEnter();  
                    break;
                    }
               case 0:
                    return;
               default:
                    printf("Invalid option!\n");
                    systemWaitEnter(); 
                    break;
          }

     }
}

void systemMenuLoadBackup(void) {
     char filePath[200];
     while(true) {
          systemCleanConsole();
          printf(" =============================================\n");
          printf(" \t\t LOAD BACKUP\n");
          printf(" =============================================\n");
          if(!systemGetFilePath(filePath)) return;
          if(systemLoadBackup(filePath)) break;
     }
     
     printf("\nBackup LOADED with SUCCESS!\n");
     systemWaitEnter();  
}

void systemMenuSaveBackup(void) {
     char filePath[200];
     while(true) {
          systemCleanConsole();
          printf(" =============================================\n");
          printf(" \t\t SAVE BACKUP\n");
          printf(" =============================================\n");
          if(!systemGetFilePath(filePath)) return;
          if(systemSaveBackup(filePath)) break;
     }
     
     printf("\nBackup SAVED with SUCCESS!\n");
     systemWaitEnter();  
}

// -----------------------------------------------------------------------------
// PRIVATE FUNCTIONS IMPLEMENTATION
// -----------------------------------------------------------------------------
void systemCleanConsole(void) {
     printf("\033[H\033[J");
}

void systemClearBuffer(void) {
     while(getchar() != '\n');
}

void systemWaitEnter(void) {
     printf("Press ENTER to continue.");
     while(getchar() != '\n');
}

bool systemLoadBackup(char *filepath) {
     FILE *backupFile = fopen(filepath, "r+");
     if(!backupFile) {
          printf("\nInvalid file path!\n");
          systemWaitEnter();
          return false;
     }

     if(personList != NULL) {
          person_list_free(personList);
          personList = person_list_init();
     }

     while(1) {
          char firstName[100];
          char secondName[100];
          char cpf[100];
          int age;
          if(fscanf(backupFile, "%s", firstName) != 1) break;
          if(fscanf(backupFile, "%s", secondName) != 1) break;
          if(fscanf(backupFile, "%s", cpf) != 1) break;
          if(fscanf(backupFile, "%d", &age) != 1) break;
          Person *person = person_init(firstName, secondName, cpf, age);
          person_list_push_back(personList, person);
     }
     
     fclose(backupFile);

     return true;
}

bool systemSaveBackup(char *filepath) {
     FILE *backupFile = fopen(filepath, "w+");
     if(!backupFile) {
          printf("\nInvalid file path!");
          systemWaitEnter();
          return false;
     }

     size_t listSize = person_list_size(personList);
     for(int i = 0; i < listSize; i++) {
          Person *person = person_list_get(personList, i);
          fprintf(backupFile, "%s\n%s\n%s\n%d\n", 
               person_get_first_name(person), 
               person_get_second_name(person), 
               person_get_cpf(person), 
               person_get_age(person)
          );
     }
     fclose(backupFile);

     return true;
}

bool systemGetId(int *id) {
     size_t listSize = person_list_size(personList);
     printf("Insert the ID (enter -1 to RETURN): ");
     while(true) {
          scanf("%d", id);
          systemClearBuffer();
          if(*id == -1) {
               return false;
          }
          if(listSize > *id && *id > 0) {
               return true;
          }
          systemCleanConsole();
          printf("\nInvalid input!\nInsert the ID again: ");
          continue;
     }
}

bool systemGetFirstName(char *firstName) {
     printf("Insert the FIRST NAME (enter Q to RETURN): ");
     while(true) {
          scanf("%100[^\n]", firstName);
          systemClearBuffer();
          if(strcmp(firstName, "Q") == 0) {
               return false;    
          }
          if(strlen(firstName) > 0) {
               return true;
          }
          systemCleanConsole();
          printf("\nInvalid input!\nInsert the FIRST NAME again: ");
          continue;
     }
}

bool systemGetSecondName(char *secondName) {  
     printf("Insert the SECOND NAME (enter Q to RETURN): ");
     while(true) {
          scanf("%100[^\n]", secondName);
          systemClearBuffer();
          if(strcmp(secondName, "Q") == 0) {
               return false;     
          }
          if(strlen(secondName) > 0) {
               return true;
          }
          systemCleanConsole();
          printf("\nInvalid input!\nInsert the SECOND NAME again: ");
          continue;
     }
}

bool systemGetCpf(char *cpf) {
     printf("Insert the CPF (enter Q to RETURN): ");
     while(true) {
          scanf("%14s", cpf);
          systemClearBuffer();
          if(strcmp(cpf, "Q") == 0) {
               return false;     
          }
          if(person_validate_cpf(cpf)) {
               return true;
          }
          systemCleanConsole();
          printf("\nInvalid input!\nInsert the CPF again: ");
          continue;
     }
}

bool systemGetAge(int *age) {
     printf("Insert the AGE (enter -1 to RETURN): ");
     while(true) {
          scanf("%d", age);
          systemClearBuffer();
          if(*age == -1) {
               return false;
          }
          if(*age >= 0) {
               return true;
          }
          systemCleanConsole();
          printf("\nInvalid input!\nInsert the AGE again: ");
          continue;
     }
}

bool systemGetFilePath(char *filePath) {
     printf("Type the file path to LOAD the backup (enter Q to RETURN): ");
     while(true) {
          scanf("%200s", filePath);
          systemClearBuffer();
          if(strcmp(filePath, "Q") == 0) {
               return false;;     
          }
          if(strlen(filePath)) {
               return true;
          }
          systemCleanConsole();
          printf("\nInvalid input!\nInsert the file path again: ");
          continue;
     }
}
