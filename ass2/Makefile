# # build

# # Linux/Mac
# CC=gcc
# CCFLAGS=-Wall -lm -std=c11 -c
# RM=rm
# OBJ=.o
# EXE=
# OFLAGS=-o 

# # Windows
# #CC=cl
# #CCFLAGS=/std:c11 /c
# #OBJ=.obj
# #EXE=.exe
# #OFLAGS=/out:
# all: searchPagerank$(EXE) pagerank$(EXE) scaledFootrule$(EXE)
# searchPagerank$(EXE): list$(OBJ) invertedTable$(OBJ) searchPagerank$(OBJ)
# 	$(CC) $(OFLAGS) searchPagerank$(EXE) searchPagerank$(OBJ) list$(OBJ) invertedTable$(OBJ)

# pagerank$(EXE): graph$(OBJ) readData$(OBJ) list$(OBJ) pagerank$(OBJ)
# 	$(CC) $(OFLAGS) pagerank$(EXE) graph$(OBJ) readData$(OBJ) list$(OBJ) pagerank$(OBJ)  

# scaledFootrule$(EXE): list$(OBJ) scaledFootrule$(OBJ)
# 	$(CC) $(OFLAGS) scaledFootrule$(EXE) scaledFootrule$(OBJ) list$(OBJ)

# list$(OBJ): list.h list.c 
# 	$(CC) $(CCFLAGS) -w list.c

# graph$(OBJ): graph.h graph.c list$(OBJ)
# 	$(CC) $(CCFLAGS) -w graph.c  

# pagerank$(OBJ): pagerank.h pagerank.c list$(OBJ) graph$(OBJ)
# 	$(CC) $(CCFLAGS) -w pagerank.c

# invertedTable$(OBJ): invertedTable.h invertedTable.c list$(OBJ)
# 	$(CC) $(CCFLAGS) -w invertedTable.c

# scaledFootrule$(OBJ): scaledFootrule.h scaledFootrule.c list$(OBJ) 
# 	$(CC) $(CCFLAGS) -w scaledFootrule.c

# searchPagerank$(OBJ): searchPagerank.h searchPagerank.c list$(OBJ) invertedTable$(OBJ)
# 	$(CC) $(CCFLAGS) -w searchPagerank.c
CC = gcc
CFLAGS = -Wall -Werror -std=c11 -g

# List all your C files that don't contain main() here
SRC_FILES = Graph.c invertedTable.c list.c readData.c

.PHONY: all
# Uncomment each of these as you start working on them
all: pagerank #searchPagerank #scaledFootrule

pagerank: pagerank.c $(SRC_FILES)
	$(CC) $(CFLAGS) -o pagerank pagerank.c $(SRC_FILES)

searchPagerank: searchPagerank.c $(SRC_FILES)
	$(CC) $(CFLAGS) -o searchPagerank searchPagerank.c $(SRC_FILES)

scaledFootrule: scaledFootrule.c $(SRC_FILES)
	$(CC) $(CFLAGS) -o scaledFootrule scaledFootrule.c $(SRC_FILES)

.PHONY: clean
clean:
	rm -f pagerank searchPagerank scaledFootrule