         /*COP 3502C
This program is written by: Alex Trieu*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 25
#define NUM_TRAITS 5
const char *TRAIT_NAMES[NUM_TRAITS] = {"friendly", "grumpy", "playful", "lazy", "curious"};

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
    int subtree_size; // stores the current size of this subtree's root(not height)
}BST_Node;

Cat* createCat(void); //Creates a Cat and returns it

Cat* createCat(void){
    char name[MAX_NAME], breed[MAX_NAME];
    int charm; 
    Cat* newCat = malloc(sizeof(Cat));

    //Getting input
    scanf("%s %s %d", name, breed, &charm);

    //Dynamically allocated memory for cat name and breed
    newCat->name = malloc((strlen(name) + 1) * sizeof(char));
    newCat->breed = malloc((strlen(breed) + 1) * sizeof(char));
    strcpy(newCat->name, name);
    strcpy(newCat->breed, breed);
    newCat->charm = charm;

    //Getting traits
    for(int i = 0; i < NUM_TRAITS; i++){
        int trait;
        scanf("%d", &trait);
        newCat->traits[i] = trait; 
    }

    return newCat;
}









int main(void){
    int query, n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", query);
        if(query == 1){
            

        }else if (query == 2){
        
        }else if (query == 3){
        
        }else if (query == 4){
        
        }else if (query == 5){
        
        }else if (query == 6){
        
        }
    }
    
    
    return 0;
}