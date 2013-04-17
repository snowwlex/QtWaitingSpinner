#include <QtGui/QHBoxLayout>

#include "dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent) {
	QHBoxLayout *layout = new QHBoxLayout;
	layout->setSpacing(30);

	QtWaitingSpinner* spinner1 = new QtWaitingSpinner(10,7,3,5);
	QtWaitingSpinner* spinner2 = new QtWaitingSpinner(20,5,3,10);
	QtWaitingSpinner* spinner3 = new QtWaitingSpinner(13,10,5,15);
	QtWaitingSpinner* spinner4 = new QtWaitingSpinner(13,25,13,30);

	spinner1->setSpeed(1.5);
	spinner2->setSpeed(2);

	layout->addWidget(spinner1);
	layout->addWidget(spinner2);
	layout->addWidget(spinner3);
	layout->addWidget(spinner4);
	setLayout(layout);

	spinner1->start();
	spinner2->start();
	spinner3->start();
	spinner4->start();
}

Dialog::~Dialog()
{

}

