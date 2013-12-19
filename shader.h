#ifndef SHADER_H_
#define SHADER_H_

#define BUFFER_OFFSET(offset) ((GLvoid*) (offset))

GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif
