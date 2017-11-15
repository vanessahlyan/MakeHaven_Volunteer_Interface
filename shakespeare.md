# To be or not to be

## ~~That is the question~~ These are the questions

4.1. script.py initially generates 1000 objects.

4.2. We initialize a variable "score" as 0. Then, we compare each character in the string to the corresponding character in the target line "to be or not to be." Every time, we add 1 to the score if the characters match. After iterating through the entire string, we divide the total score by the length of the target phrase and save this number as a string's fitness.

4.3. Only 1 of the characters match, so score is one. fitness = 1.0/18 = .0555...

4.4. Using the analogy of genetic mutations where each gap has cost 2 and a change has cost 1, we calculate the cost of converting the string to the target line by creating a lookup table with characters of the string as columns and characters of the target line as rows. Beginning at the lower-right corner of the table, we compute the cost to match corresponding characters of the two strings as cost[i][j] = min(cost[i+1][j] + 2, cost[i][j+1] + 2, cost[i+1][j+1] + x); the minimum edit distance we're looking for is the value in the top-left cell; however, we also need to invert the edit distance because to obtain the fitness of the string because the larger the edit distance, the lower the string's fitness.

4.5. The first generation of design is not necessarily the best solution. By randomly changing a small percentage of the characters, we allow for the child to arrive at the best solution even if it didn't inherit it from the parent.

## Debrief

a. I found the notes on Lecture 7 and the linked reading helpful in answering this question.

b. I spent 45 minutes on this question.
