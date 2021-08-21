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

int Freezer::addItem(int drawer, const std::string& name, const std::string& description){
	int ret{next_id};
	content.emplace(next_id,Item(next_id,drawer,name,description));
	next_id = findNextId();

	return ret;
}

bool Freezer::moveItem(int key, int drawer){
	bool ret{false};
	auto item{content.find(key)};
	if(item != content.cend()){
		item->second.setDrawer(drawer);
		ret = true;
	}
	return ret;
}

bool Freezer::editItem(int key,  int drawer, const std::string& name, const std::string& description){
	bool ret{false};
	auto item{content.find(key)};
	if(item != content.cend()){
		item->second.setName(name);
		item->second.setDescription(description);
        item->second.setDrawer(drawer);
		ret = true;
	}
	return ret;
}

bool Freezer::removeItem(int key){
	bool ret{content.erase(key) == 1};
	next_id = findNextId();
	return ret;
}

Item Freezer::getItem(int key){
	return content.find(key)->second;
}

std::vector<Item> Freezer::getItems(){
	std::vector<Item> items;
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
