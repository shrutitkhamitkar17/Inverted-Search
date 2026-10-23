#include "header.h"

int create_db(Flist *f_head, Hash_t *ht)
{
    Flist *temp = f_head;

    //Traverse all nodes present in Flist
    while(temp != NULL)
    {
        printf("---------------------------------------------------------------------\n");

        FILE *fptr = fopen(temp->arr, "r");

        if(fptr == NULL)
        {
            printf("ERROR: Unable to open file %s\n", temp->arr);
            return FAILURE;
        }

        char word[100];
        while(fscanf(fptr, "%99s", word) != EOF)
        {
            int index;

            //Hashing logic to find the index 
            //word starting with alphabetic character or not
            if(isalpha(word[0]))
            {
                index = tolower(word[0]) - 'a';
            }
            else
            {
                index = 26;
            }

            //search word in Mlist
            Mlist *mtemp = ht[index].link;

            while(mtemp != NULL)
            {
                if(strcmp(mtemp->word, word) == 0)
                {
                    break;
                }
                mtemp = mtemp->link;
            }

            //word does not exist
            if(mtemp == NULL)
            {
                Mlist *newM = (Mlist *)malloc(sizeof(Mlist));

                if(newM == NULL)
                {
                    printf("ERROR: Memory allocation failed for Mlist\n");
                    fclose(fptr);
                    return FAILURE;
                }

                newM->word = malloc(strlen(word) + 1);
                if(newM->word == NULL)
                {
                    free(newM);
                    fclose(fptr);
                    return FAILURE;
                }

                strcpy(newM->word, word);
                newM->fileCount = 1;

                //create first sublist node
                Slist *newS = (Slist *)malloc(sizeof(Slist));

                //check memory allocation success or not
                if(newS == NULL)
                {
                    free(newM->word);
                    free(newM);
                    fclose(fptr);
                    return FAILURE;
                }

                newS->filename = malloc(strlen(temp->arr) + 1);
                //check memory allocation success or not
                if(newS->filename == NULL)
                {
                    free(newM->word);
                    free(newM);
                    free(newS);
                    fclose(fptr);
                    return FAILURE;
                }

                strcpy(newS->filename, temp->arr);

                newS->wordcount = 1;
                newS->link = NULL;

                newM->sublink = newS;

                //insert newM at the beginning of the mainNode list 
                newM->link = ht[index].link;
                ht[index].link = newM;

            }
            //word is already exists in Mlist
            else
            {
                Slist *stemp = mtemp->sublink;

                //search current file in Slist
                while(stemp != NULL)
                {
                    //word is present in existing file or not.
                    if(strcmp(stemp->filename, temp->arr) == 0)
                    {
                        break;
                    }

                    stemp = stemp->link;
                }

                //word is present in existing file
                if(stemp != NULL)
                {
                    //same file
                    stemp->wordcount++;
                }
                //different file
                else
                {
                    Slist *newS = (Slist *)malloc(sizeof(Slist));

                    //check memory allocation success or not
                    if(newS == NULL)
                    {
                        fclose(fptr);
                        return FAILURE;
                    }

                    newS->filename = malloc(strlen(temp->arr) + 1);
                    //check memory allocation success or not
                    if(newS->filename == NULL)
                    {
                        free(newS);
                        fclose(fptr);
                        return FAILURE;
                    }

                    strcpy(newS->filename, temp->arr);
                    newS->wordcount = 1;
                    newS->link = NULL;

                    //Insert Slist node
                    newS->link = mtemp->sublink;
                    mtemp->sublink = newS;

                    //Increment fileCount in Mlist
                    mtemp->fileCount++;
                }
            }    
        }

        printf("Successful : Creation of DATABASE for file : %s\n", temp->arr);
        fclose(fptr);

        temp = temp->link;
    }
    printf("---------------------------------------------------------------------\n");

    return SUCCESS;
}