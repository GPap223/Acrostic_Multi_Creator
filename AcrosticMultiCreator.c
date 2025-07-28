#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define SIZE 3000
#define FALSE 0
#define TRUE 1

typedef struct wList 
{
    char *word;
    int wordLength;
    int uniqLetters;
    int numOfTimes;
    int insertionMode;
    char insertionDate[11];
    char insertionTime[9];
    int used;
    struct wList *next;
    struct wList *previous;
    char *acrosticword;
} wordList;


void HeadList(wordList **head)
{
    *head = NULL;
}

int EmptyListCheck(wordList *head)
{
    return head == NULL;
}

void SortWordList(wordList *head)
{
    if (!head || !head->next) return;

    int swapped;
    wordList *ptr1;
    wordList *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head->next;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->word, ptr1->next->word) > 0) 
            {
                char *temppinak = ptr1->word;
                char *tempAcrosticWord = ptr1->acrosticword;
                int tempLength = ptr1->wordLength;
                int tempUniq = ptr1->uniqLetters;
                int tempTimes = ptr1->numOfTimes;
                int tempMode = ptr1->insertionMode;
                char tempDate[11], tempTime[9];
                strcpy(tempDate, ptr1->insertionDate);
                strcpy(tempTime, ptr1->insertionTime);

                ptr1->word = ptr1->next->word;
                ptr1->acrosticword = ptr1->next->acrosticword;
                ptr1->wordLength = ptr1->next->wordLength;
                ptr1->uniqLetters = ptr1->next->uniqLetters;
                ptr1->numOfTimes = ptr1->next->numOfTimes;
                ptr1->insertionMode = ptr1->next->insertionMode;
                strcpy(ptr1->insertionDate, ptr1->next->insertionDate);
                strcpy(ptr1->insertionTime, ptr1->next->insertionTime);

                ptr1->next->word = temppinak;
                ptr1->next->acrosticword = tempAcrosticWord;
                ptr1->next->wordLength = tempLength;
                ptr1->next->uniqLetters = tempUniq;
                ptr1->next->numOfTimes = tempTimes;
                ptr1->next->insertionMode = tempMode;
                strcpy(ptr1->next->insertionDate, tempDate);
                strcpy(ptr1->next->insertionTime, tempTime);

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
int CountUniqueLetters(char *word)
{
    int grammata[26] = {0};
    int count = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        char ch = toupper((char)word[i]);
        if (ch >= 'A' && ch <= 'Z')
        {
            if (grammata[ch - 'A'] == 0)
            {
                grammata[ch - 'A'] = 1;
                count++;
            }
        }
    }
    return count;
}

int InsertKeyboard(wordList *head, char leji, char input[SIZE])
{
    int j = 7;
    int mhkos = strlen(input);
    wordList *newnode;
    int counter = 0, x = 0, teliko = 0;

    if (input[j - 1] == ' ' && input[j] == ' ')
    {
        printf("ERROR! Two or more spaces detected in the row\n");
        return FALSE;
    }

    for (int i = j; i < mhkos - 1; i++)
    {
        if (input[i] == ' ' && input[i + 1] == ' ')
        {
            printf("ERROR!\nFound two or more consecutive spaces!\n");
            return FALSE;
        }
    }

    for (int i = j+1; i < mhkos; i++)
    {
        if (input[i - 1] == ' ' && ispunct((char)input[i]))
        {
            printf("ERROR!\nFound a space before punctuation at position %d!\n", i - 1);
            return FALSE;
        }
    }

    for (int i = j; i <= mhkos; i++)
    {
        if (isalpha((char)input[i]) || ispunct((char)input[i]) || isdigit((char)input[i]))
        {
            if (counter == 0)
            {
                x = i;
            }
            counter++;
        }

        if ((input[i] == ' ' || input[i] == '\0') && counter > 0)
        {
            int isWord = TRUE;
            teliko = counter;

            if (teliko > 0 && ispunct((char)input[x + teliko - 1]))
            {
                teliko--;
            }

            for (int k = 0; k < teliko; k++)
            {
                if (!isalpha((char)input[x + k]))
                {
                    printf("\nThe letter at %d isn't letter!\n", x + k);
                    isWord = FALSE;
                    break;
                }
            }

            for (int u = 0; u < teliko + 1; u++)
            {
                if (ispunct((char)input[x + u]) && ispunct((char)input[x + u + 1]))
                {
                    printf("\nThe letters at the seats %d and %d aren't letters!", x + u, x + u + 1);
                    isWord = FALSE;
                    break;
                }
            }

            if (!isWord && teliko > 0)
            {
                char *temppinak = (char *)malloc(teliko + 2);
                if (!temppinak)
                {
                    printf("Memory allocation failed!\n");
                    return FALSE;
                }

                for (int k = 0; k < teliko; k++)
                {
                    temppinak[k] = toupper(input[x + k]);
                }
                temppinak[teliko] = '\0';

                printf(" The word %s was discarded\n", temppinak);
                free(temppinak);
            }
            else if (isWord && teliko > 0)
            {
                char *temppinak = (char *)malloc(teliko + 1);
                if (!temppinak)
                {
                    printf("Memory allocation failed!\n");
                    return FALSE;
                }

                for (int k = 0; k < teliko; k++)
                {
                    temppinak[k] = toupper(input[x + k]);
                }
                temppinak[teliko] = '\0';

                wordList *current = head->next;
                int found = FALSE;
                while (current != NULL)
                {
                    if (strcmp(current->word, temppinak) == 0)
                    {
                        current->numOfTimes++;
                        found = TRUE;
                        break;
                    }
                    current = current->next;
                }

                if (!found)
                {
                    newnode = (wordList *)malloc(sizeof(wordList));
                    if (!newnode)
                    {
                        printf("Memory allocation failed!\n");
                        free(temppinak);
                        return FALSE;
                    }

                    newnode->word = temppinak;
                    newnode->acrosticword = malloc(strlen(temppinak) + 1);
                    strcpy(newnode->acrosticword, temppinak);
                    newnode->wordLength = teliko;
                    newnode->uniqLetters = CountUniqueLetters(newnode->word);
                    newnode->numOfTimes = 1;
                    newnode->insertionMode = 1;

                    time_t now = time(NULL);
                    struct tm *t = localtime(&now);
                    strftime(newnode->insertionDate, sizeof(newnode->insertionDate), "%Y-%m-%d", t);
                    strftime(newnode->insertionTime, sizeof(newnode->insertionTime), "%H:%M:%S", t);

                    newnode->next = head->next;
                    newnode->previous = head;
                    if (head->next != NULL)
                        head->next->previous = newnode;
                    head->next = newnode;
                    printf(" The Word %s was Successfully inserted\n", temppinak);
                }
                else
                {
                    free(temppinak);
                }
            }
            counter = 0;
        }
    }

    SortWordList(head);

    return TRUE;
}

int DeleteSelection(wordList *head, char input[])
{
    char pinak1[] = "delete: ";
    int i;

    for (i = 0; i < 8; i++)
    {
        if (pinak1[i] != input[i])
        {
            printf("The letter '%c' is wrong! Please try again! (Your command should start with delete:)\n", input[i]);
            return FALSE;
        }
    }

    wordList *current;
    wordList *temp;

    int mhkos = strlen(input);
    int j = 8;

    while (j < mhkos)
    {
        while (j < mhkos && input[j] == ' ')
         j++; 
        int start = j;
        while (j < mhkos && input[j] != ' ')
            j++;
        int end = j;

        int length = end - start;
        if (length <= 0) continue;

        char *temppinak = (char *)malloc(length + 1);
        if (!temppinak) 
        {
            printf("Memory allocation failed!\n");
            return FALSE;
        }

        for (int k = 0; k < length; k++)
            temppinak[k] = toupper((char)input[start + k]);
        temppinak[length] = '\0';

        int found = FALSE;
        current = head->next;

        while (current != NULL)
        {
            if (strcmp(current->word, temppinak) == 0)
            {
                printf("Word \"%s\" deleted successfully!\n", temppinak);

                if (current->previous != NULL)
                    current->previous->next = current->next;
                if (current->next != NULL)
                    current->next->previous = current->previous;

                free(current->word);
                temp = current;
                current = current->next;
                free(temp);
                found = TRUE;
                break;
            }
            else
            {
                current = current->next;
            }
        }

        if (!found)
            printf("Word \"%s\" not found in list.\n", temppinak);

        free(temppinak);
    }

    return TRUE;
}


int PrintListFwd(wordList *head, int num, char input[])
{
    char pinak1[] = "showfwd:";
    for (int i = 0; i < 8; i++)
    {
        if (pinak1[i] != input[i])
        {
            printf("The letter '%c' is wrong! Please try again! (Your command should start with showfwd:)\n", input[i]);
            return FALSE;
        }
    }

    if (num <= 0)
        return FALSE;

    int count = 0;
    wordList *current = head->next;

    while (current != NULL && count < num)
    {
        printf("%s ", current->word);
        current = current->next;
        count++;
    }
    printf("\n");
    return TRUE;
}

int PrintListRev(wordList *head, int num, char input[])
{
    char pinak1[] = "showrev:";
    for (int i = 0; i < 8; i++)
    {
        if (pinak1[i] != input[i])
        {
            printf("The letter '%c' is wrong! Please try again! (Your command should start with showrev:)\n", input[i]);
            return FALSE;
        }
    }

    if (num <= 0)
        return FALSE;

    int count = 0;
    wordList *current = head;

    while (current->next != NULL)
    {
        current = current->next;
    }

    while (current != head && count < num)
    {
        printf("%s ", current->word);
        current = current->previous;
        count++;
    }
    printf("\n");
    return TRUE;
}

int PrintListWFwd(wordList *head, char input[],int num, char input2[])
{
    char pinak1[] = "findfwd:";
    int mhkos=strlen(input2);
    char temp[mhkos];
    for (int k = 0; k < mhkos; k++)
        {
           temp[k] = toupper((char)input2[k]);
        }
       temp[mhkos+1] = '\0';

    if (num <= 0)
        return FALSE;

    int count = 0;
    wordList *current = head->next;

    while (current != NULL && count < num)
    {
        if (strncmp(current->word, temp, strlen(input2)) == 0)
        {
            printf("%s ", current->word);
            count++;
        }
        current = current->next;
    }
    printf("\n");
    return TRUE;
}

int PrintListWRev(wordList *head, char input[], int num, char input2[]) 
{
    if (num <= 0)
        return FALSE;

    int mhkos = strlen(input2);
    char temp[mhkos + 1];

    for (int k = 0; k < mhkos; k++) 
    {
        temp[k] = toupper((char)input2[k]);
    }
    temp[mhkos] = '\0';

    wordList* current = head;
    while (current->next != NULL)
        current = current->next;

    int count = 0;
    while (current != head && count < num)
    {
        char WordDel[SIZE];
        for (int i = 0; current->word[i] && i < SIZE - 1; i++)
        {
            WordDel[i] = toupper((char)current->word[i]);
            WordDel[i + 1] = '\0';
        }

        if (strncmp(WordDel, temp, mhkos) == 0)
        {
            printf("%s ", current->word);
            count++;
        }
        current = current->previous;
    }

    printf("\n");
    return TRUE;
}

void AkrostixidaLushEasy(wordList *head, char lejh[])
{
    int mhkos = strlen(lejh);
    wordList *reset = head->next;
    while (reset != NULL)
    {
        reset->used = 0;
        reset = reset->next;
    }

    for (int i = 0; i < mhkos; i++)
    {
        char c = lejh[i];
        wordList *current = head->next;

        wordList *bestWord = NULL;
        int minLength = 3000;
        int maxNumOfTimes = -1;

        while (current != NULL)
        {
            if (toupper((char)current->word[0]) == toupper((char)c) && current->used == 0)
            {
                if (current->wordLength < minLength)
                {
                    minLength = current->wordLength;
                    maxNumOfTimes = current->numOfTimes;
                    bestWord = current;
                }
                else if (current->wordLength == minLength && current->numOfTimes > maxNumOfTimes)
                {
                    maxNumOfTimes = current->numOfTimes;
                    bestWord = current;
                }
            }
            current = current->next;
        }

        if (bestWord != NULL)
        {
            bestWord->used = 1;
            int mhkos1 = strlen(bestWord->word);

            for (int j = 0; j < mhkos1; j++)
            {
                printf("%c", bestWord->word[j]);
                if (j < mhkos1 - 1) printf(" ");
            }
            printf("\n\n");
        }
        else
        {
            printf("%c (Word not found)\n\n", toupper(c));
        }
    }
    wordList *current = head->next;
    while (current != NULL)
    {
        current->used = 0;
        current = current->next;
    }
}

int AkrostixidaPrintEasy(wordList *head, char lejh[], char input[], char ***hiddenLetters)
{
    int mhkos2 = strlen(lejh);
    wordList *reset = head->next;
    while (reset != NULL) 
    {
        reset->used = 0;
        reset = reset->next;
    }
    int *lettercounter = malloc(sizeof(int) * mhkos2);
    char **hiddenPerWord = malloc(sizeof(char*) * mhkos2);
    if (!lettercounter || !hiddenPerWord) 
    {
        printf("Memory allocation failed\n");
        free(lettercounter);
        free(hiddenPerWord);
        return FALSE;
    }
    for (int i = 0; i < mhkos2; i++) 
    {
        hiddenPerWord[i] = NULL; 
    }
    for (int i = 0; i < mhkos2; i++) 
    {
        char c = lejh[i];
        wordList *current = head->next;

        wordList *bestWord = NULL;
        int minLength = 3000;
        int maxNumOfTimes = -1;

        while (current != NULL) 
        {
            if (toupper((char)current->word[0]) == toupper((char)c) && current->used == 0) 
            {
                if (current->wordLength < minLength) 
                {
                    minLength = current->wordLength;
                    maxNumOfTimes = current->numOfTimes;
                    bestWord = current;
                } else if (current->wordLength == minLength && current->numOfTimes > maxNumOfTimes) 
                {
                    maxNumOfTimes = current->numOfTimes;
                    bestWord = current;
                }
            }
            current = current->next;
        }

        if (bestWord != NULL) 
        {
            bestWord->used = 1;

            int Whide;
            if (bestWord->wordLength <= 10) 
            {
                Whide = rand() % 2 + 1;
            } 
            else 
            {
                Whide = rand() % 4 + 1;
            }

            lettercounter[i] = Whide;

            hiddenPerWord[i] = malloc(sizeof(char) * (Whide + 1));
            if (!hiddenPerWord[i]) 
            {
                printf("Memory allocation failed\n");
                for (int j = 0; j <= i; j++) 
                free(hiddenPerWord[j]);
                free(hiddenPerWord);
                free(lettercounter);
                return FALSE;
            }

            for (int j = 0; j < Whide; j++) 
            {
                hiddenPerWord[i][j] = 'A' + rand() % 26;
            }
            hiddenPerWord[i][Whide] = '\0';
        } 
        else 
        {
            lettercounter[i] = 0;
        }
    }
    reset = head->next;
    while (reset != NULL) 
    {
        reset->used = 0;
        reset = reset->next;
    }
    for (int i = 0; i < mhkos2; i++) 
    {
        char c = lejh[i];
        wordList *current = head->next;

        wordList *bestWord = NULL;
        int minLength = 3000;
        int maxNumOfTimes = -1;

        while (current != NULL) 
        {
            if (toupper((char)current->word[0]) == toupper((char)c) && current->used == 0) 
            {
                if (current->wordLength < minLength) {
                    minLength = current->wordLength;
                    maxNumOfTimes = current->numOfTimes;
                    bestWord = current;
                } 
                else if (current->wordLength == minLength && current->numOfTimes > maxNumOfTimes) 
                {
                    maxNumOfTimes = current->numOfTimes;
                    bestWord = current;
                }
            }
            current = current->next;
        }

        if (bestWord != NULL) 
        {
            bestWord->used = 1;
            int Whide = lettercounter[i];

            strcpy(bestWord->acrosticword, bestWord->word);

            for (int j = 0; j < bestWord->wordLength; j++) 
            {
                int hidden = 0;
                for (int h = 0; h < Whide; h++)
                 {
                    if (toupper((char)bestWord->word[j]) == hiddenPerWord[i][h]) 
                    {
                        hidden = 1;
                        break;
                    }
                }
                if (hidden) 
                {
                    bestWord->acrosticword[j] = '_';
                } 
                else 
                {
                    bestWord->acrosticword[j] = bestWord->word[j];
                }
            }

            for (int j = 0; j < bestWord->wordLength; j++) 
            {
                printf("%c ", bestWord->acrosticword[j]);
            }
            printf("\n\n");

        } else {
            printf("%c (Word not found)\n\n", toupper((char)c));
        }
    }

    free(lettercounter);

    *hiddenLetters = hiddenPerWord;

    return TRUE;
}


void AkrostixidaLushHard(wordList *head, char lejh[])
{
    int mhkos = strlen(lejh);
    wordList *reset = head->next;
    while (reset != NULL)
    {
        reset->used = 0;
        reset = reset->next;
    }

    for (int i = 0; i < mhkos; i++)
    {
        char c = lejh[i];
        wordList *current = head->next;

        wordList *bestWord = NULL;
        int maxLength = -1;
        int minNumOfTimes = 3000;

        while (current != NULL)
        {
            if (toupper((char)current->word[0]) == toupper((char)c) && current->used == 0)
            {
                if (current->wordLength > maxLength)
                {
                    maxLength = current->wordLength;
                    minNumOfTimes = current->numOfTimes;
                    bestWord = current;
                }
                else if (current->wordLength == maxLength && current->numOfTimes < minNumOfTimes)
                {
                    minNumOfTimes = current->numOfTimes;
                    bestWord = current;
                }
            }
            current = current->next;
        }

        if (bestWord != NULL)
        {
            bestWord->used = 1;  
            for (int j = 0; j < bestWord->wordLength; j++)
            {
                printf("%c", bestWord->word[j]);
                if (j < bestWord->wordLength - 1) printf(" ");
            }
        }
        else
        {
            printf("%c (Word not found)", toupper(c));
        }
        printf("\n\n");
    }
    wordList *current = head->next;
    while (current != NULL)
    {
        current->used = 0;
        current = current->next;
    }
}

int AkrostixidaPrintHard(wordList *head, char lejh[], char input[], char ***hiddenLetters)
{
    int mhkos2 = strlen(lejh);

    wordList *cur = head->next;
    while (cur != NULL) 
    {
        strcpy(cur->acrosticword, cur->word);
        cur = cur->next;
    }

    wordList *reset = head->next;
    while (reset != NULL) 
    {
        reset->used = 0;
        reset = reset->next;
    }

    int *lettercounter = malloc(sizeof(int) * mhkos2);
    if (!lettercounter) 
    {
        printf("Memory allocation failed\n");
        return FALSE;
    }

    for (int i = 0; i < mhkos2; i++) 
    {
        char c = lejh[i];
        wordList *current = head->next;
        wordList *bestWord = NULL;
        int maxLength = -1;
        int minNumOfTimes = 3000;

        while (current != NULL) 
        {
            if (toupper((char)current->word[0]) == toupper((char)c) && current->used == 0) 
            {
                if (current->wordLength > maxLength ||
                    (current->wordLength == maxLength && current->numOfTimes < minNumOfTimes)) 
                    {
                    maxLength = current->wordLength;
                    minNumOfTimes = current->numOfTimes;
                    bestWord = current;
                }
            }
            current = current->next;
        }

        if (bestWord != NULL) 
        {
            bestWord->used = 1;
            lettercounter[i] = (bestWord->wordLength <= 10) ? rand() % 4 + 2 : rand() % 8 + 4;
        } 
        else 
        {
            lettercounter[i] = 0;
        }
    }
    char **allHidden = malloc(sizeof(char *) * mhkos2);
    if (!allHidden) 
    {
        printf("Memory allocation failed\n");
        free(lettercounter);
        return FALSE;
    }

    reset = head->next;
    while (reset != NULL) 
    {
        reset->used = 0;
        reset = reset->next;
    }

    for (int i = 0; i < mhkos2; i++) 
    {
        char c = lejh[i];
        wordList *current = head->next;
        wordList *bestWord = NULL;
        int maxLength = -1;
        int minNumOfTimes = 3000;

        while (current != NULL) 
        {
            if (toupper((char)current->word[0]) == toupper((char)c) && current->used == 0) 
            {
                if (current->wordLength > maxLength ||
                    (current->wordLength == maxLength && current->numOfTimes < minNumOfTimes)) 
                {
                    maxLength = current->wordLength;
                    minNumOfTimes = current->numOfTimes;
                    bestWord = current;
                }
            }
            current = current->next;
        }

        if (bestWord != NULL) 
        {
            bestWord->used = 1;
            int Whide = lettercounter[i];

            allHidden[i] = malloc(sizeof(char) * (Whide + 1));
            if (!allHidden[i]) 
            {
                printf("Memory allocation failed\n");
                for (int k = 0; k < i; k++) 
                free(allHidden[k]);
                free(allHidden);
                free(lettercounter);
                return FALSE;
            }

            for (int j = 0; j < Whide; j++) 
            {
                allHidden[i][j] = 'A' + rand() % 26;
            }
            allHidden[i][Whide] = '\0';

            strcpy(bestWord->acrosticword, bestWord->word);

            for (int j = 0; j < bestWord->wordLength; j++) 
            {
                int hidden = 0;
                for (int h = 0; h < Whide; h++) 
                {
                    if (toupper((char)bestWord->word[j]) == allHidden[i][h]) 
                    {
                        hidden = 1;
                        break;
                    }
                }
                bestWord->acrosticword[j] = hidden ? '_' : bestWord->word[j];
            }

            for (int j = 0; j < bestWord->wordLength; j++)
             {
                printf("%c ", bestWord->acrosticword[j]);
            }
            printf("\n");

        } else 
        {
            printf("%c (Word not found)\n", toupper((char)c));
        }
        printf("\n");
    }

    free(lettercounter);
    *hiddenLetters = allHidden;

    return TRUE;
}


void InsertFromFile(wordList *head, char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Could not open file: %s\n", filename);
        return;
    }

    char buffer[SIZE];
    while (fscanf(fp, "%s", buffer) != EOF)
    {
        int valid = 1;
        int len = strlen(buffer);

        for (int i = 0; i < len; i++)
        {
            if (!isalpha((char)buffer[i]))
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
        {
            printf("'%s' is not a valid word. Rejected.\n", buffer);
            continue;
        }

        for (int i = 0; i < len; i++)
        {
            buffer[i] = toupper((char)buffer[i]);
        }

        wordList *current = head->next;
        int found = 0;
        while (current != NULL) 
        {
            if (strcmp(current->word, buffer) == 0)
            {
                current->numOfTimes++;
                found = 1;
                printf("'%s' already in list. Incremented numOfTimes.\n", buffer);
                break;
            }
            current = current->next;
        }

        if (!found)
        {
            wordList *newnode = (wordList *)malloc(sizeof(wordList));
            if (!newnode)
            {
                printf("Memory allocation failed for '%s'\n", buffer);
                continue;
            }
            newnode->word = strdup(buffer);
            newnode->acrosticword = strdup(buffer);
            newnode->wordLength = strlen(buffer);
            newnode->uniqLetters = CountUniqueLetters(buffer);
            newnode->numOfTimes = 1;
            newnode->insertionMode = 0;

            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            strftime(newnode->insertionDate, sizeof(newnode->insertionDate), "%Y-%m-%d", t);
            strftime(newnode->insertionTime, sizeof(newnode->insertionTime), "%H:%M:%S", t);

            newnode->next = head->next;
            newnode->previous = head;
            if (head->next != NULL)
                head->next->previous = newnode;
            head->next = newnode;

            printf("Inserted '%s' from file.\n", buffer);
        }
    }

    fclose(fp);
    SortWordList(head);
}
void SaveAcrosticToFile(wordList *head, char *filename, char *level, char *lejh, char **hiddenLetters)
{
    char fullFile[SIZE];
    strcpy(fullFile, filename);
    strcat(fullFile, ".txt");

    FILE *fp = fopen(fullFile, "w");
    if (!fp)
    {
        printf("Could not create file: %s\n", fullFile);
        return;
    }

    fprintf(fp, "Acrostic (%s mode):\n\n", level);

    int mhkos = strlen(lejh);

    wordList *reset = head->next;
    while (reset != NULL) 
    {
        reset->used = 0;
        reset = reset->next;
    }

    for (int i = 0; i < mhkos; i++) 
    {
        char c = lejh[i];
        wordList *current = head->next;
        wordList *bestWord = NULL;

        while (current != NULL) 
        {
            if (toupper(current->word[0]) == toupper(c) && current->used == 0)
            {
                bestWord = current;
                break;
            }
            current = current->next;
        }

        if (bestWord != NULL)
        {
            bestWord->used = 1;

            char *hiddenForWord = hiddenLetters[i]; 

            char templejh[SIZE];
            strcpy(templejh, bestWord->word);

            for (int j = 0; j < bestWord->wordLength; j++) 
            {
                for (int k = 0; hiddenForWord[k] != '\0'; k++) 
                {
                    if (toupper(bestWord->word[j]) == toupper(hiddenForWord[k])) 
                    {
                        templejh[j] = '_';
                        break;
                    }
                }
            }

            for (int j = 0; j < (int)strlen(templejh); j++) 
            {
                fprintf(fp, "%c", templejh[j]);
                if (j < (int)strlen(templejh) - 1)
                    fprintf(fp, " ");
            }
            fprintf(fp, "\n");
        } 
        else
        {
            fprintf(fp, "%c (Word not found)\n", toupper(c));
        }
    }

    fprintf(fp, "\nSolution:\n");

for (int i = 0; i < mhkos; i++) {
    char c = lejh[i];
    wordList *cur = head->next;
    int found = 0;

    while (cur != NULL) {
        if (toupper(cur->word[0]) == toupper(c) && cur->used == 1) {
            found = 1;  
            for (int j = 0; j < (int)strlen(cur->word); j++) {
                fprintf(fp, "%c", cur->word[j]);
                if (j < (int)strlen(cur->word) - 1) {
                    fprintf(fp, " ");
                }
            }
            fprintf(fp, "\n"); 
            break; 
        }
        cur = cur->next;
    }

    if (!found) {
        fprintf(fp, "%c (Word not found)\n", toupper(c));
    }
}

fclose(fp);
}

int extractNumber(char *input, int firstnum) 
{
    int number = 0;
    char c;
    for (int i = firstnum; (c = input[i]) != '\0'; i++) 
    {
        if (c == ' ')
         {
            continue;
        } else if (c >= '0' && c <= '9') 
        {
            number = number * 10 + (c - '0');
        } 
        else 
        {
            break;
        }
    }
    return number;
}
int main()
{
    srand(time(NULL));

    wordList *head = (wordList *)malloc(sizeof(wordList));
    if (!head) {
        printf("Memory allocation failed for head node.\n");
        return 1;
    }
    head->next = NULL;
    head->previous = NULL;
    head->word = NULL;

    char input[SIZE];
    char pinak[] = "insert: ";
    char lastLejh[SIZE] = "";  
    char lastLevel[SIZE] = "";  
    char **hiddenLetters = NULL;

    printf("╔══════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                「 ✦ MENU✦ 」                            ║  \n");
    printf("║----------------------------------------------------------------------║\n");
    printf("║   .Options:                                                          ║\n");
    printf("║   -Insert: Command -> insert: word1, word2 or insert: word1 word2    ║\n");
    printf("║   -Insertfile: Command -> load: filename(from choices                ║\n");
    printf("║   -Files Choices:Sports,Cars,History,Geography,Cooking               ║\n");
    printf("║   -Delete: Command -> delete: word1 word2                            ║\n");
    printf("║   -Showfwd: Command -> showfwd: (number)                             ║\n");
    printf("║   -Showrev: Command -> showrev: (number)                             ║\n");
    printf("║   -Findfwd: Command -> findfwd: (word or letter) (number)            ║\n");
    printf("║   -Findrev: Command -> findrev: (word or letter) (number)            ║\n");
    printf("║   -Create: Command -> create: (word or letter) (easy/hard)           ║\n");
    printf("║   -Savefile: Command -> save: filename                               ║\n");
    printf("║   -Exit: Command -> exit                                             ║\n");
    printf("║----------------------------------------------------------------------║\n");
    printf("╚══════════════════════════════════════════════════════════════════════╝\n");

    while (1)
    {
        printf("Command> ");
        if (!fgets(input, SIZE, stdin)) 
        {
            printf("Input error.\n");
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0)
            break;

        else if (strncmp(input, pinak, strlen(pinak)) == 0) 
        {
            if (!InsertKeyboard(head, '\0', input))
                printf("PROBLEM DETECTED. TRY AGAIN!!\n");
        }

        else if (strncmp(input, "load:", 5) == 0) 
        {
            char filename[SIZE];
            char *fStart = input + 5;
            while (*fStart == ' ') fStart++;
            strncpy(filename, fStart, SIZE - 1);
            filename[SIZE - 1] = '\0';
            strcat(filename, ".txt");
            InsertFromFile(head, filename);
        }

        else if (strncmp(input, "delete:", 7) == 0) 
        {
            DeleteSelection(head, input);
        }

        else if (strncmp(input, "showfwd:", 8) == 0) 
        {
            int number = extractNumber(input, 8);
            if (number <= 0)
                printf("Invalid number for showfwd. Provide a positive number.\n");
            else
                PrintListFwd(head, number, input);
        }

        else if (strncmp(input, "showrev:", 8) == 0) 
        {
            int number = extractNumber(input, 8);
            if (number <= 0)
                printf("Invalid number for showrev. Provide a positive number.\n");
            else
                PrintListRev(head, number, input);
        }

        else if (strncmp(input, "findfwd:", 8) == 0 || strncmp(input, "findrev:", 8) == 0)
        {
            int isRev = strncmp(input, "findrev:", 8) == 0;
            int i = 8;
            while (input[i] == ' ') i++;

            char input2[SIZE] = {0};
            char *inputStart = &input[i];
            while (*inputStart == ' ') 
                inputStart++;
            strncpy(input2, inputStart, SIZE - 1);
            input2[SIZE - 1] = '\0';

            char *spacePtr = strchr(input2, ' ');
            if (!spacePtr) {
                printf("Invalid format. Use: findfwd: <word/letter> <number>\n");
                continue;
            }

            *spacePtr = '\0';
            char *numberPart = spacePtr + 1;
            while (*numberPart == ' ') numberPart++;

            int number = atoi(numberPart);
            if (number <= 0) {
                printf("Invalid number. Must be a positive integer.\n");
                continue;
            }

            if (strlen(input2) == 0) {
                printf("Invalid search term. Please provide a word or letter.\n");
                continue;
            }

            if (isRev)
                PrintListWRev(head, input, number, input2);
            else
                PrintListWFwd(head, input, number, input2);
        }

        else if (strncmp(input, "create:", 7) == 0)
        {
            int i = 7;
            while (input[i] == ' ') i++;

            char word[SIZE];
            char *wordStart = &input[i];
            while (*wordStart == ' ') wordStart++;
            strncpy(word, wordStart, SIZE - 1);
            word[SIZE - 1] = '\0';
            char *spaceInWord = strchr(word, ' ');
            if (spaceInWord) *spaceInWord = '\0';

            while (input[i] != ' ' && input[i] != '\0') i++;
            while (input[i] == ' ') i++;

            int validWord = 1;
            for (int j = 0; j < strlen(word); j++)
            {
                if (!isalpha((unsigned char)word[j]))
                {
                    printf("Invalid choice!! The word has to contain only letters!\n");
                    validWord = 0;
                    break;
                }
            }
            if (!validWord) continue;

            if (strncmp(&input[i], "easy", 4) == 0)
            {
                strcpy(lastLejh, word);
                strcpy(lastLevel, "easy");

                if (hiddenLetters)
                {
                    for (int k = 0; k < strlen(lastLejh); k++)
                        free(hiddenLetters[k]);
                    free(hiddenLetters);
                    hiddenLetters = NULL;
                }

                if (AkrostixidaPrintEasy(head, word, input, &hiddenLetters))
                {
                    printf("Here is the solution:\n");
                    AkrostixidaLushEasy(head, word);
                }
            }
            else if (strncmp(&input[i], "hard", 4) == 0)
            {
                strcpy(lastLejh, word);
                strcpy(lastLevel, "hard");

                if (hiddenLetters)
                {
                    for (int k = 0; k < strlen(lastLejh); k++)
                        free(hiddenLetters[k]);
                    free(hiddenLetters);
                    hiddenLetters = NULL;
                }

                if (AkrostixidaPrintHard(head, word, input, &hiddenLetters))
                {
                    printf("Here is the solution:\n");
                    AkrostixidaLushHard(head, word);
                }
            }
            else
            {
                printf("Invalid difficulty level. Use 'easy' or 'hard'.\n");
            }
        }

        else if (strncmp(input, "save:", 5) == 0)
        {
            if (strlen(lastLejh) == 0 || strlen(lastLevel) == 0)
            {
                printf("No acrostic to save. Use 'create:' first.\n");
                continue;
            }

            char filename[SIZE];
            char *saveStart = input + 5;
            while (*saveStart == ' ') saveStart++;
            strncpy(filename, saveStart, SIZE - 1);
            filename[SIZE - 1] = '\0';

            SaveAcrosticToFile(head, filename, lastLevel, lastLejh, hiddenLetters);
        }

        else
        {
            printf("Invalid command. Must start with one of the listed keywords.\n");
        }
    }

    printf("\nFinal Word List:\n");
    wordList *current = head->next;
    while (current)
    {
        printf("Word: %s | Length: %d | Unique: %d | Times: %d | Date: %s | Time: %s\n",
               current->word, current->wordLength, current->uniqLetters,
               current->numOfTimes, current->insertionDate, current->insertionTime);
        current = current->next;
    }

    current = head;
    while (current)
    {
        wordList *temp = current;
        current = current->next;
        if (temp->word) free(temp->word);
        free(temp);
    }

    if (hiddenLetters)
    {
        for (int i = 0; i < strlen(lastLejh); i++)
        {
            free(hiddenLetters[i]);
        }
        free(hiddenLetters);
    }

    return 0;
}
