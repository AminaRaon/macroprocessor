//
// Created by aminaraon on 09.10.2023.
//

#include "macro.h"

bool expanding = false;

NAMETAB_elem *NAMETAB = NULL;
DEFTAB_elem *DEFTAB = NULL;
ARGTAB_elem *ARGTAB = NULL;

int max_size_deftab = 0, curr_size_deftab = 0;
int max_size_nametab = 0, curr_size_nametab = 0;
int max_size_argtab = 0, curr_size_argtab = 0;

char str[256];
char *string = NULL;

void replaceSubstring(const char *old, const char *new) {
    char *pos = strstr(string, old);
    if (pos != NULL) {
        int len_old = strlen(old);
        int len_new = strlen(new);
        if (len_new != len_old) {
            memmove(pos + len_new, pos + len_old, strlen(pos + len_old) + 1);
        }
        memcpy(pos, new, len_new);
    }
}


void macro_processor(FILE *receives, FILE *answer) {
    get_line(receives);
    while (string != NULL) {
        process_line(receives, answer);
        get_line(receives);
    }

    for (int i = 0; i < max_size_deftab - 1; i++) {
        free(DEFTAB[i].definition_macro);
    }
    free(DEFTAB);

    for (int i = 0; i < max_size_nametab - 1; i++) {
        free(NAMETAB[i].name_macro);
    }
    free(NAMETAB);
}

void process_line(FILE *receives, FILE *answer) {
    char *str_copy = (char *) malloc(sizeof(str));

    strcpy(str_copy, string);
    int index = find_in_nametab(strtok(str_copy, " :,"));
    free(str_copy);

    if (index != -1) {
        expand(index, receives, answer);
    } else if (!expanding && strstr(string, "macro")) {
        define(receives);
    } else {
        fprintf(answer, "%s", string);
    }
}

void define(FILE *receives) {
    char *str_copy = (char *) malloc(sizeof(str));

    strcpy(str_copy, string);
    NAMETAB_elem nametab_elem = create_nametab_elem(strtok(str_copy, " :,"));
    free(str_copy);

    add_deftab_elem(create_deftab_elem(string));
    int start_index_macro = curr_size_deftab;

    int level = 1;
    while (level > 0) {
        get_line(receives);
        add_deftab_elem(create_deftab_elem(string));
        if (strstr(string, "macro")) {
            level += 1;
        } else if (strstr(string, "endm")) {
            level -= 1;
        }
    }

    nametab_elem.begin_macro = start_index_macro;
    nametab_elem.end_macro = curr_size_deftab;

    add_nametab_elem(nametab_elem);
}

void expand(int index, FILE *receives, FILE *answer) {
    expanding = true;

    int begin = NAMETAB[index].begin_macro;
    int end = NAMETAB[index].end_macro;

    char *str_copy = (char *) malloc(strlen(DEFTAB[begin - 1].definition_macro));
    strcpy(str_copy, DEFTAB[begin - 1].definition_macro);
    char *token = strtok(str_copy, " ,:\n");

    while (token != NULL) {
        if (token[0] == '&') {
            add_argtab_elem(create_argtab_elem(token));
        }
        token = strtok(NULL, " ,:\n");
    }

    str_copy = (char *) malloc(strlen(string));
    strcpy(str_copy, string);

    token = strtok(str_copy, " ,:\n");
    token = strtok(NULL, " ,:\n");
    int j = 0;

    while (token != NULL && j <= curr_size_argtab) {

        ARGTAB[j].value = (char *) malloc(strlen(token));
        strcpy(ARGTAB[j].value, token);
        token = strtok(NULL, " ,:\n");
        j++;
    }
    free(str_copy);

    for (int i = begin; i < end - 1; i++) {
        string = DEFTAB[i].definition_macro;
        get_line(receives);
        process_line(receives, answer);
    }

    for (int i = 0; i < max_size_argtab - 1; i++) {
        free(ARGTAB[i].key);
        free(ARGTAB[i].value);
    }
    free(ARGTAB);
    ARGTAB = NULL;
    expanding = false;
}

void get_line(FILE *receives) {
    if (expanding) {
        for (int i = 0; i < curr_size_argtab; i++) {
            while (strstr(string, ARGTAB[i].key)) {
                replaceSubstring(ARGTAB[i].key, ARGTAB[i].value);
            }
        }
    } else {
        string = fgets(str, sizeof(str), receives);
    }
}

int find_in_nametab(char *name) {
    for (int i = 0; i < curr_size_nametab; i++) {
        if (strcmp(NAMETAB[i].name_macro, name) == 0) {
            return i;
        }
    }
    return -1;
}

void add_nametab_elem(NAMETAB_elem newElem) {
    if (curr_size_nametab == max_size_nametab) {
        max_size_nametab = (max_size_nametab == 0) ? 1 : curr_size_nametab * 2;
        NAMETAB = realloc(NAMETAB, max_size_nametab * sizeof(NAMETAB_elem));
    }
    NAMETAB[curr_size_nametab++] = newElem;
}

void add_deftab_elem(DEFTAB_elem newElem) {
    if (curr_size_deftab == max_size_deftab) {
        max_size_deftab = (max_size_deftab == 0) ? 1 : curr_size_deftab * 2;
        DEFTAB = realloc(DEFTAB, max_size_deftab * sizeof(DEFTAB_elem));
    }
    DEFTAB[curr_size_deftab++] = newElem;

}

void add_argtab_elem(ARGTAB_elem newElem) {
    if (curr_size_argtab == max_size_argtab) {
        max_size_argtab = (max_size_argtab == 0) ? 1 : curr_size_argtab * 2;
        ARGTAB = realloc(ARGTAB, max_size_argtab * sizeof(ARGTAB_elem));
    }
    ARGTAB[curr_size_argtab++] = newElem;
}

