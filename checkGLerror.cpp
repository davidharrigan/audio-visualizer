/**
 * checkGLerror.cpp - checks and prints OpenGL errors
 *
 */

#include "opengl.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>

int checkGLerror(const char* src, bool endit = false) {
    int errCount = 0;
    GLuint gle = glGetError();
    
    while (gle != GL_NO_ERROR) {
        std::stringstream msg;
        msg << "**** GL ERROR **** " << src <<": ";
        
        switch (gle) {
            case GL_INVALID_ENUM: 
                msg << "Invalid enum"; 
                break;
            case GL_INVALID_VALUE:
                msg << "Invalid value";
                break;
            case GL_INVALID_OPERATION:
                msg << "Invalid operation";
                break;
            case GL_OUT_OF_MEMORY:
                msg << "Out of memory";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                msg << "Bad framebuffer operation";
                break;
        }
        std::cerr << msg.str() << std::endl;
        errCount++;
        gle = glGetError();
    }

    if (errCount > 0 && endit)
        exit(gle);
    return errCount;
}

