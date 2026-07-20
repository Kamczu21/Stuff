#pragma once

#include <string>
#include "PlaybackAction.hpp"

class AudioSource {
protected:
    std::string title;
    std::string filename;
    double duration;

public:
    AudioSource(std::string temp_title, double temp_duration, std::string temp_filename)
        : title(std::move(temp_title)), duration(temp_duration), filename(std::move(temp_filename)) {}

    virtual ~AudioSource() = default;

    virtual PlaybackAction play() = 0; 
    virtual AudioSource* clone() const = 0;

    std::string getTitle() const {
        return title;
    }

    std::string getFilename() const {
        return filename;
    }
};