/* Original Work Copyright (c) 2012-2014 Alexander Turkin
   Modified 2014 by William Hallatt

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
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
  QtWaitingSpinner(QWidget *parent, Qt::WindowModality modality,
                   bool centreOnParent);

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

protected:
  void paintEvent(QPaintEvent *ev);

private:
  static int countTimeout(int lines, qreal speed);
  static int lineDistance(int from, int to, int lines);
  static QColor countTrailColor(int distance, int lines, int trail,
                                int minOpacity, QColor color);

  void initialise();
  void updateSize();
  void updateTimer();
  void updatePosition();

private:
  int myLinesNumber;
  int myLength;
  int myWidth;
  int myRadius;
  qreal myRoundness; // 0..100
  QColor myColor;
  qreal mySpeed; // in rounds per second
  int myTrail;
  int myOpacity;

  bool myCentreOnParent;

private:
  QTimer *myTimer;
  QWidget *myParent;
  int myCurrentCounter;
};

#endif // QTWAITINGSPINNER_H
