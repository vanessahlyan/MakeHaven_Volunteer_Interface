# Helping `help50`

## Questions

1. % only works for integers. If you want to perform such an operation on doubles or floats, you may want use fmod or fmodf. But for the purpose of cash.c, you should have converted the float dollar value to an integer value in cents using the round function. That would allow you to use the % operator.

2. get_string is a function defined in the CS50 library. To use a function, one must type () after the function name and place any necessary input within the parantheses. In this case, one must type getstring() at the very least, or better with with some sort of prompt, e.g. getstring("enter plaintext: ")

3. The buffer needs to be defined as unsigned char rather than char. The regular signed char can only take up 128 in the positive direction because one bit has to be used for the sign. In contrast, an unsigned char can take values from 0 to 255.

4. If the boolean of the node is false, the node also needs to include a pointer to the next node. This pointer cannot be NULL unless the boolean is true. Also, you can remove the set of curly brackets around NULL.

## Debrief

1. I looked back on my previous problem sets to answer this problem's questions.

2. I spent 5 minutes working on this problem's questions.
