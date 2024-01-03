#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

// Define the game width
static int GAME_WIDTH = 800;

// Struct to hold game-related data
static struct GameData
{
    int player1Y = 0; // Y-coordinate of player 1
    int player2Y = 0; // Y-coordinate of player 2
    int ballX = 0;    // X-coordinate of the ball
    int ballY = 0;    // Y-coordinate of the ball
} game_data;

// Struct to hold player scores
static struct Scores
{
    int player1Score = 0; // Score of player 1
    int player2Score = 0; // Score of player 2
} scores;

// Main game class
class MyGame
{
    // Nested Text class for rendering text
    class Text
    {
    public:
        // Constructor without parameters
        Text()
        {
            font = TTF_OpenFont("res/pong.ttf", 70); // Load default font
            value = "";                               // Initialize text value as empty
            x = 0;                                    // Initialize x-coordinate
            y = 0;                                    // Initialize y-coordinate
            color = { 255, 255, 255 };                  // Initialize text color
        }

        // Constructor with parameters
        Text(std::string value_, int x_, int y_, SDL_Color color_)
        {
            font = TTF_OpenFont("res/pong.ttf", 70); // Load font
            value = value_;                           // Set text value
            x = x_;                                   // Set x-coordinate
            y = y_;                                   // Set y-coordinate
            color = color_;                           // Set text color
        }

        TTF_Font* font;                      // Font used for rendering
        void render(SDL_Renderer* renderer); // Render text on the screen
        void setValue(std::string value_);   // Set text value

    private:
        std::string value; // Text content
        int x;             // X-coordinate
        int y;             // Y-coordinate
        SDL_Color color;   // Text color
    };

    // Nested Sprite class inheriting from SDL_Rect
    class Sprite : public SDL_Rect
    {
    public:
        // Constructor with parameters for setting position and dimensions
        Sprite(int x_, int y_, int w_, int h_)
        {
            x = x_; // Set x-coordinate
            y = y_; // Set y-coordinate
            w = w_; // Set width
            h = h_; // Set height
        }

        void render(SDL_Renderer* renderer); // Render sprite on the screen
    };

    // Nested Player class inheriting from Sprite
    class Player : public Sprite
    {
    public:
        // Constructor for Player with additional parameters for score rendering
        Player(int x_, int y_, int w_, int h_, int scoreX_, int scoreY_) : Sprite(x_, y_, w_, h_)
        {
            scoreText = Text("0", scoreX_, scoreY_, { 240, 255, 255 }); // Initialize score text
        }

        int getScore();               // Get player score
        void updateScore(int score_); // Update player score
        Text scoreText;               // Text object for displaying score

    private:
        int score = 0; // Player score
    };

    // Nested Ball class
    class Ball {
    public:
        Ball(int radius_) {
            radius = radius_; // Set radius
            centerX = 0; // Set centerX
            centerY = 0; // Set centerY
        }

        int centerX; // Center of ball along x axis
        int centerY; // Center of ball along y axis

        void render(SDL_Renderer* renderer); // Render ball on the screen

    private:
        int radius; // Radius of ball
    };

private:
    // Instances of Player and Sprite for the game
    Player player1 = Player(GAME_WIDTH / 4, 0, 20, 60, GAME_WIDTH / 4 - 100, 110);                   // Player 1
    Player player2 = Player(3 * GAME_WIDTH / 4 - 20, 0, 20, 60, 3 * GAME_WIDTH / 4 - 20 + 90, 110); // Player 2
    Ball ball = Ball(10);                                                             // Game ball

public:
    std::vector<std::string> messages; // Vector to store game messages

    // Game functions
    void on_receive(std::string message, std::vector<std::string>& args);
    void send(std::string message);
    void sendKey(std::string key, bool keyDown);
    void input(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);
};

#endif // __MY_GAME_H__
