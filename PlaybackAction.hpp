#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <SFML/Audio.hpp>

enum class PlaybackAction {
    Finished, // ~FIN
    Next,     // [N]
    Previous, // [P]
    Stopped   // [S] / [ESC]
};

inline PlaybackAction playAudioFileWithControls(const std::string& filename, const std::string& displayInfo) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        std::cout << "Nie udalo sie wczytac pliku audio: " << filename << std::endl;
        return PlaybackAction::Stopped;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    std::cout << "\n=======================================================" << std::endl;
    std::cout << "Odtwarzanie: " << displayInfo << std::endl;
    std::cout << "KONTROLA:" << std::endl;
    std::cout << "  [SPACJA]     - Pauza / Wznowienie" << std::endl;
    std::cout << "  [STRZALKA >] - Przewin +10 sek" << std::endl;
    std::cout << "  [STRZALKA <] - Przewin -10 sek" << std::endl;
    std::cout << "  [N]          - Nastepny utwor" << std::endl;
    std::cout << "  [P]          - Poprzedni utwor" << std::endl;
    std::cout << "  [S] / [ESC]  - Stop" << std::endl;
    std::cout << "=======================================================\n" << std::endl;

    while (_kbhit()) {
        _getch();
    }

    while (sound.getStatus() == sf::Sound::Playing || sound.getStatus() == sf::Sound::Paused) {
        sf::sleep(sf::milliseconds(20));

        if (_kbhit()) {
            int key = _getch();

            if (key == 0 || key == 224) {
                int arrowKey = _getch();
                if (arrowKey == 77) { // Strzalka w prawo
                    sf::Time currentOffset = sound.getPlayingOffset();
                    sf::Time targetOffset = currentOffset + sf::seconds(10);
                    if (targetOffset > buffer.getDuration()) {
                        targetOffset = buffer.getDuration();
                    }
                    sound.setPlayingOffset(targetOffset);
                    int totalSeconds = static_cast<int>(targetOffset.asSeconds());
                    int minutes = totalSeconds / 60;
                    int seconds = totalSeconds % 60;

                    std::cout << " >> [+10s] Pozycja: " << minutes << "m " << (seconds < 10 ? "0" : "") << seconds << "s" << std::endl;
                }
                else if (arrowKey == 75) { // Strzalka w lewo
                    sf::Time currentOffset = sound.getPlayingOffset();
                    sf::Time targetOffset = (currentOffset > sf::seconds(10)) ? (currentOffset - sf::seconds(10)) : sf::Time::Zero;
                    sound.setPlayingOffset(targetOffset);
                    int totalSeconds = static_cast<int>(targetOffset.asSeconds());
                    int minutes = totalSeconds / 60;
                    int seconds = totalSeconds % 60;

                    std::cout << " >> [-10s] Pozycja: " << minutes << "m " << (seconds < 10 ? "0" : "") << seconds << "s" << std::endl;
                }
            }
            else if (key == ' ') { // Spacja
                if (sound.getStatus() == sf::Sound::Playing) {
                    sound.pause();
                    std::cout << " >> [PAUZA]" << std::endl;
                } else {
                    sound.play();
                    std::cout << " >> [WZNOWIONO]" << std::endl;
                }
            }
            else if (key == 'n' || key == 'N') {
                sound.stop();
                std::cout << " >> [NASTEPNY UTWOR]" << std::endl;
                return PlaybackAction::Next;
            }
            else if (key == 'p' || key == 'P') {
                sound.stop();
                std::cout << " >> [POPRZEDNI UTWOR]" << std::endl;
                return PlaybackAction::Previous;
            }
            else if (key == 's' || key == 'S' || key == 27) { // ESC
                sound.stop();
                std::cout << " >> [ZATRZYMANO ODTWARZANIE]" << std::endl;
                return PlaybackAction::Stopped;
            }
        }
    }

    return PlaybackAction::Finished;
}