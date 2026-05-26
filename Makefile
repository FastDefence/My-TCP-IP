CC      = gcc
CFLAGS  = -Wall -Wextra -I. -Iheaders

SRCS    = main.c make_tap.c \
          util/checksum.c \
          dispatcher/ethii.c \
          parser/ethii.c

OBJS    = $(SRCS:.c=.o)

TARGET  = my_stack

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	sudo ./$(TARGET)