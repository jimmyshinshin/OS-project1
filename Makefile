COMPILER = gcc

TARGET = ./main

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
CFLAG = -Wall

.PHONY: all run clean

all: clean $(TARGET)

run:
	$(TARGET)

$(TARGET): $(OBJS)
	$(COMPILER) $(CFLAG) -o $^

%.o: %.c
	$(COMPILER) $(CFLAGS) -o $@ -c $<

clean:
	@$(RM) $(TARGET) $(OBJS)

