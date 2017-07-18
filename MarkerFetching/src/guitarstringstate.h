#ifndef GUITARSTRINGSTATE_H
#define GUITARSTRINGSTATE_H

#include "vector"

class GuitarStringState
{

public:
    GuitarStringState();

    bool getStringState(int stringIdx, int fretIdx);
    void set(int stringIdx, int fretIdx, bool on);
    std::vector<std::vector<bool>> stateBoard = std::vector<std::vector<bool>>(6);



private:
};

#endif // GUITARSTRINGSTATE_H
