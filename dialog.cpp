#include <QtGui/QVBoxLayout>

#include "dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent) {
	QVBoxLayout *layout = new QVBoxLayout;
	mySpinner = new QtWaitingSpinner(13,25,13,35);
	layout->addWidget(mySpinner);
	setLayout(layout);

	mySpinner->start();
}

Dialog::~Dialog()
{

}
