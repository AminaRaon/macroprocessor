#ifndef LABA4_MACRO_H
#define LABA4_MACRO_H

#include "macro_datastructures.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

extern bool expanding;

extern NAMETAB_elem *NAMETAB;
extern DEFTAB_elem *DEFTAB;
extern ARGTAB_elem *ARGTAB;

extern int max_size_deftab, curr_size_deftab;
extern int max_size_nametab, curr_size_nametab;
extern int max_size_argtab, curr_size_argtab;

extern void macro_processor(FILE *receives, FILE *answer);
extern void process_line(FILE *receives, FILE *answer);
extern void define(FILE *receives);
extern void expand(int index, FILE *receives, FILE *answer);
extern void get_line(FILE *receives);

extern void add_deftab_elem(DEFTAB_elem newElem);
extern void add_nametab_elem(NAMETAB_elem newElem);
extern void add_argtab_elem(ARGTAB_elem newElem);

extern int find_in_nametab(char *name);


#endif //LABA4_MACRO_H
