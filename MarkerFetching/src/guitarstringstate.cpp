#include "guitarstringstate.h"
#include "guitar.h"
#include "guitarmeasure.h"

GuitarStringState::GuitarStringState()
{
    for(int i=0; i<6; i++) {
        state[i] = std::vector<bool>(GuitarMeasure::MAX_FRET);
        for(int fret = 0; fret<GuitarMeasure::MAX_FRET; fret++) {
            state[i][fret] = false;
        }
    }
}

bool GuitarStringState::getStringState(int stringIdx, int fretIdx) {
    GuitarMeasure::check_access(stringIdx, fretIdx);
    return state[stringIdx][fretIdx];
}

void GuitarStringState::set(int stringIdx, int fretIdx, bool on) {
    GuitarMeasure::check_access(stringIdx, fretIdx);
    state[stringIdx][fretIdx] = on;
}
