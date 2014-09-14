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
#include <cmath>
#include <algorithm>

#include <QtGui/QPainter>
#include <QtCore/QTimer>

#include "QtWaitingSpinner.h"

/*----------------------------------------------------------------------------*/

// Defaults
const QColor c_color(Qt::black);
const qreal c_roundness(70.0);
const int c_lines(12);
const int c_length(7);
const int c_width(5);
const int c_radius(10);
const int c_speed(1);
const int c_trail(70);
const int c_opacity(15);

/*----------------------------------------------------------------------------*/

QtWaitingSpinner::QtWaitingSpinner(QWidget *parent, Qt::WindowModality modality,
                                   bool centreOnParent)
    : QWidget(parent, Qt::Dialog | Qt::FramelessWindowHint),
      myLinesNumber(c_lines), myLength(c_length + c_width), myWidth(c_width),
      myRadius(c_radius), myRoundness(c_roundness), myColor(c_color),
      mySpeed(c_speed), myTrail(c_trail), myOpacity(c_opacity), myTimer(NULL),
      myParent(parent), myCurrentCounter(0), myCentreOnParent(centreOnParent) {
  initialise();

  // We need to set the window modality AFTER we've hidden the
  // widget for the first time since changing this property while
  // the widget is visible has no effect.
  this->setWindowModality(modality);
}

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::initialise() {
  myTimer = new QTimer(this);
  connect(myTimer, SIGNAL(timeout()), this, SLOT(rotate()));
  updateSize();
  updateTimer();
  this->hide();
}

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::paintEvent(QPaintEvent * /*ev*/) {
  QPainter painter(this);
  painter.fillRect(this->rect(), Qt::transparent);
  painter.setRenderHint(QPainter::Antialiasing, true);

  if (myCurrentCounter >= myLinesNumber) {
    myCurrentCounter = 0;
  }
  painter.setPen(Qt::NoPen);
  for (int i = 0; i < myLinesNumber; ++i) {
    painter.save();
    painter.translate(myRadius + myLength, myRadius + myLength);
    qreal rotateAngle = (qreal)360 * qreal(i) / qreal(myLinesNumber);
    painter.rotate(rotateAngle);
    painter.translate(myRadius, 0);
    int distance = lineDistance(i, myCurrentCounter, myLinesNumber);
    QColor color =
        countTrailColor(distance, myLinesNumber, myTrail, myOpacity, myColor);
    painter.setBrush(color);
    // TODO improve the way rounded rect is painted
    painter.drawRoundedRect(QRect(0, -myWidth / 2, myLength, myWidth),
                            myRoundness, myRoundness, Qt::RelativeSize);
    painter.restore();
  }
}

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::start() {
  updatePosition();
  this->show();
  if (!myTimer->isActive()) {
    myTimer->start();
    myCurrentCounter = 0;
  }
}

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::finish() {
  this->hide();
  if (myTimer->isActive()) {
    myTimer->stop();
    myCurrentCounter = 0;
  }
}

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::setLinesNumber(int linesNumber) {
  myLinesNumber = linesNumber;
  myCurrentCounter = 0;
  updateTimer();
}

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::setLength(int length) {
  myLength = length;
  updateSize();
}

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::setWidth(int width) {
  myWidth = width;
  updateSize();
}

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::setRadius(int radius) {
  myRadius = radius;
  updateSize();
}

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::setRoundness(qreal roundness) {
  myRoundness = std::max(0.0, std::min(100.0, roundness));
}

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::setColor(QColor color) { myColor = color; }

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::setSpeed(qreal speed) {
  mySpeed = speed;
  updateTimer();
}

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::setTrail(int trail) { myTrail = trail; }

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::setOpacity(int minOpacity) { myOpacity = minOpacity; }

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::rotate() {
  ++myCurrentCounter;
  if (myCurrentCounter >= myLinesNumber) {
    myCurrentCounter = 0;
  }
  update();
}

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::updateSize() {
  int size = (myRadius + myLength) * 2;
  setFixedSize(size, size);
}

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::updateTimer() {
  myTimer->setInterval(countTimeout(myLinesNumber, mySpeed));
}

/*----------------------------------------------------------------------------*/

void QtWaitingSpinner::updatePosition() {
  if (myParent && myCentreOnParent) {
    this->move(myParent->frameGeometry().topLeft() + myParent->rect().center() -
               this->rect().center());
  }
}

/*----------------------------------------------------------------------------*/

int QtWaitingSpinner::countTimeout(int lines, qreal speed) {
  return 1000 / (lines * speed);
}

/*----------------------------------------------------------------------------*/

int QtWaitingSpinner::lineDistance(int from, int to, int lines) {
  int result = to - from;
  if (result < 0) {
    result += lines;
  }
  return result;
}

/*----------------------------------------------------------------------------*/

QColor QtWaitingSpinner::countTrailColor(int distance, int lines, int trail,
                                         int minOpacity, QColor color) {
  if (distance == 0) {
    return color;
  }
  const qreal minAlphaF = (qreal)minOpacity / 100;
  int distanceThreshold = ceil((lines - 1) * (qreal)trail / 100);
  if (distance > distanceThreshold) {
    color.setAlphaF(minAlphaF);
    return color;
  }
  qreal alphaDiff = color.alphaF() - (qreal)minAlphaF;
  qreal gradation = alphaDiff / (qreal)(distanceThreshold + 1);
  qreal resultAlpha = color.alphaF() - gradation * distance;

  // If alpha is out of bound, clip it.
  resultAlpha = std::min(1.0, std::max(0.0, resultAlpha));
  color.setAlphaF(resultAlpha);
  return color;
}

/*----------------------------------------------------------------------------*/
