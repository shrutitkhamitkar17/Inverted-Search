#include "header.h"

// Saves the complete inverted database into a file
int save_database(Hash_t *ht, char *filename)
{
    // Open the file in write mode
    FILE *fptr = fopen(filename, "w");

    // Check whether the file was opened successfully
    if(fptr == NULL)
    {
        printf("ERROR: Unable to open file %s for writing\n", filename);
        return FAILURE;
    }

    // Traverse all 27 hash table indexes
    for(int i = 0; i < 27; i++)
    {
        // If no word is present at this index, skip it
        if(ht[i].link == NULL)
        {
            continue;
        }

        // Start traversing the main word list at this hash index
        Mlist *mtemp = ht[i].link;

        while(mtemp != NULL)
        {
            fprintf(fptr, "# [%d]; %s; %d;", i, mtemp->word, mtemp->fileCount);

            // Start traversing the sublist containing file information
            Slist *stemp = mtemp->sublink;

            while(stemp != NULL)
            {
                fprintf(fptr, "%s; %d; #", stemp->filename, stemp->wordcount);
                stemp = stemp->link;
            }

            mtemp = mtemp->link;

            fprintf(fptr, "\n");
        }
        
        fprintf(fptr, "\n");
    }

    // Close the database file
    fclose(fptr);
    
    return SUCCESS;
}