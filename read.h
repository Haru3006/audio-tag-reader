#ifndef READ_H
#define READ_H

#include "types.h"
#include <stdio.h>

typedef struct _ReadInfo
{
    char *src_mp3_name;
    FILE *fptr_src_mp3;
}ReadInfo;

OperationType check_operation_type(char *argv[]);

Status read_and_validate_read_args(char *argv[], ReadInfo *readInfo);

Status open_files(ReadInfo *readInfo);

void skip_header(FILE *fptr_src_mp3);

Status do_reading(ReadInfo *readInfo);

Status read_tag(FILE *fptr_src_mp3,char *tag);

Status read_size(FILE *fptr_src_mp3, int *size);

Status read_tag_data(FILE *fptr_src_mp3, unsigned int size);

Status compare_tag(char *tag);

#endif