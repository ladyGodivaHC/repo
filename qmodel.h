#ifndef QMODEL_H
#define QMODEL_H

#include "genericcontainer.h"
#include "smartinstrument.h"

class qModel{
private:

    qModel(qModel const&);
    void operator=(qModel const&);

    //Similar to design pattern singleton but constructor is not protected.
    //more GenericContainer classes might be instantiated
    //This choice is useful to keep Model and View separated and have a global access point to the Model class
    qModel();
    static qModel* _instance;
    GenericContainer<SmartInstrument>* container;

public:

    static qModel* Instance();
    GenericContainer<SmartInstrument>* getContainer();
};

#endif // QMODEL_H

