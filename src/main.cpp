/*
 * main.cpp
 *
 *  Created on: 10 Dec 2017
 *      Author: Oscar Crespo
 */

#include <QApplication>

#include "model/Model.h"
#include "presenter/MainPresenter.h"
#include "view/MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    Model model;
    MainWindow w;
    MainPresenter presenter(&w, &model);

    w.show();
    return a.exec();
}
