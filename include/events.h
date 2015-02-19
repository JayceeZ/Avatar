#ifndef EVENTS_H
#define EVENTS_H

#include <SDL.h>

class CEvent {
public:
    CEvent();
    virtual ~CEvent();
    virtual void OnEvent(SDL_Event* Event);
    virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
    virtual void OnResize(int w, int h);
    virtual void OnExpose();
    virtual void OnExit();
};

#endif // EVENTS_H
