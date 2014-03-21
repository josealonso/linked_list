#ifndef CONTACTS_H
#define CONTACTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define MAX_ELEMENTS 200
#define NUM_DIGITS 11

struct element {
    uint8_t id;
    char name[20];
    char phone_number[NUM_DIGITS];
    struct element* next_element; 
}; 
struct element* head;
uint8_t global_id;
struct element elements_pool[MAX_ELEMENTS];  // not used
void initialize_memory();
void create_element(const char* string, const char* number);
void delete_element(const char* name);
struct element* search_element(uint8_t num);
void update_indexes(struct element* elem); 
void print_list(struct element*); 

#endif

