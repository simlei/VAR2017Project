#ifndef GUITARSTRINGSTATE_H
#define GUITARSTRINGSTATE_H

#include "vector"

class GuitarStringState
{

public:
    GuitarStringState();

    bool getStringState(int stringIdx, int fretIdx);
    void set(int stringIdx, int fretIdx, bool on);

    
private:
    std::vector<std::vector<bool>> state = std::vector<std::vector<bool>>(6);

};

#endif // GUITARSTRINGSTATE_H
