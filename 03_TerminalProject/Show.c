#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curses.h>

#define DX 3

typedef struct {
    size_t size;
    size_t alloced_size;
    char **buffer;
} StringArray;

int min(int a, int b) {
    return a < b ? a : b;
}

void PushBack(StringArray *array, char *str) {
    if (array->alloced_size <= array->size) {
        array->alloced_size *= 2;
        array->buffer = realloc(array->buffer, sizeof(*array->buffer) * array->alloced_size);
    }

    array->buffer[array->size] = malloc(sizeof(**array->buffer) * strlen(str) + 1);
    strcpy(array->buffer[array->size++], str);
}

void Destroy(StringArray *array) {
    for (int i = 0; i < array->size; i++) {
        free(array->buffer[i]);
    }

    free(array);
}

StringArray* Init() {
    StringArray *array = malloc(sizeof(StringArray));

    array->size = 0;
    array->alloced_size = 256;

    array->buffer = malloc(sizeof(*array->buffer) * array->alloced_size);

    return array;
}

StringArray *ReadFileAsLineArray(const char *filename) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    StringArray* array = Init();

    fp = fopen(filename, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        line[strlen(line) - 1] = '\0';
        PushBack(array, line);
    }

    fclose(fp);
    
    if (line)
        free(line);

    return array;
} 

int main (int argc, const char** argv)
{
    WINDOW *win;
    int c = 0;

    if (argc < 2) {
        printf("No file provided");

        return 1;
    }

    StringArray *text = ReadFileAsLineArray(argv[1]);

    initscr();
    noecho();
    cbreak();
    
    printw("File: %s; size: %d\n", argv[1], text->size);
    refresh();

    win = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
    keypad(win, TRUE);
    scrollok (win, TRUE);

    int current_top_line = 0;

    do {
        werase(win);
        
        wprintw(win, "");

        if (c == ' ' && current_top_line + LINES - 2 * DX < text->size) {
            current_top_line++;
        }

        int y = 2;
        for (int line = current_top_line; line < min(text->size, current_top_line + LINES - 2 * DX - 1); line++) {
            mvwprintw(win, y++, 1, "%3d: %s\n", line + 1, text->buffer[line]);
        }
        box(win, 0, 0);
        wrefresh(win);
    } while((c = wgetch(win)) != 27);

    Destroy(text);

    endwin();

    return 0;
}