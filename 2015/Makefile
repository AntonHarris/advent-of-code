CC = gcc
CFLAGS = -Wall -Wextra -std=c99
RM_TARGETS = $(shell find . -type f -executable)

.PHONY: all clean

all: 01 02 03 04 05 06 08 10 12 14 16 18

01: 01.c
		$(CC) $(CFLAGS) $< -o $@

02: 02.c
		$(CC) $(CFLAGS) $< -o $@

03: 03.c
		$(CC) $(CFLAGS) $< -o $@

04: 04.c
		$(CC) $(CFLAGS) $< -o $@ -lmd

05: 05.c
		$(CC) $(CFLAGS) $< -o $@

06: 06.c
		$(CC) $(CFLAGS) $< -o $@

07: 07.c
		$(CC) $(CFLAGS) $< -o $@

08: 08.c
		$(CC) $(CFLAGS) $< -o $@

10: 10.c
		$(CC) $(CFLAGS) $< -o $@

12: 12.c
		$(CC) $(CFLAGS) $< -o $@

14: 14.c
		$(CC) $(CFLAGS) $< -o $@

16: 16.c
		$(CC) $(CFLAGS) $< -o $@

18: 18.c
		$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f $(RM_TARGETS) 2>/dev/null || true