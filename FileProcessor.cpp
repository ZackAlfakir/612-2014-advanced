#include "FileProcessor.h"

/*
 * Constructor takes a filename and a mode
 * sets objects fname and fmode to given parameters
 * and opens a file according to the specifications
 * updates the buffer, which is a char array of the file's contents 
 * 
 * default file processing mode is read/write
 */

FileProcessor::FileProcessor(char* name, fileMode mode=rw) {
    open(name, mode);
}

/*
 * deletes the name of file and 
 * the buffer which holds the data of the file
 */ 

FileProcessor::~FileProcessor() {
    fclose(file);
}

/*
 * Essentially a mirror of the constructor in the case 
 * if a file is already open, close it, and let the function open another one
 * 
 * default file processing mode is read/write
 */

void FileProcessor::open(char* name, fileMode mode) {
    //if (file != 0) {
    //    fclose(file);
    //}
    fname = name;
    fmode = mode;
    switch(mode) {
        case r:
            file = fopen(fname, "r");
            break;
        case w:
            file = fopen(fname, "w");
            break;
        case rw:
            file = fopen(fname, "w+");
            break;
        default:
            file = fopen(fname, "w+");
    }
    //updateBuffer();
}

/*
 * uhh redundancy
 * 
 * actually this is in there because inheriting 
 * from fstream might be a pain
 * @anirudh if you know how to inherit from fstream
 * and have things not die
 * hmu
 * 
 */ 

void FileProcessor::close() {
    fclose(file);
}

/*
 * checks if the mode contains w, if not, nothing happens
 * writes current time and a specified val to file
 * updates the buffer
 */ 
void FileProcessor::write(char* str) {
    if (!(fmode == w || fmode == rw)) {
        return;
    }
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    char output[100];
    char* curtime = asctime (timeinfo); 
    curtime[24] = '\0';
    snprintf(output, 100, "%s: %s\n", curtime, str);
    
    fprintf(file, output);
    //updateBuffer();
}
