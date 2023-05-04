/*
* C Program creates a linked list with numbers inputted by the user
* and allows user to use a menu to display linked list, insert new
* numbers, delete numbers in the linked list, and search for position 
* of number in linked list.
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

//Node structure created
struct LinkedList {
    int value;
    struct LinkedList *next;

};

typedef struct LinkedList *node;

//Function declarations
node createNode();
void display(node start);
void insertLast(node start);
node insertFirst(node start);
node insertAnywhere(node start);
node deleteFirst(node start);
node deleteLast(node start);
node deleteAnywhere(node start);
void search(node start);
bool validateNumInput(char num[]);

//Main function for menu and getting user input
int main() 
{
    //Variable declaration
    int size = 1;
    int choiceNum = 1;
    char num[256];
    char choice[256];
    char repeatInput[100];
    char repeat = 'y';
    bool checkValid = true;

    node start = NULL;
    node temp;
    node ptr;

    //Create new node
    while (repeat == 'y')
    {
        temp = createNode();
        printf("Input the data for node %d: \n", size);
        scanf("%s", num);
        checkValid = validateNumInput(num);

        //Validates user number input
        while (checkValid == false) 
        {
            printf("Re-entered value for node %d: \n", size);
            scanf("%s", num);
            checkValid = validateNumInput(num);
        }
        temp -> value = atoi(num);

        //Adds user node into linked list
        if (start == NULL) 
        {
            start = temp;
        } 
        else 
        {
            ptr = start;

            while (ptr -> next != NULL) 
            {
                ptr = ptr -> next;
            }
            ptr -> next = temp;
        }

        //Asks user if they want to add more nodes to linked list
        do
        {   
            //Clears input
            fflush(stdin);
            printf("Enter more <y>es/<n>o?\n");
            scanf("%s", repeatInput);
            //Checks for repeatInput validity
            if(strlen(repeatInput) == 1)
            {
                repeat = repeatInput[0];

                //Checks for repeat validity and clears input
                if(repeat != 'y' && repeat != 'n')
                {
                    printf("\nInvalid input.\n");
                    fflush(stdin);
                }
                else
                {
                    break;
                }
            }
            else
            {
                printf("\nInvalid input.\n");
                repeat = 'p';
            }

        } while (repeat != 'y' && repeat != 'n');
        //Exits out of loop
        if(repeat == 'n') 
        {
            fflush(stdin);   
            break;
        }
        //Continues creating new nodes 
        if(repeat == 'y')
        {
            size++;
            repeat = 'y';
        }  
        
    }
    //Menu for selecting options
    while(choiceNum != 0 && repeat == 'n') 
    {
        checkValid = false;
        
        while(checkValid == false)
        {
            //Displays menu to user
            printf("\n======================\n");
            printf("1) Display\n");
            printf("2) Insert First\n");
            printf("3) Insert Last\n");
            printf("4) Insert Anywhere\n");
            printf("5) Delete First\n");
            printf("6) Delete Last\n");
            printf("7) Delete Anywhere\n");
            printf("8) Search\n");
            printf("0) Exit\n");
            printf("Enter your choice\n");
            scanf("%s", choice);
            //Validates user input for choice
            checkValid = validateNumInput(choice);
        }
        choiceNum = atoi(choice);

        switch(choiceNum) {
            //Display all nodes in linked list
            case 1:
                display(start);
                break;

            //Insert new number first
            case 2:
                start = insertFirst(start);
                break;
            
            //Insert new number last
            case 3:
                insertLast(start);
                break;
            
            //Insert new number anywhere in linked list
            case 4:
                start = insertAnywhere(start);
                break;
            
            //Delete first number
            case 5:
                start = deleteFirst(start);
                break;
            
            //Delete last number
            case 6:
                deleteLast(start);
                break;
            
            //Delete number from anywhere in linked list
            case 7:
                start = deleteAnywhere(start);
                break;
            
            //Searches for a number and displays position in linked list
            case 8:
                search(start);
                break; 
            
            //Exits program
            case 0:
                printf("\nProgram is exiting.\n");
                break; 
            
            //Invalid input
            default:
                printf("\nInvalid input.\n");
                break;
        }
    }

}

//Allocates memory for new node created
node createNode() 
{
    node temp;
    temp = (node)malloc(sizeof(struct LinkedList));
    if(temp == NULL ) 
    {
        printf("Out of memory space.\n");
        return NULL;
    } 
    else 
    {
        temp -> next = NULL;
        return temp;
    }
    
}

//Displays all nodes in linked list
void display(node start) 
{
    node ptr = start;
    //Checks for empty linked list
    if(ptr == NULL) 
    {
        printf("\nList is empty.\n");
        return;
    }
    //Displays numbers in linked list
    printf("\nNumbers in list: ");
    while(ptr != NULL) {
        printf("%d ",ptr -> value);
        ptr = ptr -> next;
    }
    printf("\n");
}

//Inserts new number at the beginning of linked list
node insertFirst(node start) 
{
    char num[256];
    bool checkValid = false;
    node temp = createNode();
    node ptr;

    //Validates new number 
    while (checkValid == false)
    {
        printf("Insert first number: \n");
        scanf("%s", num);

        checkValid = validateNumInput(num);
    }
    //Creates new node for number and stores it at the beginning
    temp -> value = atoi(num); 
    temp -> next = start;
    start = temp;  
    printf("Number inserted first is: %d.\n", start -> value);
    return start;
}

//Inserts new number at the very end of linked list
void insertLast(node start) 
{
    char num[256];
    bool checkValid = false;
    node temp = createNode();
    node ptr;

    //Validates new number 
    while (checkValid == false)
    {
        printf("\nInsert last number: \n");
        scanf("%s", num);

        checkValid = validateNumInput(num);
    }
    //Creates new node for number
    temp -> value = atoi(num);

    ptr = start;

    //Searches for end of linked list
    while (ptr -> next != NULL) 
    {
        ptr = ptr -> next;
    }

    //Moves pointer to point to new node
    ptr -> next = temp;
    ptr = ptr -> next;
    printf("Number inserted last is: %d.\n", ptr -> value);
    
}

node insertAnywhere(node start)
{
    int posChoice;
    char pos[256];
    char num[256];
    bool checkValid = false;
    node temp = createNode();
    node ptr = start;

    //Checks for empty linked list
    if(start == NULL) 
    {
        printf("\nList is empty.\n");
        return start;
    }

    //Validates new number
    while (checkValid == false) 
    {
        printf("\nEnter new number being inserted: \n");
        scanf("%s", num);
        checkValid = validateNumInput(num);
    }
    //Creates new node for new number
    temp -> value = atoi(num);

    //Looks for entered position

    checkValid = false;
    while(1) 
    {
        while(checkValid == false) 
        {
            printf("Enter position to insert number starting from 1.\n");
            scanf("%s", pos);
            checkValid = validateNumInput(pos);
            if(atoi(pos) == 0) 
            {
                printf("Position not valid\n");
                checkValid = false;
            }
        }
        posChoice = atoi(pos);

        //Insert new node at the beginning
        if(posChoice == 1) 
        {
            temp -> next = start;
            start = temp;
            printf("%d was inserted in the first position.\n", start -> value);
            return start;
        } 
        else 
        {
            checkValid = true;
            ptr = start;
            for (int i = 0; i < posChoice - 1; i++) 
            {
                if (i == 0) 
                {

                }
                else if (checkValid == false) 
                {

                }
                else 
                {
                    ptr = ptr->next;
                    if (ptr == NULL) 
                    {
                        printf ("Position not valid\n");
                        checkValid = false;
                    }
                }
            }

            if(checkValid == true) 
            {
                temp->next = ptr->next;
                ptr->next = temp;
                break;
            }
        }
    }

    printf("%d was inserted in position %d", temp -> value, posChoice);
    return start;
}

//Delete first node in the linked list
node deleteFirst(node start) 
{
    node ptr;

    //Checks for empty linked list
    if (start == NULL) 
    {
        printf("\nList is empty.\n");
        return start;
    }
    else
    {
        //Deletes first node in the list
        ptr = start;
        start = start -> next;
        printf("\nNumber deleted is: %d.\n", ptr -> value);
        free(ptr);
        return start;
    }
    
}

//Deletes last node in linked list
node deleteLast(node start) 
{
    node temp;
    node ptr;

    //Checks for empty linked list
    if (start == NULL) 
    {
        printf("\nList is empty.\n");
        return start;
    }
    //Deletes next node if null
    else if (start -> next == NULL)
    {
        ptr = start;
        start = NULL;
        free(ptr);
        printf("\nNumber deleted is: %d.\n", ptr -> value);
        return start;
    }
    else 
    {
        //Searches for last node in linked list
        ptr = start;
        while (ptr -> next != NULL) 
        {
            temp = ptr;
            ptr = ptr -> next;
        }
        //Deletes last found node in linked list
        temp -> next = NULL;
        printf("\nNumber deleted is: %d.\n", ptr -> value);
        free(ptr);
        return start;
    }

}

//Deletes a node from anywhere in the linked list
node deleteAnywhere(node start)
{
    int posChoice;
    char pos[256];
    char num[256];
    bool checkValid = false;
    node ptr = start;
    node temp = ptr;

    //Checks for empty linked list
    if(start == NULL) 
    {
        printf("\nList is empty.\n");
        return start;
    }

    //Looks for entered position
    checkValid = false;
    while(1) 
    {
        while(checkValid == false) 
        {
            printf("Enter position to delete number starting from 1.\n");
            scanf("%s", pos);
            checkValid = validateNumInput(pos);
            if(atoi(pos) == 0) 
            {
                printf("Position not valid\n");
                checkValid = false;
            }
        }

        posChoice = atoi(pos);

        //Delete node at the beginning
        if(posChoice == 1) 
        {
            ptr = start;
            start = start -> next;
            printf("The number %d was deleted in the first position.\n", ptr -> value);
            free(ptr);
            return start;
        } 
        else 
        {
            checkValid = true;
            ptr = start;
            for (int i = 0; i < posChoice; i++) 
            {
                if(i == 0) 
                {

                }
                else if(checkValid == false) 
                {

                } 
                else 
                {
                    temp = ptr;
                    ptr = ptr->next;
                    if (ptr == NULL) 
                    {
                        printf ("Position not valid\n");
                        checkValid = false;
                    }
                }
            }

            if(checkValid == true) 
            {
                if(ptr -> next == NULL) 
                {
                    temp->next = NULL;
                } 
                else 
                {
                    temp->next = ptr->next;
                }

                printf("%d was deleted at position %d", ptr->value, posChoice);
                free(ptr);
                return start;
            }
        }
    }
}

//Searches for number in linked list
void search(node start) 
{
    char num[256];
    char pos[256];
    int posChoice;
    int posLoc = 0;
    bool posValid = false;
    bool checkValid = false;
    node ptr = start;
    
    //Checks for empty linked list
    if(start == NULL) 
    {
        printf("\nList is empty.\n");
        return;

    }

    //Validates and searches for number in linked list
    while (posValid == false)
    {
        while (checkValid == false)
        {
            printf("\nEnter a number in the list to find its position: \n");
            scanf("%s", num);
            checkValid = validateNumInput(num);
        }

        posChoice = atoi(num);

        int posLoc = 0;

        //Searches for number in linked list
        while(ptr -> value != posChoice && ptr -> next != NULL)
        {
            ptr = ptr -> next;
            posLoc++;
        }

        //Unable to find number in linked list
        if(ptr -> next == NULL)
        {
            printf("Number does not exist in list.\n");
            posValid = false;
            checkValid = false;
            ptr = start;
        }

        //Number in linked list found
        if(ptr -> value == posChoice)
        {
            posValid = true;
            printf("%d is at position %d in the list.\n", ptr -> value, posLoc + 1);
        }
    }
}

//Validates number inputs
bool validateNumInput(char num[])
{
    //Checks each character in array for digit
    for(int index = 0; index < strlen(num); index++)
    {
        if (!isdigit(num[index]))
        {
            printf("\nEntered value is not a positive integer.\n");
            return false;
            break;
        }
    }

    return true;
    
}
