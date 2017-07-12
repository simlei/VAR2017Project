#include "songplayer.h"

SongPlayer::SongPlayer(float inputBpm)
{
    bpm = inputBpm;
    setup();
}

void SongPlayer::setup(){
    running = false;
    runningTime = 0.f;
    processedBeats = 0.f;
    currentChordIndex = 0;

    //Smoke on the water Intro
    song.push_back(runningChord{GuitarOverlay::Chord{9, GuitarOverlay::MAYOR},10}); // A
    song.push_back(runningChord{GuitarOverlay::Chord{0, GuitarOverlay::MAYOR},10}); // C
    song.push_back(runningChord{GuitarOverlay::Chord{2, GuitarOverlay::MAYOR},10}); // D
    song.push_back(runningChord{GuitarOverlay::Chord{9, GuitarOverlay::MAYOR},10}); // A
    song.push_back(runningChord{GuitarOverlay::Chord{0, GuitarOverlay::MAYOR},10}); // C
    song.push_back(runningChord{GuitarOverlay::Chord{3, GuitarOverlay::MAYOR},10}); // Eb
    song.push_back(runningChord{GuitarOverlay::Chord{2, GuitarOverlay::MAYOR},10}); // D
    song.push_back(runningChord{GuitarOverlay::Chord{9, GuitarOverlay::MAYOR},10}); // A
    song.push_back(runningChord{GuitarOverlay::Chord{0, GuitarOverlay::MAYOR},10}); // C
    song.push_back(runningChord{GuitarOverlay::Chord{2, GuitarOverlay::MAYOR},10}); // D
    song.push_back(runningChord{GuitarOverlay::Chord{0, GuitarOverlay::MAYOR},10}); // C
    song.push_back(runningChord{GuitarOverlay::Chord{9, GuitarOverlay::MAYOR},10}); // A
}

void SongPlayer::update(){
    if(running){
        runningTime += (float)ofGetLastFrameTime();
    }
}

void SongPlayer::start(){
    running = true;
}

void SongPlayer::pause(){
    running = false;
}
