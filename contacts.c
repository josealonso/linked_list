
#include "contacts.h"

#if 0
int binary_search(int point) {
    if (point == 1)
        return point;
    return binary_search(point / 2);
#endif
int main (int argc, char **argv) {
    // Implementing a very basic contact list
    /***********************************************************
First, we allocate al the memore up front, since we wont be using dynamic memory allocation.
Like in many embedded systems and other applications (web browsers, videogames, etc.) 
we will implement our own memory allocator.
In reality, the SQLite databese that comes with Android will take care of the memory management.
----------
We will have the following operations:
- Create, Delete, Modify 
    ***********************************************************/
  /* TODO: Implement the Modify operation
           Introduce the new names in alphabetical order
           Macro FOR_EACH
           Other improvements
  */

    initialize_memory();
    create_element("Sam Hicks", "76367565213");
    create_element("Von Newman", "71267565277");
    create_element("Samuel Beckett", "12347565282");
    create_element("Lewis Caroll", "97654565111");
    delete_element("Samuel beckett");
    delete_element("Samuel Beckett");
    delete_element("Sam Hicks");
    print_list(head);
    return 0;
}

void initialize_memory() {
    head = malloc(sizeof (struct element));
    global_id = 0;
    head->id = 0;
    strcpy(head->name, "Myself");
    memcpy(head->phone_number, "00000000000", NUM_DIGITS - 1);
    head->next_element = NULL; 
}

void create_element(const char* name, const char* number) {
    struct element* temp = NULL;
    struct element* new_element = malloc(sizeof (struct element));
    if (new_element == NULL) {
        fprintf(stderr, "Unable to allocate memory for new element\n");
        exit(-1);
    }
    global_id++;  
    new_element->id = global_id;
    strcpy(new_element->name, name);
    memcpy(new_element->phone_number, number, NUM_DIGITS);
    new_element->next_element = NULL; 

    if (head->next_element == NULL) {
        /* when the head is the only node */
        head->next_element = new_element;
    }
    else {
      temp = head; 
      while (temp->next_element != NULL) {
          temp = temp->next_element;
      }
      temp->next_element = new_element;
    }
    printf("\nThe name %s has been ADDED to the list\n", name);
}

/* Assumption: the header will never be deleted */
void delete_element(const char* name) {
    uint8_t index = 0;
    struct element* temp = NULL, *prev = NULL;
    temp = head;
    while (strcmp(temp->name, name) != 0  && temp->next_element != NULL) {
        temp = temp->next_element;
    }
    if (temp->next_element == NULL) {
        printf("\nThe name %s IS NOT in the list\n", name);
        return;
    }
    if (temp->next_element != NULL) {
        /* the node to be removed is interior to the list */
        index = temp->id;
        prev = search_element(index - 1);
        prev->next_element = temp->next_element;
        update_indexes(temp);
    }
    free(temp);
    printf("\nThe name %s has been DELETED from the list\n", name);
}
 
struct element* search_element(uint8_t num) {
    struct element* temp = head;
    while (temp->id < num) {
        temp = temp->next_element;
    }
    return temp;
}

void update_indexes(struct element* elem) {
    struct element* elem2 = elem->next_element;
    while (elem2 != NULL) {
        elem2->id = elem2->id - 1;
        elem2 = elem2->next_element; 
    }
}

void print_list(struct element* elem2) {
    struct element* temp2 = elem2;
    while (temp2 != NULL) {
        printf("\nElement %d", temp2->id);
        printf("\twith name %s", temp2->name);
        printf("\tand phone number %s\n", temp2->phone_number);
        temp2 = temp2->next_element;
    }
}



