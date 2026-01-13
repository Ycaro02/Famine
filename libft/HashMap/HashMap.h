/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HashMap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:35:19 by nfour             #+#    #+#             */
/*   Updated: 2024/06/17 17:28:02 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HASHMAP_H
#define HEADER_HASHMAP_H

#include "../libft.h"
#include "../tinycthread.h"

typedef mtx_t Mutex;

/**
 *	- Hash Map
 *	- A hash map is a data structure that implements an associative array abstract data type, a structure that can map keys to values.
 *	- A hash map uses a hash function to compute an index into an array of buckets or slots, from which the desired value can be found.
 *	- Ideally, the hash function will assign each key to a unique bucket, but most hash table designs employ an imperfect hash function, 
		which might cause hash collisions where the hash function generates the same index for more than one key.
 *	- In a well-dimensioned hash table, the average cost (number of instructions) for each lookup is independent of the number of elements stored in the table.
 *	- Many hash table designs also allow arbitrary insertions and deletions of key-value pairs, at (amortized) constant average cost per operation.
 *	- In many situations, hash tables turn out to be more efficient than search trees or any other table lookup structure.
 *	- For this implementation, we will use a simple hash function to hash the block position (x,y,z) to a unique key.
 *	- The hash map is implemented with a list of t_list pointers, each t_list pointer is the head of a list of HashMap_entry
 **	- Main features:
 *		- store any type of data (void*), the user will have to handle the data type and give a free function to free the data.
 *		- get the length of the map.
 *		- set the value associated with the key (x,y,z).
 *		- get the value associated with the key (x,y,z).
 *		- destroy the map and free all the memory.
 *		- create and initialize an iterator for the hash map.
 *		- move to the next entry in the hash map.
 *		- expand the given hashmap capacity when needed.
 *		- update the entry if the key already exists.
 *		- remove the entry associated with the key.
 *		- protect against multiple access with a mutex.
 **	- Note:
 * 	- API design from https://benhoyt.com/writings/hash-table-in-c/
 *  - t_list structure definition from ../libft.h
 *		typedef struct s_list {
 *			void			*content;
 *			struct s_list	*next;
 *		} t_list;
 *  - Content must be an allocated pointer on the heap, free will be called on each node with the free_obj function

 * Add Mutex to make it thread safe
*/

/* Block position structure */
typedef struct PACKED_STRUCT s_block_pos {
	s32			x;
	s32			y;
	s32			z;
} BlockPos;

/* HashMap entry key + value + original data */
typedef struct s_hashmap_entry {
	BlockPos	origin_data;	/* Original data (block pos) */
	u64			key;			/* Key of the entry */
	void		*value;			/* Value linked */
} HashMap_entry;

/* HashMap structure */
typedef struct s_hashmap {
	t_list 		**entries;				/* array of t_list double ptr, head of each HashMap_entry list*/
	size_t		capacity;				/* Capacity of the array ( entry size, number of list ptr )*/
	size_t		size;					/* Number of current item stored  */
	void		(*free_obj)(void *obj); /* Free function to free the given obj */
	Mutex		mtx;					/* Mutex to protect data */
	// u64			(*hash)(); /* Hash function to hash the given obj/data to a key */
	// s8			(*obj_cmp)(void *a, void *b); /* Scmp obj function  */
} HashMap;

/* HashMap iterator struct */
typedef struct s_hashmap_it {
	u64			key;			/* Key of the current node */
	void 		*value;			/* Value of the current node */
	
	/* Fields get with HashMap iterator/next don't use these directly */
	HashMap		*_map;			/* HashMap head in this iterator */
	size_t		_idx;			/* Current index in the array */
	t_list		*_current;		/* Current node in the list */
} HashMap_it;


/* First capacity init, prime number arround 100 or 1000*/
#define HASHMAP_SIZE_100		151U
#define HASHMAP_SIZE_1000		1009U
#define HASHMAP_SIZE_2000		2053U
#define HASHMAP_SIZE_4000		4099U

/* Hashmap return value */
#define HASHMAP_UPT_ENTRY		0	/* Update hashmap entry */
#define HASHMAP_ADD_ENTRY		1	/* Add new entry */
#define HASHMAP_MALLOC_ERROR	2	/* Malloc error */
#define HASHMAP_DATA_REMOVED	3	/* Data removed */
#define HASHMAP_ENTRY_FREE		4	/* Entry free */
#define HASHMAP_NOT_FOUND		5	/* Entry not found */


/* Hashmap remove possible value */
#define HASHMAP_FREE_NODE		0	/* Free the entry node only (not the data) */
#define HASHMAP_FREE_DATA		1	/* Free the data with the given function */


/* Hash Map entry.value is valid (not null) */
#define HASHMAP_VALID_ENTRY(entry)	(entry->value != NULL)

/* Hash Map entry.key is the same as the key_cmp, same for x,y,z */
#define HASHMAP_SAME_ENTRY(entry, key_cmp, x_cmp, y_cmp, z_cmp) (\
		entry->key == key_cmp &&\
        entry->origin_data.x == x_cmp &&\
        entry->origin_data.y == y_cmp &&\
        entry->origin_data.z == z_cmp\
)

/* Hash Map entry.key is the same as the key_cmp */
#define HASHMAP_SAME_KEY(entry, key_cmp) (entry.key == key_cmp)

/* Get hashmap index by key and capacity */

#define HASHMAP_INDEX(key, capacity) (size_t)(key % (size_t)(capacity))

/* HashMap function API */

/**
 * @brief hash block coordinate to a unique key
 * @param x,y,z block coordinate
 * @return u64 KEY used to store the block in HashMap
*/
u64 hash_block_position(s32 x, s32 y, s32 z);

/**
 * @brief HashMap init, create a new HashMap 
 * @param capacity initial capacity of the HashMap
 * If the capacity is not a prime number, the capacity will be set to the next (grather) prime number 
 * @param free_obj function to free the object
 * @return HashMap* new HashMap (NULL if failed)
*/
HashMap *hashmap_init(size_t capacity, void (*free_obj)(void *obj));

/**
 * @brief HashMap entry free, free the entry (give to parameter to HashMap init see implementation in HashMap.c)
 * @param entry entry to free
*/
void hashmap_entry_free(void *entry);
void hashmap_free_node_only(void *entry);

/**
 * @brief HashMap destroy the map and free all the memory
 * @param map HashMap to destroy
*/
void hashmap_destroy(HashMap *map);

/**
 * @brief HashMap get the associated value with the key (x,y,z are the key)
 * @param map HashMap to search in
 * @param x,y,z key to search
 * @return void* value associated with the key (NULL if not found)
*/
void *hashmap_get(HashMap *map, BlockPos p);

/**
 * @brief HashMap set the value associated with the key (x,y,z are the key)
 * @param map HashMap to set in
 * @param x,y,z key to set
 * @param value value to set
 * @return s8 HASHMAP_UPT_ENTRY if update, HASHMAP_ADD_ENTRY if add, HASHMAP_MALLOC_ERROR if malloc failed
*/
s8 hashmap_set_entry(HashMap *map, BlockPos p, void *value);


/**
 * @brief HashMap remove the entry associated with the key (x,y,z are the key)
 * @param map HashMap to remove from
 * @param x,y,z key to remove
 * @param free_data HASHMAP_FREE_NODE to free the entry node only (not the data), HASHMAP_FREE_DATA to free the data with the given function
 * @return s8 HASHMAP_DATA_REMOVED if entry deleted, HASHMAP_NOT_FOUND if entry not found
*/
s8 hashmap_remove_entry(HashMap *map, BlockPos p, s8 free_data);

/**
 * @brief Function to get the length of the hash map
 * @param map HashMap to get the length
 * @return size_t length of the map
*/
size_t hashmap_size(HashMap *map);


/**
 * @brief Function to get the capacity of the hash map
 * @param map HashMap to get the capacity
 * @return size_t capacity of the map
*/
size_t hashmap_capacity(HashMap *map);

/**
 * @brief Function to create and initialize an iterator for the hash map 
 * @param map HashMap to iterate
 * @return HashMap_it Iterator to the first entry in the map
*/
HashMap_it hashmap_iterator(HashMap *map);

/**
 *  @brief Function to move to the next item in the hash map
 *	@param it Iterator to move
 *	@return int TRUE if move successful, FALSE otherwise (end of the map)
*/
s8 hashmap_next(HashMap_it *it);

/**
 * @brief Expand the given hashmap capacity
 * @param map HashMap to expand
 * @return int TRUE if expansion successful, FALSE otherwise
*/
s8 hashmap_expand(HashMap *map);

#endif /* HEADER_HASHMAP_H */