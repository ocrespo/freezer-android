/*
 * ItemViewData.cpp
 *
 *  Created on: 30 Aug 2021
 *      Author: Oscar Crespo
 */

#include "ItemViewData.h"

ItemViewData::ItemViewData(const QString& freezer,
        int id,
        int drawer,
        const QString& name,
        const QString& description):
            freezer(freezer),
            id(id),
            drawer(drawer),
            name(name),
            description(description){

}

ItemViewData::~ItemViewData() {
    // TODO Auto-generated destructor stub
}

