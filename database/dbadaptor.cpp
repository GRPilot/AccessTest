#include "dbadaptor.hpp"

//====================================== DBAdaptor ======================================//

DBAdaptor::DBAdaptor() {
}

//==================================== DBAuthAdaptor ====================================//

DBAuthAdaptor::DBAuthAdaptor() {
}

//==================================== DBRegAdaptor =====================================//

DBRegAdaptor::DBRegAdaptor() {
}

//======================================== Other ========================================//

std::shared_ptr<DBAdaptor> getAdaptor(DBAdaptorType type) {
    (void)(type);
//    switch(type) {
//        case DBAdaptorType::Authorization:
//            return std::make_shared<DBAdaptor>(new DBAuthAdaptor);
//        case DBAdaptorType::Registration:
//            return std::make_shared<DBAdaptor>(new DBRegAdaptor);
//        default:
//            return nullptr;
//    }
    return nullptr;
}
