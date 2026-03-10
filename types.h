#ifndef TYPES_H
#define TYPES_H

/* User defined types */
typedef unsigned int uint;

/* Status will be used in fn. return type */
typedef enum
{
    e_success, //0
    e_failure  //-1 value
} Status;

typedef enum
{
    e_edit,
    e_read,
    e_unsupported
} OperationType;

#endif
