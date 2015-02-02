/* Original Work Copyright (c) 2012-2014 Alexander Turkin
   Modified 2014 by William Hallatt
   Modified 2015 by Jacob Dawid

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

// Own includes
#include "waitingspinnerwidget.h"

// Standard incluces
#include <cmath>
#include <algorithm>

// Qt includes
#include <QPainter>
#include <QTimer>

const QColor c_color(Qt::black);
const qreal c_roundness(70.0);
const qreal c_minTrailOpacity(15.0);
const qreal c_trailFadePercentage(70.0);
const int c_lines(12);
const int c_lineLength(10);
const int c_lineWidth(5);
const int c_innerRadius(10);
const int c_revPerSec(1);

WaitingSpinnerWidget::WaitingSpinnerWidget(QWidget *parent)
    : QWidget(parent),
      _color(c_color),
      _roundness(c_roundness),
      _minimumTrailOpacity(c_minTrailOpacity),
      _trailFadePercentage(c_trailFadePercentage),
      _revolutionsPerSecond(c_revPerSec),
      _numberOfLines(c_lines),
      _lineLength(c_lineLength + c_lineWidth),
      _lineWidth(c_lineWidth),
      _innerRadius(c_innerRadius),

      // Other
      _timer(NULL),
      _centerOnParent(false),
      _currentCounter(0),
      _isSpinning(false) {
    initialise();
}

WaitingSpinnerWidget::WaitingSpinnerWidget(Qt::WindowModality modality,
                                           QWidget *parent,
                                           bool centreOnParent)
    : QWidget(parent, Qt::Dialog | Qt::FramelessWindowHint),

      _color(c_color),
      _roundness(c_roundness),
      _minimumTrailOpacity(c_minTrailOpacity),
      _trailFadePercentage(c_trailFadePercentage),
      _revolutionsPerSecond(c_revPerSec),
      _numberOfLines(c_lines),
      _lineLength(c_lineLength + c_lineWidth),
      _lineWidth(c_lineWidth),
      _innerRadius(c_innerRadius),

      // Other
      _timer(NULL),
      _centerOnParent(centreOnParent),
      _currentCounter(0) {
    initialise();

    // We need to set the window modality AFTER we've hidden the
    // widget for the first time since changing this property while
    // the widget is visible has no effect.
    this->setWindowModality(modality);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void WaitingSpinnerWidget::initialise() {
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(rotate()));
    updateSize();
    updateTimer();
    this->hide();
}

void WaitingSpinnerWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.fillRect(this->rect(), Qt::transparent);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if (_currentCounter >= _numberOfLines) {
        _currentCounter = 0;
    }

    painter.setPen(Qt::NoPen);
    for (int i = 0; i < _numberOfLines; ++i) {
        painter.save();
        painter.translate(_innerRadius + _lineLength,
                          _innerRadius + _lineLength);
        qreal rotateAngle =
                static_cast<qreal>(360 * i) / static_cast<qreal>(_numberOfLines);
        painter.rotate(rotateAngle);
        painter.translate(_innerRadius, 0);
        int distance =
                lineCountDistanceFromPrimary(i, _currentCounter, _numberOfLines);
        QColor color =
                currentLineColor(distance, _numberOfLines, _trailFadePercentage,
                                 _minimumTrailOpacity, _color);
        painter.setBrush(color);
        // TODO improve the way rounded rect is painted
        painter.drawRoundedRect(
                    QRect(0, -_lineWidth / 2, _lineLength, _lineWidth), _roundness,
                    _roundness, Qt::RelativeSize);
        painter.restore();
    }
}

void WaitingSpinnerWidget::start() {
    updatePosition();
    _isSpinning = true;
    this->show();
    if (!_timer->isActive()) {
        _timer->start();
        _currentCounter = 0;
    }
}

void WaitingSpinnerWidget::stop() {
    _isSpinning = false;
    this->hide();
    if (_timer->isActive()) {
        _timer->stop();
        _currentCounter = 0;
    }
}

void WaitingSpinnerWidget::setNumberOfLines(int lines) {
    _numberOfLines = lines;
    _currentCounter = 0;
    updateTimer();
}

void WaitingSpinnerWidget::setLineLength(int length) {
    _lineLength = length;
    updateSize();
}

void WaitingSpinnerWidget::setLineWidth(int width) {
    _lineWidth = width;
    updateSize();
}

void WaitingSpinnerWidget::setInnerRadius(int radius) {
    _innerRadius = radius;
    updateSize();
}

bool WaitingSpinnerWidget::isSpinning() const {
    return _isSpinning;
}

void WaitingSpinnerWidget::setRoundness(qreal roundness) {
    _roundness = std::max(0.0, std::min(100.0, roundness));
}

void WaitingSpinnerWidget::setColor(QColor color) {
    _color = color;
}

void WaitingSpinnerWidget::setRevolutionsPerSecond(int rps) {
    _revolutionsPerSecond = rps;
    updateTimer();
}

void WaitingSpinnerWidget::setTrailFadePercentage(qreal trail) {
    _trailFadePercentage = trail;
}

void WaitingSpinnerWidget::setMinimumTrailOpacity(qreal minOpacity) {
    _minimumTrailOpacity = minOpacity;
}

void WaitingSpinnerWidget::rotate() {
    ++_currentCounter;
    if (_currentCounter >= _numberOfLines) {
        _currentCounter = 0;
    }
    update();
}

void WaitingSpinnerWidget::updateSize() {
    int size = (_innerRadius + _lineLength) * 2;
    setFixedSize(size, size);
}

void WaitingSpinnerWidget::updateTimer() {
    _timer->setInterval(calculateTimerInterval(_numberOfLines, _revolutionsPerSecond));
}

void WaitingSpinnerWidget::updatePosition() {
    if (parentWidget() && _centerOnParent) {
        move(parentWidget()->frameGeometry().topLeft() + parentWidget()->rect().center() - rect().center());
    }
}

int WaitingSpinnerWidget::calculateTimerInterval(int lines, int speed) {
    return 1000 / (lines * speed);
}

int WaitingSpinnerWidget::lineCountDistanceFromPrimary(int current, int primary,
                                                       int totalNrOfLines) {
    int distance = primary - current;
    if (distance < 0) {
        distance += totalNrOfLines;
    }
    return distance;
}

QColor WaitingSpinnerWidget::currentLineColor(int countDistance, int totalNrOfLines,
                                              qreal trailFadePerc, qreal minOpacity,
                                              QColor color) {
    if (countDistance == 0) {
        return color;
    }
    const qreal minAlphaF = minOpacity / 100.0;
    int distanceThreshold =
            static_cast<int>(ceil((totalNrOfLines - 1) * trailFadePerc / 100.0));
    if (countDistance > distanceThreshold) {
        color.setAlphaF(minAlphaF);
    } else {
        qreal alphaDiff = color.alphaF() - minAlphaF;
        qreal gradient = alphaDiff / static_cast<qreal>(distanceThreshold + 1);
        qreal resultAlpha = color.alphaF() - gradient * countDistance;

        // If alpha is out of bounds, clip it.
        resultAlpha = std::min(1.0, std::max(0.0, resultAlpha));
        color.setAlphaF(resultAlpha);
    }
    return color;
}
