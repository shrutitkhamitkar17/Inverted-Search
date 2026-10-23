#include "header.h"

// Searches the given word in the inverted database
int search_db(Hash_t *ht, char *word)
{
    int index;

    // Determine the hash index based on the first character of the word
    if(isalpha(word[0]))
    {
        index = tolower(word[0]) - 'a';
    
    }
    else
    {   
        index = 26;
    }

    // If the selected hash index has no words, the word is not present
    if(ht[index].link == NULL)
    {
        return NOT_FOUND;
    }

    // Start traversing the main linked list at the selected hash index
    Mlist *mtemp = ht[index].link;

    while(mtemp != NULL)
    {
        // Compare the searched word with the current word in the database
        if(strcmp(mtemp->word, word) == 0)
        {
            printf("\n+-------+----------------------+-------+---------------------------+------------+\n");
            printf("| %-5s | %-20s | %-5s | %-25s | %-10s |\n",
                   "Index", "Word", "Files", "File Name", "Word Count");
            printf("+-------+----------------------+-------+---------------------------+------------+\n");

            // Start traversing the sublist containing file information
            Slist *stemp = mtemp->sublink;

            while(stemp != NULL)
            {
                printf("| %-5d | %-20.20s | %-5d | %-25.25s | %-10d |\n",
                       index, mtemp->word, mtemp->fileCount,
                       stemp->filename, stemp->wordcount);

                stemp = stemp->link;
            }

            printf("+-------+----------------------+-------+---------------------------+------------+\n");

            return SUCCESS;
        }

        mtemp = mtemp->link;
    }

    return NOT_FOUND;
}