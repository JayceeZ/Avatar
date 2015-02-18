#include "avatar.h"
#include "gl_objects.h"
#include <iostream>

#define SDL_VIDEO_MODE_OPTIONS (SDL_RESIZABLE | SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)
#define SDL_DEPTH 32

#define SCENE_ROTATION_STEP 5
#define CAMERA_Z_OFFSET 2
#define CAMERA_TRANSLATION_STEP 0.1

#define RDR_FRAME_LENGTH 1
#define RDR_CUBE_HALF_SIDE 0.5

CAvatar::CAvatar() {
    should_be_running = false;
    needs_rendering = true;
    window_width = 0;
    window_height = 0;
    window_title = "";

    world_origin_x = 0;
    world_origin_y = 0;
    world_origin_z = 0;

    camera_aspect_ratio = 0;
    camera_fovy = 0;

    camera_tx = 0;
    camera_ty = 0;
    camera_tz = 0;

    camera_min_z = 0;
    camera_max_z = 0;

    camera_min_tz = 0;
}

CAvatar::~CAvatar() {}

int CAvatar::OnExecute() {
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event event;
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    should_be_running = true; 
    needs_rendering = true;

    while(should_be_running) {
        while(SDL_PollEvent(&event)) {
            //OnEvent(&event);
        }
        OnLoop();
        OnRender();
    }
    OnCleanup();

    return 0;
}

bool CAvatar::OnInit()
{
    char sdl_wdw_pos[] = "SDL_VIDEO_WINDOW_POS";
    char sdl_wdw_ctr[] = "SDL_VIDEO_CENTERED=1";
    putenv(sdl_wdw_pos);
    putenv(sdl_wdw_ctr);

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    window_width = 640;
    window_height = 480;
    window_title = "Avatar Main Window";

    SDL_WM_SetCaption(window_title, 0);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
/*
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,8);
*/
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);


    sdl_pimage = SDL_SetVideoMode(window_width, window_height, SDL_DEPTH, SDL_VIDEO_MODE_OPTIONS);

    if(sdl_pimage == NULL) {
        return false;
    }
    return true;

    glClearColor(0,0,0,0);
    glViewport(0,0,window_width, window_height);

    camera_aspect_ratio = ((float) window_width) / ((float) window_height);
    camera_min_z = 0.1;
    camera_max_z = 10;
    camera_fovy = 60;

    InitProjectionMatrix();
}

void CAvatar::InitProjectionMatrix() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(camera_fovy, camera_aspect_ratio, camera_min_z, camera_max_z);
}

void CAvatar::OnCleanup() {
    if(sdl_pimage)
        SDL_FreeSurface(sdl_pimage);
    SDL_Quit();
}

void CAvatar::OnLoop()
{

}

void CAvatar::OnRender()
{
    if(!needs_rendering)
        return;
    needs_rendering = false;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    GLfloat scaling[] = {1, 0, 0, 0,
                         0, 1.5, 0, 0,
                         0, 0, 1, 0,
                         0, 0, 0, 1};

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-camera_tx, -camera_ty, -camera_tz);
    glRotatef(world_rx, 1, 0, 0);
    glRotatef(world_ry, 0, 1, 0);
    glMultMatrixf(scaling);

    DrawFrame(world_origin_x, world_origin_y, world_origin_z, RDR_FRAME_LENGTH);
    DrawCube(world_origin_x, world_origin_y, world_origin_z, RDR_CUBE_HALF_SIDE);

    SDL_GL_SwapBuffers();
}

void CAvatar::OnEvent(SDL_Event*) {
    return;
}

void CAvatar::InitSceneConstants() {
    world_rx = 0;
    world_ry = 0;

    camera_min_tz = world_origin_z + CAMERA_Z_OFFSET;
    camera_tx = world_origin_x;
    camera_ty = world_origin_y;
    camera_tz = camera_min_tz;
}
