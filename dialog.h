#ifndef DIALOG_H
#define DIALOG_H

#include <QtGui/QDialog>

#include <QtWaitingSpinner.h>

class Dialog : public QDialog {
	Q_OBJECT
	
public:
	explicit Dialog(QWidget *parent = 0);
	~Dialog();

};

#endif // DIALOG_H
