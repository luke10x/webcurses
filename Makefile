# vim: tabstop=4 shiftwidth=4 noexpandtab

NCURSES_DIR := $(shell brew --prefix ncurses)
CFLAGS := -I$(NCURSES_DIR)/include
SRCDIR := examples
BUILDDIR := $(SRCDIR)/build
SRCS := $(wildcard $(SRCDIR)/*.c)
EXES := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%, $(SRCS))

$(BUILDDIR)/%: $(SRCDIR)/%.c
	mkdir -p ./examples/build
	gcc $(CFLAGS) -o $@ $< -L$(NCURSES_DIR)/lib -lncurses -lpanel -lmenu

$(BUILDDIR): $(EXES) 
all: $(BUILDDIR)

clean:
	rm -rf ./examples/build

