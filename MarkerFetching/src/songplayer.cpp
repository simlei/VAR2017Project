#include "songplayer.h"

const string SongPlayer::SMOKE_ON_THE_WATER = "Smoke on the Water";
const string SongPlayer::SONG_2 = "Song 2";
const string SongPlayer::SONG_3 = "Song 3";
const string SongPlayer::SONG_4 = "Song 4";

SongPlayer::SongPlayer(GuitarOverlay* inputOverlay,string inputName):overlay(inputOverlay){
    overlay = inputOverlay;
    songName = inputName;
    if(songName == SMOKE_ON_THE_WATER){
    //Smoke on the water Intro
        song.push_back(runningChord{GuitarOverlay::Chord{9, GuitarOverlay::MAYOR},4}); // A
        song.push_back(runningChord{GuitarOverlay::Chord{0, GuitarOverlay::MAYOR},4}); // C
        song.push_back(runningChord{GuitarOverlay::Chord{2, GuitarOverlay::MAYOR},4}); // D
        song.push_back(runningChord{GuitarOverlay::Chord{9, GuitarOverlay::MAYOR},4}); // A
        song.push_back(runningChord{GuitarOverlay::Chord{0, GuitarOverlay::MAYOR},4}); // C
        song.push_back(runningChord{GuitarOverlay::Chord{3, GuitarOverlay::MAYOR},4}); // Eb
        song.push_back(runningChord{GuitarOverlay::Chord{2, GuitarOverlay::MAYOR},4}); // D
        song.push_back(runningChord{GuitarOverlay::Chord{9, GuitarOverlay::MAYOR},4}); // A
        song.push_back(runningChord{GuitarOverlay::Chord{0, GuitarOverlay::MAYOR},4}); // C
        song.push_back(runningChord{GuitarOverlay::Chord{2, GuitarOverlay::MAYOR},4}); // D
        song.push_back(runningChord{GuitarOverlay::Chord{0, GuitarOverlay::MAYOR},4}); // C
        song.push_back(runningChord{GuitarOverlay::Chord{9, GuitarOverlay::MAYOR},4}); // A
    }
    bpm=100.f;
    setup();
}

SongPlayer::~SongPlayer(){

}

void SongPlayer::setup(){
    running = false;
    runningTime = 0.f;
    beatsPlayed = 0.f;
    currentChordIndex = -1;
    overlay->resetState();
    overlay->resetChords();
    overlay->mode=1;
}

void SongPlayer::update(){
    if(running){
        //std::cout << "CCIndex: " << currentChordIndex << std::endl;
        //std::cout << "Song size: " << song.size() << std::endl;
        if(currentChordIndex == -1){
            overlay->setChord(song.at(0).chord);
            currentChordIndex++;
        }else if((currentChordIndex+1 < song.size())
                 && (runningTime - beatsPlayed*(bpm/60.f) > song.at(currentChordIndex+1).beats)){
            beatsPlayed += song.at(currentChordIndex+1).beats;
            overlay->setChord(song.at(currentChordIndex+1).chord);
            currentChordIndex++;
        }
        //TODO Update next chord
        if(currentChordIndex + 1 < song.size()){
            overlay->nextChord = song.at(currentChordIndex+1).chord;
        }
        runningTime += (float)ofGetLastFrameTime();
    }
}

void SongPlayer::play(){
    running = true;
}

void SongPlayer::pause(){
    running = false;
}

bool SongPlayer::isRunning(){
    return running;
}
