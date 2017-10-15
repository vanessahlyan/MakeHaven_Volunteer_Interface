# Now Boarding

## Questions

1.

```c
typedef struct
{
    int head;
    passenger my_array[CAPACITY];
    int size;
}
pqueue;
```

2. To add a single passenger to array

if there is no room in array (CAPACITY <= pqueue.size)
    return false
if there is room in array
    if array is empty (size = 0)
        make first element of my_array Passenger 1
    if array not empty
        if previous passenger's group number <= current passenger's group #
            place new passenger at pqueue.my_array[(head+size) % capacity]
        else, compare until you find a previous value that is <= current passenger.group, recording how many times (n) you compared
            place new passenger at pqueue.my_array[(head+size-n) % capacity]
    add 1 to pqueue.size


3. The upper bound on the algorithm's running time is O(n). In the worst case scenario, the element we add to the queue has a group number less than all the element before it and we make (n-1) comparisons before placing it in the premier location in the array.

4. Dequeue a single passenger from beginning of array

if no more elements in array (pqueue.size = 0)
    return false
else if there are still elements in array
    move head
    subtract 1 from pqueue.size

5. The upper bound on that algorithm's running time is O(1) because the algorithm just needs to go through a single element and remove it from the array. For this runtime, it doesn't matter how many more passengers there are in the array.

## Debrief

1. I found https://study.cs50.net/queues useful for solving this problem.

2. I spent one hour on this problem's questions.
