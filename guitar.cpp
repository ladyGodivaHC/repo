#include "guitar.h"
#include <sstream>

Guitar::Guitar(double pr, std::string mod, int str, int fret) : Instruments(pr, mod){

    std::stringstream code_str;
    code_str << code_number;
    std::string final_code = code_str.str() + "_GU";

    this->setCode(final_code);

    nStrings = str;
    nFrets = fret;

    code_number++;
}


//get methods
int Guitar::getStrings() const {return nStrings;}
int Guitar::getFrets() const {return nFrets;}

//set methods
void Guitar::setStrings(int ns) {nStrings = ns;}
void Guitar::setFrets(int nf) {nFrets = nf;}

//operator ==
bool Guitar::operator== (const Instruments& i) const {
    Instruments& instr = const_cast<Instruments&>(i);
    Guitar* g = dynamic_cast<Guitar*>(&instr);
    return (Instruments::operator==(i) && getStrings()==g->getStrings() && getFrets()==g->getFrets());
}

int Guitar::code_number = 1;

