#ifndef JUNCTION_ID_H
#define JUNCTION_ID_H

typedef enum {
    JUNC_END,
    JUNC_LEFT,
    JUNC_RIGHT,
    JUNC_T,
} JUNC_types_e;

JUNC_types_e JUNC_identify();

#endif