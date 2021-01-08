#Alexander Rollison
SRC1 = Code7.c
SRC2 = GameLib.c
SRC3 = FileLib.c

OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)
OBJ3 = $(SRC3:.c=.o)
EXE = $(SRC1:.c=.e)

HFILES = GameLib.h FileLib.h

CFLAGS = -g 

all : $(EXE)

$(EXE): $(OBJ1) $(OBJ2) $(OBJ3)
	gcc $(CFLAGS) $(OBJ1) $(OBJ2) $(OBJ3) -o $(EXE)
	
$(OBJ1) : $(SRC1) $(HFILES)
	gcc -c $(CFLAGS) $(SRC1) -o $(OBJ1)

$(OBJ2) : $(SRC2) $(HFILES)
	gcc -c $(CFLAGS) $(SRC2) -o $(OBJ2)
	
$(OBJ3) : $(SRC3) $(HFILES)
	gcc -c $(CFLAGS) $(SRC3) -o $(OBJ3)
