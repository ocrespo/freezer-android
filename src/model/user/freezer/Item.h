/*
 * Item.h
 *
 *  Created on: 1 Dec 2018
 *      Author: Oscar Crespo
 */

#ifndef SRC_MODEL_FREEZER_ITEM_H_
#define SRC_MODEL_FREEZER_ITEM_H_

#include <string>
#include <chrono>

namespace freezer {

struct SItem {
    int id;
    int drawer;
    std::string name;
    std::string description;
    std::chrono::time_point<std::chrono::system_clock> date;

    inline SItem():id(0),
            drawer(0){};

    inline SItem(int drawer, const std::string& name, const std::string& description = ""):
        id(0),
        drawer(drawer),
        name(name),
        description(description),
        date(std::chrono::system_clock::now()){};

    inline SItem(int id, int drawer, const std::string& name, const std::string& description = ""):
        id(id),
        drawer(drawer),
        name(name),
        description(description),
        date(std::chrono::system_clock::now()){};

	inline virtual ~SItem(){};


	inline int getId()const {return id;}

	inline int getDrawer()const {return drawer;}
	inline bool setDrawer(int drawer){
	    bool changed{false};
	    if(this->drawer != drawer){
	        this->drawer = drawer;
	        changed = true;
       }
       return changed;
	}

	inline std::string getName()const {return name;}
	inline bool setName(const std::string& name){
        bool changed{false};
	    if(this->name != name){
	        this->name = name;
            changed = true;
        }
        return changed;
	}

	inline std::string getDescription()const {return description;}
	inline bool setDescription(const std::string& description){
        bool changed{false};
	    if(this->description != description){
	        this->description = description;
            changed = true;
        }
        return changed;
	}

	inline std::chrono::time_point<std::chrono::system_clock> getDate()const {return date;}

	inline bool updateItem(int drawer, const std::string& name, const std::string& description){
	    bool ret{setDrawer(drawer)};
	    ret |= setName(name);
        ret |= setDescription(description);
        return ret;
	}


};

} /* namespace freezer */

#endif /* SRC_MODEL_FREEZER_ITEM_H_ */
