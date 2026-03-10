#include "read.h"
#include "types.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Status open_files(ReadInfo *readInfo)
{
    readInfo->fptr_src_mp3 = fopen(readInfo->src_mp3_name, "r");
    if(readInfo->fptr_src_mp3 == NULL)
    {
        perror("fopen");
        fprintf(stderr,"ERROR: Unable to open file %s\n",readInfo->src_mp3_name);

        return e_failure;
    }
    return e_success;
}

Status read_and_validate_read_args(char *argv[], ReadInfo *readInfo)
{
    if(argv[2] == NULL)
    {
        printf("Error: .mp3 file not passed\n");
        return e_failure;
    }
    if(strstr(argv[2],".mp3") == NULL)
    {
        printf("Invalid song file name\n");
        return e_failure;
    }
    readInfo->src_mp3_name = argv[2];
    return e_success;
}

Status do_reading(ReadInfo *readInfo)
{
    Status ret;
    ret = open_files(readInfo);
    int size;
    char tag[5];
    skip_header(readInfo->fptr_src_mp3);	
	for(int i=0;i<6;i++)
    {
        read_tag(readInfo->fptr_src_mp3,tag);
        read_size(readInfo->fptr_src_mp3, &size);
        //printf("size:%d\n",size);
        fseek(readInfo->fptr_src_mp3,2,SEEK_CUR);
        if (compare_tag(tag) == e_success)
        {
            read_tag_data(readInfo->fptr_src_mp3, size);   
        }
        else
        {
            fseek(readInfo->fptr_src_mp3, size, SEEK_CUR);
            i--;   
        }
        fseek(readInfo->fptr_src_mp3,ftell(readInfo->fptr_src_mp3),SEEK_SET);
    }
    printf ("--------------------------\n");
    fclose (readInfo->fptr_src_mp3);				
    return e_success;
}

void skip_header(FILE *fptr_src_mp3)
{
    fseek(fptr_src_mp3, 10, SEEK_SET);
    printf("Skip: %ld\n",ftell(fptr_src_mp3));   
}

Status read_tag(FILE *fptr_src_mp3,char *tag)
{
    int i=0;
    fread(tag,1,4,fptr_src_mp3);
    tag[4]='\0';
    //printf("\n");
     return e_success;
}
Status read_size(FILE *fptr_src_mp3, int *size)
{
    unsigned char size_bytes[4];
    fread(size_bytes,4,1,fptr_src_mp3);
    *size = size_bytes[0]<<24 | size_bytes[1]<<16 | size_bytes[2]<<8 | size_bytes[3];
    return e_success;
}


Status read_tag_data(FILE *fptr_src_mp3, unsigned int size)
{
    char *data = malloc(size + 1);
    if (data == NULL)
    {
        printf("Memory allocation failed\n");
        return e_failure;
    }

    if (fread(data, size, 1, fptr_src_mp3) != 1)
    {
        printf("ERROR: Unable to read TAG DATA\n");
        free(data);
        return e_failure;
    }

    data[size] = '\0';
   
    if (data[0] == 0 || data[0] == 3)
    {
        printf("Tag Data: %s\n", data + 1);
    }
   
    else if (data[0] == 1)
    {
        printf("Tag Data: ");

        for (int i = 3; i < size; i += 2)
        {
            printf("%c", data[i]);
        }
        printf("\n");
    }

    printf("Offset after reading data: %ld\n", ftell(fptr_src_mp3));

    free(data);
    return e_success;
}

Status compare_tag(char *tag)
{
    char * tag_names[6] = {"TIT2","TALB","TYER","TCON","COMM","TPE1"};
    char* info [6] = {"Title name", "Artist name", "Album", "Year", "Content type", "Composer"};
    for(int i=0;i<6;i++)
    {
        if(strcmp(tag, tag_names[i])==0)
        {
            printf("TAG :%s\n",tag);
            return e_success;
        }
    }
    return e_failure;
}
