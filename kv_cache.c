
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "kv_cache.h"


// Lookup the provided key in the KV cache.
// If the key is not found, fetch it from storage by calling read_key
// and place the KVPAIR in the cache.
// If placing a KVPAIR from memory into the cache causes the number of elements
// in the bin to exceed MAX_BIN_ELEMENTS, remove a KVPAIR using the LRU
// replacement policy and call write_key if the removed KVPAIR has
// been modified and changes need to be written back to memory.
// If the key is found in the cache, update LRU order for the
// key's bin appropriately.
// Input: the KV cache hash table and key to lookup
// Return: pointer to KVPAIR with the desired key
// Utility function to remove a KVPAIR from its bin

void remove_kvpair(KVCACHE *kv_cache, KVPAIR *kvpair, unsigned int bin_index) {
    if (kvpair->prev) kvpair->prev->next = kvpair->next;
    else kv_cache[bin_index].list = kvpair->next; // Update head if first element
    if (kvpair->next) kvpair->next->prev = kvpair->prev; 
}

// Utility function to add a KVPAIR to the front of its bin
void add_kvpair_to_front(KVCACHE *kv_cache, KVPAIR *kvpair, unsigned int bin_index) {
    kvpair->next = kv_cache[bin_index].list;
    if (kv_cache[bin_index].list != NULL) kv_cache[bin_index].list->prev = kvpair;
    kv_cache[bin_index].list = kvpair;
    kvpair->prev = NULL;
}

KVPAIR *lookup(KVCACHE *kv_cache, long key, unsigned int bins) {
    unsigned int bin_index = key % bins;
    KVPAIR *current = kv_cache[bin_index].list;
    KVPAIR *tail = NULL;

    while (current != NULL) {
        if (current->key == key) {
            hits++;
            if (current != kv_cache[bin_index].list) {
                remove_kvpair(kv_cache, current, bin_index);
                add_kvpair_to_front(kv_cache, current, bin_index);
            }
            return current;
        }
        if (current->next == NULL) tail = current;
        current = current->next;
    }

    misses++;
    KVPAIR *new_kvpair = read_key(key);
    if (!new_kvpair) return NULL;

    if (kv_cache[bin_index].num_keys >= MAX_BIN_ELEMENTS) {
        if (tail->modified) {
            writebacks++;
            write_key(tail);
        }
        // Adjusting here to ensure we don't access `tail` after it's potentially freed
        KVPAIR *to_free = tail;
        remove_kvpair(kv_cache, tail, bin_index);
        kv_cache[bin_index].num_keys--; // Decrement before freeing the KVPAIR to maintain accurate count
        free(to_free->val); // Ensure to free dynamically allocated value string
        free(to_free); // Free the KVPAIR structure itself after it's completely unlinked and processed
    }

    add_kvpair_to_front(kv_cache, new_kvpair, bin_index);
    kv_cache[bin_index].num_keys++;

    return new_kvpair;
}