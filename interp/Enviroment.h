#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

extern bool initialized;
uint8_t *esp;
uint8_t *top;

struct Variable {
    int id;
    char* name;
    uint32_t type;
    uint64_t data;
};

void init_enviroment();

//Returns variable descriptor (id)
int register_variable(char* name);

//Returns variable descriptor (id)
int hash_variable(char* name);

//Access hash element using id
struct Variable* lookup_variable(int i);




#endif