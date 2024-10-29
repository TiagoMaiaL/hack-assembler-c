#include <stdio.h>
#include <stdlib.h>
#include "symbols.h"

#define STORE_SIZE 10000

static int *address_store;

int hash(char *symbol);

void store(int address, char *symbol)
{
    if (address_store == NULL) {
        address_store = malloc(sizeof(int) * STORE_SIZE);
        for (int i = 0; i < STORE_SIZE; ++i)
            *(address_store + i) = NULL_ADDRESS;
    }

    int i = hash(symbol);
    *(address_store + i) = address;
}

int address(char *symbol)
{
    if (address_store == NULL) {
        perror("Attempting to access unintialized store");
        return NULL_ADDRESS;
    }

    int i = hash(symbol);
    int address = *(address_store + i);
    return address;
}

void free_store()
{
    free(address_store);
}

int hash(char symbol[])
{
    int hashVal;
    int i;
    int c;
    
    hashVal = 0;
    i = 0;

    while ((c = symbol[i]) != '\0') {
        hashVal += c;
    }

    return hashVal;
}
