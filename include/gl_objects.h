#ifndef GL_OBJECTS_H
#define GL_OBJECTS_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

void DrawFrame(float origin_x, float origin_y, float origin_z, float frame_length);
void DrawCube(float origin_x, float origin_y, float origin_z, float half_side);
void DrawCube(float origin_x, float origin_y, float origin_z, float half_side, GLuint texture_ID);

void DrawAvatar(float origin_x, float origin_y, float origin_z, int shoulderTwist, int elbowTwist, int wristTwist, GLuint texture);
void DrawArm(float origin_x, float origin_y, float origin_z, int shoulderTwist, int elbowTwist, int wristTwist, bool mirror);
void DrawBody(float origin_x, float origin_y, float origin_z);
void DrawHead(float origin_x, float origin_y, float origin_z, GLuint texture);

void FillWindowWithTexture(GLuint texture_ID);

GLuint loadTexture();
GLuint Load2DTexture(GLsizei width, GLsizei height, int BytesPerPixel, const GLvoid* data);

void defineMaterialReflectionProperties();

#endif
