#include "searchfunctor.h"
#include <typeinfo>
#include <iostream>
#include <sstream>
#include "instruments.h"
#include "guitar.h"
#include "piano.h"

SearchFunctor::SearchFunctor(std::string s1, std::string s2, std::string s3) :
    Instrument(s1), Attribute(s2), AttrValue(s3) {}

std::string SearchFunctor::getInstrument() const {return Instrument;}
std::string SearchFunctor::getAttribute() const {return Attribute;}
std::string SearchFunctor::getAttrValue() const {return AttrValue;}

//converts the string to uppercase
std::string SearchFunctor::toUpper(const std::string& s) const{
    std::string result;
    std::locale loc;

    for (unsigned int i = 0; i < s.length(); ++i){
        result += std::toupper(s.at(i), loc);
    }
    return result;
}

//overloading operator()
bool SearchFunctor::operator()(SmartInstrument& si) const {

    if(getInstrument() == "Guitar"){
        Guitar* g = dynamic_cast<Guitar*>(&(*si));
        if(g){
            if(getAttribute() == "Code")
                return ((toUpper(g->getCode())) == (toUpper(getAttrValue())));
            else if(getAttribute() == "Model")
                return (toUpper(g->getModel()) == toUpper(getAttrValue()));
            else if(getAttribute() == "Price"){
                double price;
                std::stringstream ss(getAttrValue());
                ss >> price;
                return g->getPrice() == price;
            }
            else if(getAttribute() == "Strings"){
                std::stringstream ss(getAttrValue());
                int strings;
                ss >> strings;
                return g->getStrings() == strings;
            }
            else if(getAttribute() == "Frets"){
                std::stringstream ss(getAttrValue());
                int frets;
                ss >> frets;
                return g->getFrets() == frets;
            }
        }
    }

    else{
        Piano* p = dynamic_cast<Piano*>(&(*si));
        if(p){
            if(getAttribute() == "Code")
                return (toUpper(p->getCode()) == toUpper(getAttrValue()));
            else if(getAttribute() == "Model")
                return (toUpper(p->getModel()) == toUpper(getAttrValue()));
            else if(getAttribute() == "Price"){
                double price;
                std::stringstream ss(getAttrValue());
                ss >> price;
                return p->getPrice() == price;
            }
            else if(getAttribute() == "Shape"){
                bool grand;
                if(getAttrValue() == "true")
                    grand=true;
                else
                    grand=false;
                return p->isTail() == grand;
            }
            else if(getAttribute() == "Wood"){
                return (toUpper(p->getWood()) == toUpper(getAttrValue()));
            }
        }
    }
}

