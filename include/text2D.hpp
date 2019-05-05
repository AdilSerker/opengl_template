#ifndef TEXT2D_HPP
#define TEXT2D_HPP

#include <string>

void initText2D(const char * texturePath);
void printText2D(const char * text, int x, int y, int size);
void cleanupText2D();
void printg(std::string info, int value, int y);

#endif