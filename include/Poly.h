#ifndef POLY_H
#define POLY_H

#include <GL/glew.h>
#include "GLSLProgram.h"

class Poly
{
    private:
    GLuint vao, vbo, ibo;
    GLSLProgram shader;
    
    void init();

    public:
    Poly();
    ~Poly();

    void draw();
};

#endif
