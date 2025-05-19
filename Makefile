SRCPATH := ../get_next_line/
SRCFILES := $(SRCPATH)get_next_line.c $(SRCPATH)get_next_line_utils.c

OUTDIR = outs/
# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(SRCPATH)
FULLDEBUGFLAGS = -fsanitize=address

SRCS = get_next_line_test.c

BUFFERS = 0 1 2 5 10 100 1024 100000

# Create a list of output .out files based on test.c files
OUTS = $(patsubst %, $(OUTDIR)buffer_%.out, $(BUFFERS))
#BUFFERFLAG = $(patsubst %, BUFFER_SIZE=%, $(BUFFERS))

# Default target: build all tests
all: $(SRCFILES) $(OUTDIR) $(OUTS) main.c

$(OUTDIR):
	mkdir -p $(OUTDIR)

# Rule to create .out files from .c files
$(OUTDIR)buffer_%.out: main.c $(SRCFILES)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$* -o $@ $< $(SRCFILES)

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
