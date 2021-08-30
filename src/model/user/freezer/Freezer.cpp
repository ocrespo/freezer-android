/*
 * Freezer.cpp
 *
 *  Created on: 1 Dec 2018
 *      Author: Oscar Crespo
 */

#include "Freezer.h"

namespace freezer {

Freezer::Freezer() :
		next_id(0),
		num_drawer(3)
{

}

Freezer::~Freezer() {

}

int Freezer::addItem(SItem &&item){
	item.id = next_id;
	content.emplace(next_id,item);
	next_id = findNextId();
	return item.id;
}

int Freezer::addItem(int drawer, const std::string& name, const std::string& description){
    return addItem(SItem(drawer,name,description));
}


bool Freezer::moveItem(int key, int drawer){
	bool ret{false};
	auto item{content.find(key)};
	if(item != content.cend()){
	    ret = item->second.setDrawer(drawer);
	}
	return ret;
}

bool Freezer::editItem(int key, int drawer, const std::string& name, const std::string& description){
	bool ret{false};
	auto item{content.find(key)};
	if(item != content.cend()){
	    ret = item->second.updateItem(drawer, name, description);
	}
	return ret;
}

bool Freezer::removeItem(int key){
	bool ret{content.erase(key) == 1};
	next_id = findNextId();
	return ret;
}

SItem Freezer::getItem(int key){
	return content.find(key)->second;
}

std::vector<SItem> Freezer::getItems(){
	std::vector<SItem> items;
	for(auto it = content.cbegin(); it != content.cend(); ++it){
		items.push_back(it->second);
	}
	return items;
}

int Freezer::findNextId(){
	if(content.empty() || content.find(0) == content.cend()){
		return 0;
	}

	bool found{false};
	int key{-1};
	for(auto it = content.cbegin(); it != content.cend() && !found; ++it){
		if(key == -1){
			key = it->second.getId();
		}
		else{
			if(it->second.getId() != key){
				found = true;
			}
		}
		if(!found){
			++key;
		}
	}

	return key;
}



} /* namespace freezer */
