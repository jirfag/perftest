CFLAGS=-I./ -std=gnu99 -Ofast -ggdb3 -Wall -Wextra -flto
OBJDIR=obj

C_SOURCES=main.c test.c strcspn.c
C_OBJS=$(patsubst %.c, $(OBJDIR)/%.c.o, $(C_SOURCES))

OBJS=$(C_OBJS)

$(OBJDIR)/%.c.o: %.c Makefile test.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/main: $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS)

all: $(OBJDIR)/main
