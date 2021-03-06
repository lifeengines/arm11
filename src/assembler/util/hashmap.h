/*
 * Generic hashmap manipulation functions
 *
 * Originally by Elliot C Back - http://elliottback.com/wp/hashmap-implementation-in-c/
 *
 * Modified by Pete Warden to fix a serious performance problem, support strings as keys
 * and removed thread synchronization - http://petewarden.typepad.com
 *
 * Further modified by Emanuele Rossi
 */
#ifndef HASHMAP_H
#define HASHMAP_H

#define MAP_MISSING -3  /* No such element */
#define MAP_FULL -2 	/* Hashmap is full */
#define MAP_OMEM -1 	/* Out of Memory */
#define MAP_OK 0 	/* OK */

/*
 * any_t is a pointer.  This allows you to put arbitrary structures in
 * the hashmap.
 */
typedef void *any_t;

/*
 * map_t is a pointer to an internally maintained data structure.
 * Clients of this package do not need to know how hashmaps are
 * represented.  They see and manipulate only map_t's.
 */
typedef any_t map_t;

/*
 * Return an empty hashmap. Returns NULL if empty.
*/
extern map_t hashmap_new();

/*
 * Add an element to the hashmap. Return MAP_OK or MAP_OMEM.
 */
extern int hashmap_put(map_t in, const char* key, any_t value);

/*
 * Get an element from the hashmap. Return NULL if the element is not present.
 */
extern any_t hashmap_get(map_t in, const char* key);

/*
 * Remove an element from the hashmap. Return MAP_OK or MAP_MISSING.
 */
extern int hashmap_remove(map_t in, const char* key);

/*
 * Free the hashmap
 */
extern void hashmap_free(map_t in);

/*
 * Get the current size of a hashmap
 */
extern int hashmap_length(map_t in);

#endif


