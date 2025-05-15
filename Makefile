SRCPATH := ../get_next_line/
SRCFILES := $(SRCPATH)get_next_line.c $(SRCPATH)get_next_line_utils.c

OUTDIR = outs/
# Compiler and flags
CC = cc
CFLAGS = -Wno-format-security -g3 -lbsd -I $(SRCPATH)
FULLDEBUGFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRCS = get_next_line_test.c

# Create a list of output .out files based on test.c files
OUTS = $(patsubst %.c, $(OUTDIR)%.out, $(SRCS))

# Default target: build all tests
all: $(SRCFILES) $(OUTDIR) $(OUTS)

$(OUTDIR):
	mkdir -p $(OUTDIR)

# Rule to create .out files from .c files
$(OUTDIR)%.out: %.c
	$(CC) $(CFLAGS) -o $@ $< $(SRCFILES)

# Run all .out files
run:
	@for file in $(OUTDIR)*.out; do \
		echo "Running $$file"; \
		./$$file; \
	done

# Clean up the output files
clean:
	rm -rf $(OUTDIR)
	make clean -C $(SRCPATH)

fclean: clean
	make fclean -C $(SRCPATH)

cleantest:
	rm -rf $(OUTDIR)

re: fclean
	$(MAKE) $(SRCPATH)
	$(MAKE) all
