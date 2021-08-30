/*
 * FilterFreezerPage.cpp
 *
 *  Created on: 30 Aug 2021
 *      Author: Oscar Crespo
 */

#include "FilterFreezerPage.h"

#include "FreezerPageModel.h"

FilterFreezerPage::FilterFreezerPage(QObject* parent) :
    QSortFilterProxyModel()
{
}

FilterFreezerPage::~FilterFreezerPage(){

}

bool FilterFreezerPage::lessThan(const QModelIndex &source_left,
        const QModelIndex &source_right) const
{

    QVariant leftData = sourceModel()->data(source_left,FreezerPageModel::IdRole);
    QVariant rightData = sourceModel()->data(source_right,FreezerPageModel::IdRole);

    if(leftData.type() == QVariant::DateTime)
    {
        return leftData.toDateTime() < rightData.toDateTime();
    }
    else {
        return leftData.toInt() < rightData.toInt();
    }
    return true;
}

bool FilterFreezerPage::filterAcceptsRow(int sourceRow,
        const QModelIndex &sourceParent) const{
    bool ret(false);
    if(sourceModel() != nullptr ){
        QModelIndex index{sourceModel()->index(sourceRow, 0, sourceParent)};
        if(index.isValid()){
            QVariant value_role(index.data(FreezerPageModel::FreezerRole));
            if(value_role.isValid()){
                ret = value_role.toString() == selected_freezer;
            }
        }
    }
    return  ret;
}

void FilterFreezerPage::selectFreezer(const QString& selected){
    selected_freezer = selected;
    invalidateFilter();
}

