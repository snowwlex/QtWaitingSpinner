#ifndef QTWAITINGSPINNER_H
#define QTWAITINGSPINNER_H

#include "qglobal.h"
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
   #include <QtGui/QWidget>
 #else
   #include <QtWidgets/QWidget>
 #endif

#include <QtGui/QColor>

class QTimer;

class QtWaitingSpinner : public QWidget {
	Q_OBJECT

public:
    QtWaitingSpinner(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    QtWaitingSpinner(int linesNumber = 12, int length = 7, int width = 5, int radius = 10, QWidget *parent = 0);

public Q_SLOTS:
	void start();
	void finish();

public:
	void setLinesNumber(int linesNumber);
	void setLength(int length);
	void setWidth(int width);
	void setRadius(int radius);
	void setRoundness(qreal roundness);
	void setColor(QColor color);
	void setSpeed(qreal speed);
	void setTrail(int trail);
	void setOpacity(int minOpacity);

private Q_SLOTS:
	void rotate();
	void updateSize();
	void updateTimer();

protected:
	void paintEvent(QPaintEvent *ev);

private:
	static int countTimeout(int lines, qreal speed);
	static int lineDistance(int from, int to, int lines);
	static QColor countTrailColor(int distance, int lines, int trail, int minOpacity, QColor color);

    void initialise();

private:
	int myLinesNumber;
	int myLength;
	int myWidth;
	int myRadius;
	qreal myRoundness; //0..100
	QColor myColor;
	qreal mySpeed; // in rounds per second
	int myTrail;
	int myOpacity;

private:
	QTimer *myTimer;
	int myCurrentCounter;
};

#endif // QTWAITINGSPINNER_H
