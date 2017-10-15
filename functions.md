# #functions

## Questions

1. This hash function creates too few buckets which means there might be a lot of items in each linked list. The function places all strings that start with the same character in the same bucket. If we have many strings that start with the same character, we have a large number of items (n) in a the corresponding linked list. Given the O(n) run time for linked lists, when n is large, O(n) will be large as well and the hash table will be slow.

2. This hash function is "perfect" by definition because it hashes each string to a unique number and therefore should not yield any collisions. However, the hash function is imperfect in practice because the hash indexes are way too long and could cause stack buffer overflow. The 3-character string ABC is already this long: 010000010100001001000011; imagine how long the hash_index for longer strings like computer would be. If we want the hash index to be shorter, we might take a modulus of the index, but that could lead to collisions.

3. If you saved the hashes in the original 50 JPEGS, students might accidentally modify the hashes and cause errors in check50.

4. For a trie, you look up an element by using successive digits to navigate from the root. If you make it to the end without hitting a NULL pointer, you've found the element. The run time for this algorithm only depends on the length of the word you are looking for and not the total number of elements in the trie. Therefore, the run time is O(k) where k is a constant representing the length of the lookup word.
 For a hash table, the run time is O(n) because even after hashing, one has to go through all n elements in the corresponding linked list in the worst case scenario.

## Debrief

1. The review session lecture was helpful in answering these questions.

2. I spent 45 minutes in answer this problem's questions.
