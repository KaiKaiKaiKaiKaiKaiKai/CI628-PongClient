#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

static int GAME_WIDTH = 800;

static struct GameData {
    int player1Y = 0;
    int player2Y = 0;
    int ballX = 0;
    int ballY = 0;
} game_data;

static struct Scores {
    int player1Score = 0;
    int player2Score = 0;
} scores;

class MyGame {

    private:
        int player1Score = 0;
        int player2Score = 0;

        SDL_Color scoreColor = { 255, 255, 255 }; // White color

        SDL_Rect player1 = { GAME_WIDTH / 4, 0, 20, 60 };
        SDL_Rect player2 = { 3 * GAME_WIDTH / 4 - 20, 0, 20, 60 };

        SDL_Rect ball = { 0, 0, 20, 20 };

    public:
        TTF_Font* scoreFont;
        std::vector<std::string> messages;

        void on_receive(std::string message, std::vector<std::string>& args);
        void send(std::string message);
        void sendKey(std::string key, bool keyDown);
        void input(SDL_Event& event);
        void update();
        void render(SDL_Renderer* renderer);
};

#endif