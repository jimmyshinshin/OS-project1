COMPILER = gcc

TARGET = ./main

OBJ_DIR = ./obj

SRCS = $(wildcard *.c)
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CFLAG = -Wall

.PHONY: all run clean

all: clean $(TARGET)

run:
	$(TARGET)

$(TARGET): $(OBJS)
	$(COMPILER) $(CFLAG) -o $^

$(OBJ_DIR)/%.o: %.c
	$(COMPILER) $(CFLAGS) -o $@ -c $<

clean:
	@$(RM) $(TARGET) $(OBJS)

