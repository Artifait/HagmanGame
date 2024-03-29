#pragma once
#include "Window.h"
#include <Game.h>

enum State
{
    Gamming = 0,
    Menu,

    // keep this last
    StateCount
};
class Application
{
public:
    Application();

    // Called once in main
    void run();
    // Called before stopping execution
    void close();
    // key gets pressed down/released
    void handleEvent(const sf::Event& ev);
    // When button/key is pressed continuosly eg. moving map by dragging
    void handleInputBuffers(const sf::Vector2i& delta_mp);

    // Changes state of the application ex. Editing (MapBuilder) and Simulating (Moving cars, lights etc.)
    void changeState(State new_state);
    // Draws GUI eg. menu bar
    void drawGUI();

private:
    ps::Window window_;
    Game Hagman;
    std::vector<std::string> logs_;
    State app_state_ = Menu;

    // Input buffers
    bool key_buffer_[sf::Keyboard::KeyCount]{ false };
    bool button_buffer_[sf::Mouse::ButtonCount]{ false };

    static Application* AppInstance;

public:
    static Application* GetInstance();
};

