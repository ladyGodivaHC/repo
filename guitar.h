#ifndef GUITAR_H
#define GUITAR_H

#include "instruments.h"

class Guitar : public Instruments{
private:

    int nStrings;
    int nFrets;

    static int code_number;

public:

    Guitar(double, std::string, int, int);

    //getCode inherited from Instruments
    //setCode inherited from Instruments

    //get methods
    int getStrings() const;
    int getFrets() const;

    //set methods
    void setStrings(int ns);
    void setFrets(int nf);

    bool operator== (const Instruments& i) const;
};

#endif // GUITAR_H

