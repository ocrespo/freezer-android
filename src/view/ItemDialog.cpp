/*
 * AddItemDialog.cpp
 *
 *  Created on: 2 Dec 2018
 *      Author: Oscar Crespo
 */

#include "ItemDialog.h"

#include "ui/ui_itemdialog.h"

ItemDialog::ItemDialog(int id, int num_drawer,QWidget *parent):
	QDialog(parent),
	ui(new Ui::ItemDialog)
{
    init(num_drawer,id);
}

ItemDialog::ItemDialog(int num_drawer,
                        int id,
                        int drawer,
                        const QString& name,
                        const QString& description,
                        QWidget *parent):
    QDialog(parent),
    ui(new Ui::ItemDialog)
{
    init(num_drawer,id);

    ui->drawerSelector->setCurrentIndex(drawer-1);
    ui->nameField->setText(name);
    ui->descriptionField->setText(name);
}

ItemDialog::~ItemDialog() {

}

void ItemDialog::init(int num_drawer,int id){
    ui->setupUi(this);

    ui->idLabel->setText(QString::number(id));
    for(int i(1); i <= num_drawer; ++i){
       ui->drawerSelector->addItem(QString::number(i),i);
    }
}

QString ItemDialog::getNameField(){
	return ui->nameField->text();
}

QString ItemDialog::getDescriptionField(){
	return ui->descriptionField->text();
}

int ItemDialog::getDrawerSelection(){
	return ui->drawerSelector->currentData().toInt();
}

#include "moc_ItemDialog.cpp"
