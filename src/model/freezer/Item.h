/*
 * Item.h
 *
 *  Created on: 1 Dec 2018
 *      Author: Oscar Crespo
 */

#ifndef SRC_MODEL_FREEZER_ITEM_H_
#define SRC_MODEL_FREEZER_ITEM_H_

#include <string>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/greg_serialize.hpp>
#include <boost/serialization/nvp.hpp>

namespace freezer {

class Item {
public:
	Item();
	Item(int id, int drawer, const std::string& name, const std::string& description = "");
	virtual ~Item();

	inline int getId()const {return id;}

	inline int getDrawer()const {return drawer;}
	inline void setDrawer(int drawer){ this->drawer = drawer;}

	inline std::string getName()const {return name;}
	inline void setName(const std::string& name){ this->name = name;}

	inline std::string getDescription()const {return description;}
	inline void setDescription(const std::string& description){ this->description = description;}

	inline boost::gregorian::date getDate()const {return date;}
	inline std::string getStringDate()const {return boost::gregorian::to_sql_string(date);}


    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & BOOST_SERIALIZATION_NVP(id);
        ar & BOOST_SERIALIZATION_NVP(drawer);
        ar & BOOST_SERIALIZATION_NVP(name);
        ar & BOOST_SERIALIZATION_NVP(description);
        ar & BOOST_SERIALIZATION_NVP(date);
    }

protected:


	int id;
	int drawer;
	std::string name;
	std::string description;
	boost::gregorian::date date;

private:


};

} /* namespace freezer */

#endif /* SRC_MODEL_FREEZER_ITEM_H_ */
