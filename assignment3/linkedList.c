/* Author: Francis C. Dailig
 * Date: 4/25/2017
 */
#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	// FIXME: you must write this
	assert(list != 0);

	list->frontSentinel = (struct Link*)malloc(sizeof(struct Link));
	assert(list->frontSentinel != 0);

	list->backSentinel = (struct Link*)malloc(sizeof(struct Link));
	assert(list->backSentinel != 0);

	list->frontSentinel->next = list->backSentinel;
	list->frontSentinel->prev = 0;

	list->backSentinel->next = 0;
	list->backSentinel->prev = list->frontSentinel;

	list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(link != 0);

	/* allocate memory for a new link */
	struct Link *newLink = (struct Link*)malloc(sizeof(struct Link));
	assert(newLink != 0);

	newLink->value = value;
	/* have newLink next point to link */
	newLink->next = link;
	/* have newLink prev point to link previous */
	newLink->prev = link->prev;

	/* update link prev to point to newLink */
	link->prev = newLink;

	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(link != 0);

	/* have the previous link point to Link's next link */
	link->prev->next = link->next;

	/* have the next link point to Link's previous link */
	link->next->prev = link->prev;

	free(link);
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);

	/* allocate memory for a new link */
	struct Link *newLink = (struct Link*)malloc(sizeof(struct Link));
	assert(newLink != 0);

	newLink->value = value;

	newLink->next = list->frontSentinel->next;
	newLink->prev = list->frontSentinel;

	list->frontSentinel->next->prev = newLink;
	list->frontSentinel->next = newLink;
	list->size++;
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);

	/* allocate memory for a new link */
	struct Link *newLink = (struct Link*)malloc(sizeof(struct Link));
	assert(newLink != 0);

	newLink->value = value;
	newLink->next = list->backSentinel;
	newLink->prev = list->backSentinel->prev;

	list->backSentinel->prev->next = newLink;
	list->backSentinel->prev = newLink;
	list->size++;
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!linkedListIsEmpty(list));

	return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!linkedListIsEmpty(list));

	return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);

	/* create a temp variable to hold the link to be deleted */
	struct Link *tmp = list->frontSentinel->next;

	list->frontSentinel->next = tmp->next;
	tmp->next->prev = tmp->prev;

	free(tmp);
	list->size--;

}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);

	/* create a tmp variable to hold the link to be deleted */
	struct Link *tmp = list->backSentinel->prev;

	list->backSentinel->prev = tmp->prev;
	tmp->prev->next = list->backSentinel;

	free(tmp);
	list->size--;
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	// FIXME: you must write this
	if(list->frontSentinel->next == list->backSentinel){
		return 1;
	}else{ return 0; }
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!linkedListIsEmpty(list));

	/* Create temporary link pointer variable */
	struct Link *tmp = list->frontSentinel->next;

	while(tmp != list->backSentinel){
		printf("%d ", tmp->value);
		tmp = tmp->next;
	}

	printf("\n");

}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);

	/* Add link to the end(back) of the bag */
	linkedListAddBack(list, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(!linkedListIsEmpty(list));

	/* Create a temporary link variable */
	struct Link *tmp = list->frontSentinel->next;

	/* Create variable to hold true or false */
	int contains = 0;

	while(tmp != list->backSentinel){
		if(tmp->value == value){
			contains = 1;
		}
		tmp = tmp->next;
	}

	return contains;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != 0);

	/* create a temporary Link variable */
	struct Link *delete;

	if(linkedListContains(list, value)){
		/* iterate thought the entire list to find link with value */
		struct Link *tmp = list->frontSentinel->next;
		while(tmp != list->backSentinel){
			if(tmp->value == value){
				delete = tmp;
			}
			tmp = tmp->next;
		}
		delete->prev->next = delete->next;
		delete->next->prev = delete->prev;
		list->size--;
		free(delete);
	}
}
