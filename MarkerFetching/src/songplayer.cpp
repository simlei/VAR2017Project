#include "songplayer.h"

void SongPlayer::setup(){
    running = false;
    runningTime = 0.f;
    processedBeats = 0.f;
    currentChordIndex = -1;

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
        if(currentChordIndex == -1){
            overlay.setChord(song.at(0).chord);
        }else{

        }
        runningTime += (float)ofGetLastFrameTime();
    }
}

void SongPlayer::start(){
    running = true;
}

void SongPlayer::pause(){
    running = false;
}
