#ifndef _AVATAR_H_
#define _AVATAR_H_

#include <SDL/SDL.h>
#include "events.h"
#include "sensor.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

//! The Avatar Object Class
/*!
 * \brief The CAvatar class
 * allow users to create a virtual avatar.
 */

class CAvatar : public CEvent
{

private:
    bool should_be_running;  //!< Used to quit the infinite process loop
    bool mode_sensor;
    bool needs_rendering;    //!< Set to true when we want to rerender the object

    int window_width;        //!< Give the window width available to display the Avatar
    int window_height;       //!< Give the window height available to display the Avatar
    const char* window_title;//!< Title of the execution window displaying the Avatar

    float world_origin_x;    //!< Define the world origin x point value
    float world_origin_y;    //!< origin point y value
    float world_origin_z;    //!< origin point z value
    float world_rx;          //!< rotation to apply to x
    float world_ry;          //!< rotation to apply to y

    float camera_aspect_ratio;

    float camera_min_tz;
    float camera_min_z;     //!< limit
    float camera_max_z;

    float camera_fovy;

    float camera_tx;
    float camera_ty;
    float camera_tz;

    void SetPerspectiveProjectionMatrix();
    void SetOrthoProjectionMatrix();

    void InitModeDemo();
    void DrawDemo();

    void InitModeSensor();
    void DrawSensor();
    void SwitchDisplayStream();

    SDL_Surface* sdl_pimage;
    SDL_Surface* surface_test;
    SDL_Surface* surface_test2;

    GLuint texture_test_id;
    GLuint texture_test2_id;

    CSensor sensor;

public:
    CAvatar();
    ~CAvatar();
    int OnExecute(bool with_sensor);

    bool OnInit(bool with_sensor);

    void OnCleanup();
    void OnLoop();
    void OnRender();

    void OnEvent(SDL_Event* Event);
    void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

    void OnMouseWheel(bool Up, bool Down);
    void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);

    void OnResize(int w, int h);
    void OnExpose();
    void OnExit();

    void InitSceneConstants();
};

#endif
