CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGETS = $(shell seq -w 01 25)
RM_TARGETS = $(shell find . -type f -executable)

.PHONY: all clean

all: $(TARGETS)

# Not skipping if source prerequisite file does not exist, TODO
%: %.c
	@if [ -e $< ] && [ -f $< ]; then \
		$(CC) $(CFLAGS) $< -o $@; \
	else \
		echo "File $< not found, skipping"; \
	fi

clean:
	@rm -f $(RM_TARGETS) 2>/dev/null || true