#include "qmodel.h"

qModel* qModel::_instance = 0;

qModel* qModel::Instance(){
    if(_instance == 0){
        _instance = new qModel;
    }
    return _instance;
}

GenericContainer<SmartInstrument>* qModel::getContainer() {
    return container;
}

qModel::qModel(){
    container = new GenericContainer<SmartInstrument>();
}
