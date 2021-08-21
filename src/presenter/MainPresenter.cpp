/*
 * MainPresenter.cpp
 *
 *  Created on: 17 Dec 2017
 *      Author: Oscar Crespo
 */

#include "MainPresenter.h"

#include <functional>

#include <events/EventStore.h>

//Project
#include <view/MainWindow.h>
#include <model/Model.h>
#include "../view/ItemDialog.h"


MainPresenter::MainPresenter(MainWindow *view,Model *model) :
	mainView(view),
	model(model),
	next_id(0),
	num_drawers(0)
{

    model->registerInitFinished(std::bind( &MainPresenter::initFinished_callback, this));

	model->registerNextId(std::bind( &MainPresenter::setNextId_callback, this, std::placeholders::_1 ));
	model->registerNumDrawers(std::bind( &MainPresenter::setNumDrawer_callback, this, std::placeholders::_1 ));
	model->registerItemAdded(std::bind( &MainPresenter::itemAdded_callback,
	                                                this,
	                                                std::placeholders::_1,
	                                                std::placeholders::_2,
	                                                std::placeholders::_3,
	                                                std::placeholders::_4,
	                                                std::placeholders::_5));
    model->registerItemRemoved(std::bind( &MainPresenter::itemRemoved_callback, this, std::placeholders::_1 ));
    model->registerItemInfo(std::bind( &MainPresenter::itemInfo_callback,
                            this,
                            std::placeholders::_1,
                            std::placeholders::_2,
                            std::placeholders::_3,
                            std::placeholders::_4,
                            std::placeholders::_5));

    model->registerItemUpdated(std::bind( &MainPresenter::itemUpdated_callback,
                                this,
                                std::placeholders::_1,
                                std::placeholders::_2,
                                std::placeholders::_3,
                                std::placeholders::_4));



	QObject::connect(mainView,SIGNAL(buttonAddedClicked()),this,SLOT(addItemClicked()));

	QObject::connect(mainView,SIGNAL(buttonDeleteClicked(const QString&)),this,SLOT(removeItemClicked(const QString&)));
    QObject::connect(mainView,SIGNAL(itemSelected(const QString&)),this,SLOT(itemClicked(const QString&)));


	ocutils::EventStore<> *event{new ocutils::EventStore<>(std::bind(&Model::requestInitialInfo,model))};
	model_thread.execute(event);

}

MainPresenter::~MainPresenter() {

}


void MainPresenter::addItemClicked(){
	ItemDialog *dialog {new ItemDialog(next_id,num_drawers)};
	if(dialog->exec()){
		ocutils::EventStore<int,std::string,std::string> *event(
				new ocutils::EventStore<int,std::string,std::string>(
						std::bind(&Model::addItem,model,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)));

		event->setValues(dialog->getDrawerSelection(),
						dialog->getNameField().toStdString(),
						dialog->getDescriptionField().toStdString());

		model_thread.execute(event);
	}
}

void MainPresenter::removeItemClicked(const QString& id){
    ocutils::EventStore<int> *event{new ocutils::EventStore<int>(std::bind(&Model::removeItem,model,std::placeholders::_1))};
    event->setValues(id.toInt());
    model_thread.execute(event);
}

void MainPresenter::itemClicked(const QString& id){
    ocutils::EventStore<int> *event{new ocutils::EventStore<int>(std::bind(&Model::requestItemInfo,model,std::placeholders::_1))};
      event->setValues(id.toInt());
      model_thread.execute(event);
}


void MainPresenter::setNextId_callback(int next_id){
     QMetaObject::invokeMethod(this,"setNextId",Qt::QueuedConnection, Q_ARG(int, next_id));
}

Q_INVOKABLE void MainPresenter::setNextId(int next_id){
	this->next_id = next_id;
}

void MainPresenter::setNumDrawer_callback(int num_drawers){
    QMetaObject::invokeMethod(this,"setNumDrawer",Qt::QueuedConnection, Q_ARG(int, num_drawers));
}

Q_INVOKABLE void MainPresenter::setNumDrawer(int num_drawers){
	this->num_drawers = num_drawers;
}

void MainPresenter::itemAdded_callback(int id,
                        int drawer,
                        const std::string& name,
                        const std::string& description,
                        const std::string& date){
    QMetaObject::invokeMethod(this,
            "itemAdded",
            Qt::QueuedConnection,
            Q_ARG(int, id),
            Q_ARG(int, drawer),
            Q_ARG(QString, QString::fromStdString(name)),
            Q_ARG(QString, QString::fromStdString(description)),
            Q_ARG(QString, QString::fromStdString(date)));

}

Q_INVOKABLE void MainPresenter::itemAdded(int id,
                        int drawer,
                        const QString& name,
                        const QString& description,
                        const QString& date){

    mainView->addItem(id,drawer,name,description,date);
}

void MainPresenter::itemRemoved_callback(int id){
    QMetaObject::invokeMethod(this,"itemRemoved",Qt::QueuedConnection, Q_ARG(int, id));
}

Q_INVOKABLE void MainPresenter::itemRemoved(int id){
    mainView->removeItem(id);
}

void MainPresenter::itemInfo_callback(int id,
                        int drawer,
                        const std::string& name,
                        const std::string& description,
                        const std::string& date){
    QMetaObject::invokeMethod(this,
            "itemInfo",
            Qt::QueuedConnection,
            Q_ARG(int, id),
            Q_ARG(int, drawer),
            Q_ARG(QString, QString::fromStdString(name)),
            Q_ARG(QString, QString::fromStdString(description)),
            Q_ARG(QString, QString::fromStdString(date)));
}

Q_INVOKABLE void MainPresenter::itemInfo(int id,
                        int drawer,
                        const QString& name,
                        const QString& description,
                        const QString& date){
    ItemDialog *dialog {new ItemDialog(num_drawers,id,drawer,name,description)};
    if(dialog->exec()){
        ocutils::EventStore<int,int,std::string,std::string> *event(
                new ocutils::EventStore<int,int,std::string,std::string>(
                        std::bind(&Model::modifyItem,model,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4)));

        event->setValues(id,
                        dialog->getDrawerSelection(),
                        dialog->getNameField().toStdString(),
                        dialog->getDescriptionField().toStdString());

        model_thread.execute(event);
    }
}

void MainPresenter::itemUpdated_callback(int id,
                        int drawer,
                        const std::string& name,
                        const std::string& description){
    QMetaObject::invokeMethod(this,
            "itemUpdated",
            Qt::QueuedConnection,
            Q_ARG(int, id),
            Q_ARG(int, drawer),
            Q_ARG(QString, QString::fromStdString(name)),
            Q_ARG(QString, QString::fromStdString(description)));
}

Q_INVOKABLE void MainPresenter::itemUpdated(int id,
                        int drawer,
                        const QString& name,
                        const QString& description){
    mainView->updateItem(id,drawer,name,description);
}

void MainPresenter::initFinished_callback(){
    QMetaObject::invokeMethod(this,"initFinished",Qt::QueuedConnection);
}

Q_INVOKABLE void MainPresenter::initFinished(){
    mainView->initCallbacks();
}


#include "moc_MainPresenter.cpp"



