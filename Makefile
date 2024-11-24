CC = clang
CFLAGS = -std=c2x -Wall -Wextra -Werror

SRCDIR := src
OUTDIR := bin

# Find all .c files recursively
SOURCES := $(shell find $(SRCDIR) -type f -name '*.c')
# Generate corresponding binary names
BINS := $(patsubst $(SRCDIR)/%.c,$(OUTDIR)/%,$(SOURCES))

# Rule to build all binaries
all: $(BINS)

# Rule to build each binary
$(OUTDIR)/%: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

# Rule to build a specific binary by filename
SOURCE := $(shell find $(SRCDIR) -type f -name '$(FILENAME).c')
build_specific_cfile: $(OUTDIR)/$(FILENAME)

# Rule to run a specific go file
gorun:
	cd src/advent-of-code/go && go run $(YEAR)/day$(DAY)/main.go

# Clean rule
clean:
	rm -rf $(OUTDIR)

.PHONY: all clean build_specific_cfile gorun
