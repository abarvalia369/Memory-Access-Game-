#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY 5
#define MAX_WORD_LENGTH 20

int numberOfWords;
int mode; // input
char words[MEMORY][MAX_WORD_LENGTH]; // store input words

// array to memorize
struct DoublyLinkedList
{
    char *word;
    struct DoublyLinkedList *next;
    struct DoublyLinkedList *prev;
};

struct DoublyLinkedList *head = NULL; // points towards the start of the array i.e leftmost
struct DoublyLinkedList *tail = NULL; // points towards the end of the array i.e rightmost

void addWordToMemory(char *word, int mode)
{
    // create a new node
    struct DoublyLinkedList *newNode = (struct DoublyLinkedList *)malloc(sizeof(struct DoublyLinkedList));
    newNode->word = strdup(word);
    newNode->next = NULL;
    newNode->prev = NULL;

    // check if the word is already in memory
    struct DoublyLinkedList *current = head;
    while (current != NULL)
    {
        if (strcmp(current->word, word) == 0)
        {
            // bring it to the start
            if (current == head)
                return; // already at the start

            current->prev->next = current->next;
            if (current->next != NULL)
                current->next->prev = current->prev;

            current->next = head;
            current->prev = NULL;
            head->prev = current;
            head = current;

            return;
        }
        current = current->next;
    }

    // if the word does not exist and does not overflow memory, add it to start
    if (numberOfWords < MEMORY)
    {
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        numberOfWords++;
    }
    else
    {
        // if overflows memory, remove the end node and add a new word to start
        struct DoublyLinkedList *temp = tail;
        tail = tail->prev;
        tail->next = NULL;

        free(temp->word);
        free(temp);
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void printMemoryArray()
{
    struct DoublyLinkedList *current = head;
    while (current != NULL)
    {
        printf("[%s] ", current->word);
        current = current->next;
    }
    printf("\n");
}

int main()
{
    printf("Enter mode (1 or 2): ");
    scanf("%d", &mode);

    printf("Enter number of words to be stored in the array: ");
    scanf("%d", &numberOfWords);

    for (int i = 0; i < numberOfWords; i++)
    {
        printf("Enter word %d: ", i + 1);
        scanf("%s", words[i]);
        addWordToMemory(words[i], mode);
        printMemoryArray();
    }

    return 0;
}
