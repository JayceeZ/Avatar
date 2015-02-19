#include "events.h"

CEvent::CEvent() {}
CEvent::~CEvent() {}

void CEvent::OnEvent(SDL_Event *Event) {
    switch(Event->type) {
    case SDL_KEYDOWN:
        OnKeyDown(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.which);
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
void CEvent::OnResize(int w, int h) {}
void CEvent::OnExpose() {}
void CEvent::OnExit() {}
