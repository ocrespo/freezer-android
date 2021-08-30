/*
 * User.cpp
 *
 *  Created on: 29 Aug 2021
 *      Author: Oscar Crespo
 */

#include "User.h"

#include "events/EventList.h"



namespace freezer {


User::User() {
    addObserver(EUserEvents::AddedItem,new ocutils::EventList());
    addObserver(EUserEvents::RemovedItem,new ocutils::EventList());
    addObserver(EUserEvents::NextId,new ocutils::EventList());
    addObserver(EUserEvents::NumDrawers,new ocutils::EventList());
    addObserver(EUserEvents::ItemInfo,new ocutils::EventList());
    addObserver(EUserEvents::UpdatedItem,new ocutils::EventList());
}

User::~User() {

}

void User::registerItemAdded(int obs_key, const AddedItem_callback_t& callback) noexcept{
    registerCall<ocutils::EventList,
               std::string,
               int,
               int,
               std::string,
               std::string,
               std::chrono::time_point<std::chrono::system_clock>>(
                       EUserEvents::AddedItem,
                       obs_key,
                       callback);
}

void User::registerItemRemoved(int obs_key, const RemovedItem_callback_t& callback) noexcept{
    registerCall<ocutils::EventList,
               std::string,
               int>(EUserEvents::RemovedItem,
                       obs_key,
                       callback);
}

void User::registerItemUpdated(int obs_key, const UpdatedItem_callback_t& callback) noexcept{
    registerCall<ocutils::EventList,
               std::string,
               int,
               int,
               std::string,
               std::string>(
                       EUserEvents::UpdatedItem,
                       obs_key,
                       callback);
}


int User::addItem(const std::string& freezer_name,
            int drawer,
            const std::string& name,
            const std::string& description){
    int item_id(-1);
    doFreezer(freezer_name,
            [&](freezer::Freezer& freezer){
        SItem item(drawer,name,description);
        item_id = freezer.addItem(std::move(item));
        donotify<ocutils::EventList,
                   std::string,
                   int,
                   int,
                   std::string,
                   std::string,
                   std::chrono::time_point<std::chrono::system_clock>>(
                               EUserEvents::AddedItem,
                               freezer_name,
                               item_id,
                               drawer,
                               name,
                               description,
                               item.getDate());
        return true;
    });
    return item_id;
}

bool User::removeItem(const std::string& freezer_name,
            int id){
    return doFreezer(freezer_name,
            [&](freezer::Freezer& freezer){
        bool ret{freezer.removeItem(id)};
        if(ret){
            donotify<ocutils::EventList,
                    std::string,
                    int>(EUserEvents::RemovedItem,
                        freezer_name,
                        id);
        }
        return ret;
    });
}

bool User::editItem(const std::string& freezer_name,
                    int id,
                    int drawer,
                    const std::string& name,
                    const std::string& description){
    return doFreezer(freezer_name,
            [&](freezer::Freezer& freezer){
        bool ret{freezer.editItem(id, drawer, name, description)};
        if(ret){
            donotify<ocutils::EventList,
                    std::string,
                    int,
                    int,
                    std::string,
                    std::string>(EUserEvents::UpdatedItem,
                            freezer_name,
                        id,
                        drawer,
                        name,description);
        }
        return ret;
    });
}

int User::getNextId(const std::string& freezer_name){
    int id(-1);
    doFreezer(freezer_name,
                [&](freezer::Freezer& freezer){
        id = freezer.getNextId();
        return true;
    });
    return id;
}

int User::getNumDrawers(const std::string& freezer_name){
    int num(-1);
    doFreezer(freezer_name,
                [&](freezer::Freezer& freezer){
        num = freezer.getNumDrawer();
        return true;
    });

    return num;
}

std::vector<SItem> User::getAllItem(){
    std::vector<SItem> vector;
    vector.reserve(50);
    for(auto &freezer : freezers){
        std::vector<SItem>&& items{freezer.second.getItems()};
        vector.insert(vector.end(),
                std::make_move_iterator(items.begin()),
                std::make_move_iterator(items.end()));
    }
    return vector;
}

std::vector<std::string> User::getFreezers(){
    std::vector<std::string> freezers_name;
    freezers_name.reserve(freezers.size());
    std::transform(freezers.begin(), freezers.end(), freezers_name.begin(), [](auto pair){
        return pair.first;
    });

    return freezers_name;
}

bool User::doFreezer(const std::string freezer_name,
        std::function<bool(freezer::Freezer& freezer)> call){
    bool ret(false);
    auto it{freezers.find(freezer_name)};
    if(it != freezers.cend()){
        ret = call(it->second);
    }
    return ret;
}

}
