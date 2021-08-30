/*
 * Model.cpp
 *
 *  Created on: 10 Dec 2017
 *      Author: Oscar Crespo
 */

#include "Model.h"

#include <fstream>

//#include <boost/archive/xml_oarchive.hpp>
//#include <boost/archive/xml_iarchive.hpp>

#include <events/EventUniq.h>

#include "user/User.h"

const std::string filename("values_freezer.xml");

Model::Model() :
	user(std::make_unique<freezer::User>())
{
}

Model::~Model() {

}

void Model::registerItemAdded(const AddedItem_callback_t& callback){
    user->registerItemAdded(getObserverId(),[&](const std::string& freezer,
            int item_id,
            int drawer,
            const std::string& name,
            const std::string& description,
            const std::chrono::time_point<std::chrono::system_clock>& date){
        callback(freezer,
                item_id,
                drawer,
                name,
                description,
                date);
        notifyNextId(freezer);
    });
}

void Model::registerItemRemoved(const RemovedItem_callback_t& callback){
    user->registerItemRemoved(getObserverId(),[&](const std::string& freezer,
            int id){
        callback(freezer,id);
        notifyNextId(freezer);
    });
}

void Model::registerItemUpdated(const UpdatedItem_callback_t& callback){
    user->registerItemUpdated(getObserverId(),callback);
}

void Model::registerNextId(const Int_callback_t& callback){
	addObserver(EModelEvents::NextId,new ocutils::EventUniq(callback));
}

void Model::registerNumDrawers(const Int_callback_t& callback){
	addObserver(EModelEvents::NumDrawers,new ocutils::EventUniq(callback));
}


void Model::registerAllItem(const AllItems_callback_t& callback){
    addObserver(EModelEvents::AllItems,new ocutils::EventUniq(callback));
}

void Model::registerInitFinished(const Void_callback_t& callback){
    addObserver(EModelEvents::InitFinished,new ocutils::EventUniq(callback));
}

void Model::notifyNextId(const std::string& freezer){
    donotify<ocutils::EventUniq,std::string,int>(EModelEvents::NextId,freezer,user->getNextId(freezer));
}

void Model::notifyNumDrawers(const std::string& freezer){
    donotify<ocutils::EventUniq,std::string,int>(EModelEvents::NumDrawers,freezer,user->getNumDrawers(freezer));
}

void Model::requestInitialInfo(){
    std::vector<freezer::SItem>&& items{user->getAllItem()};
    donotify<ocutils::EventUniq,std::vector<freezer::SItem>>(EModelEvents::AllItems,items);

    std::vector<std::string>&& freezers{user->getFreezers()};
    for(auto &it : freezers){
        notifyNextId(it);
        notifyNumDrawers(it);
    }

    donotify<ocutils::EventUniq>(EModelEvents::InitFinished);
}

void Model::addItem(const std::string& freezer,
        int drawer,
        const std::string& name,
        const std::string& description){
    user->addItem(freezer, drawer, name, description);
}

void Model::modifyItem(const std::string& freezer,
        int id,
        int drawer,
        const std::string& name,
        const std::string& description){
    user->editItem(freezer, id, drawer, name, description);
}

void Model::removeItem(const std::string& freezer,
        int id){
    user->removeItem(freezer, id);
}



