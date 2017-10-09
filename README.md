# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?
It's a word referring to lung disease caused by the inhalation of silica dust. It's supposedly the longest word in a dictionary.
## According to its man page, what does `getrusage` do?
it returns resource usage statistics including CPU time used, integral shared memory size, etc, for "int who." spelelr.c/ uses RUSAGE_SELF, which gives usage statistics for the calling process- the sum of resources used by all threads in the process.

## Per that same man page, how many members are in a variable of type `struct rusage`?
16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

We pass 'before' and 'after' by reference to 'calculate' because passing large structs by value would be slow and take up a lot of memory space. Passing them by value could lead to stack overflow if copies of those values were placed on the stack.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

In the main function, we used c = fgetc(file). This function reads each character from file and advances the cursor in the file until the end of file is reached.
For each character we receive, (1) if character is alphabetical/ apostrophe, it is appended to the char array word; however, if the alphabetical string seems too long to be a word, we move to the next word (2) else if character is a number, we move to the next word (3) else if character is a space/ punctuation, we should be at end of a word so we add \0 to the array.
fgetc

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fscanf with a formal string "%s" reads characters until a white space is found, so it might incorrectly consider punctuation as part of the word.
Moreover, since fscanf puts no limit on the length of a word, hackers who input an extremely long string in the text file could overwrite important data in memory or cause segmentation fault.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Declaring them as constants prevents changes in the word and dictionary we are using. This is a safety measure against modification in functions.