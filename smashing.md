# Stack Smashing

## Questions

1. A stack canary is a known value written just before a return address in the stack frame. Before returning from the function, we compare the original canary value to its current value; if the value changed, then there is stack buffer overflow and we should make the program terminate to prevent from falling into hackers' traps.

2. A stack canary is analogous to a canary in a coal mine in signaling to humans that something's amiss. Coalminers used to bring caged canaries with them to detect toxic gases becauses canaries die sooner from toxic gases earlier than humans do. If the canaries became sick or died in the mines, the coalminers would know that something's wrong and that they should leave.

3.

#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    char buffer[5];
    strcpy(buffer, argv[1]);
    return 0;
}
## Debrief

1. The linked youtube video on stack canaries was helpful in answering this problem's questions.

2. I spent 25 minutes on this problem's questions.
