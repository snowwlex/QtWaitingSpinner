#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <QtWaitingSpinner.h>

class Dialog : public QDialog {
	Q_OBJECT
	
public:
	explicit Dialog(QWidget *parent = 0);
	~Dialog();
	
private:
	QtWaitingSpinner *mySpinner;

};

#endif // DIALOG_H
