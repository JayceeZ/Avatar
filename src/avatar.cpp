#include "avatar.h"
#include "gl_objects.h"
#include <iostream>

#define SDL_VIDEO_MODE_OPTIONS (SDL_RESIZABLE | SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)
#define SDL_DEPTH 32

#define SCENE_ROTATION_STEP 5
#define CAMERA_Z_OFFSET 2
#define CAMERA_TRANSLATION_STEP 0.1

#define TWIST_STEP 5

#define RDR_FRAME_LENGTH 1
#define RDR_CUBE_HALF_SIDE 0.5

CAvatar::CAvatar() {
    should_be_running = false;
    needs_rendering = false;

    window_width = 0;
    window_height = 0;
    window_title = "";

    // Repère du monde
    world_origin_x = 0;
    world_origin_y = 0;
    world_origin_z = 0;

    // Camera
    camera_aspect_ratio = 0;
    camera_fovy = 0;
    camera_tx = 0;
    camera_ty = 0;
    camera_tz = 0;

    camera_min_z = 0;
    camera_max_z = 0;

    camera_min_tz = 0;

    // Avatar members
    shoulderTwist = 0;
    elbowTwist = 0;
    wristTwist = 0;

    // Mode
    mode_sensor = false;
}

CAvatar::~CAvatar() {}

int CAvatar::OnExecute(bool with_sensor) {
    if(OnInit(with_sensor) == false) {
        std::cout << "Initialization failed !" << std::endl;
        return -1;
    }

    SDL_Event event;

    // pour le maintient d'une touche
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    should_be_running = true; 
    needs_rendering = true;

    while(should_be_running) {
        while(SDL_PollEvent(&event)) {
            OnEvent(&event);
        }
        OnLoop();
        OnRender();
    }
    OnCleanup();

    std::cout << "Application ended normally." << std::endl;
    return 0;
}

bool CAvatar::OnInit(bool with_sensor)
{
    char sdl_wdw_pos[] = "SDL_VIDEO_WINDOW_POS";
    char sdl_wdw_ctr[] = "SDL_VIDEO_CENTERED=1";
    putenv(sdl_wdw_pos);
    putenv(sdl_wdw_ctr);

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    SDL_WM_SetCaption(window_title, 0);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,8);

    /*
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
    */

    window_width = 640;
    window_height = 480;
    window_title = "Avatar Main Window";

    sdl_pimage = SDL_SetVideoMode(window_width, window_height, SDL_DEPTH, SDL_VIDEO_MODE_OPTIONS);

    if(sdl_pimage == NULL) {
        std::cout << "Drawing window have not been initialized correcly." << std::endl;
        return false;
    }

    // Défini la valeur de la "gomme" opengl, nous on veut que effacer=noir
    glClearColor(0,0,0,0);
    glViewport(0,0,window_width, window_height);

    // Paramètres caméra virtuelle
    camera_aspect_ratio = ((float) window_width) / ((float) window_height);
    camera_min_z = 0.1;
    camera_max_z = 50;
    camera_fovy = 60;

    if(with_sensor) {
        if(sensor.OnInit(true)) {
            std::cout << "Mode Sensor" << std::endl;
            mode_sensor = true;
        } else {
            std::cout << "Error initializing sensor: Mode Demo" << std::endl;
        }
    } else {
        std::cout << "Mode Demo" << std::endl;
    }

    InitSceneConstants();

    if(mode_sensor)
        InitModeSensor();
    else
        InitModeDemo();

    return true;
}

void CAvatar::SetPerspectiveProjectionMatrix() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(camera_fovy, camera_aspect_ratio, camera_min_z, camera_max_z);
}

void CAvatar::SetOrthoProjectionMatrix() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -10, 10);
}

void CAvatar::OnCleanup() {
    if(sdl_pimage)
        SDL_FreeSurface(sdl_pimage);
    SDL_Quit();
}

void CAvatar::OnLoop()
{}

void CAvatar::InitSceneConstants() {
    // valeurs initiales de la vue pour la représentation
    world_rx = 0;
    world_ry = 0;

    camera_min_tz = world_origin_z + CAMERA_Z_OFFSET;
    camera_tx = world_origin_x;
    camera_ty = world_origin_y;
    camera_tz = camera_min_tz;
}

void CAvatar::InitModeDemo() {
    SetPerspectiveProjectionMatrix();

/*
    // Lumière
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);
*/

    texture = loadTexture();
    camera_tz += 10;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
}

void CAvatar::DrawDemo() {
/*
    // Lumière
    GLfloat light_position[] = { 0.0, 0.0, 100.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
*/

    // on dit à opengl que les matrices définies ci-après appartiennent à MODELVIEW (ce qui est observé)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // la matrice identité, à charger avant tout calcul matriciel pour être sûr que l'on calcul sur une matrice propre

    // ces trois opérations de matrices sont effectuée à la fin donc pour avoir un rendu de notre modéle en fonction des attribut de camera
    glTranslatef(-camera_tx, -camera_ty, -camera_tz);
    glRotatef(world_rx, 1, 0, 0);
    glRotatef(world_ry, 0, 1, 0);

    // dessine un repère orthonormé
    DrawFrame(world_origin_x, world_origin_y, world_origin_z, RDR_FRAME_LENGTH);
    // dessine notre avatar
    DrawAvatar(world_origin_x, world_origin_y, world_origin_z, shoulderTwist, elbowTwist, wristTwist, texture);
}


void CAvatar::InitModeSensor() {
    // Initialisations des attributs pour sensor
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    // génération d'une fenêtre adaptée
    SDL_SetVideoMode(sensor.m_colorStream.getVideoMode().getResolutionX(), sensor.m_colorStream.getVideoMode().getResolutionY(), SDL_DEPTH, SDL_VIDEO_MODE_OPTIONS);

    // Paramètres caméra réelle
    camera_aspect_ratio = (sensor.m_colorStream.getHorizontalFieldOfView()) / (sensor.m_colorStream.getVerticalFieldOfView());
    camera_fovy = sensor.m_colorStream.getVerticalFieldOfView()*(180/3.14);
}

void CAvatar::DrawSensor() {
    // on défini la matrice de projection selon nos besoins
    if(sensor.active_stream == color_stream) {
        // le flux couleur n'ayant pas de notion de profondeur,
        // on choisi de simplifier la projection des points sur le plan de la fenêtre
        SetOrthoProjectionMatrix();
    } else {
        // sinon, le calcul de la projection en perspective est défini par les paramètres camera
        SetPerspectiveProjectionMatrix();
    }

    openni::VideoFrameRef m_colorFrame, m_depthFrame;

    sensor.m_colorStream.readFrame(&m_colorFrame);
    if(!m_colorFrame.isValid()) {
        std::cout << "Color Frame Invalid" << std::endl;
        return;
    }

    // on dit que les données sont des pixels R=8bits G=8bits et B=8bits
    const openni::RGB888Pixel* pImage = (const openni::RGB888Pixel*) m_colorFrame.getData();

    if(sensor.active_stream == color_stream) {
        GLuint texture_id = Load2DTexture(m_colorFrame.getWidth(), m_colorFrame.getHeight(), 3, pImage);
        FillWindowWithTexture(texture_id);
        // destruction de la texture
        glDeleteTextures(1, &texture_id);
    } else {
        sensor.m_depthStream.readFrame(&m_depthFrame);
        if(!m_depthFrame.isValid()) {
            std::cout << "Depth Frame Invalid" << std::endl;
            return;
        }

        // on dit que les données sont des pixels de profondeurs
        const openni::DepthPixel* pDepth = (const openni::DepthPixel*) m_depthFrame.getData();

        int width = m_depthFrame.getWidth();
        int height = m_depthFrame.getHeight();
        float min_depth = sensor.m_depthStream.getMinPixelValue();
        float max_depth = sensor.m_depthStream.getMaxPixelValue();
        float ratio = min_depth/max_depth;

        float pWorldX, pWorldY, pWorldZ;

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(-camera_tx, -camera_ty, -camera_tz);
        glRotatef(world_rx, 1, 0, 0);
        glRotatef(world_ry, 0, 1, 0);

        // on choisi une taille fixe pour nos points
        glPointSize(2);
        glBegin(GL_POINTS);

        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                if((x % 2 == 0) && (y % 2 == 0) && (*pDepth != 0) && (*pDepth < 2000)) {
                    openni::CoordinateConverter::convertDepthToWorld(sensor.m_depthStream, x, y, *pDepth, &pWorldX, &pWorldY, &pWorldZ);
                    // on attribue la valeur de couleur du pixel image correspondant
                    glColor3f(pImage->r/255.0, pImage->g/255.0, pImage->b/255.0);
                    // on dessine notre point
                    glVertex3f(pWorldX/1000.0, pWorldY/1000.0, camera_tz-pWorldZ/1000.0);
                }
                pDepth++;
                pImage++;
            }
        }
        glEnd();
    }

    // le needs_rendering n'est pas utilisé ici, mais si on veut, on pourrait limiter la fréquence de rafraîchissement avec
    needs_rendering = true;
}


void CAvatar::OnRender()
{
    // Condition d'exécution du contenu de cette méthode
    if(!needs_rendering)
        return;
    needs_rendering = false;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(mode_sensor)
        DrawSensor();
    else
        DrawDemo();

    SDL_GL_SwapBuffers();
}

void CAvatar::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}

void CAvatar::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
    if(Left) { // bouton gauche
        // Translation
        camera_tx -= CAMERA_TRANSLATION_STEP*relX/16;
        camera_ty += CAMERA_TRANSLATION_STEP*relY/16;
    }
    if(Right) { // bouton droit
        // Rotation
        world_rx += SCENE_ROTATION_STEP*relY/16;
        if(world_rx > 360 || world_rx < -360)
            world_rx = 0;
        world_ry += SCENE_ROTATION_STEP*relX/16;
        if(world_ry > 360 || world_ry < -360)
            world_ry = 0;
    }
    needs_rendering = true;
}

void CAvatar::OnResize(int w, int h) {
    // au redimensionnement, on redéfinie la fenêtre comme dans le OnInit
    window_width = w;
    window_height = h;

    SDL_FreeSurface(sdl_pimage);
    sdl_pimage = SDL_SetVideoMode(window_width, window_height, SDL_DEPTH, SDL_VIDEO_MODE_OPTIONS);

    glViewport(0, 0, window_width, window_height);

    if(!mode_sensor)
        camera_aspect_ratio = ((float) window_width)/((float) window_height);

    needs_rendering = true;
}

void CAvatar::SwitchDisplayStream() {
    // uniquement en mode sensor
    if(mode_sensor) {
        InitSceneConstants();
        if(sensor.active_stream == color_stream) {
            // Passage en vue de profondeur
            sensor.active_stream = depth_stream;
            sensor.setColorDepthSync(true);
            std::cout << "Flux de profondeur" << std::endl;
        } else {
            // Passage en vue caméra couleur
            sensor.active_stream = color_stream;
            sensor.setColorDepthSync(false);
            std::cout << "Flux couleur" << std::endl;
        }
        needs_rendering = true;
    }
}

void CAvatar::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch(sym) {
    case SDLK_ESCAPE:
        OnExit();
        break;

    case SDLK_SPACE:
        InitSceneConstants();
        needs_rendering = true;
        break;

    case SDLK_LEFT:
        if(mod & KMOD_SHIFT) {
            world_ry -= SCENE_ROTATION_STEP;
            if(world_ry < 0)
                world_ry += 360;
        }
        else
            camera_tx -= CAMERA_TRANSLATION_STEP;
        needs_rendering = true;
        break;

    case SDLK_RIGHT:
        if(mod & KMOD_SHIFT) {
            world_ry += SCENE_ROTATION_STEP;
            if(world_ry > 360)
                world_ry -= 360;
        }
        else
            camera_tx += CAMERA_TRANSLATION_STEP;
        needs_rendering = true;
        break;

    case SDLK_DOWN:
        if(mod & KMOD_SHIFT) {
            world_rx -= SCENE_ROTATION_STEP;
            if(world_rx < 360)
                world_rx += 360;
        }
        else
            camera_ty -= CAMERA_TRANSLATION_STEP;
        needs_rendering= true;
        break;

    case SDLK_UP:
        if(mod & KMOD_SHIFT) {
            world_rx += SCENE_ROTATION_STEP;
            if(world_rx > 360)
                world_rx -= 360;
        }
        else
            camera_ty += CAMERA_TRANSLATION_STEP;
        needs_rendering= true;
        break;

    case SDLK_q:
        camera_tz -= CAMERA_TRANSLATION_STEP;
        needs_rendering = true;
        break;

    case SDLK_a:
        camera_tz += CAMERA_TRANSLATION_STEP;
        needs_rendering = true;
        break;
    case SDLK_f:
        SwitchDisplayStream();
        break;
    case SDLK_u:
        shoulderTwist += TWIST_STEP;
        needs_rendering = true;
        break;
    case SDLK_j:
        shoulderTwist -= TWIST_STEP;
        needs_rendering = true;
        break;
    case SDLK_i:
        elbowTwist += TWIST_STEP;
        needs_rendering = true;
        break;
    case SDLK_k:
        elbowTwist -= TWIST_STEP;
        needs_rendering = true;
        break;
    case SDLK_o:
        wristTwist += TWIST_STEP;
        needs_rendering = true;
        break;
    case SDLK_l:
        wristTwist -= TWIST_STEP;
        needs_rendering = true;
        break;
    }
}

void CAvatar::OnExpose()
{
    // a completer
}

void CAvatar::OnExit() {
    should_be_running = false;
}
