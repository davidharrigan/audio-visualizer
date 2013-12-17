/**
 *
 *
 *
 *
 */
#include "makeShader.h"
#include <sys/stat.h>

static char* readShaderSource(const char* shaderFile) {
    struct stat filestatus;
    stat(shaderFile, &filestatus);

    long size = filestatus.st_size;
    FILE* fp = fopen(shaderFile, "r");
    if (fp == NULL)
        return NULL;

    char* buf = new char[size +1];
    fread(buf, 1, size, fp);
    buf[size] = '\0';
    fclose(fp);
    return buf;
}

GLuint makeShader(const char* fileName, GLenum sType) {
    GLchar* source = readShaderSource(fileName);
    if (source == NULL) {
        fprintf(stderr, "Failed to load %s\n", fileName);
        exit(EXIT_FAILURE);
    }
    GLuint shader = glCreateShader(sType);

    glShaderSource(shader, 1, (const GLchar**) &source, NULL);
    glCompileShader(shader);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        fprintf(stderr, "Failed to compile %s\n", fileName);
        exit(EXIT_FAILURE);
    }

    delete [] source;
    return shader;
}

GLuint makeShaderProgram(const char* vShaderFile,
                         const char* fShaderFile) {
    GLuint program = glCreateProgram();
    GLuint vShader = makeShader(vShaderFile, GL_VERTEX_SHADER);
    GLuint fShader = makeShader(fShaderFile, GL_FRAGMENT_SHADER);

    glAttachShader(program, vShader);
    glAttachShader(program, fShader);

    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (!linked) {
        fprintf(stderr, "Failed to link shader programs");
        exit(EXIT_FAILURE);
    }

    glDetachShader(program, vShader);
    glDetachShader(program, fShader);

    return program;
}


