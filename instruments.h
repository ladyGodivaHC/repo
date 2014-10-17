#ifndef INSTRUMENTS_H
#define INSTRUMENTS_H

#include<iostream>

class Instruments{
private:

    double price;
    std::string model;
    std::string code;

public:

    //constructors
    Instruments();
    Instruments(double, std::string, std::string = "");

    //polymorphic
    virtual bool operator== (const Instruments&) const;
    virtual ~Instruments(){}

    //get methods
    std::string getCode() const;
    double getPrice() const;
    std::string getModel() const;

    //set methods
    void setCode(std::string);
    void setPrice(double);
    void setModel(std::string);
};

#endif // INSTRUMENTS_H
