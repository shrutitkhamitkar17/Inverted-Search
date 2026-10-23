#include "header.h"

// Displays the complete inverted database
int display_db(Hash_t *ht)
{
    // Print the database heading
    printf("\n==============DATABASE================\n");

     // Flag to check whether the database contains any data
    int empty = 1;

    printf("\n+-------+----------------------+-------+---------------------------+------------+\n");
    printf("| %-5s | %-20s | %-5s | %-25s | %-10s |\n",
           "Index", "Word", "Files", "File Name", "Word Count");
    printf("+-------+----------------------+-------+---------------------------+------------+\n");

    // Traverse all 27 hash table indexes
    for(int i = 0; i < 27; i++)
    {
        // Traverse all words stored at the current hash index
        for(Mlist *m = ht[i].link; m != NULL; m = m->link)
        {
            // Traverse all file nodes associated with the current word
            for(Slist *s = m->sublink; s != NULL; s = s->link)
            {
                empty = 0;
                printf("| %-5d | %-20.20s | %-5d | %-25.25s | %-10d |\n",
                       i, m->word, m->fileCount, s->filename, s->wordcount);
            }
        }
    }

    // If no data was found in the database, display an empty message
    if(empty)
    {
        printf("| %-83s |\n", "Database is empty");
    }

    printf("+-------+----------------------+-------+---------------------------+------------+\n");

    return SUCCESS;
}