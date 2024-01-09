#pragma once



#include <SFML/Window/Event.hpp>
#include <Timer.h>
#include <vector>

class Game {
public:
    friend class Application;

    enum StateGame
    {
        Gamming = 0,
        Pause,

        // keep this last
        StateCount
    };
private:
    Game();

    std::string word;
    std::string guessWord;
    std::string bufferLett;

    sf::Vector2f sizeLett = { 30, 40 };    // размер буквы
    sf::Vector2f offsetLett = { 10, 10 };  // растояние между буквами
    int cntLettRow = 5;

    int HP;
    Timer timer;
    StateGame gameState = Pause;
    bool SettingsIsOpen = false;

    class GeneratorWords {
    private:
        std::vector<std::string> words;

    public:
        GeneratorWords(const std::string& filePath);

        std::string getRandomWord() const;
    };
    GeneratorWords generator;
public:
    void init();

    int GetHp();
    float GetTime();
    const std::string& GetBufferLett(); // веденные буквы
    const std::string& GetGuessWord();  // как на данный момент слово из угаданных userом букв

    void DrawGUISettings();
    void DrawGUIGame();
    void DrawGUI();

    void StartTimer();
    void PauseTimer();
    void RestartTimer();

    void handleEvent(const sf::Event& event);

    void CheckLett(char letter);

    const char* GetStatusGame();
    const char* state_mode(StateGame state);

    bool gameOver();
    bool win();
    bool gaming();


};

