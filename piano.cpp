#include "piano.h"
#include <sstream>

Piano::Piano(double pr, std::string mod, bool ta, std::string wd) : Instruments(pr, mod){

    std::stringstream code_str;
    code_str << code_number;
    std::string final_code = code_str.str() + "_PI";

    this->setCode(final_code);

    tail = ta;
    wood = wd;

    code_number++;
}

//get methods
bool Piano::isTail() const { return tail; }
std::string Piano::getWood() const { return wood; }

//set methods
void Piano::setTail(bool t) { tail = t; }
void Piano::setWood(std::string w) { wood = w; }

//operator==
bool Piano::operator== (const Instruments& i) const {
    Instruments& instr = const_cast<Instruments&>(i);
    Piano* p = dynamic_cast<Piano*>(&instr);
    return (Instruments::operator==(i) && isTail()==p->isTail() && getWood()==p->getWood());
}

int Piano::code_number = 1;
