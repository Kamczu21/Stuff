#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <iostream>
#include "AudioSource.hpp"
#include "PlaybackAction.hpp"

class Playlist {
private:
    std::vector<AudioSource*> source;
    std::string name;

public:
    Playlist(std::string temp_name) : name(std::move(temp_name)) {}

    ~Playlist() {
        for (size_t i = 0; i < source.size(); ++i) {
            delete source[i];
        }
        source.clear();
    }

    Playlist(const Playlist& other) {
        name = other.name;
        for (size_t i = 0; i < other.source.size(); ++i) {
            source.push_back(other.source[i]->clone());
        }
    }

    Playlist& operator=(const Playlist& other) {
        if (this != &other) {
            for (auto track : source) {
                delete track;
            }
            source.clear();

            name = other.name;
            for (auto track : other.source) {
                source.push_back(track->clone());
            }
        }
        return *this;
    }

    std::string getName() const {
        return name;
    }

    void setName(std::string newName) {
        name = std::move(newName);
    }

    void addTrack(AudioSource* temp_track) {
        source.push_back(temp_track);
    }

    void removeTrack(size_t index) {
        if (index >= source.size()) {
            throw std::out_of_range("Nie mozna usunac pozycji - zly indeks!");
        }
        delete source[index];
        source.erase(source.begin() + index);
    }

    void shuffle() {
        std::random_device random;
        std::mt19937 generator(random());
        std::shuffle(source.begin(), source.end(), generator);
    }

    void sort() {
        std::sort(source.begin(), source.end(), [](AudioSource* a, AudioSource* b) {
            return a->getTitle() < b->getTitle();
        });
    }

    void playAll() {
        if (!source.empty()) {
            playFromIndex(0);
        }
    }

    void playFromIndex(size_t startIndex) {
        if (startIndex >= source.size()) {
            throw std::out_of_range("Nie mozna wystartowac z tego indeksu - zly indeks!");
        }

        size_t i = startIndex;
        while (i < source.size()) {
            PlaybackAction action = source[i]->play();
            if (action == PlaybackAction::Next || action == PlaybackAction::Finished) {
                i++;
            } 
            else if (action == PlaybackAction::Previous) {
                if (i > 0) {
                    i--;
                } else {
                    std::cout << " >> To jest pierwszy utwor na playliscie!" << std::endl;
                }
            } 
            else if (action == PlaybackAction::Stopped) {
                break;
            }
        }
    }

    Playlist& operator+=(AudioSource* temp_track) {
        source.push_back(temp_track);
        return *this;
    }

    AudioSource* getTrack(size_t index) {
        if (index >= source.size()) {
            throw std::out_of_range("Taki index nie istnieje na playliscie!");  
        }
        return source[index];
    }

    size_t getTrackCount() const {
        return source.size();
    }
};