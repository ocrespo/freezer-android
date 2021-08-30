/*
 * ItemViewData.h
 *
 *  Created on: 30 Aug 2021
 *      Author: Oscar Crespo
 */

#ifndef SRC_VIEW_ITEMVIEWDATA_H_
#define SRC_VIEW_ITEMVIEWDATA_H_

#include <QString>
#include <QDate>

class ItemViewData {
public:
    ItemViewData(const QString& freezer,
                int id,
                int drawer,
                const QString& name,
                const QString& description);
    virtual ~ItemViewData();

    inline QString getFreezer()const {return freezer;}
    inline int getId()const {return id;}
    inline int getDrawer()const {return drawer;}

    inline QString getName()const {return name;}
    inline QString getDescription()const {return description;}

private:

    QString freezer;
    int id;
    int drawer;
    QString name;
    QString description;
    QDate date;


};

#endif /* SRC_VIEW_ITEMVIEWDATA_H_ */
