/*
 * MainPresenter.h
 *
 *  Created on: 17 Dec 2017
 *      Author: Oscar Crespo
 */

#ifndef SRC_PRESENTER_MAINPRESENTER_H_
#define SRC_PRESENTER_MAINPRESENTER_H_

#include <QObject>

#include <threadutils/ThreadSwapperSingle.h>

class Model;
class MainWindow;

class MainPresenter: public QObject  {

	Q_OBJECT

public:
	MainPresenter(MainWindow *mainView,Model *model);
	virtual ~MainPresenter();

private slots:
	void addItemClicked();
	void removeItemClicked(const QString&);
    void itemClicked(const QString&);

private:

	void setNextId_callback(int next_id);
    Q_INVOKABLE void setNextId(int next_id);

	void setNumDrawer_callback(int num_drawers);
    Q_INVOKABLE void setNumDrawer(int num_drawers);

	void itemAdded_callback(int id,
						    int drawer,
							const std::string& name,
							const std::string& description,
							const std::string& date);
    Q_INVOKABLE void itemAdded(int id,
                            int drawer,
                            const QString& name,
                            const QString& description,
                            const QString& date);

    void itemRemoved_callback(int id);
    Q_INVOKABLE void itemRemoved(int id);

    void itemInfo_callback(int id,
                            int drawer,
                            const std::string& name,
                            const std::string& description,
                            const std::string& date);
    Q_INVOKABLE void itemInfo(int id,
                            int drawer,
                            const QString& name,
                            const QString& description,
                            const QString& date);

    void itemUpdated_callback(int id,
                            int drawer,
                            const std::string& name,
                            const std::string& description);
    Q_INVOKABLE void itemUpdated(int id,
                            int drawer,
                            const QString& name,
                            const QString& description);

    void initFinished_callback();
    Q_INVOKABLE void initFinished();




	MainWindow *mainView;
	Model *model;
	ocutils::ThreadSwapperSingle model_thread;

	int next_id;
	int num_drawers;
};

#endif /* SRC_PRESENTER_MAINPRESENTER_H_ */
