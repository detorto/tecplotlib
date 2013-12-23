OUT = lib/libtecplotlib.so

CC = gcc

LDFLAGS += -shared
CFLAGS=-c -Wall -fPIC -std=c++11 -lz


ODIR = obj
SDIR = src

INCLUDES =./include


_OBJS = TecplotVar.o \
		TecplotZone.o \
		TecplotFile.o \
		TecplotParser.o \
		TecplotData.o \
		Utils.o \
		MglTecplotDrawer.o \
		gzstream.o \




OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))


$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(INCLUDES) -o $@  $<

$(OUT): $(OBJS)
	$(CC) $(LDFLAGS) $(CPPFLAGS) -I$(INCLUDES) -o $@ $^

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(OUT)



