DIR_INC=./
DIR_SRC= ../cpp11netbase .
DIR_OBJ=./
DIR_BIN=./

CC=g++
CFLAGS=-g -std=c++11

FILES = $(foreach dir, $(DIR_SRC), $(wildcard $(dir)/*.c))
OBJS = $(patsubst %.c, %.o, $(FILES))

TARGET = client 

RM = rm -f

$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) -lpthread

$(OBJS):%o:%c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(TARGET) $(OBJS)
