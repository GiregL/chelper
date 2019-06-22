#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef char* string;

string create_path_to_project(string project_name);
void create_folder(string path);
string append_to_path(string path, string s);

int main(int argc, string* argv) {

    if (argc != 2) {
        fprintf(stderr, "Usage: chelper new <path>");
        return 1;
    }

    string full_path = create_path_to_project(argv[1]);
    string src_path = append_to_path(create_path_to_project(argv[1]), "src");
    string build_path = append_to_path(create_path_to_project(argv[1]), "build");
    string lib_path = append_to_path(create_path_to_project(argv[1]), "lib");

    create_folder(full_path);
    create_folder(src_path);
    create_folder(build_path);
    create_folder(lib_path);

    FILE * makefile;

    makefile = fopen(append_to_path(create_path_to_project(argv[1]), "Makefile"), "w");
    if (makefile == NULL) {
        fprintf(stderr, "Failed to create Makefile\n");
        return 1;
    }
    printf("Created Makefile\n");

    fprintf(makefile, "PROJECTNAME = %s\n", argv[1]);
    fprintf(makefile, "EXT = c\n"
                      "CXX = gcc\n"
                      "\n"
                      "CXXFLAGS = -Wall -Werror -W -pedantic -ansi\n"
                      "LDFLAGS = -I lib\n"
                      "\n"
                      "OBJDIR = build\n"
                      "SRC = $(wildcard *.$(EXT))\n"
                      "OBJ = $(SRC:.$(EXT)=.o)\n"
                      "OBJ := $(addprefix $(OBJDIR)/, $(OBJ))\n"
                      "\n"
                      "all: $(PROJECTNAME)\n"
                      "\n"
                      "$(PROJECTNAME): $(OBJ)\n"
                      "    @$(CXX) -o $@ $^ $(LDFLAGS)\n"
                      "\n"
                      "$(OBJDIR)/%.o: %.$(EXT)\n"
                      "    @$(CXX) -o $@ -c $< $(CXXFLAGS)\n"
                      "\n"
                      "clean:\n"
                      "    @rm -rf $(OBJDIR)/*.o\n"
                      "    @rm -f $(PROJECTNAME)\n"
                      "\n"
                      "install: $(PROJECTNAME)\n"
                      "    @cp $(PROJECTNAME) /usr/bin/");
    fclose(makefile);

    return 0;
}

string append_to_path(string path, string s) {
    string buffer = strcat(strcat(path, "/"), s);
    return buffer;
}

void create_folder(string path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
        printf("Created folder : %s\n", path);
    } else {
        fprintf(stderr, "Failed to create folder : %s\n", path);
    }
}

string create_path_to_project(string project_name) {
    string buffer = malloc(sizeof(char) * 255);
    buffer = getcwd(buffer, 255);
    buffer = strcat(buffer, "/");
    buffer = strcat(buffer, project_name);
    return buffer;
}