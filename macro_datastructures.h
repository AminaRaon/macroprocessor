#ifndef LABA4_MACRO_DATASTRUCTURES_H
#define LABA4_MACRO_DATASTRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *definition_macro;
} DEFTAB_elem;

typedef struct {
    char *key;
    char *value;
} ARGTAB_elem;

typedef struct {
    char *name_macro;
    int begin_macro;
    int end_macro;
} NAMETAB_elem;

NAMETAB_elem create_nametab_elem(const char *name);

ARGTAB_elem create_argtab_elem(const char *key);

DEFTAB_elem create_deftab_elem(const char *definition);

#endif //LABA4_MACRO_DATASTRUCTURES_H
