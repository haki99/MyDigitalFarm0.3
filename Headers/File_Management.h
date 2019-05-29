#ifndef FILE_MANAGEMENT_H_INCLUDED
#include "Header.h"
#define FILE_MANAGEMENT_H_INCLUDED

//!FileManagement.c
//!Log keszito fuggvenyek
void logfile();
void writelog(char *tomb);
void SDLwritelog(char *tomb);
void logfileclose();
void Mentes(Field *mezo, Ido *noves, int nevhossz, char *jatekosnev, int fieldx, int fieldy);

#endif // FILE_MANAGEMENT_H_INCLUDED
