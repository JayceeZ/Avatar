#ifndef GL_OBJECTS_H
#define GL_OBJECTS_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

void DrawFrame(float origin_x, float origin_y, float origin_z, float frame_length);
void DrawCube(float origin_x, float origin_y, float origin_z, float half_side);
void DrawCube(float origin_x, float origin_y, float origin_z, float half_side, GLuint texture_IDs[]);

void FillWindowWithTexture(GLuint texture_ID);

GLuint Load2DTexture(GLsizei width, GLsizei height, int BytesPerPixel, const GLvoid* data);

void defineMaterialReflectionProperties();

#endif
