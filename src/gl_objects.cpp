#include "gl_objects.h"
#include <GL/gl.h>

void DrawFrame(float origin_x, float origin_y, float origin_z, float frame_length) {
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(origin_x,origin_y,origin_z);
    glVertex3f(origin_x+frame_length, origin_y,origin_z);

    glColor3f(0,0,1);
    glVertex3f(origin_x, origin_y, origin_z);
    glVertex3f(origin_x, origin_y+frame_length, origin_z);

    glColor3f(0,0,1);
    glVertex3f(origin_x, origin_y, origin_z);
    glVertex3f(origin_x, origin_y, origin_z+frame_length);
    glEnd();
}

void DrawCube(float origin_x, float origin_y, float origin_z, float half_side)
{
    defineMaterialReflectionProperties();

    glBegin(GL_QUADS);
    // front
    glColor3f(0, 1, 0);
    glVertex3f(origin_x+half_side, origin_y-half_side, origin_z+half_side);
    glVertex3f(origin_x+half_side, origin_y+half_side, origin_z+half_side);
    glVertex3f(origin_x-half_side, origin_y+half_side, origin_z+half_side);
    glVertex3f(origin_x-half_side, origin_y-half_side, origin_z+half_side);
    // back
    glColor3f(0, 0.5, 0);
    glVertex3f(origin_x+half_side, origin_y+half_side, origin_z-half_side);
    glVertex3f(origin_x+half_side, origin_y-half_side, origin_z-half_side);
    glVertex3f(origin_x-half_side, origin_y-half_side, origin_z-half_side);
    glVertex3f(origin_x-half_side, origin_y+half_side, origin_z-half_side);
    // left
    glColor3f(0.5, 0, 0);
    glVertex3f(origin_x-half_side, origin_y-half_side, origin_z-half_side);
    glVertex3f(origin_x-half_side, origin_y+half_side, origin_z-half_side);
    glVertex3f(origin_x-half_side, origin_y+half_side, origin_z+half_side);
    glVertex3f(origin_x-half_side, origin_y-half_side, origin_z+half_side);
    // right
    glColor3f(1, 0, 0);
    glVertex3f(origin_x+half_side, origin_y+half_side, origin_z-half_side);
    glVertex3f(origin_x+half_side, origin_y+half_side, origin_z+half_side);
    glVertex3f(origin_x+half_side, origin_y-half_side, origin_z+half_side);
    glVertex3f(origin_x+half_side, origin_y-half_side, origin_z-half_side);
    // top
    glColor3f(0, 0, 1);
    glVertex3f(origin_x-half_side, origin_y+half_side, origin_z+half_side);
    glVertex3f(origin_x+half_side, origin_y+half_side, origin_z+half_side);
    glVertex3f(origin_x+half_side, origin_y+half_side, origin_z-half_side);
    glVertex3f(origin_x-half_side, origin_y+half_side, origin_z-half_side);
    // bottom
    glColor3f(0, 0, 0.5);
    glVertex3f(origin_x+half_side, origin_y-half_side, origin_z+half_side);
    glVertex3f(origin_x-half_side, origin_y-half_side, origin_z+half_side);
    glVertex3f(origin_x-half_side, origin_y-half_side, origin_z-half_side);
    glVertex3f(origin_x+half_side, origin_y-half_side, origin_z-half_side);
    glEnd();
}

void DrawCube(float origin_x, float origin_y, float origin_z, float half_side, GLuint texture_IDs[])
{
    defineMaterialReflectionProperties();

    //glTexEnvi(GL_TEXTURE_2D, GL_2D, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, texture_IDs[0]);
    glBegin(GL_QUADS);
        // front
        //glColor3f(1, 1, 1);
        glNormal3f(0, 0, 1);
        glTexCoord2f(1, 1);    // haut-droite
        glVertex3f(origin_x+half_side, origin_y-half_side, origin_z+half_side);
        glTexCoord2f(1, 0);    // bas-droite
        glVertex3f(origin_x+half_side, origin_y+half_side, origin_z+half_side);
        glTexCoord2f(0, 0);    // bas-gauche
        glVertex3f(origin_x-half_side, origin_y+half_side, origin_z+half_side);
        glTexCoord2f(0, 1);    // haut-gauche
        glVertex3f(origin_x-half_side, origin_y-half_side, origin_z+half_side);

        // back
        glNormal3f(0, 0, -1);
        glColor3f(1, 1, 1);
        glTexCoord2f(0, 0);
        glVertex3f(origin_x+half_side, origin_y+half_side, origin_z-half_side);
        glTexCoord2f(0, 1);
        glVertex3f(origin_x+half_side, origin_y-half_side, origin_z-half_side);
        glTexCoord2f(1, 1);
        glVertex3f(origin_x-half_side, origin_y-half_side, origin_z-half_side);
        glTexCoord2f(1, 0);
        glVertex3f(origin_x-half_side, origin_y+half_side, origin_z-half_side);

        // left
        glNormal3f(-1, 0, 0);
        glColor3f(1, 1, 1);
        glTexCoord2f(1, 1);
        glVertex3f(origin_x-half_side, origin_y-half_side, origin_z-half_side);
        glTexCoord2f(1, 0);
        glVertex3f(origin_x-half_side, origin_y+half_side, origin_z-half_side);
        glTexCoord2f(0, 0);
        glVertex3f(origin_x-half_side, origin_y+half_side, origin_z+half_side);
        glTexCoord2f(0, 1);
        glVertex3f(origin_x-half_side, origin_y-half_side, origin_z+half_side);

        // right
        glNormal3f(1, 0, 0);
        glColor3f(1, 1, 1);
        glTexCoord2f(1, 0);
        glVertex3f(origin_x+half_side, origin_y+half_side, origin_z-half_side);
        glTexCoord2f(0, 0);
        glVertex3f(origin_x+half_side, origin_y+half_side, origin_z+half_side);
        glTexCoord2f(0, 1);
        glVertex3f(origin_x+half_side, origin_y-half_side, origin_z+half_side);
        glTexCoord2f(1, 1);
        glVertex3f(origin_x+half_side, origin_y-half_side, origin_z-half_side);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture_IDs[1]);

    glBegin(GL_QUADS);

        // top
        glNormal3f(0, 1, 0);
        glColor3f(1, 1, 1);
        glTexCoord2f(1, 0);
        glVertex3f(origin_x-half_side, origin_y+half_side, origin_z+half_side);
        glTexCoord2f(0, 0);
        glVertex3f(origin_x+half_side, origin_y+half_side, origin_z+half_side);
        glTexCoord2f(0, 1);
        glVertex3f(origin_x+half_side, origin_y+half_side, origin_z-half_side);
        glTexCoord2f(1, 1);
        glVertex3f(origin_x-half_side, origin_y+half_side, origin_z-half_side);

        // bottom
        glNormal3f(0, -1, 0);
        glColor3f(1, 1, 1);
        glTexCoord2f(1, 0);
        glVertex3f(origin_x+half_side, origin_y-half_side, origin_z+half_side);
        glTexCoord2f(0, 0);
        glVertex3f(origin_x-half_side, origin_y-half_side, origin_z+half_side);
        glTexCoord2f(0, 1);
        glVertex3f(origin_x-half_side, origin_y-half_side, origin_z-half_side);
        glTexCoord2f(1, 1);
        glVertex3f(origin_x+half_side, origin_y-half_side, origin_z-half_side);
    glEnd();
}

void FillWindowWithTexture(GLuint texture_ID) {
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glBegin(GL_QUADS);
        // front
        //glColor3f(1, 1, 1);
        //glNormal3f(0, 0, 1);
        glTexCoord2f(1, 1);
        glVertex2f(0, 0);      // bas-gauche
        glTexCoord2f(0, 1);
        glVertex2f(1, 0);      // bas-droite
        glTexCoord2f(0, 0);
        glVertex2f(1, 1);      // haut-droite
        glTexCoord2f(1, 0);
        glVertex2f(0, 1);      // haut-gauche
    glEnd();
}

GLuint Load2DTexture(GLsizei width, GLsizei height, int BytesPerPixel, const GLvoid* data) {
    GLuint texture_ID;
    glGenTextures(1, &texture_ID);
    glBindTexture(GL_TEXTURE_2D, texture_ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int color_mode = (BytesPerPixel == 3 ? GL_RGB : GL_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, color_mode, width, height, 0, color_mode, GL_UNSIGNED_BYTE, data);

    return texture_ID;
}

void defineMaterialReflectionProperties() {
    float colorBronzeDiff[4] = { 0.8, 0.6, 0.0, 1.0 };
    float colorBronzeSpec[4] = { 1.0, 1.0, 0.4, 1.0 };
    GLfloat mat_emission[] = {0.1, 0.3, 0.2, 0.0};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
}

