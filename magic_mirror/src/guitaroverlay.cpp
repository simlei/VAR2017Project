#include "guitaroverlay.h"

GuitarOverlay::GuitarOverlay(Guitar& pGuitar):
    guitar(pGuitar)
{
    setGuitar(pGuitar);
}

void GuitarOverlay::setup(){

}

void GuitarOverlay::customDraw(){

}

void GuitarOverlay::update(){

}

Guitar GuitarOverlay::getGuitar() {
    return guitar;
}

void GuitarOverlay::setGuitar(Guitar &pGuitar) {
    guitar = pGuitar;
    setParent(guitar);
}
