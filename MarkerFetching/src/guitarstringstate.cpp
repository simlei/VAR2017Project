#include "guitarstringstate.h"
#include "guitar.h"
//#include "guitarmeasure.h"

GuitarStringState::GuitarStringState()
{
    for(int i=0; i<Guitar::MAX_STRING; i++) {
        stateBoard[i] = std::vector<bool>(Guitar::MAX_FRET);
        for(int fret = 0; fret<Guitar::MAX_FRET; fret++) {
            stateBoard[i][fret] = false;
        }
    }
}

bool GuitarStringState::getStringState(int stringIdx, int fretIdx) {
    Guitar::check_access(stringIdx, fretIdx);
    return stateBoard[stringIdx][fretIdx];
}

void GuitarStringState::set(int stringIdx, int fretIdx, bool on) {
    Guitar::check_access(stringIdx, fretIdx);
    stateBoard[stringIdx][fretIdx] = on;
}
