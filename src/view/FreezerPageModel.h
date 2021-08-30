#ifndef FREEZERPAGEMODEL_H
#define FREEZERPAGEMODEL_H

#include <QAbstractListModel>

#include "ItemViewData.h"

class FreezerPageModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum ItemRoles {
        FreezerRole = Qt::UserRole + 1,
        IdRole,
        DrawerRole,
        NameRole,
        DescriptionRole,
        DateRole,
    };

    explicit FreezerPageModel(QObject *parent = nullptr);


    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addItem(const ItemViewData& item);
    void removeItem(const QString& freezer, int id);

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;


protected:
    QHash<int, QByteArray> roleNames() const;

private:

    QList<ItemViewData> items;

};

#endif // FREEZERPAGEMODEL_H
