#include "smartinstrument.h"

SmartInstrument::SmartInstrument(Instruments *p):pointer(p){}

SmartInstrument::SmartInstrument(const SmartInstrument& p):pointer(p.pointer){}

SmartInstrument::~SmartInstrument(){
    delete pointer;
}

SmartInstrument& SmartInstrument::operator= (const SmartInstrument& p){
    if(this!=&p){
        Instruments* t = pointer;
        pointer=p.pointer;
        delete t;
    }
    return *this;
}

Instruments& SmartInstrument::operator*() const{
    return const_cast<Instruments&>(*pointer);
}

Instruments* SmartInstrument::operator->() const{
    return const_cast<Instruments*>(pointer);
}

bool SmartInstrument::operator==(const SmartInstrument& p) const{
    return pointer == p.pointer;
}

bool SmartInstrument::operator!=(const SmartInstrument& p) const{
    return pointer != p.pointer;
}
