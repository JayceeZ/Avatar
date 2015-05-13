#include "gl_objects.h"
#include "surface.h"

#include <GL/gl.h>
#include <iostream>
#include <vector>

#define TEST_TEXTURE "../images/companion_cube_face.bmp"

void DrawFrame(float origin_x, float origin_y, float origin_z, float frame_length) {
    glBegin(GL_LINES);
    // axe x
    glColor3f(1,0,0);
    glVertex3f(origin_x,origin_y,origin_z);
    glVertex3f(origin_x+frame_length, origin_y,origin_z);

    // axe y
    glColor3f(0,1,0);
    glVertex3f(origin_x, origin_y, origin_z);
    glVertex3f(origin_x, origin_y+frame_length, origin_z);

    // axe z
    glColor3f(0,0,1);
    glVertex3f(origin_x, origin_y, origin_z);
    glVertex3f(origin_x, origin_y, origin_z+frame_length);
    glEnd();
}

void DrawCube(float origin_x, float origin_y, float origin_z, float half_side)
{
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

void DrawCube(float origin_x, float origin_y, float origin_z, float half_side, GLuint texture_ID)
{
    //defineMaterialReflectionProperties();
    //glTexEnvi(GL_TEXTURE_2D, GL_2D, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glBegin(GL_QUADS);
        // front
        glNormal3f(0, 0, 1);
        glColor3f(1, 1, 1);
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

void DrawAvatar(float origin_x, float origin_y, float origin_z, int shoulderTwist, int elbowTwist, int wristTwist, GLuint texture) {
    DrawArm(origin_x-2, origin_y, origin_z, shoulderTwist, elbowTwist, wristTwist, false);
    DrawArm(origin_x+2, origin_y, origin_z, shoulderTwist, elbowTwist, wristTwist, true);
    DrawBody(origin_x, origin_y-2, origin_z);
    DrawHead(origin_x, origin_y+1, origin_z, texture);
}

void DrawBody(float origin_x, float origin_y, float origin_z) {
    glPushMatrix();
    glTranslatef(origin_x, origin_y, origin_z);
    glScalef(4, 4, 1);
    DrawCube(0, 0, 0, 0.5);
    glPopMatrix();
}

GLuint loadTexture() {
    SDL_Surface* surface_test;

    GLuint texture;

    if((surface_test = CSurface::OnLoad(TEST_TEXTURE)) == NULL) {
        std::cout << "Error loading texture " <<  TEST_TEXTURE << ", aborting texturing" << std::endl;
        return NULL;
    }
    texture = Load2DTexture(surface_test->w, surface_test->h, surface_test->format->BytesPerPixel, surface_test->pixels);

    return texture;
}

void DrawHead(float origin_x, float origin_y, float origin_z, GLuint texture) {
    // on met la matrice de calcul en cours de coté dans la pile
    glPushMatrix();
    glTranslatef(origin_x, origin_y, origin_z);
    glScalef(2, 2, 2);
    DrawCube(0, 0, 0, 0.5, texture);
    glPopMatrix();
    // on récupére notre précédente matrice

    // ceci a pour but de rendre totalement indépendants les calculs que nous ne voulont appliquer que sur notre cube
    // et éviter qu'ils ne s'appliquent au reste de nos objets puisques ces calculs n'ont pas été appliqué à la matrice mise de côté
}

void DrawArm(float origin_x, float origin_y, float origin_z, int shoulderTwist, int elbowTwist, int wristTwist, bool mirror) {
    int longueurMorceau = 2;
    glPushMatrix();
    glTranslatef(origin_x, origin_y, origin_z);

    // Dessin biceps
    glRotatef(shoulderTwist, -1, 0, 0);    // Rotation de l'épaule
    glTranslatef(0, -longueurMorceau/2, 0); // Translation pour rotation (l'épaule)

    glPushMatrix();
    glScalef(1, longueurMorceau, 1);
    DrawCube(0, 0, 0, 0.5);     // Dessiner cube à l'origine
    glPopMatrix();

    // Dessin avant bras
    glTranslatef(0, -longueurMorceau/2, 0); // Translation pour laisser la place au morceau suivant
    glRotatef(elbowTwist, -1, 0, 0);    // Rotation du coude
    glTranslatef(0, -longueurMorceau/2, 0); // Translation pour rotation (le coude)

    glPushMatrix();
    glScalef(1, longueurMorceau, 1);
    DrawCube(0, 0, 0, 0.5);     // Dessiner cube à l'origine
    glPopMatrix();

    // Dessin main
    float longueurMain = 1;
    glTranslatef(0, -longueurMorceau/2, 0); // Translation pour laisser la place au morceau suivant
    glRotatef(wristTwist, -1, 0, 0);    // Rotation de la main
    glTranslatef(0, -longueurMain/2, 0); // Translation pour rotation (le poignet)

    glScalef(1, 1, 0.5);
    DrawCube(0, 0, 0, 0.5);     // Dessiner cube à l'origine
    glPopMatrix();
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
    glGenTextures(1, &texture_ID); // on demande à opengl de nous donner (de reserver) un identifiant de texture
    glBindTexture(GL_TEXTURE_2D, texture_ID); // on dit d'associer cette texture au traitements en cours

    // pour certifier l'utilisabilité de cette texture (et la corriger si nécessaire)
    // on définie à cette texture des filtres d'interpolation linéaire de façon à corriger
    // des éventuels défauts de taille
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // enfin, on écrit les données de pixels sur cette texture
    int color_mode = (BytesPerPixel == 3 ? GL_RGB : GL_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, color_mode, width, height, 0, color_mode, GL_UNSIGNED_BYTE, data);

    return texture_ID;
}

void defineMaterialReflectionProperties() {
    // pour les reflets, on définie les propriétés de réflexion du matériaux
    // l'exemple ici est le bronze, ces valeurs n'ont pas été vérifiée
    float colorBronzeDiff[4] = { 0.8, 0.6, 0.0, 1.0 };
    float colorBronzeSpec[4] = { 1.0, 1.0, 0.4, 1.0 };
    GLfloat mat_emission[] = {0.1, 0.3, 0.2, 0.0};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
}

