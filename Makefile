COMPILER = gcc

TARGET = ./main


SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

CFLAG = -Wall

POLICY = ./TestData/FIFO ./TestData/PSJF ./TestData/SJF ./TestData/RR

N = _1.txt _2.txt _3.txt _4.txt _5.txt

.PHONY: all run clean

all: $(TARGET) clean

run:
	@for i in $(POLICY); do \
		for j in $(N); do \
			echo "[*] Testing $$i$$j"; \
			sudo ./main < $$i$$j; \
		done \
	done

$(TARGET): $(OBJS)
	$(COMPILER) $(CFLAG) -o $@ $^

%.o: %.c
	$(COMPILER) $(CFLAGS) -o $@ -c $<

clean:
	@$(RM) $(OBJS)

