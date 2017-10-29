from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # split the strings by line
    a_lines = a.split('\n')
    b_lines = b.split('\n')
    # create sets with no duplicate lines
    a_set = set(a_lines)
    b_set = set(b_lines)

    return list(a_set & b_set)


def sentences(a, b):
    """Return sentences in both a and b"""

    # split the strings by sentences
    a_lines = sent_tokenize(a)
    b_lines = sent_tokenize(b)
    a_set = set(a_lines)
    b_set = set(b_lines)
    return list(a_set & b_set)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    a_set = set()
    b_set = set()

    # iterate through each character up till (length- n) and add to the sets
    for i in range(len(a) - n + 1):
        a_set.add(a[i:(i + n)])
    for j in range(len(b) - n + 1):
        b_set.add(b[j:(j + n)])
    return list(a_set & b_set)
