#include "modifyfunctor.h"
#include <iostream>
#include <typeinfo>

bool ModifyFunctor::operator()(SmartInstrument& si, SmartInstrument& ssi){

    if(si->getCode() == ssi->getCode()){

        Guitar* gp = dynamic_cast<Guitar*>(&(*si));

        if(gp!=NULL){

            Guitar* current = dynamic_cast<Guitar*>(&(*ssi));

            gp->setPrice(current->getPrice());
            gp->setModel(current->getModel());

            gp->setStrings(current->getStrings());
            gp->setFrets(current->getFrets());

        }
        else{

            Piano* pp = dynamic_cast<Piano*>(&(*si));
            if(pp){
                Piano* current = dynamic_cast<Piano*>(&(*ssi));

                pp->setPrice(current->getPrice());
                pp->setModel(current->getModel());

                pp->setTail(current->isTail());
                pp->setWood(current->getWood());
            }
        }

        return 1;
    }

    else
        return 0;

}
