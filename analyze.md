# Analyze This

## Questions

1a. Yes, this algorithm is correct because all the cards that start with the same digit are grouped together in step iii. Within each group, the cards are ordered due to step i, and the groups are ordered due to step iv.

1b. The upper bound on this algorithm's runtime is O(n). Stelios runs through all n cards the first time when he checks their second digit. Stelios runs through all n cards again when he checks the first digit and divide them into piles. Stacking the piles together involves constant time because no matter what n is, the number of piles to stack together is always 10. Overall, since the runtime of the algorithm increases linearly with the size of the input, the runtime is of the order O(n).

2a. Yes, this algorithm is correct because it successfully moves the largest element to the back and the smallest to the front.

2b. The upper bound on this algorithm's runtime is still O(n^2) in the worst case that the array is in reverse order. (n-1) + (n-2) + ... + 0 = n(n-1)/2 = O(n^2).

3a. Yes, this algorithm is correct.

3b. The upper bound on this algorithm is O(n). In the worst case scenario, she reads it once, shuffles it and reads again, and repeats until there is only 1 card left. She reads it n times in total.

## Debrief

1. I found the lecture notes on sorting helpful.

2. I spent one hour on this problem's questions.
