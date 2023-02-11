#ifndef MYSTRUCT_H
#define MYSTRUCT_H

struct SubnationalPeriodLifeTables
{
    int id;
    char measure[256];
    float quantile;
    char area[256];
    char sex[255];
    char age[255];
    char geography[255];
    char ethnic[255];
    float value;
};

#endif