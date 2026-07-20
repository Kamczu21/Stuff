#pragma once

#include <string>
#include <iostream>
#include "AudioSource.hpp"
#include "PlaybackAction.hpp"

class Podcast : public AudioSource {
private:
    std::string host;
    int episodeN;

public:
    Podcast(std::string temp_title, int temp_episodeN, std::string temp_host, double temp_duration, std::string temp_filename) 
        : AudioSource(std::move(temp_title), temp_duration, std::move(temp_filename)), host(std::move(temp_host)), episodeN(temp_episodeN) {}

    std::string getHost() const {
        return host;
    }

    int getEpisodeN() const {
        return episodeN;
    }

    PlaybackAction play() override {
        std::cout << "Odtwarzany podcast: " << host << " - " << title << " | Epizod " << episodeN << std::endl;
        return playAudioFileWithControls(filename, title + " (Epizod " + std::to_string(episodeN) + ")");
    }

    AudioSource* clone() const override {
        return new Podcast(*this); 
    }
};