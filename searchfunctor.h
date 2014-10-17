#ifndef SEARCHFUNCTOR_H
#define SEARCHFUNCTOR_H

#include "smartinstrument.h"
#include <locale>
#include <string>

class SearchFunctor{
public:

    SearchFunctor(std::string, std::string, std::string);
    bool operator() (SmartInstrument&) const;

    std::string getInstrument() const;
    std::string getAttribute() const;
    std::string getAttrValue() const;

    std::string toUpper(const std::string&) const;

private:

    std::string Instrument;
    std::string Attribute;
    std::string AttrValue;
};

#endif // SEARCHFUNCTOR_H
