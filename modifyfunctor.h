#ifndef MODIFYFUNCTOR_H
#define MODIFYFUNCTOR_H

#include "smartinstrument.h"
#include "guitar.h"
#include "piano.h"

class ModifyFunctor{
private:

public:
    bool operator() (SmartInstrument& si, SmartInstrument& ssi);
};

#endif // MODIFYFUNCTOR_H
