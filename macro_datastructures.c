#include "macro_datastructures.h"

NAMETAB_elem create_nametab_elem(const char *name) {

    NAMETAB_elem newElem;

    newElem.name_macro = (char *) malloc(strlen(name));
    strcpy(newElem.name_macro, name);
    newElem.begin_macro = 0;
    newElem.end_macro = 0;

    return newElem;
}


DEFTAB_elem create_deftab_elem(const char *definition) {
    DEFTAB_elem newElem;

    newElem.definition_macro = (char *) malloc(strlen(definition));
    strcpy(newElem.definition_macro, definition);

    return newElem;
}

ARGTAB_elem create_argtab_elem(const char *key) {
    ARGTAB_elem newElem;

    newElem.key = (char *) malloc(strlen(key));
    strcpy(newElem.key, key);

    return newElem;
}