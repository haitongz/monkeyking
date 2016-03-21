mapping = {10: "a", 11: "b", 12: "c", 13: "d", 14: "e", 15: "f", 16: "g", 17: "h"}
seventeen1s = "11111111111111111"

""" check whether a string (alpha-numeric in this case) is palindromic """
def isPalindrome(string):
    return True if string and string == string[::-1] else False

""" creates a list of the next N bit sequences that contain 17 consecutive 1's
    e.g. passing in 1 gives us "0" and "1" (because we have one free bit)
        these are the next two bit permutations that still
        contain 17 consecutive ones:
        11111111111111111 -> "11111111111111111" + "0"
        11111111111111111 -> "11111111111111111" + "1" """
def genBitSeqs(bits):
    if bits == 0: # check empty sequence
        return []

    combinations = []
    for i in range(0, bits):
        combinations.append(0)

    ret = []

    while True:
        ret.append("".join(map(str, combinations))) # add the possible permutations to a list
        for i in range(0, len(combinations)): # calculates next permutation based on previous permutation
            if combinations[i] < 1:
                combinations[i] += 1
                break
            else:
                combinations[i] = 0
                if i == len(combinations) - 1:
                    return ret

""" concatenates every elements of each list with every other elements """
def concatenates(list1, string, list2):
    combinations = []
    ret = []

    if list1 == []: # check empty arrays
        for elmt in list2:
            ret.append(string + elmt)
    elif list2 == []:
        for elmt in list1:
            ret.append(elmt + string)
    else:
        for elmt in list1:
            combinations.append(elmt + string)
        for elmt1 in combinations:
            for elmt2 in list2:
                ret.append(elmt1 + elmt2)

    return ret

""" consolidates a multidimensional array of permutations into a single array """
def consolidates(multiArray):
    ret = []

    for array in multiArray:
        for elmt in array:
            ret.append(elmt)

    return ret

""" calculates all permutations for a given bit sequence length """
def allPermutations(bitSeqLen):
    difference = bitSeqLen - 17
    bound = difference
    permutations = []

    """ calculates all possible "front" and "back" permutations of all possible lengths """
    while difference > -1:
        front = genBitSeqs(bound - difference)
        back = genBitSeqs(difference)
        permutations.append(concatenates(front, seventeen1s, back))
        difference -= 1

    return consolidates(permutations)

""" convert base10 to base17 """
def base10TObase17(number):
    base = 17
    representation = []

    while number > 0:
        remainder = number % base
        representation.insert(0, mapping[remainder] if remainder > 9 else str(remainder))
        number //= base # floordiv

    return "".join(representation)

""" convert base17 to base10 """
def base17TObase10(number):
    revMapping = dict((v,k) for k,v in mapping.iteritems()) # reverse the mapping dictionary to perform reverse lookup
    numList = dict(enumerate(list(number)))
    ret = 0

    for index, value in numList.items():
        if not value in revMapping.keys():
            ret += int(value) * pow(17, len(numList) - index - 1)
        else:
            ret += revMapping[value] * pow(17, len(numList) - index - 1)

    return ret

""" convert base10 to base2 """
def base10TObase2(base10):
    return int(bin(base10).split("b",1)[1])

""" convert base2 to base10 """
def base2TObase10(binary):
    numList = dict(enumerate(list(binary)))
    ret = 0

    for index, value in numList.items():
        ret += int(value) * pow(2, len(numList) - index - 1)

    return ret

""" checks if a number in base 17 (formatted as string) is a palindrome """
""" finds the next number which has 17 consecutive 1's in base2 and is a palindrome in base17 """
def findNextNum():
    bitSeed = seventeen1s

    while True:
        bitSeed += "11"
        permutations = allPermutations(len(bitSeed)) # all permutations for a given bitSeed
        for sequence in permutations:
            base17Num = base10TObase17(base2TObase10(sequence))
            if isPalindrome(base17Num) and base17TObase10(base17Num) != 131071: # call isPalindrome first bcoz it should be faster than base17Tobase10 
                return base17TObase10(base17Num)

if __name__ == "__main__":
    result = findNextNum()
    print "Found next number: ", result
    print "Next number in base 2: ", base10TObase2(result)
    print "Next number in base 17: ", base10TObase17(result)
