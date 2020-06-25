/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Francis C. Dailig
 * Date: 6/2/2018
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // FIXME: implement

	printf("Calling hash map cleanup\n");
	assert(map != 0);

	/* Create a variable to hold links in each bucket */
	struct HashLink *tmpLink;

	/* Iterate through each bucket */
	printf("map size is: %d\n", map->size);

	if(map->size > 0){
		printf("iterating through bucket, size is greater than 0\n");
		for(int i = 0; i < map->capacity; i++){
			tmpLink = map->table[i];

			if(tmpLink != NULL){
				while(tmpLink != NULL){
					HashLink *deleteMe = tmpLink;
					tmpLink =tmpLink->next;
					hashLinkDelete(deleteMe);
				}
			}

		}

	}
	free(map->table);

}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // FIXME: implement
	assert(map != 0);
	assert(key != 0);

	/* get the hash to determine which bucket the key is placed */
	int index = HASH_FUNCTION(key) % map->capacity;
	if(index < 0){ index += map->capacity; }


	/* create a variable to hold the links in each bucket */
	struct HashLink *tmpLink = map->table[index];


	/* iterate through each link in the bucket until key is found or end is reached */
	while(tmpLink != 0 ){
		if(strcmp(tmpLink->key, key) == 0){
			return &(tmpLink->value);
		}else{
			tmpLink = tmpLink->next;
		}
	}

	/* return 0 if key not found */
	return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    // FIXME: implement
	assert(map != 0);

	struct HashMap *oldMap = map;

	map = hashMapNew(capacity);

	/* iterate through all the old buckets in the original table */
	for(int i = 0; i < oldMap->capacity; i++){
		struct HashLink *tmpLink = oldMap->table[i];
		while(tmpLink != NULL){
			hashMapPut(map, tmpLink->key, tmpLink->value);
			tmpLink = tmpLink->next;
		}
	}

	hashMapCleanUp(oldMap);
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // FIXME: implement
	assert(map != 0);
	assert(key != 0);


	/* calculate which bucket to place the value in */
	int index = HASH_FUNCTION(key) % map->capacity;
	if(index < 0){ index += map->capacity; }

	/* check to see if MAX_TABLE_LOAD is reached */
	if(hashMapTableLoad(map) >= MAX_TABLE_LOAD){ resizeTable(map, 2 * map->capacity); }


	/* if the bucket is empty add the link to the bucket */
	if(map->table[index] == 0){
		map->table[index] = hashLinkNew(key, value, 0);
		map->size++;

	/* else find the last link in the bucket */
	}else{
		struct HashLink *link = map->table[index];

		while(link->next != 0 && strcmp(link->key, key) != 0){
			link = link->next;
		}

		if(strcmp(link->key, key) == 0){
			link->value = value;
		}else{
			link->next = hashLinkNew(key, value, 0);
			map->size++;
		}
	}

}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
	assert(map != 0);
	assert(key != 0);

	printf("Removing key: %s\n", key);
	hashMapPrint(map);

	/* variable to hold the index of the bucket */
	int index = HASH_FUNCTION(key) % map->capacity;
	if(index < 0){ index += map->capacity; }

	/* tmp variable to hold the value of links in the bucket */
	HashLink *tmpLink = map->table[index];

	if(tmpLink == 0){
		printf("Attempting to remove a key that does not exist.\n");
		return;
	}else if(strcmp(tmpLink->key, key) == 0){
		map->table[index] = tmpLink->next;
		hashLinkDelete(tmpLink);
		map->size--;
	}else{
		while(strcmp(tmpLink->key, key) != 0 && tmpLink != 0){
			tmpLink = tmpLink->next;
		}

		if(strcmp(tmpLink->next->key, key) == 0){
			HashLink *deleteMe = tmpLink;
			tmpLink->next = deleteMe->next;
			hashLinkDelete(deleteMe);
			map->size--;
		}
	}

	printf("After removal\n");
	printf("Size of map: %d\n", map->size);
	hashMapPrint(map);
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // FIXME: implement
	/* variable to hold index of the bucket */
	int index = HASH_FUNCTION(key) % map->capacity;
	if(index < 0){ index += map->capacity; }


	/* temp link to hold the link in the bucket */
	HashLink *tmpLink = map->table[index];
	hashMapPrint(map);

	while(tmpLink != 0){
		if(strcmp(tmpLink->key, key) == 0){
			return 1;
		}
		tmpLink = tmpLink->next;
	}

	/* if while loop exits without finding the key, it does not exit, return 0 */
	return 0;

}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // FIXME: implement
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // FIXME: implement
	return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // FIXME: implement
	int count = 0;

	for(int i = 0; i < map->capacity; i++){
		if(map->table[i] == 0){ count++; }
	}

	return count;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
	float size = (float)map->size;

	float returnMe = size / map->capacity;

    return returnMe;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}
