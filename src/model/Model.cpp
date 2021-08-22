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

#include "freezer/Freezer.h"

const std::string filename("values_freezer.xml");

Model::Model() :
	freezer(new freezer::Freezer())
{
    load(filename);
}

Model::~Model() {
	delete freezer;
}

void Model::registerItemAdded(const AddedItem_callback_t& callback){
	addObserver(EModelEvents::AddedItem,new  ocutils::EventUniq(callback));
}

void Model::registerItemRemoved(const Int_callback_t& callback){
	addObserver(EModelEvents::RemovedItem,new  ocutils::EventUniq(callback));
}

void Model::registerNextId(const Int_callback_t& callback){
	addObserver(EModelEvents::NextId,new  ocutils::EventUniq(callback));
}

void Model::registerNumDrawers(const Int_callback_t& callback){
	addObserver(EModelEvents::NumDrawers,new  ocutils::EventUniq(callback));
}

void Model::registerItemInfo(const AddedItem_callback_t& callback){
    addObserver(EModelEvents::ItemInfo,new  ocutils::EventUniq(callback));
}

void Model::registerItemUpdated(const UpdatedItem_callback_t& callback){
    addObserver(EModelEvents::UpdatedItem,new  ocutils::EventUniq(callback));
}

void Model::registerInitFinished(const Void_callback_t& callback){
    addObserver(EModelEvents::InitFinished,new  ocutils::EventUniq(callback));
}




void Model::requestInitialInfo(){
	donotify<ocutils::EventUniq,int>(EModelEvents::NextId,freezer->getNextId());
	donotify<ocutils::EventUniq,int>(EModelEvents::NumDrawers,freezer->getNumDrawer());

	std::vector<freezer::Item> items{freezer->getItems()};
	for(auto it{items.cbegin()}; it != items.cend(); ++it){
		donotify<ocutils::EventUniq,
				int,
				int,
				std::string,
				std::string,
				std::string>(EModelEvents::AddedItem,
							it->getId(),
							it->getDrawer(),
							it->getName(),
							it->getDescription(),
							it->getStringDate());
	}
    donotify<ocutils::EventUniq>(EModelEvents::InitFinished);
}

void Model::addItem(int drawer,const std::string& name, const std::string& description){
	int ret{freezer->addItem(drawer,name,description)};
	save(filename);
	donotify<ocutils::EventUniq,
			int,
			int,
			std::string,
			std::string,
			std::string>(EModelEvents::AddedItem,
						ret,
						drawer,
						name,
						description,
						freezer->getItem(ret).getStringDate());
    donotify<ocutils::EventUniq,int>(EModelEvents::NextId,freezer->getNextId());

}

void Model::modifyItem(int id, int drawer,const std::string& name, const std::string& description){
    if(freezer->editItem(id,drawer,name,description)){
        save(filename);

        donotify<ocutils::EventUniq,
                           int,
                           int,
                           std::string,
                           std::string>(EModelEvents::UpdatedItem,
                                       id,
                                       drawer,
                                       name,
                                       description);
    }
}

void Model::removeItem(int id){
	if(freezer->removeItem(id)){
	    save(filename);

		donotify<ocutils::EventUniq,int>(EModelEvents::RemovedItem,id);
	    donotify<ocutils::EventUniq,int>(EModelEvents::NextId,freezer->getNextId());
	}
}

void Model::requestItemInfo(int id){
    freezer::Item item(freezer->getItem(id));

    donotify<ocutils::EventUniq,
                    int,
                    int,
                    std::string,
                    std::string,
                    std::string>(EModelEvents::ItemInfo,
                                item.getId(),
                                item.getDrawer(),
                                item.getName(),
                                item.getDescription(),
                                item.getStringDate());
}


void Model::save(const std::string& path){
    /*std::ofstream file(path);

    boost::archive::xml_oarchive oarch(file);
    oarch << BOOST_SERIALIZATION_NVP(freezer);*/
}

void Model::load(const std::string& path){
    /*std::ifstream file(path);
    if(!file.fail()){
        boost::archive::xml_iarchive iarch(file);
        iarch >> BOOST_SERIALIZATION_NVP(freezer);
    }*/
}


