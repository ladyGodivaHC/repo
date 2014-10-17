#ifndef SMARTINSTRUMENT_H
#define SMARTINSTRUMENT_H
#include "instruments.h"

class SmartInstrument{
public:

    SmartInstrument(Instruments* =0);
    SmartInstrument(const SmartInstrument&);

    ~SmartInstrument();

    SmartInstrument& operator= (const SmartInstrument&);
    Instruments& operator*() const;
    Instruments* operator->() const;
    bool operator==(const SmartInstrument& ) const;
    bool operator!=(const SmartInstrument& ) const;

private:

    Instruments* pointer;

};

#endif // SMARTINSTRUMENT_H
