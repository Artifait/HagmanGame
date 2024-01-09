#include <Game.h>

#include <string>
#include <fstream>
#include <iostream>

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

Game::Game() : generator("words.txt")
{

}


void Game::DrawGUIGame()
{
    if (gameState == Pause)
    {
        if (ImGui::Begin("HagmanGame"))
        {
            if (SettingsIsOpen)
            {
                if (ImGui::Begin("Settings"))
                {
                    ImGui::SliderFloat("Width Lett", &sizeLett.x, 20.f, 100.f);
                    ImGui::SliderFloat("Height Lett", &sizeLett.y, 40.f, 100.f);

                    ImGui::SliderFloat("Distance Lett in x", &offsetLett.x, 0.f, 100.f);
                    ImGui::SliderFloat("Distance Lett in y", &offsetLett.y, 0.f, 100.f);

                    ImGui::SliderInt("Cnt Letts in row", &cntLettRow, 1, 7);

                    ImGui::Text("Example Alfavit");

                    ImVec2 pos(offsetLett.x, ImGui::GetCursorPosY());

                    for (char i = 'a'; i <= 'z'; i++)
                    {
                        pos.x = 0;
                        for (int j = i; j < i + cntLettRow && j <= 'z'; j++)
                        {
                            ImGui::SetCursorPos(pos);
                            const char Lett[2] = { j };
                            ImGui::Button(Lett, ImVec2(sizeLett));
                            pos.x += sizeLett.x + offsetLett.x;
                        }
                        pos.y += sizeLett.y + offsetLett.y;
                        i += cntLettRow - 1;
                    }
                    ImGui::SetCursorPosY(pos.y + 5);
                    if (ImGui::Button("Close settings"))
                        SettingsIsOpen = false;

                    ImGui::End();
                }

            }
            else 
                if ((ImGui::Button("Open Settings"))) SettingsIsOpen = true;

            ImGui::Text("Status: %s", GetStatusGame());
            ImGui::Text("Time: %.2f", GetTime());
            ImGui::Text("Hp: %d", GetHp());
            ImGui::Text("InputLetts: %s", GetBufferLett().c_str());
            ImGui::Text("Your word: %s", GetGuessWord().c_str());
            ImGui::End();
        }
        
    }
    if (gameState == Gamming)
    {
        if (ImGui::Begin("HagmanGame"))
        {
            ImGui::Text("Status: %s", GetStatusGame());
            ImGui::Text("Time: %.2f", GetTime());
            ImGui::Text("Hp: %d", GetHp());
            ImGui::Text("InputLetts: %s", GetBufferLett().c_str());
            ImGui::Text("Your word: %s", GetGuessWord().c_str());

            ImVec2 pos(0, ImGui::GetCursorPosY());

            for (char i = 'a'; i <= 'z'; i++)
            {
                pos.x = 0;
                for (int j = i; j < i + cntLettRow && j <= 'z'; j++)
                {
                    ImGui::SetCursorPos(pos);
                    const char Lett[2] = { j };
                    if (ImGui::Button(Lett, ImVec2(sizeLett)))
                    {
                        CheckLett(j);
                    }
                    pos.x += sizeLett.x + offsetLett.x;
                }
                pos.y += sizeLett.y + offsetLett.y;
                i += cntLettRow - 1;
            }
            ImGui::End();
        }
    }
    if (ImGui::Begin("HagmanGame"))
    {
        if (timer.GetElapsedTime() != 0.f)
        {
            if(gameState == Pause)
                if (ImGui::Button("Return to Game"))    gameState = Gamming;
            if(gameState == Gamming)
                if(ImGui::Button("Pause"))              gameState = Pause;
        }
        else
        {
            if (ImGui::Button("Start new Game"))
            {
                init();
                gameState = Gamming;
            }
        }
        ImGui::End();
    }
}

void Game::DrawGUISettings()
{

}

void Game::DrawGUI()
{
    DrawGUIGame();
}
Game::GeneratorWords::GeneratorWords(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        words.push_back(line);
    }

    file.close();
}

std::string Game::GeneratorWords::getRandomWord() const {
    if (!words.empty()) {
        int index = rand() % words.size();
        return words[index];
    }
    return "";
}


void Game::init() {
    word = generator.getRandomWord();
    guessWord = std::string(word.length(), '_');
    bufferLett.clear();
    HP = 10;
    timer.Restart();
}

void Game::StartTimer()   { timer.Start(); }
void Game::PauseTimer()   { timer.Pause(); }
void Game::RestartTimer() { timer.Restart(); }

void Game::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        // Проверяем, что введена буква
        char letter = static_cast<char>(event.text.unicode);
        std::cout << letter << std::endl;
        CheckLett(letter);
    }
    if (gameOver() || win())
    {
        std::system("cls");
        std::printf("=====Statistics Game=====\n");
        std::printf("Status: %s\n", GetStatusGame());
        std::printf("Time: %.2f\n", GetTime());
        std::printf("Hp: %d\n", GetHp());
        std::printf("InputLetts: %s\n", GetBufferLett().c_str());
        std::printf("Your word: %s\n", GetGuessWord().c_str());
        std::printf("Comp word: %s\n", word.c_str());
        std::printf("=========================\n");
        init();
        timer.Pause();
        timer.Restart();
        gameState = Pause;
    }
}

void Game::CheckLett(char letter) {
    if (std::find(bufferLett.begin(), bufferLett.end(), letter) == bufferLett.end() &&
        std::find(bufferLett.begin(), bufferLett.end(), tolower(letter)) == bufferLett.end())
        bufferLett += letter;
    else
        return;
    bool found = false;
    for (int i = 0; i < word.length(); i++) {
        if (tolower(word[i]) == tolower(letter)) {
            guessWord[i] = letter;
            found = true;
        }
    }

    if (!found) {
        HP--;
    }
}

bool Game::gameOver() {
    if(HP <= 0)
    {
        return true;
    }
    return false;
}

bool Game::win()
{
    if (word == guessWord)
    {
        return true;
    }
    return false;
}

bool Game::gaming()
{
    return !(gameOver() || win());
}
int Game::GetHp()
{
    return HP;
}

float Game::GetTime()
{
    return timer.GetElapsedTime();
}

const std::string& Game::GetBufferLett()
{
    return bufferLett;
}

const std::string& Game::GetGuessWord()
{
    return guessWord;
}


const char* Game::GetStatusGame()
{
    if (win()) return "Your Win!!!";
    if (gameOver()) return "You lozer!!!";
    if (timer.GetElapsedTime() == 0.f) return "No Game";
    if (timer.IsPause()) return "Game Pause";
    return "Game Gaming";
}

const char* Game::state_mode(StateGame state)
{
    const char* states[StateCount] = {
        "Gamming",
        "Pause"
    };
    return states[state];
}