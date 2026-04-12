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

Cat* createCat(void); //Creates a Cat, itializes its values and returns it
BST_Node* createNode(Cat* value); //Creates a node, initializes its values and returns it
BST_Node* insert(BST_Node* root, BST_Node* value); //Inserts a node into BST
BST_Node* compareTraits(BST_Node* root, BST_Node* value); //Compares the amount of traits set to 1 and returns the node with the most

Cat* createCat(void){
    char name[MAX_NAME], breed[MAX_NAME];
    int charm; 
    Cat *newCat = malloc(sizeof(Cat));

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

BST_Node* createNode(Cat* value){

    //Allocate space for the node
    BST_Node* temp;
    temp = malloc(sizeof(BST_Node));

    //Initialize the fields
    temp->cat = value;
    temp->left = NULL;
    temp->right = NULL;
    temp->subtree_size = 0;

    return temp;
}

BST_Node* insert(BST_Node* root, BST_Node* value){
    if(root == NULL)
        return value;
    else{

        //element should be inserted to the right
        if(strcmp(value->cat->name, root->cat->name) > 0){
            if(root->right != NULL)    
                root->right = insert(root->right, value);
            else
                root->right = value;
        } else if(strcmp(value->cat->name, root->cat->name) < 0) {
            //element should be inserted to the left
            if(root->left != NULL)
                root->left = insert(root->left, value);
            else 
                root->left = value;
        } else {
            //root and value have the same name
            if(compareTraits(root,value) == value)
                root->cat = value->cat;
        }
    } 

    return root;
}

BST_Node* compareTraits(BST_Node* root, BST_Node* value){
    Cat* t1 = root->cat;
    Cat* t2 = value->cat;

    //Counters
    int n1 = 0, n2 = 0;

    //Finding number of traits 
    for(int i = 0; i < NUM_TRAITS; i++){
        if(t1->traits[i] == 1)
            n1++;
        if(t2->traits[i] == 1)
            n2++;
    }

    //Freeing temp cats
    free(t1);
    free(t2);

    //The existing node is replaced only if the new cat has strictly more traits set to 1
    if(n1 >= n2)
        return root;
    else    
        return value;
}







int main(void){
    int query, n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", query);
        if(query == 1){
            Cat *newCat = createCat(); //Create the cat
            BST_Node *newNode = createNode(newCat); //Create the node

        }else if (query == 2){
        
        }else if (query == 3){
        
        }else if (query == 4){
        
        }else if (query == 5){
        
        }else if (query == 6){
        
        }
    }
    
    
    return 0;
}