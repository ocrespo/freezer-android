/*
 * Freezer.h
 *
 *  Created on: 1 Dec 2018
 *      Author: Oscar Crespo
 */

#ifndef SRC_MODEL_FREEZER_FREEZER_H_
#define SRC_MODEL_FREEZER_FREEZER_H_

#include <map>
#include <vector>

#include <boost/serialization/map.hpp>

#include "Item.h"

namespace freezer {

class Freezer {
public:
	Freezer();
	virtual ~Freezer();

	inline int getNextId()const{return next_id;}

	inline void setNumDrawer(int drawers){num_drawer = drawers;}
	inline int getNumDrawer()const{return num_drawer;}

	int addItem(int drawer, const std::string& name, const std::string& description);

	bool moveItem(int key, int drawer);

	bool editItem(int key, int drawer, const std::string& name, const std::string& description);

	bool removeItem(int key);

	Item getItem(int key);
	std::vector<Item> getItems();

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        //ar & boost::serialization::make_nvp("version",version);
        ar & BOOST_SERIALIZATION_NVP(num_drawer);
        ar & BOOST_SERIALIZATION_NVP(next_id);
        ar & BOOST_SERIALIZATION_NVP(content);
    }

protected:

	int findNextId();

	std::map<int,Item> content;
	int next_id;

	int num_drawer;


private:


};

} /* namespace freezer */

#endif /* SRC_MODEL_FREEZER_FREEZER_H_ */
