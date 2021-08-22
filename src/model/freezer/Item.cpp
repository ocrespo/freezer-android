/*
 * Item.cpp
 *
 *  Created on: 1 Dec 2018
 *      Author: Oscar Crespo
 */

#include "Item.h"

namespace freezer {

Item::Item():
	id(0),
	drawer(0),
	date(boost::gregorian::day_clock::universal_day())
{

}

Item::Item(int id, int drawer, const std::string& name, const std::string& description):
		id(id),
		drawer(drawer),
		name(name),
		description(description),
		date(boost::gregorian::day_clock::universal_day())
{

}

Item::~Item() {
}

} /* namespace freezer */
