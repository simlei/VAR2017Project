#ifndef SONGPLAYER_H
#define SONGPLAYER_H

#include "guitaroverlay.h"


class SongPlayer
{
public:
    SongPlayer(float inputBpm);
    void setup();
    void update();

    void start();
    void pause();

    struct runningChord{
        GuitarOverlay::Chord chord;
        float beats; //Length of the chord

    };

    std::vector<runningChord> song = std::vector<runningChord>();

    float runningTime;
    float bpm;

private:
    bool running;
    int currentChordIndex;
    float processedBeats;
};

#endif // SONGPLAYER_H
