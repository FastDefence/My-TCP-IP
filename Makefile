CC      = gcc
CFLAGS  = -Wall -Wextra -I. -Iheaders

SRCS    = main.c make_tap.c \
          util/checksum.c \
          dispatcher/layer3.c dispatcher/layer4.c \
          handler/arp.c handler/ethernet.c handler/ipv4.c handler/icmp.c

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