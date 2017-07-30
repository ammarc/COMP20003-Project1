CC=gcc
CFLAGS = -g -Werror
DEPS1 = yelp1.h
DEPS2 = yelp2.h
OBJ1 = main1.o bst1.o
OBJ2 = main2.o bst2.o
LIB = -lm


# we make the use of a lot of conventions that
# use to the left or right of
# we also make the object files first
# the program is made with -g to help with debugging

all: yelp1 yelp2

%.o: %.c $(DEPS1)
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c $(DEPS2)
	$(CC) $(CFLAGS) -c -o $@ $<

yelp1: $(OBJ1)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

yelp2: $(OBJ2)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm -f $(OBJ1) yelp1
	rm -f $(OBJ2) yelp2
