#include "FreezerPageModel.h"

#include <algorithm>

FreezerPageModel::FreezerPageModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

/*FreezerPageModel::~FreezerPageModel(){

}*/

QVariant FreezerPageModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

bool FreezerPageModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

int FreezerPageModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return items.count();
}

QVariant FreezerPageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const ItemViewData& item{items[index.row()]};

    QVariant value;
    switch(role){
    case FreezerRole:
        value = item.getFreezer();
        break;
    case IdRole:
        value = item.getId();
        break;
    case DrawerRole:
        value = item.getDrawer();
        break;
    case NameRole:
        value = item.getName();
        break;
    case DescriptionRole:
        value = item.getDescription();
        break;
    case DateRole:
        break;
    }
    return value;
}

void FreezerPageModel::addItem(const ItemViewData& item){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items << item;
    endInsertRows();
}

void FreezerPageModel::removeItem(const QString& freezer, int id){
    beginRemoveRows(QModelIndex(), rowCount(), rowCount());
    items.erase(std::remove_if(items.begin(), items.end(), [&](ItemViewData& item){
        return item.getFreezer() == freezer && item.getId() == id;
    }),
    items.end());
    endRemoveRows();
}

bool FreezerPageModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags FreezerPageModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> FreezerPageModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "type";
    roles[DrawerRole] = "drawer";
    roles[NameRole] = "name";
    roles[DescriptionRole] = "description";
    roles[DateRole] = "date";
    return roles;
}

