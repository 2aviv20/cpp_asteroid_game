#ifndef APPLICATION_H
#define APPLICATION_H

#include "./Graphics.h"
#include "./Physics/Constants.h"
#include "./Physics/Force.h"
#include "./Physics/CollisionDetection.h"
#include "./Physics/Contact.h"
#include "./Physics/Body.h"
#include <vector>
#include "./Mouse.h"
#include "../lib/SDL_ttf.h"
#include "./Physics/Vec2.h"
#include "Player.h"
class Application {
    private:
        bool running = false;
        std::vector<Body*> asteroids;
        Mouse* mouse = nullptr;
        //LineShape* mouseVector;
        TTF_Font* Font;
        SDL_Texture* textTexture;
        Vec2 MouseClickPos;
        int fps = 0;
        int frameCount = 0;
        int timePreviousFrame = 0;
        float fpsOneSecCounter = 0;
    public:
        Player* player;
        Application() = default;
        ~Application() = default;
        bool IsRunning();
        void Setup();
        void Input();
        void Update();
        void Render();
        void Destroy();
        void newAstroidWave();
};

#endif
