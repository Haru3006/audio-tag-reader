#include <stdio.h>
#include "edit.h"
#include "read.h"
#include "types.h"
#include<string.h>

int main(int argc, char *argv[])
{
    ReadInfo readInfo;
    EditInfo editInfo;
    int ret = check_operation_type(argv);
    
    if(ret == e_unsupported)
    {
        printf("Error: INVALID ARGUMENTS\n");
        return 0;
    }

    if(ret == e_read)
    {
        printf("Reading....\n");
        //read
        Status ret = read_and_validate_read_args(argv, &readInfo);
        if(ret == e_failure)
        {
            printf("INVALID ARGUMENTS\n");
            return 0;
        }
        ret = do_reading(&readInfo);
        if(ret == e_failure)
        {
            printf("Reading failed\n");
            return 0;
        }
        else
        {
            printf("Reading successfull\n");
            return 0;
        }
        return e_success;
    }

    if(ret ==  e_edit)
    {
        //edit
        printf("Editing.......\n");
        Status ret = read_and_validate_edit_args(argv, &editInfo);
        if(ret == e_failure)
        {
            printf("INVALID ARGUMENTS\n");
            return 0;
        }
        ret = do_editing(&editInfo);
         if(ret == e_failure)
        {
            printf("Editing failed\n");
            return 0;
        }
        else
        {
            printf("Editing successfull\n");
            return 0;
        }
        return e_success;
    }
}

OperationType check_operation_type(char *argv[])
{
    if(argv[1] == NULL)
    {
        return e_unsupported;
    }
    if (strcmp(argv[1], "-r") == 0)
    {
        return e_read;
    }
    if (strcmp(argv[1], "-e") == 0)
    {
        return e_edit;
    }
     else
    {
        return e_unsupported;
    }
}