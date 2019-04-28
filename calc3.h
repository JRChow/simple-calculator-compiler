#include "uthash.h"

typedef enum { typeCon, typeId, typeOpr } nodeEnum;
typedef enum { typeInt, typeChr, typeStr } dataEnum;
typedef enum { typeLocal, typeGlobal } scopeEnum;

/* Constants */
typedef struct {
    dataEnum dataType; /* Type of data (can be null) */
    union {
        int iVal;    /* Int value    */
        char cVal;   /* Char value   */
        char* sVal;  /* String value */
    };
} ConstNode;

/* Variables */
typedef struct {
    char name[13];      /* Key: name of variable */
    dataEnum dataType;
    scopeEnum scope;
    int idx;            /* Subscript to pointer */
    UT_hash_handle hh;  /* Make this struct hashable */
} VarNode;

/* Operators */
typedef struct {
  int                 oper;     /* Operator */
  int                 nops;     /* Number of operands */
  struct nodeTypeTag *op[1];    /* Operands (expandable) */
} OprNode;

typedef struct nodeTypeTag {
  nodeEnum nodeType; /* Type of node */
  dataEnum dataType; /* Type of data (can be null) */

  /* Union must be last entry in nodeType          */
  /* because operNodeType may dynamically increase */
  union {
    ConstNode con; /* Constants   */
    VarNode  id;   /* Variables */
    OprNode opr;   /* Operators   */
  };
} Node;

/* ---------------------------------------------- */

/* Hash table unit */
//typedef struct {
    //char name[13];  [> Key (maximum 12 characters) <]
    //dataEnum dataType;
    //scopeEnum scope;
    //int idx;  [> Subscript to pointer <]
    //UT_hash_handle hh;  [> Make this struct hashable <]
//} varInfo;

//extern int sym[26];
extern VarNode* sym;  /* Hash table */
