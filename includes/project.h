#ifndef _PROJECT_H
#define _PROJECT_H

typedef enum { typeCon, typeStr, typeId, typeOpr, typeTyp } nodeEnum;

typedef enum { voidTyp, intTyp, stringTyp, floatTyp } cTyp;

typedef enum {TRANS_UNIT, FUNC_DEF, FUNC_DEC, COMP_STAT, STAT_LIST, RET, POST_EXP, ARG_EXP_LIST, HEAD} oper_types; 

#define STRING_MAX_SIZE 256

typedef char stringT[STRING_MAX_SIZE];

typedef struct {
    stringT s;
} strNodeType;

/* constants */
typedef struct {
    int value;
} conNodeType;

/* identifiers */
typedef struct {
    int i;                      /* subscript to sym array */
} idNodeType;

/* operators */
typedef struct {
    oper_types oper;                   /* operator */
    int nops;                   /* number of operands */
    struct nodeTypeTag **op;	/* operands, extended at runtime */
} oprNodeType;

/* type */
typedef struct {
    cTyp t;                   /* operator */
} typNodeType;

typedef struct nodeTypeTag {
    nodeEnum type;              /* type of node */

    union {
        strNodeType str;
        conNodeType con;        /* constants */
        idNodeType ide;          /* identifiers */
        oprNodeType opr;        /* operators */
        typNodeType typ;
    };
} nodeType;

extern int sym[26];

#endif