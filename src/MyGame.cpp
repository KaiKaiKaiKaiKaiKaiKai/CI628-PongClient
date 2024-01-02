#include "MyGame.h"

void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "GAME_DATA") {
        // we should have exactly 4 arguments
        if (args.size() == 4) {
            game_data.player1Y = stoi(args.at(0));
            game_data.player2Y = stoi(args.at(1));
            game_data.ballX = stoi(args.at(2));
            game_data.ballY = stoi(args.at(3));
        }
    } else if (cmd == "SCORES") {
        // we should have exactly 2 arguments
        if (args.size() == 2) {
            scores.player1Score = stoi(args.at(0));
            scores.player2Score = stoi(args.at(1));
        }
    }
    else {
        std::cout << "Received: " << cmd << std::endl;
    }
}

void MyGame::send(std::string message) {
    messages.push_back(message);
}

void MyGame::input(SDL_Event& event) {
    const bool keyDown = (event.type == SDL_KEYDOWN);

    switch (event.key.keysym.sym) {
    case SDLK_w:
        sendKey("W", keyDown);
        break;
    case SDLK_s:
        sendKey("S", keyDown);
        break;
    case SDLK_i:
        sendKey("I", keyDown);
        break;
    case SDLK_k:
        sendKey("K", keyDown);
        break;
    }
}

void MyGame::sendKey(std::string key, bool keyDown) {
    send(key + (keyDown ? "_DOWN" : "_UP"));
}

void MyGame::update() {
    player1.y = game_data.player1Y;
    player2.y = game_data.player2Y;

    ball.x = game_data.ballX;
    ball.y = game_data.ballY;

    player1Score = scores.player1Score;
    player2Score = scores.player2Score;
}

void MyGame::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    SDL_RenderDrawRect(renderer, &player1);
    SDL_RenderDrawRect(renderer, &player2);

    SDL_RenderDrawRect(renderer, &ball);

    // Create a surface from the text
    std::string player1ScoreText = std::to_string(player1Score);
    SDL_Surface* player1ScoreTextSurface = TTF_RenderText_Solid(scoreFont, player1ScoreText.c_str(), scoreColor);
    SDL_Texture* player1ScoreTextTexture = SDL_CreateTextureFromSurface(renderer, player1ScoreTextSurface);

    std::string player2ScoreText = std::to_string(player2Score);
    SDL_Surface* player2ScoreTextSurface = TTF_RenderText_Solid(scoreFont, player2ScoreText.c_str(), scoreColor);
    SDL_Texture* player2ScoreTextTexture = SDL_CreateTextureFromSurface(renderer, player2ScoreTextSurface);

    // Define a rect for the text position
    SDL_Rect player1ScoreTextRect = { GAME_WIDTH / 4 - 50, 110, player1ScoreTextSurface->w, player1ScoreTextSurface->h };
    SDL_Rect player2ScoreTextRect = { 3 * GAME_WIDTH / 4 - 20 + 40, 110, player2ScoreTextSurface->w, player2ScoreTextSurface->h };

    // Render the text
    SDL_RenderCopy(renderer, player1ScoreTextTexture, NULL, &player1ScoreTextRect);
    SDL_RenderCopy(renderer, player2ScoreTextTexture, NULL, &player2ScoreTextRect);

    SDL_FreeSurface(player1ScoreTextSurface);
    SDL_DestroyTexture(player1ScoreTextTexture);

    SDL_FreeSurface(player2ScoreTextSurface);
    SDL_DestroyTexture(player2ScoreTextTexture);
}