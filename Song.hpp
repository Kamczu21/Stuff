#pragma once

#include <string>
#include <iostream>
#include "AudioSource.hpp"
#include "PlaybackAction.hpp"

class Song : public AudioSource {
private:
    std::string artist;

public:
    Song(std::string temp_title, std::string temp_artist, double temp_duration, std::string temp_filename) 
        : AudioSource(std::move(temp_title), temp_duration, std::move(temp_filename)), artist(std::move(temp_artist)) {}

    std::string getArtist() const {
        return artist;
    }

    PlaybackAction play() override {
        std::cout << "Odtwarzana piosenka: " << artist << " - " << title << std::endl;
        return playAudioFileWithControls(filename, artist + " - " + title);
    }

    AudioSource* clone() const override {
        return new Song(*this);
    }

    friend std::ostream& operator<<(std::ostream& os, const Song& song) {
        os << "Utwor: " << song.title << ", Autorstwa " << song.artist << ", " << song.duration << ". \n";
        return os;
    }
};