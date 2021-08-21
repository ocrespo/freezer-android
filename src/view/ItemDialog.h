/*
 * AddItemDialog.h
 *
 *  Created on: 2 Dec 2018
 *      Author: Oscar Crespo
 */

#ifndef SRC_VIEW_ITEMDIALOG_H_
#define SRC_VIEW_ITEMDIALOG_H_

#include <qdialog.h>


namespace Ui {
class ItemDialog;
}

class ItemDialog: public QDialog {
    Q_OBJECT

public:
	ItemDialog(int id, int num_drawer, QWidget *parent = 0);
	ItemDialog(int num_drawer,
            int id,
            int drawer,
            const QString& name,
            const QString& description,
            QWidget *parent = 0);
	virtual ~ItemDialog();

	QString getNameField();
	QString getDescriptionField();
	int getDrawerSelection();

private:

	void init(int num_drawer,int id);

    Ui::ItemDialog *ui;
};

#endif /* SRC_VIEW_ITEMDIALOG_H_ */
