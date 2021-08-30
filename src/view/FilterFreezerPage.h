/*
 * FilterFreezerPage.h
 *
 *  Created on: 30 Aug 2021
 *      Author: Oscar Crespo
 */

#ifndef SRC_VIEW_FILTERFREEZERPAGE_H_
#define SRC_VIEW_FILTERFREEZERPAGE_H_

#include <QSortFilterProxyModel>

class FilterFreezerPage : public QSortFilterProxyModel{
    Q_OBJECT
public:
    explicit FilterFreezerPage(QObject* parent = nullptr);

    virtual ~FilterFreezerPage();

    void selectFreezer(const QString& selected);

protected:

    bool lessThan(const QModelIndex &source_left,
            const QModelIndex &source_right) const override;

    bool filterAcceptsRow(int sourceRow,
            const QModelIndex &sourceParent) const override;

private:

    QString selected_freezer;

};

#endif /* SRC_VIEW_FILTERFREEZERPAGE_H_ */
