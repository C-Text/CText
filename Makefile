OBJS	= main.o neuron.o layer.o network.o
SOURCE	= main.c neuron.c layer.h network.c
HEADER	= 
OUT	= ctext
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wformat-truncation -Wformat-overflow -Wundef -fno-common -Wconversion -Wunused-parameter
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c -std=c99

neuron.o: neuron.c
	$(CC) $(FLAGS) neuron.c -std=c99

layer.o: layer.c
	$(CC) $(FLAGS) layer.c -std=c99

network.o: network.c
	$(CC) $(FLAGS) network.c -std=c99

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)

