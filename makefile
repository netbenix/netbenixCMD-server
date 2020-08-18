CC = gcc
ARGS = -std=gnu99
OBJ= main.o

netbenixCMD-server: $(OBJ)
	$(CC) $(ARGS) -o netbenixCMD-server $(OBJ)
main.o: main.c
	$(CC) -c main.c