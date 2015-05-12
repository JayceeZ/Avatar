#include "events.h"

CEvent::CEvent() {}
CEvent::~CEvent() {}

void CEvent::OnEvent(SDL_Event *Event) {
    switch(Event->type) {
    case SDL_KEYDOWN:
        OnKeyDown(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.which);
        break;
    case SDL_MOUSEMOTION:
        OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
        break;
    case SDL_VIDEORESIZE:
        OnResize(Event->resize.w, Event->resize.h);
        break;
    case SDL_QUIT:
        OnExit();
        break;
    }
}

void CEvent::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {}

void CEvent::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {}

void CEvent::OnResize(int w, int h) {}
void CEvent::OnExpose() {}
void CEvent::OnExit() {}
