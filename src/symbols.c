#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbols.h"
#include "utils.h"

#define STORE_SIZE 10000

void store_entry(char *key, int val);
struct list_node *stored_entry(char *key);
void increase_address_count();
int available_address(char *label);
int hash(char *label);

static struct list_node **address_store;
struct list_node {
    int addr;
    char *key;
    struct list_node *next;
};

struct list_node *make_empty_node();

void init_store()
{
    if (address_store == NULL) {
        address_store = malloc(
            sizeof(struct list_node *) * STORE_SIZE
        );
        for (int i = 0; i < STORE_SIZE; ++i)
            address_store[i] = NULL;
    }
}

void map_symbol(char *label, int line_count)
{
    init_store();
    store_entry(label, line_count);
}

void map_var(char *label)
{
    init_store();

    if (address(label) != NULL_ADDRESS)
        return;

    int address = available_address(label);
    store_entry(label, address);
}

void store_entry(char *key, int val)
{
    struct list_node *node = stored_entry(key);
 
    if (node == NULL) {
        char *key_copy = malloc(
            (sizeof(char) * strlen(key)) + 1
        );
        strcpy(key_copy, key);

        struct list_node *new_node = make_empty_node();
        new_node->key = key_copy;
        new_node->addr = val;

        int i = hash(key);
        assert(i < STORE_SIZE);
        address_store[i] = new_node;

        return;
    }

    if (!streq(key, node->key)) {
        char *key_copy = malloc(
            (sizeof(char) * strlen(key)) + 1
        );
        strcpy(key_copy, key);

        struct list_node *new_node = make_empty_node();
        new_node->key = key_copy;
        new_node->addr = val;

        node->next = new_node;
    }
}

struct list_node *stored_entry(char *key)
{
    int i;
    struct list_node *node;

    i = hash(key);
    assert(i < STORE_SIZE);
    node = address_store[i];

    while (node != NULL) {
        if (streq(node->key, key)) {
            return node;
        }

        if (node->next != NULL) {
            struct list_node *prev = node;
            node = prev->next;
        } else {
            return node;
        }
    }
    
    return NULL;
}

int address(char *label)
{
    if (address_store == NULL) {
        return NULL_ADDRESS;
    }

    struct list_node *node = stored_entry(label);

    if (node != NULL)
        return node->addr;
    else
        return NULL_ADDRESS;
}

void free_store()
{
    if (address_store == NULL) {
        return;
    }

    for (int i = 0; i < STORE_SIZE; i++) {
        struct list_node *node = address_store[i];
        struct list_node *next;

        while (node != NULL) {
            next = node->next;
            free(node->key);
            free(node);
            node = next;
        }
    }

    free(address_store);
    address_store = NULL;
}

int hash(char key[])
{
    assert(strlen(key) > 0);

    int hashVal;
    int i;
    int c;
    
    hashVal = 0;
    i = 0;

    while ((c = key[i]) != '\0') {
        hashVal += c;
        i++;
    }

    return hashVal % STORE_SIZE;
}

#define ADDRESS_START 16
static int curr_address = ADDRESS_START;

int available_address(char *label)
{
    if (streq(label, "SP")) {
        return 0;

    } else if (streq(label, "LCL")) {
        return 1;

    } else if (streq(label, "ARG")) {
        return 2;

    } else if (streq(label, "THIS")) {
        return 3;

    } else if (streq(label, "THAT")) {
        return 4;

    } else if (streq(label, "R0")) {
        return 0;

    } else if (streq(label, "R1")) {
        return 1;

    } else if (streq(label, "R2")) {
        return 2;

    } else if (streq(label, "R3")) {
        return 3;

    } else if (streq(label, "R4")) {
        return 4;

    } else if (streq(label, "R5")) {
        return 5;

    } else if (streq(label, "R7")) {
        return 7;
        
    } else if (streq(label, "R8")) {
        return 8;

    } else if (streq(label, "R9")) {
        return 9;

    } else if (streq(label, "R10")) {
        return 10;

    } else if (streq(label, "R11")) {
        return 11;

    } else if (streq(label, "R12")) {
        return 12;

    } else if (streq(label, "R13")) {
        return 13;

    } else if (streq(label, "R14")) {
        return 14;

    } else if (streq(label, "R15")) {
        return 15;

    } else if (streq(label, "SCREEN")) {
        return 16384;

    } else if (streq(label, "KBD")) {
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

struct list_node *make_empty_node()
{
    struct list_node *node = malloc(sizeof(struct list_node) * 1);
    node->addr = NULL_ADDRESS;
    node->key = NULL;
    node->next = NULL;
    return node;
}
