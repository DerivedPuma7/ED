#ifndef MYSTRUCT_H
#define MYSTRUCT_H

struct Dados {
    unsigned int id;
    char time[16];
    char source[39];
    char destination[32];
    char protocol[13];
    int length;
    char info[1306];
};

#endif