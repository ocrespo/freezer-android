/*
 * MainWindow.h
 *
 *  Created on: 10 Dec 2017
 *      Author: Oscar Crespo
 */

#ifndef SRC_VIEW_MAINWINDOW_H_
#define SRC_VIEW_MAINWINDOW_H_

#include <QMainWindow>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow: public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();

	void initCallbacks();

	void addItem(int id,int drawer, const QString& name, const QString& description, const QString& date);

	void removeItem(int id);

	void updateItem(int id,int drawer, const QString& name, const QString& description);

signals:
	void buttonAddedClicked();
	void buttonDeleteClicked(const QString&);
    void itemSelected(const QString&);


private:
    Ui::MainWindow *ui;

    QMap<int, class QTreeWidgetItem *> items;
};

#endif /* SRC_VIEW_MAINWINDOW_H_ */
