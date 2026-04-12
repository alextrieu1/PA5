         /*COP 3502C
This program is written by: Alex Trieu*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 25
#define NUM_TRAITS 5

typedef struct Cat{
    char *name; //dynamically allocate space for a cat's name
    char *breed; //dynamically allocate space for a cat's breed
    int charm; // unique charm score for each cat
    int traits[NUM_TRAITS]; //Scored corresponding to each index in TRAIT_NAMES
}Cat;

typedef struct BST_Node{
    Cat *cat;
    struct BST_Node *left;
    struct BST_Node *right;
    int subtree_size; // stores the current sixe of this subtree's root(not height)
}BST_Node;

const char *TRAIT_NAMES[NUM_TRAITS] = {"friendly", "grumpy", "playful", "lazy", "curious"};