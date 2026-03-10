# MP3 Tag Reader

This is a simple C-based MP3 Tag Reader application that allows users to read and edit metadata stored in MP3 files.
I created this project to practice modular programming in C, file handling, and working with binary file formats.

MP3 files contain metadata called ID3 tags, which store information such as the song title, artist, album, and year.
This application reads those tags from an MP3 file and also allows users to modify them.


# Features
- Read metadata from MP3 files
- Display details such as title, artist, album, year, genre, and comments
- Edit existing MP3 tag information
- Uses ID3 tag format for metadata handling
- Modular implementation using multiple source and header files


# Project Structure
MP3-Tag-Reader/
├── main.c        # Entry point of the program
├── read.c        # Functions to read MP3 tag information
├── edit.c        # Functions to edit MP3 tag information
├── read.h        # Header file for read operations
├── edit.h        # Header file for edit operations
├── types.h       # Structure definitions
└── sample.mp3    # Sample MP3 file used for testing


# Compilation and Execution
To compile and run the program using GCC:

```bash
gcc main.c read.c edit.c -o mp3tagreader
./mp3tagreader sample.mp3
