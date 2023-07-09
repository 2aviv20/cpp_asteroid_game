#pragma once
#include "Application.h"
#include <random>
#include <string> 
#include <iostream>

bool Application::IsRunning() {
    return running;
}

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup() {
    running = Graphics::OpenWindow();
 
    TTF_Init();
    this->Font = TTF_OpenFont("./assets/OpenSans-Bold.ttf", 16);
    this->player = new Player(Graphics::windowWidth, Graphics::windowHeight);

    float scale = 0.5f;
    //https://www.geogebra.org/
    Body* astroid_1 = new Body(PolygonShape({Vec2(0, 20), Vec2(20, -20), Vec2(0, -40), Vec2(-20, 20)}), 500, 500, 2.0,scale);
    Body* astroid_2 = new Body(PolygonShape({Vec2(0, 20), Vec2(10, 10), Vec2(10, -10), Vec2(0, -20) }), 600, 500, 2.0,scale);
    Body* astroid_3 = new Body(PolygonShape({Vec2(1, 5), Vec2(4, 5), Vec2(5, 2), Vec2(1, -3) ,Vec2(-4,1),Vec2(-5,4)}), 700, 500, 2.0,scale);
    Body* astroid_4 = new Body(PolygonShape({ Vec2(0, 20), Vec2(20, -20), Vec2(0, -40), Vec2(-20, 20) }), 800, 500, 2.0,scale);

    asteroids.push_back(astroid_1);
    asteroids.push_back(astroid_2);
    asteroids.push_back(astroid_3);
    asteroids.push_back(astroid_4);

}

///////////////////////////////////////////////////////////////////////////////
// Input processing
///////////////////////////////////////////////////////////////////////////////
void Application::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }
            if (event.key.keysym.sym == SDLK_w) {
                this->player->move(Vec2(0, 1));
                std::cout << "w key pressed\n";
            }
            if (event.key.keysym.sym == SDLK_s) {
                this->player->move(Vec2(0, -1));
                std::cout << "s key pressed\n";

            }
            if (event.key.keysym.sym == SDLK_a) {
                std::cout << "a key pressed\n";
                this->player->playerBody->restitution += 1;

            }
            if (event.key.keysym.sym == SDLK_d) {
                std::cout << "d key pressed\n";
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);
            this->MouseClickPos = Vec2(x, y);
            //Body* smallBall = new Body(CircleShape(40), x, y, 50.0);
            //smallBall->restitution = 0.2;
            //bodies.push_back(smallBall);
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Update function (called several times per second to update objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Update() {
    Graphics::ClearScreen(0xFF0F0721);
    // Wait some time until the reach the target frame time in milliseconds
    //static int timePreviousFrame;
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - this->timePreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }
  
    // Calculate the deltatime in seconds
    float deltaTime = (SDL_GetTicks() - this->timePreviousFrame) / 1000.0f;
    //if (deltaTime > 0.016)
    //    deltaTime = 0.016;

    // Calculate the frames per second
    this->fpsOneSecCounter += deltaTime;
    this->frameCount++;
    if (this->fpsOneSecCounter >= 1) {
        this->fps = this->frameCount;
        this->frameCount = 0;
        this->fpsOneSecCounter = 0;
    }

    // Set the time of the current frame to be used in the next one
    this->timePreviousFrame = SDL_GetTicks();

    // Apply forces to the bodies
    for (auto body : asteroids) {
        // Apply the weight force
        Vec2 weight = Vec2(body->mass * 1.8 * PIXELS_PER_METER, body->mass * 1.8 * PIXELS_PER_METER);
        body->AddForce(weight);

        // Apply the wind force
      /*  Vec2 wind = Vec2(0.2 * PIXELS_PER_METER, 0.0);
        body->AddForce(wind);*/
    }

    // Integrate the acceleration and velocity to estimate the new position
    for (auto body : asteroids) {
        body->Update(deltaTime);
        body->isCollide = false;
    }

    player->Update(deltaTime);

    // Check all the rigidbodies with the other rigidbodies for collision
    for (int i = 0; i <= asteroids.size() - 1; i++) {
        for (int j = i + 1; j < asteroids.size(); j++) {
            Body* a = asteroids[i];
            Body* b = asteroids[j];
            /*a->isCollide = false;
            b->isCollide = false;*/

            Contact contact;

            if (CollisionDetection::IsColliding(a, b, contact)) {
                // Resolve the collision using the impulse method
                contact.ResolveCollision();

                // Draw debug contact information
                //Graphics::DrawFillCircle(contact.start.x, contact.start.y, 3, 0xFFFF00FF);
                //Graphics::DrawFillCircle(contact.end.x, contact.end.y, 3, 0xFFFF00FF);
                //Graphics::DrawLine(contact.start.x, contact.start.y, contact.start.x + contact.normal.x * 15, contact.start.y + contact.normal.y * 15, 0xFFFF00FF);
                a->isCollide = true;
                b->isCollide = true;
            }
        }
    }

    // Check the boundaries of the window applying a hardcoded bounce flip in velocity
    for (auto body : asteroids) {
        if (body->shape->GetType() == CIRCLE) {
            CircleShape* circleShape = (CircleShape*)body->shape;
            if (body->position.x - circleShape->radius <= 0) {
                body->position.x = circleShape->radius;
                body->velocity.x *= -0.9;
            }
            else if (body->position.x + circleShape->radius >= Graphics::Width()) {
                body->position.x = Graphics::Width() - circleShape->radius;
                body->velocity.x *= -0.9;
            }
            if (body->position.y - circleShape->radius <= 0) {
                body->position.y = circleShape->radius;
                body->velocity.y *= -0.9;
            }
            else if (body->position.y + circleShape->radius >= Graphics::Height()) {
                body->position.y = Graphics::Height() - circleShape->radius;
                body->velocity.y *= -0.9;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render() {
    // Draw all bodies
    for (auto body : asteroids) {
        Uint32 color = body->isCollide ? 0xFF0000FF : 0xFFFFFFFF;

        if (body->shape->GetType() == CIRCLE) {
            CircleShape* circleShape = (CircleShape*)body->shape;
            Graphics::DrawFillCircle(body->position.x, body->position.y, circleShape->radius, body->color);
        }
        if (body->shape->GetType() == BOX ) {
            BoxShape* boxShape = (BoxShape*)body->shape;
            Graphics::DrawRect(body->position.x, body->position.y, boxShape->width, boxShape->height, 0xFFFFFFFF);
        }
        if (body->shape->GetType() == POLYGON) {
            PolygonShape *polygon = (PolygonShape*)body->shape;
            Graphics::DrawPolygon(body->position.x, body->position.y, polygon->worldVertices, 0xFFFFFFFF, body->scale);
        }
    }
    this->player->Draw();

    //std::string text = "(" + std::to_string(this->MouseClickPos.x) + "," + std::to_string(this->MouseClickPos.y) + ")";
    //std::string text = "circles on screen: " + std::to_string(this->bodies.size()-3);
    int textWidth = 200;
    int textHeight = 25;
    std::string fpsText = "fps: " + std::to_string(this->fps);
    const char* cFpsText = fpsText.c_str();
    Graphics::DrawText(Graphics::windowWidth - (textWidth+20), 0, textWidth - 150, textHeight, cFpsText, 0xFFFFFFFF, this->Font, this->textTexture);

    std::string numOfBodiestext = "num of circles:" + std::to_string(this->asteroids.size()-3);
    const char* cNumOfBodiestext = numOfBodiestext.c_str();
    Graphics::DrawText(Graphics::windowWidth - (textWidth+20) , textHeight, textWidth, textHeight, cNumOfBodiestext, 0xFFFFFFFF, this->Font, this->textTexture);

    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy() {
    for (auto body : asteroids) {
        delete body;
    }
    Graphics::CloseWindow();
    TTF_CloseFont(this->Font);
    TTF_Quit();
}

void Application::newAstroidWave()
{
    int R = 20;
    int space = 100;
    int width = Graphics::Width() / 2;
    int heigth = Graphics::Height();

    std::uint32_t colors[8] = {
        0xFF0000FF, // Red
        0x00FF00FF, // Green +
        0x0000FFFF, // Blue +
        0xFFFF00FF, // Yellow
        0xFF00FFFF, // Magenta
        0x00FFFFFF, // Cyan + 
        0xFF8000FF, // Orange
        0x8000FFFF  // Purple
    };

    //random number generator
    std::random_device rd;  // Obtain a random number from a hardware device
    std::mt19937 gen(rd()); // Seed the random number generator
    std::uniform_int_distribution<int> colorDistribution(0, 7); // Define the range of random numbers
    std::uniform_int_distribution<int> positionDistribution(-20, 20); // Define the range of random numbers

    for (int row = 1; row < 13; row++) {
        for (int col = 0; col < 13; col++) {
            int positionFactor = positionDistribution(gen);
            float scale = 1.0f;
            Body* circle = new Body(CircleShape(20), (width - (R * 2 + space) * col) + positionFactor, 0 - row * space, 1.0,scale);
            circle->restitution = 0.2;
            int rand = colorDistribution(gen);
            circle->changeColor(colors[rand]);
            asteroids.push_back(circle);
        }
    }
}
