MDIR=map
LDIR=lib
ODIR=obj
BDIR=.

TESTS=$(BDIR)/mittest
MAPS=$(MDIR)/vmap $(MDIR)/simap $(MDIR)/ismap
MOUT=$(LDIR)/vmap.? $(LDIR)/simap.? $(LDIR)/ismap.?

OBJS=$(ODIR)/map_util.o

LDFLAGS=
CFLAGS=-std=c99 -D_BSD_SOURCE
CFLAGS+=-pedantic -Wall -Wextra
CFLAGS+=-I$(LDIR)

ifndef RELEASE
CFLAGS+=-g
else
CFLAGS+=-O3 -Os
endif

ifdef PROFILE
CFLAGS+=-pg
LDFLAGS+=-pg
endif

all: dirs maps tests
maps:    $(MAPS)
modules: $(MODULES)
tests:   $(TESTS)
dirs:
	mkdir -p $(MDIR) $(LDIR) $(ODIR) $(BDIR)

# make rules for the tests
$(BDIR)/mittest: $(ODIR)/mittest.o $(ODIR)/map_util.o $(ODIR)/ismap.o
	$(CC) $(LDFLAGS) -o $@ $^

$(ODIR)/%.o: $(LDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(ODIR)/%.o: test/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

map/%: map/%.def map/%.dec map/%.def
	$(BDIR)/mstruct.sh $< map $(LDIR)

clean:
	rm -f $(ODIR)/*.o $(TESTS) $(MOUT)

