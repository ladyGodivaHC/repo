#include "instruments.h"

Instruments::Instruments(){}

Instruments::Instruments(double p, std::string m, std::string cod): price(p), model(m), code(cod){}


std::string Instruments::getCode() const { return code; }
double Instruments::getPrice() const { return price; }
std::string Instruments::getModel() const { return model; }


void Instruments::setPrice(double p) { price=p; }
void Instruments::setCode(std::string cod) { code=cod; }
void Instruments::setModel(std::string mod) { model=mod;}


bool Instruments::operator== (const Instruments& i) const{
    return (getCode()==i.getCode() && getPrice()==i.getPrice() && getModel()==i.getModel());
}

