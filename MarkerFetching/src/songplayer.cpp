#include "songplayer.h"

const string SongPlayer::SMOKE_ON_THE_WATER = "Smoke on the Water";
const string SongPlayer::SEVEN_NATION_ARMY = "Seven Nation Army";
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
        bpm=100.f;
    }
    if(songName == SEVEN_NATION_ARMY){
    //Seven Nation Army Verse 1 + Chorus
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},4}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},1}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{7, GuitarOverlay::MAYOR},1}); // G
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},1}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{2, GuitarOverlay::MAYOR},1}); // D
        song.push_back(runningChord{GuitarOverlay::Chord{0, GuitarOverlay::MAYOR},2}); // C
        song.push_back(runningChord{GuitarOverlay::Chord{11, GuitarOverlay::MAYOR},2}); // B
        //---
        song.push_back(runningChord{GuitarOverlay::Chord{11, GuitarOverlay::MAYOR},4}); // B
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},4}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},1}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{7, GuitarOverlay::MAYOR},1}); // G
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},1}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{2, GuitarOverlay::MAYOR},1}); // D
        song.push_back(runningChord{GuitarOverlay::Chord{0, GuitarOverlay::MAYOR},2}); // C
        song.push_back(runningChord{GuitarOverlay::Chord{11, GuitarOverlay::MAYOR},2}); // B
        //---
        song.push_back(runningChord{GuitarOverlay::Chord{11, GuitarOverlay::MAYOR},4}); // B
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},4}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},1}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{7, GuitarOverlay::MAYOR},1}); // G
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},1}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{2, GuitarOverlay::MAYOR},1}); // D
        song.push_back(runningChord{GuitarOverlay::Chord{0, GuitarOverlay::MAYOR},2}); // C
        song.push_back(runningChord{GuitarOverlay::Chord{11, GuitarOverlay::MAYOR},2}); // B
        //---
        song.push_back(runningChord{GuitarOverlay::Chord{11, GuitarOverlay::MAYOR},4}); // B
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},4}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},1}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{7, GuitarOverlay::MAYOR},1}); // G
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},1}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{2, GuitarOverlay::MAYOR},1}); // D
        song.push_back(runningChord{GuitarOverlay::Chord{0, GuitarOverlay::MAYOR},2}); // C
        song.push_back(runningChord{GuitarOverlay::Chord{11, GuitarOverlay::MAYOR},2}); // B
        //---
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},4}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},1}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{7, GuitarOverlay::MAYOR},1}); // G
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},1}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{2, GuitarOverlay::MAYOR},1}); // D
        song.push_back(runningChord{GuitarOverlay::Chord{0, GuitarOverlay::MAYOR},2}); // C
        song.push_back(runningChord{GuitarOverlay::Chord{11, GuitarOverlay::MAYOR},2}); // B
        //---
        if(currentChordIndex + 1 < song.size()){
            overlay->nextChord = song.at(currentChordIndex+1).chord;
            std::cout << "Declared next chord to be: " << currentChordIndex+1 << std::endl;
        }
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},4}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},1}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{7, GuitarOverlay::MAYOR},1}); // G
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},1}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{2, GuitarOverlay::MAYOR},1}); // D
        song.push_back(runningChord{GuitarOverlay::Chord{0, GuitarOverlay::MAYOR},2}); // C
        song.push_back(runningChord{GuitarOverlay::Chord{11, GuitarOverlay::MAYOR},2}); // B
        //---
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},4}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},1}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{7, GuitarOverlay::MAYOR},1}); // G
        song.push_back(runningChord{GuitarOverlay::Chord{4, GuitarOverlay::MAYOR},1}); // E
        song.push_back(runningChord{GuitarOverlay::Chord{2, GuitarOverlay::MAYOR},1}); // D
        song.push_back(runningChord{GuitarOverlay::Chord{0, GuitarOverlay::MAYOR},2}); // C
        song.push_back(runningChord{GuitarOverlay::Chord{11, GuitarOverlay::MAYOR},2}); // B
        //---Chorus---
        song.push_back(runningChord{GuitarOverlay::Chord{7, GuitarOverlay::MAYOR},4}); // G
        song.push_back(runningChord{GuitarOverlay::Chord{9, GuitarOverlay::MAYOR},4}); // A
        bpm = 60.f;
    }
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
            overlay->clearLastChord();
            currentChordIndex++;
        }else if((currentChordIndex+1 < song.size())
                 && (runningTime - beatsPlayed*(60.f/bpm) > song.at(currentChordIndex).beats)){
            //std::cout << "Current Beats: " << beatsPlayed << " | Beats to be added: " << song.at(currentChordIndex).beats<< " | From chord: " << song.at(currentChordIndex).chord.baseTone << std::endl;
            beatsPlayed += song.at(currentChordIndex).beats;
            overlay->setChord(song.at(currentChordIndex+1).chord);
            currentChordIndex++;
        }
        //Update next chord
        if(currentChordIndex + 1 < song.size()){
            overlay->nextChord = song.at(currentChordIndex+1).chord;
            std::cout << "Declared next chord to be: " << currentChordIndex+1 << std::endl;
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
