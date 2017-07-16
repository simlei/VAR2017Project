#ifndef SONGPLAYER_H
#define SONGPLAYER_H

#include "ofMain.h"
#include "guitaroverlay.h"


class SongPlayer
{
public:
    SongPlayer(GuitarOverlay* inputOverlay, string songName);
    ~SongPlayer();

    void setup();
    void update();
    void play();
    void pause();
    bool isRunning();

    struct runningChord{
        GuitarOverlay::Chord chord;
        float beats; //Length of the chord
    };
    string songName;
    std::vector<runningChord> song = std::vector<runningChord>();
    float runningTime;
    float bpm;
    GuitarOverlay* overlay;

    //Constant Fields
    const static string SMOKE_ON_THE_WATER;
    const static string SONG_2;
    const static string SONG_3;
    const static string SONG_4;

private:
    bool running;
    int currentChordIndex;
    float beatsPlayed;
};

#endif // SONGPLAYER_H
