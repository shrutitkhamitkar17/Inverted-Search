#include "header.h"

// Function to insert a file name into the file linked list
int insert_filename(char *file_name, Flist **head)
{
    // check for duplicate 
    Flist *temp = *head;

    // Check whether the file name is already present or not
    while(temp != NULL)
    {
        // Compare the current file name with the new file name
        if(strcmp(temp->arr, file_name) == 0)
        {
            return DUPLICATE;
        }

        temp = temp->link;
    }
    
    // Allocate memory for a new file-list node
    Flist *newNode = (Flist*)malloc(sizeof(Flist));

    // check memory allocation success or not
    if(newNode == NULL)
    {
        printf("Memory allocation is failed\n");
        return FAILURE;
    }

    // Allocate memory to store the file name
    newNode->arr = malloc(strlen(file_name) + 1);
     // check memory allocation success or not
    if(newNode->arr == NULL)
    {
        free(newNode);
        printf("Memory allocation failed\n");
        return FAILURE;
    }
    strcpy(newNode->arr, file_name);

    newNode->link = NULL;

    // Check whether the linked list is empty
    if(*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        //insert last in SLL
        Flist *tail = *head;
    
        if(tail == NULL)
        {
            printf("Memory allocation fails");
            return FAILURE;
        }
        
        // Traverse until the last node is reached
        while(tail->link != NULL)
        {
            tail = tail->link;
        }
        
        // Link the last node to the new node
        tail->link = newNode;
    }

    return SUCCESS;
}

//Displays all Valid File Names
int print_filenames(Flist *head)
{
    printf("Head ->");
    // Traverse the complete linked list
    while(head)
    { 
		printf(" %s -> ",head->arr);
		head = head->link;
	}
	printf("NULL\n");
}

// Function to check whether a file is already present in the list
int is_file_present(Flist *head, char *filename)
{
    // Traverse the linked list
    while(head != NULL)
    {
        // Compare the current file name with the given file name
        if(strcmp(head->arr, filename) == 0)
        {
            return 1;   // already present
        }
        head = head->link;
    }
    return 0;
}
