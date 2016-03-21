def getCoordinates(value, table): #given value find coordinates 
    print
    rows = len(table)
    cols = len(table[0])
    for i in range(rows):
        for j in range(cols):
            if table[i][j] == value:
                return([i,j])

def nextKnightMove(value, table): #Next Knights move from current coordinates
    i, j = getCoordinates(value, table)
    rows = len(table)
    cols = len(table[0])
    ret = []
 
    #down 3 right
    if(i+1 < rows and j+2 < cols and table[i+1][j+2] is not None):
        ret.append(table[i+1][j+2])
    #down 3 left
    if(i+1 < rows and j-2 >= 0 and table[i+1][j-2] is not None):
        ret.append(table[i+1][j-2])
    #up 3 right
    if(i-1 >= 0 and j+2 < cols and table[i-1][j+2] is not None):
        ret.append(table[i-1][j+2])
    #up 3 left
    if(i-1 >= 0 and j-2 >= 0 and table[i-1][j-2] is not None):
        ret.append(table[i-1][j-2])
    #down 1 right
    if(i+2 < rows and j+1 < cols and table[i+2][j+1] is not None):
        ret.append(table[i+2][j+1])
    #down 1 left
    if(i+2 < rows and j-1 >= 0 and table[i+2][j-1] is not None):
        ret.append(table[i+2][j-1])
    #up 1 right
    if(i-2 >= 0 and j+1 < cols and table[i-2][j+1] is not None):
        ret.append(table[i-2][j+1])
    #up 1 left
    if(i-2 >=0  and j-1 >= 0 and table[i-2][j-1] is not None):
        ret.append(table[i-2][j-1])
    return ret

def genKnightMTable(table, mtable, digits, start):
    if digits == 1:
        return 1
    if (mtable[digits][start] == 0):
        for n in nextKnightMove(start, table):
            mtable[digits][start] += generateTableM(table, mtable, digits-1, n)
    return mtable[digits][start]


if __name__ == "__main__":
    while True:
        piece = raw_input("piece: ")
        numLen = int(raw_input("number length: "))
        startings = raw_input("space-separated valid starting digits: ").split()
        rows = int(raw_input("rows: "))
        cols = int(raw_input("columns: "))
        table = [[0 for i in range(cols)] for j in range(rows)]

        for i in range(rows):
            row = raw_input("space-separated characters: ").split()
            for j in range(cols):
                table[i][j] = row[j] if row[j].isdigit() else -1
                print i, j, table[i][j] 

        mtable = [[0 for i in range(numLen)] for j in range(numLen+1)] #memoization table
        result = 0

        if piece == "knight":
            for i in startings:
                result += genKnightMTable(table, mtable, numLen, int(i))
        elif piece == "bishop":
            for i in startings:
                result += genBishopMTable(table, mtable, numLen, int(i))
        else:
            print("Invalid piece!")

        print result
        continue
