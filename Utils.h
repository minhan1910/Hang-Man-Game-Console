
#ifndef __UTILS_H__
#define __UTILS_H__


const int IGNORE_CHARS = 256;

char GetCharacter(const char*, const char*);
char GetCharacter(const char*, const char*, const char[], int);

void ClearScreen();

void WaitForKeyPress();

#endif

