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
int addSize(BST_Node *node); //Gets the size of the BST and returns it
BST_Node *find(BST_Node *root, char name[]); //Takes in a name and looks for it in the Binary Tree
BST_Node* minVal(BST_Node *root); //Finds the minimum node in a given binary tree
BST_Node* maxVal(BST_Node *root); //Finds the maximum node in a given binary tree
int isLeaf(BST_Node *node); //Returns 1 if node is a leaf node, 0 otherwise 
int hasOnlyLeftChild(BST_Node *node); //Returns 1 if node has a left child and no right child 
int hasOnlyRightChild(BST_Node *node); //Returns 1 if node has a right child and no left child 

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
        } else { //root and value have the same name
            
            // If value has more traits, replace root's data with value's
            if(compareTraits(root,value) == value){
                free(root->cat->name);
                free(root->cat->breed);
                free(root->cat);
                root->cat = value->cat;
                free(value);
            } else {

                //If root has greater than or the same amount of traits, get rid of value
                freeNode(value);
                printf("Replaced\n");
            }
        }
    } 

    //Updating the sizes after inserting
    addSize(root);
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

    //The existing node is replaced only if the new cat has strictly more traits set to 1
    if(n1 >= n2)
        return root;
    else    
        return value;
}

int addSize(BST_Node *node){
    if(node == NULL)
        return 0; 

    //Finding the total number of nodes by adding the sizes of the left and right nodes and adding 1. 
    node->subtree_size = addSize(node->left) + addSize(node->right) + 1;
    return node->subtree_size;
}

BST_Node *find(BST_Node *root, char name[]){

    //We haven't found the name
    if(root == NULL){
        return NULL;
    }

    //We've found the name
    if(strcmp(root->cat->name, name) == 0)
        return root;

    //The name is less than temp's name, go left
    else if (strcmp(root->cat->name, name) > 0)
        return find(root->left, name);

    //The name is greater than temp's name, go right
    else
        return find(root->right,name);
}

BST_Node *parent(BST_Node *root, BST_Node *node){
    
    //Root is empty or root is being deleted return NULL;
    if(root == NULL || root == node)
        return NULL;
    
    //Root is the direct parent of node
    if(root->left == node || root->right == node)
        return root;
    
    //Look for node's parents in the left side of the tree
    if(strcmp(root->cat->name, node->cat->name) > 0)
        return parent(root->left, node);
    
    //Look for node's parents in the right side of the tree
    if(strcmp(root->cat->name, node->cat->name) < 0)
        return parents(root->right, node);
    return NULL; //Catch any other extraneous cases 
}

//Finds the minimum value in a given binary tree
BST_Node* minVal(BST_Node *root){
    if(root->left == NULL)
        return root;
    else   
        return minVal(root->left);
}

//Finds the maximum value in a given binary tree
BST_Node* maxVal(BST_Node *root){
    if(root->right == NULL)
        return root;
    else 
        return maxVal(root->right);
}

//Returns 1 if node is a leaf node, 0 otherwise
int isLeaf(BST_Node *node){
    return (node->left == NULL && node->right == NULL);
}

int hasOnlyLeftChild(BST_Node *node){
    return (node->left != NULL && node->right == NULL);
}

int hasOnlyRightChild(BST_Node *node){
    return (node->left == NULL && node->right != NULL);
}

BST_Node* delete(BST_Node *root, char name[]){
    BST_Node *delNode, *new_del_node, *save_node, *par;
    Cat* save_val;

    delNode = find(root, name); //Get pointer to the node to delete
    par = parent(root, delNode); //Get the parent of the node to delete

    //Case 1: The node we're deleting is a leaf node
    if(isLeaf(delNode)){

        //Delete if it is the only node in the tree
        if(par == NULL){
            freeNode(root);
            return NULL;
        }

        //Delete if node is a left child
        if(par->left == delNode){
            par->left = NULL;
            freeNode(delNode);
        }

        //Delte if node is a right child
        if(par->right == delNode){
            par->right = NULL;
            freeNode(delNode);
        }

        return root;
    }

    // Case 2.1: Delete the node that only has a left child
    if(hasOnlyLeftChild(delNode)){

        //Deleting the root node of the tree
        if(par == NULL){
            save_node = delNode->left;
            freeNode(delNode);
            return save_node; //Return the new root of the tree
        }

        //Delete if node is a left child
        if(par->left == delNode){
            save_node = par->left; //Save the node to delete
            par->left = par->left->left; //Read just the parent pointer
            freeNode(save_node); //Free the memory for the deleted node

        //Delete the node if it is a right child 
        } else{
            save_node = par->right;
            par->right = par->right->left;
            freeNode(save_node);
        }
        return root;
    }

    //Case 2.2: Delete the node that only has a right child
    if(hasOnlyRightChild(delNode)){

        //Root node is the one to delete
        if(par == NULL){
            save_node = delNode->right;
            freeNode(delNode);
            return save_node;
        }

        //Delete the node if it is a left child
        if(par->left == delNode){
            save_node = par->left;
            par->left = par->left->right;
            freeNode(delNode);

        //Delete the node if it is a right child
        } else{
            save_node = par->right;
            par->right = par->right->right;
            freeNode(save_node);
        }
        return root;
    }

    //At this point it means delNode has two children.
    new_del_node = minVal(delNode->right);
    save_val = new_del_node->cat;

    //Delete the proper value
    delete(root, save_val->name);

    //Restore the data to the original node to be deleted
    delNode->cat = save_val;

    return root;
}

void freeNode(BST_Node *node){
    free(node->cat->name);
    free(node->cat->breed);
    free(node->cat);
    free(node);
}

int main(void){
    int query, n;
    BST_Node *root = NULL;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", query);
        if(query == 1){
            Cat *newCat = createCat(); //Create the cat
            BST_Node *newNode = createNode(newCat); //Create the node
            root = insert(root, newNode); //Insert into the tree

        }else if (query == 2){
            char name[MAX_NAME];
            scanf("%s", name);
            delete(root, name);
            printf("Deletion Complete\n");
        }else if (query == 3){
        
        }else if (query == 4){
        
        }else if (query == 5){
        
        }else if (query == 6){
        
        }
    }
    
    
    return 0;
}