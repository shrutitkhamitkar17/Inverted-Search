#include "header.h"

int update_db(Flist **f_head, Hash_t *ht, char *updateFile)
{
    //insert the new file name in Flist
    Flist *new = (Flist *)malloc(sizeof(Flist));

    if(new == NULL)
    {
        return FAILURE;
    }

    new->arr = malloc(strlen(updateFile) + 1);

    if(new->arr == NULL)
    {
        free(new);
        return FAILURE;
    }

    strcpy(new->arr, updateFile);
    new->link = NULL;

    // If list is empty
    if(*f_head == NULL)
    {
        *f_head = new;
    }
    else
    {
        Flist *temp = *f_head;

        // Traverse to last node
        while(temp->link != NULL)
        {
            temp = temp->link;
        }

        // Insert new node at last
        temp->link = new;
    }

    //create database for the new file
    create_db(new, ht);

    return SUCCESS;
}