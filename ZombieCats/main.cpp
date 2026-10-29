#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Surface* zombiesurface;
    SDL_Texture* zombietexture;
    SDL_Surface* conezombiesurface;
    SDL_Texture* conezombietexture;
    SDL_Surface* bucketzombiesurface;
    SDL_Texture* bucketzombietexture;
    SDL_Surface* bulletsurface;
    SDL_Texture* bullettexture;
    SDL_Surface* healthsurface;
    SDL_Texture* healthtexture;
    SDL_Event event;
    int health = 196;
    Uint64 fps = 0;
    Uint64 lastTime = 0;
    Uint64 characterx = 110;
    int zombiex = 1;
    bool facingleftside = false;
    bool facingrightside = true;
    bool bulletleft = false;
    bool bulletright = true;
    bool dowehaveabullet = false;
    Uint64 bullets = 64;
    int bulletx = characterx + 1;
    int zombietype = 0;
    bool zombiecatalive = false;
    bool zombiemovingleftside = false;
    bool zombiemovingrightside = true;
    bool gameover = false;
    int zombiehealth = 1;
    Uint64 score = 0;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    if (!SDL_CreateWindowAndRenderer("Zombie Cats", 500, 410, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }

    surface = IMG_Load("cat.png");
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load character image: %s", SDL_GetError());
        return 3;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        return 3;
    }
    bulletsurface = IMG_Load("bullet.png");
    if (!bulletsurface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load bullet: %s", SDL_GetError());
        return 3;
    }
    bullettexture = SDL_CreateTextureFromSurface(renderer, bulletsurface);
    if (!bullettexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create bullet texture from surface: %s", SDL_GetError());
        return 3;
    }
    zombiesurface = IMG_Load("catzombie.png");
    if (!zombiesurface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load zombie: %s", SDL_GetError());
        return 3;
    }
    zombietexture = SDL_CreateTextureFromSurface(renderer, zombiesurface);
    if (!zombietexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create zombie texture from surface: %s", SDL_GetError());
        return 3;
    }
    conezombiesurface = IMG_Load("conecatzombie.png");
    if (!conezombiesurface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load cone zombie: %s", SDL_GetError());
        return 3;
    }
    conezombietexture = SDL_CreateTextureFromSurface(renderer, conezombiesurface);
    if (!conezombietexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create cone zombie texture from surface: %s", SDL_GetError());
        return 3;
    }
    bucketzombiesurface = IMG_Load("helmetcatzombie.png");
    if (!bucketzombiesurface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load bucket zombie: %s", SDL_GetError());
        return 3;
    }
    bucketzombietexture = SDL_CreateTextureFromSurface(renderer, bucketzombiesurface);
    if (!bucketzombietexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create bucket zombie texture from surface: %s", SDL_GetError());
        return 3;
    }
    healthsurface = IMG_Load("healthbar.png");
    if (!healthsurface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load health bar: %s", SDL_GetError());
        return 3;
    }
    healthtexture = SDL_CreateTextureFromSurface(renderer, healthsurface);
    if (!healthtexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create health bar texture from surface: %s", SDL_GetError());
        return 3;
    }
    
    SDL_DestroySurface(surface);
    SDL_DestroySurface(bulletsurface);
    SDL_DestroySurface(zombiesurface);
    SDL_DestroySurface(healthsurface);

    const bool* keys = SDL_GetKeyboardState(nullptr);

    while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT) {
            break;
        }
        //else if (event.type == SDL_EVENT_KEY_DOWN) {
            //SDL_Log("
            // A key was pressed! it was %d", event.key.key);
        //}

        Uint64 currentTick = SDL_GetTicks();
        SDL_Delay(16);
        fps++;
        Uint64 deltaTime = SDL_GetTicks() - currentTick;
        if (currentTick > lastTime + 1000) {
            lastTime = currentTick;
            std::string title;
            title += "Zombies Cats - FPS " + std::to_string(fps);
            SDL_SetWindowTitle(window, title.c_str());
            fps = 0;

            if (gameover == false && zombiecatalive == false) {
                int side = rand() % 2;
                if (side == 0) {
                    zombiex = 1;
                    zombiemovingrightside = true;
                    zombiemovingleftside = false;
                }
                else {
                    zombiex = 211;
                    zombiemovingrightside = false;
                    zombiemovingleftside = true;
                }
                zombiecatalive = true;
                int whatsitgonnabe = rand() % 100;
                if (whatsitgonnabe < 70) {
                    zombietype = 0;
                    zombiehealth = 1;
                }
                else if (whatsitgonnabe < 80) {
                    zombietype = 1;
                    zombiehealth = 2;
                }
                else {
                    zombietype = 2;
                    zombiehealth = 3;
                }
            }
        }

        if (zombiecatalive == true) {
            if (zombiemovingleftside == true) {
                zombiex -= 1;
            }
            else if (zombiemovingrightside == true) {
                zombiex += 1;
            }
        }

       if (keys[SDL_SCANCODE_LEFT] == true) {
            if (characterx < 45) {
                characterx = 45;
            }
            characterx -= 2;
            facingleftside = true;
            facingrightside = false;
        }
        if (keys[SDL_SCANCODE_RIGHT] == true) {
            if (characterx > 170) {
                characterx = 170;
            }
            characterx += 2;
            facingleftside = false;
            facingrightside = true;
        }
        if (keys[SDL_SCANCODE_A] == true) {
            if (characterx < 45) {
                characterx = 45;
            }
            characterx -= 2;
            facingleftside = true;
            facingrightside = false;
        }
        if (keys[SDL_SCANCODE_D] == true) {
            if (characterx > 170) {
                characterx = 170;
            }
            characterx += 2;
            facingleftside = false;
            facingrightside = true;
        }
        if (event.type == SDL_EVENT_KEY_DOWN && keys[SDL_SCANCODE_SPACE] == true) {
            if (bullets > 0) {
                bullets -= 1;
                dowehaveabullet = true;
                if (facingleftside == true) {
                    bulletx = characterx - 1;
                }
                else if (facingrightside == true) {
                    bulletx = characterx + 1;
                }
                bulletleft = facingleftside;
                bulletright = facingrightside;
            }
        }

        if (dowehaveabullet == true) {
            if (bulletleft == true) {
                bulletx -= 2;
                if (bulletx < 0) {
                    dowehaveabullet = false;
                }
            }
            else if (bulletright == true) {
                bulletx += 2;
                if (bulletx > 214) {
                    dowehaveabullet = false;
                    bulletx = -100;
                }
            }
        }

        SDL_FRect rect{ characterx, 170, 32, 32 };
        SDL_FRect zombierect{ zombiex, 170, 32, 32 };
        SDL_FRect bulletrect{ bulletx, 180, 16, 16 };
        SDL_FRect healthrect{ 30, 20, 200, 22 };
        SDL_FRect healthrect2{ 32, 22, health, 18 };
        std::string scoretext;
        scoretext += "Score: " + std::to_string(score);

        std::string gameovertext = "GAME OVER";
        std::string restarttext = "PRESS R TO RESTART";

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_SetRenderScale(renderer, 2.0f, 2.0f);

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        if (gameover == false && dowehaveabullet == true) {
            SDL_RenderTexture(renderer, bullettexture, NULL, &bulletrect);
        }
        if (gameover == false && zombiecatalive == true) {
            if (zombietype == 0) {
                SDL_RenderTexture(renderer, zombietexture, NULL, &zombierect);
            }
            else if (zombietype == 1) {
                SDL_RenderTexture(renderer, conezombietexture, NULL, &zombierect);
            }
            else if (zombietype == 2) {
                SDL_RenderTexture(renderer, bucketzombietexture, NULL, &zombierect);
            }
        }
        if (dowehaveabullet == true && zombiecatalive == true && SDL_HasRectIntersectionFloat(&bulletrect, &zombierect)) {
            zombiehealth -= 1;
            dowehaveabullet = false;
            if (zombiehealth == 0) {
                if (zombietype == 0) {
                    score += 100;
                }
                else if (zombietype == 1) {
                    score += 200;
                }
                else if (zombietype == 2) {
                    score += 300;
                }
                zombiecatalive = false;
                bullets += 2;
            }
        }
        if (zombiecatalive == true && SDL_HasRectIntersectionFloat(&rect, &zombierect)) {
            zombiecatalive = false;
            dowehaveabullet = false;
            health -= 30;
        }
        if (health < 0) {
            health = 0;
            gameover = true;
        }
        if (gameover == true) {
            SDL_RenderDebugText(renderer, 100.0f, 120.0f, gameovertext.c_str());
            SDL_RenderDebugText(renderer, 90.0f, 100.0f, restarttext.c_str());
            characterx = 1000;
            zombiecatalive = false;
            dowehaveabullet = false;
            if (keys[SDL_SCANCODE_R] == true) {
                characterx = 110;
                zombiex = -100;
                zombiecatalive = false;
                dowehaveabullet = false;
                gameover = false;
                score = 0;
                bullets = 64;
                health = 196;
            }
        }
        SDL_RenderTexture(renderer, texture, NULL, &rect);
        std::string bulletamount;
        bulletamount += "Bullets: " + std::to_string(bullets);
        SDL_RenderDebugText(renderer, 10.0f, 10.0f, bulletamount.c_str());
        SDL_RenderDebugText(renderer, 50.0f, 50.0f, scoretext.c_str());
        SDL_RenderTexture(renderer, healthtexture, NULL, &healthrect);
        SDL_RenderFillRect(renderer, &healthrect2);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
