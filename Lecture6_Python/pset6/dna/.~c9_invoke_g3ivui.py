'''
python dna.py databases/large.csv sequences/5.txt
python dna.py
python dna.py data.csv
'''
import csv
import sys
import re


def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py databases/large.csv sequences/5.txt")

    databases = []
    with open(sys.argv[1],"r") as file:
        reader = csv.reader(file)
        for database in reader:
            databases.append(database)
    STR = ""
    with open(sys.argv[2],"r") as file:
        for line in file:
            STR += line
    counter = 0
    tmp = list()

    for i in range(1,len(databases[0])):
        dna = (databases[0][i])
        # make a list of the repeated sequence in STR
        listAll = re.findall(r'(?:'+dna+')+', STR)
        # find the longest repeated string
        longest = max(listAll, key=len)
        count = len(longest) // len(dna)
        # put in a list
        tmp.append(str(count))


    match = None
    for i in range(1, len(databases)):
        # Check if the counts are equal
        if databases[i][1:] == tmp:
            match = (databases[i][0])
    # Return match if match database
    if match != None:
        print(match)
    else:
        print("No Match")


if __name__ == "__main__":
    main()

