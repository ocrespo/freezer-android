/*
 * Freezer_test.cpp
 *
 *  Created on: 2 Dec 2018
 *      Author: Oscar Crespo
 */

#include <fstream>

#include <gtest/gtest.h>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include <model/freezer/Freezer.h>
#include <events/EventStore.h>


class FreezerTest : public ::testing::Test {

public:
	FreezerTest(){};


protected:

	  void SetUp() override {
		freezer.addItem(0,"A","B");
		freezer.addItem(0,"B","B");
		freezer.addItem(0,"C","B");
		freezer.addItem(0,"D","B");
		freezer.addItem(0,"E","B");
	}

	freezer::Freezer freezer;


private:

};

TEST_F(FreezerTest, addItem) {
	freezer::Freezer freezer;
	freezer.addItem(0,"A","B");
	EXPECT_EQ(freezer.getNextId() , 1);

	freezer.addItem(0,"B","B");
	EXPECT_EQ(freezer.getNextId() , 2);

	freezer.addItem(0,"C","B");
	EXPECT_EQ(freezer.getNextId() , 3);

	freezer.addItem(0,"D","B");
	EXPECT_EQ(freezer.getNextId() , 4);

	freezer.addItem(0,"E","B");
	EXPECT_EQ(freezer.getNextId() , 5);

	EXPECT_EQ(freezer.getItems().size(), 5);

}

TEST_F(FreezerTest, removeItem) {

	EXPECT_EQ(freezer.removeItem(5), false);

	EXPECT_EQ(freezer.removeItem(4), true);
	EXPECT_EQ(freezer.removeItem(4), false);

	EXPECT_EQ(freezer.getNextId() , 4);

	EXPECT_EQ(freezer.removeItem(2), true);
	EXPECT_EQ(freezer.getNextId() , 2);

	EXPECT_EQ(freezer.removeItem(0), true);
	EXPECT_EQ(freezer.getNextId() , 0);

	EXPECT_EQ(freezer.getItem(1).getName(), "B");
	EXPECT_EQ(freezer.getItem(3).getName(), "D");

	std::vector<freezer::Item> items{freezer.getItems()};
	EXPECT_EQ(items.size(), 2);
	EXPECT_EQ(items[0].getId(), 1);
	EXPECT_EQ(items[0].getName(), "B");
	EXPECT_EQ(items[1].getId(), 3);
	EXPECT_EQ(items[1].getName(), "D");
}


TEST_F(FreezerTest, editItem) {
	EXPECT_EQ(freezer.getItem(0).getName(), "A");

	freezer.editItem(0,1,"AA","AAA");
	EXPECT_EQ(freezer.getItem(0).getName(), "AA");

}

TEST_F(FreezerTest, serilizationSave) {
	//std::stringstream ss;
    std::ofstream ofs("test.xml");

	boost::archive::xml_oarchive oarch(ofs);
	oarch << BOOST_SERIALIZATION_NVP(freezer);
}
TEST_F(FreezerTest, serilizationLoad) {

	freezer::Freezer freezer2;

	std::ifstream ifs("test.xml");

	boost::archive::xml_iarchive iarch(ifs);
	iarch >> BOOST_SERIALIZATION_NVP(freezer2);

	EXPECT_EQ(freezer2.getItem(0).getName(), freezer.getItem(0).getName());
	EXPECT_EQ(freezer2.getItem(1).getName(), freezer.getItem(1).getName());
	EXPECT_EQ(freezer2.getItem(2).getName(), freezer.getItem(2).getName());
	EXPECT_EQ(freezer2.getItem(3).getName(), freezer.getItem(3).getName());
	EXPECT_EQ(freezer2.getItem(4).getName(), freezer.getItem(4).getName());
}



