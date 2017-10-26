from cs50 import get_string
import sys


def main():
    "takes key as a command line argument and converts a plaintext into a ciphered string"
    if len(sys.argv) != 2:
        print("You must provide 2 arguments in the command line.")
        exit(1)
    else:
        key = int(sys.argv[1])
        if key == None or key < 0:
            print("Error! Invalid key.")
            exit(1)
        else:
            # get the plaintext string
            plaintext = get_string("Enter the plaintext: ")
            plaintext_length = len(plaintext)

            print(f"plaintext: {plaintext}")
            print("ciphertext: ", end='')

            # going through all elements of the plaintext
            for c in plaintext:
                # check if character is alphabetical
                if c.isalpha() == 0:
                    # if not alphabetical, print unciphered character
                    print(c, end='')
                elif c.isalpha() != 0:
                    # check if character is lower case
                    if c.islower() != 0:
                        # switch to alphabetical index and shift by key
                        alphabet_index = (ord(c) - ord('a') + key) % 26
                        # switch back to ascii index
                        new_ascii_index = alphabet_index + ord('a')
                        # print new ciphered alphabetical character
                        print(chr(new_ascii_index), end='')

                    # check if character is upper case
                    elif c.isupper() != 0:
                        # switching to alphabetical index and shift by key
                        alphabet_index = (ord(c) - ord('A') + key) % 26
                        # switch back to ascii index
                        new_ascii_index = alphabet_index + ord('A')
                        # print new ciphered alphabetical character
                        print(chr(new_ascii_index), end='')

            print("\n")
            exit(0)


if __name__ == "__main__":
    main()
