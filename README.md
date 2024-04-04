**Objectives:**
- Gain familiarity with the organization of caches.
- Practice determining whether a cache access is a hit or a miss, and
when to read from and write to storage.
- Gain practical experience using hash tables and linked lists.

---

**Format:**

Your job is to implement the core part of a key\-value software cache, which
relies on the KVPAIR struct representing a key\-value pair in a doubly linked list.
You need to use a hash table which maps each key\-value pair to a bucket
based on its key. The table should have a bounded "chain depth" of 4, which
means that each bucket should contain no more than 4 elements. Buckets
in the table are in the form of doubly linked lists.

Please look at kv_cache.h to see many of the definitions for data structures
and functions used in this project,
including the KVPAIR and KVCACHE (the hash table) structures
and the MAX_BIN_ELEMENTS constant (chain depth).

Your objective is to write the code for the lookup function in kv_cache.c. All your 
modifications are to be in that file alone.

---

**lookup:**

You need to track hits, misses, and writebacks (KV pairs that are modified and
need to be written back to storage when replaced from the cache).

lookup must call read_key if a key is not currently in the cache in order to
load it from storage.
lookup must call write_key if a key being replaced in the cache has been modified,
in order to write the change back to storage.
read_key and write_key are provided for you--see kv_cache.h for function prototypes
and descriptions.

kv_cache.h includes 3 global int values `hits`, `misses`, and `writebacks`.
You should increment `hits` when lookup finds the key in the cache, increment `misses`
when the key is not the cache, and increment `writebacks` whenever a modified
key is replaced from the cache and written back into memory.

---

**Checking your work:**

There are eight different tests provided, numbered 1 through 8, each having increasing
complexity. Test number 0 will run all the tests. Run the tests individually via the command line for debugging and to check valgrind output.

Using `make` on the command line will build the program kv_cache_test which includes your code from kv_cache.c
along with test harness code that is not visible to you.

Run the program on the command line with
```
./kv_cache_test -b <bins> -n <keypairs> -t <test>
```
Note that tests 1-5 ignore the keypair parameter.

You can also run the local python tests using
```
python3 hwtest.py ALL
```
The results of these local tests should be the same as those on the autograder.

---

**Debugging:**

kvcache.h includes two printing functions to help you understand
the state of your cache. printlist prints the contents of
an individual list in your cache, and print_cache prints the entire contents
of the cache. Pair this with command line arguments for kv_cache_test
to run your program with small inputs and understand the cache contents
after each lookup.

---

**Submission:**

- Submit your project on gradescope using the gitlab submission process.

- ***Team specific instructions*** 
  - Teams should only do one submission via group submission.
  - Teams must also edit the file called reflection.txt and include a detailed description of each team members contributions to the project.
