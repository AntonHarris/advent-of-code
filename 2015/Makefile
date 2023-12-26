CC = gcc
CFLAGS = -Wall -Wextra -std=c99
RM_TARGETS = $(shell find . -type f -executable)

.PHONY: all clean

all: 01 02 05

01: 01.c
		$(CC) $(CFLAGS) $< -o $@

02: 02.c
		$(CC) $(CFLAGS) $< -o $@

03: 03.c
		$(CC) $(CFLAGS) $< -o $@

04: 04.c
		$(CC) $(CFLAGS) $< -o $@

05: 05.c
		$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f $(RM_TARGETS) 2>/dev/null || true