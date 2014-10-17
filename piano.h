#ifndef PIANO_H
#define PIANO_H

#include "instruments.h"

class Piano : public Instruments{
private:

    bool tail;
    std::string wood;

    static int code_number;

public:

    Piano(double, std::string, bool, std::string);

    //get methods
    bool isTail() const;
    std::string getWood() const;

    //set methods
    void setTail(bool tail);
    void setWood(std::string wd);

    bool operator== (const Instruments& i) const;
};

#endif // PIANO_H
