PROJECTNAME = qzdqzdqzd
EXT = c
CXX = gcc

CXXFLAGS = -Wall -Werror -W -pedantic -ansi
LDFLAGS = -I lib

OBJDIR = build
SRC = $(wildcard *.$(EXT))
OBJ = $(SRC:.$(EXT)=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))

all: $(PROJECTNAME)

$(PROJECTNAME): $(OBJ)
    @$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/: %.0$(EXT)
    @$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
    @rm -rf $(OBJDIR)/*.o
    @rm -f $(PROJECTNAME)

install: $(PROJECTNAME)
    @cp $(PROJECTNAME) /usr/bin/