#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbols.h"
#include "utils.h"

#define STORE_SIZE 1000000

static int *address_store;

int hash(char *symbol);

void init_store()
{
    if (address_store == NULL) {
        address_store = malloc(sizeof(int) * STORE_SIZE);
        for (int i = 0; i < STORE_SIZE; ++i)
            *(address_store + i) = NULL_ADDRESS;
    }
}

void map_symbol(int line_count, char *symbol)
{
    init_store();

    int i = hash(symbol);
    assert(i < STORE_SIZE);

    printf("symbol = %s, index = %d, line = %d \n", symbol, i, line_count);

    if (address(symbol) == NULL_ADDRESS) {
        *(address_store + i) = line_count;
    }
}

void map_var(char *symbol)
{
    init_store();

    int i = hash(symbol);
    assert(i < STORE_SIZE);

    printf("var = %s, index = %d\n", symbol, i);

    if (address(symbol) == NULL_ADDRESS) {
        int addr = available_address(symbol);
        printf("mapping var to addr = %d\n", addr);
        *(address_store + i) = addr;
    }
}

int address(char *symbol)
{
    if (address_store == NULL) {
        return NULL_ADDRESS;
    }

    int i = hash(symbol);
    int address = *(address_store + i);
    return address;
}

void free_store()
{
    if (address_store == NULL) {
        return;
    }

    free(address_store);
    address_store = NULL;
}

int hash(char symbol[])
{
    assert(strlen(symbol) > 0);

    int hashVal;
    int i;
    int c;
    
    hashVal = 0;
    i = 0;

    while ((c = symbol[i]) != '\0') {
        hashVal += c;
        i++;
    }

    return hashVal % STORE_SIZE;
}

#define ADDRESS_START 16
static int curr_address = ADDRESS_START;

int available_address(char *symbol)
{
    if (streq(symbol, "SP")) {
        return 0;

    } else if (streq(symbol, "LCL")) {
        return 1;

    } else if (streq(symbol, "ARG")) {
        return 2;

    } else if (streq(symbol, "THIS")) {
        return 3;

    } else if (streq(symbol, "THAT")) {
        return 4;

    } else if (streq(symbol, "R0")) {
        return 0;

    } else if (streq(symbol, "R1")) {
        return 1;

    } else if (streq(symbol, "R2")) {
        return 2;

    } else if (streq(symbol, "R3")) {
        return 3;

    } else if (streq(symbol, "R4")) {
        return 4;

    } else if (streq(symbol, "R5")) {
        return 5;

    } else if (streq(symbol, "R7")) {
        return 7;
        
    } else if (streq(symbol, "R8")) {
        return 8;

    } else if (streq(symbol, "R9")) {
        return 9;

    } else if (streq(symbol, "R10")) {
        return 10;

    } else if (streq(symbol, "R11")) {
        return 11;

    } else if (streq(symbol, "R12")) {
        return 12;

    } else if (streq(symbol, "R13")) {
        return 13;

    } else if (streq(symbol, "R14")) {
        return 14;

    } else if (streq(symbol, "R15")) {
        return 15;

    } else if (streq(symbol, "SCREEN")) {
        return 16384;

    } else if (streq(symbol, "KBD")) {
        return 24576;

    } else {
        int addr = curr_address;
        increase_address_count();
        return addr;
    }
}

void increase_address_count()
{
    ++curr_address;
}

