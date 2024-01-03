#include "MyGame.h"
#include <Windows.h>

// Function to handle receiving messages and updating game data accordingly
void MyGame::on_receive(std::string cmd, std::vector<std::string>& args)
{
    if (cmd == "GAME_DATA")
    {
        // Update game data if the command is for game data
        if (args.size() == 4)
        {
            game_data.player1Y = stoi(args.at(0)); // Update player 1 Y-coordinate
            game_data.player2Y = stoi(args.at(1)); // Update player 2 Y-coordinate
            game_data.ballX = stoi(args.at(2));    // Update ball X-coordinate
            game_data.ballY = stoi(args.at(3));    // Update ball Y-coordinate
        }
    }
    else if (cmd == "SCORES")
    {
        // Update scores if the command is for scores
        if (args.size() == 2)
        {
            scores.player1Score = stoi(args.at(0)); // Update player 1 score
            scores.player2Score = stoi(args.at(1)); // Update player 2 score
        }
    }
    else
    {
        std::cout << "Received: " << cmd << std::endl; // Log the received command
    }
}

// Function to add a message to the message queue
void MyGame::send(std::string message)
{
    messages.push_back(message); // Add the message to the vector
}

// Function to handle keyboard input events
void MyGame::input(SDL_Event& event)
{
    const bool keyDown = (event.type == SDL_KEYDOWN); // Check if key is pressed or released

    switch (event.key.keysym.sym)
    {
    case SDLK_w:
        sendKey("W", keyDown); // Send 'W' key status
        break;
    case SDLK_s:
        sendKey("S", keyDown); // Send 'S' key status
        break;
    case SDLK_i:
        sendKey("I", keyDown); // Send 'I' key status
        break;
    case SDLK_k:
        sendKey("K", keyDown); // Send 'K' key status
        break;
    }
}

// Function to send key events to the message queue
void MyGame::sendKey(std::string key, bool keyDown)
{
    send(key + (keyDown ? "_DOWN" : "_UP")); // Send key status message
}

// Get current player score
int MyGame::Player::getScore()
{
    return score;
}

// Set value for Text object
void MyGame::Text::setValue(std::string value_)
{
    value = value_;
}

// Update player's score and update associated text
void MyGame::Player::updateScore(int score_)
{
    score = score_;                                 // Update player's score
    scoreText.setValue(std::to_string(getScore())); // Update displayed score text
}

// Update game state based on received data
void MyGame::update()
{
    player1.y = game_data.player1Y; // Update player 1 position
    player2.y = game_data.player2Y; // Update player 2 position

    ball.centerX = game_data.ballX; // Update ball position
    ball.centerY = game_data.ballY;

    player1.updateScore(scores.player1Score); // Update player 1 score
    player2.updateScore(scores.player2Score); // Update player 2 score
}

// Render game elements on the screen
void MyGame::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set render color

    // Render players, their scores, and the ball
    player1.render(renderer);
    player2.render(renderer);
    player1.scoreText.render(renderer);
    player2.scoreText.render(renderer);
    ball.render(renderer);
}

// Render Sprite on the screen
void MyGame::Sprite::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 211, 211, 211, 255); // Set draw color to gray
    SDL_RenderDrawRect(renderer, this);                   // Render the Sprite as a rectangle
    SDL_RenderFillRect(renderer, this);                   // Fill rectangle with color
}

// Render Ball on the screen
void MyGame::Ball::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 211, 211, 211, 255); // Set color to gray

    int diameter = (radius * 2);
    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y)
    {
        // Draw eight points by symmetry
        for (int y = -radius; y <= radius; ++y)
        { // Iterate over the vertical range of the circle
            for (int x = -radius; x <= radius; ++x)
            { // Iterate over the horizontal range of the circle
                if (x * x + y * y <= radius * radius)
                {                                                            // Check if the point falls within the circle equation
                    SDL_RenderDrawPoint(renderer, centerX + x, centerY + y); // Render the point inside the circle
                }
            }
        }

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

// Render Text on the screen
void MyGame::Text::render(SDL_Renderer* renderer)
{
    if (!font)
    {
        font = TTF_OpenFont("res/pong.ttf", 70);
    } // Load font if not already loaded

    // Render text on the screen
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, value.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect); // Copy texture to renderer
    SDL_FreeSurface(textSurface);                           // Free surface memory
    SDL_DestroyTexture(textTexture);                        // Destroy texture
}
