#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include <fstream>
#include <ctime> 

#include <cstdio>
#include <cstdlib>

typedef enum {
    r,
    w,
    rw
} fileMode;

class FileProcessor {
public:
    FileProcessor(char*, fileMode);
    ~FileProcessor();
    void open(char*, fileMode);
    void close();
    void write(double);
    void getline(int);
    void updateBuffer();
    void print();
private:

    FILE* file;   
    char* fname;
    fileMode fmode;
    char* buffer;
    int length;
};  

#endif
