#ifndef EDIT_H
#define EDIT_H

#include "types.h"   

typedef struct EditInfo
{
    char *tag;           
    char *new_data;     
    char *audio_fname;   

    FILE *fptr_audio;    
    FILE *fptr_temp;    
} EditInfo;



Status read_and_validate_edit_args(char *argv[], EditInfo *editInfo);


Status do_editing(EditInfo *editInfo);


Status open_edit_files(EditInfo *editInfo);

Status copy_header(EditInfo *editInfo);


Status read_frame_header(char *frame_id, int *size, char *flags, EditInfo *editInfo);


void int_to_bigendian(int size, unsigned char *buffer);


Status edit_frames(EditInfo *editInfo);

#endif