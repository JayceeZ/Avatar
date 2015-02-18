#ifndef _AVATAR_H_
#define _AVATAR_H_

#include <SDL/SDL.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

class CAvatar
{

bool should_be_running;
bool needs_rendering;
int window_width;
int window_height;
const char* window_title;

float world_origin_x;
float world_origin_y;
float world_origin_z;
float world_rx;
float world_ry;

float camera_aspect_ratio;

float camera_min_tz;
float camera_min_z;
float camera_max_z;

float camera_fovy;

float camera_tx;
float camera_ty;
float camera_tz;

void InitProjectionMatrix();

SDL_Surface* sdl_pimage;

public:
    CAvatar();
    ~CAvatar();
    int OnExecute();

    bool OnInit();

    void OnCleanup();
    void OnLoop();
    void OnRender();

    void OnEvent(SDL_Event*);

    void InitSceneConstants();
};

#endif
