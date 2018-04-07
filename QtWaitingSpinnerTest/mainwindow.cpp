#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QHBoxLayout>
#include <QTimer>
#include "../waitingspinnerwidget.h"

/*----------------------------------------------------------------------------*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_spinner(NULL) {
  ui->setupUi(this);

  /* This spinner will be embedded in a layout. For the modal, centred spinner,
   * see "launchBlockingSpinner" below*/
  m_spinner = new WaitingSpinnerWidget(this);
  connect(ui->startButton, SIGNAL(clicked()), m_spinner, SLOT(start()));
  connect(ui->stopButton, SIGNAL(clicked()), m_spinner, SLOT(stop()));

  QVBoxLayout *spinnerLayout = new QVBoxLayout;
  spinnerLayout->insertWidget(0, m_spinner);
  spinnerLayout->insertStretch(0);
  spinnerLayout->addStretch();
  ui->horizontalLayoutFrame->insertLayout(1, spinnerLayout);
}

/*----------------------------------------------------------------------------*/

MainWindow::~MainWindow() { delete ui; }

/*----------------------------------------------------------------------------*/

void MainWindow::showColourDialog() {
  QColorDialog *colorDialog = new QColorDialog(Qt::black, this);
  connect(colorDialog, SIGNAL(currentColorChanged(QColor)), this,
          SLOT(setColor(QColor)));
  connect(colorDialog, SIGNAL(colorSelected(QColor)), this,
          SLOT(setColor(QColor)));
  colorDialog->show();
}

/*----------------------------------------------------------------------------*/

void MainWindow::launchBlockingSpinner() {
  const int ms = 5000; // 5 seconds

  /* Stop the "permanent" spinner, it just looks messy when
   * both are running at the same time. */
  bool isSpinning = m_spinner->isSpinning();

  if (isSpinning) {
    m_spinner->stop();
    QTimer::singleShot(ms, m_spinner, SLOT(start()));
  }

  WaitingSpinnerWidget *blockingSpinner =
      new WaitingSpinnerWidget(Qt::ApplicationModal, this, true);
  blockingSpinner->setColor(Qt::red);
  blockingSpinner->start();

  /* Stop and kill after ms elapsed. */
  QTimer::singleShot(ms, blockingSpinner, SLOT(stop()));
  QTimer::singleShot(ms+100, blockingSpinner, SLOT(deleteLater()));
}

/*----------------------------------------------------------------------------*/

void MainWindow::setColor(QColor color) { m_spinner->setColor(color); }

/*----------------------------------------------------------------------------*/

void MainWindow::setRoundness(double roundness) {
  m_spinner->setRoundness(roundness);
}

/*----------------------------------------------------------------------------*/

void MainWindow::setMinimumTrailOpacity(double minOpacity) {
  m_spinner->setMinimumTrailOpacity(minOpacity);
}

/*----------------------------------------------------------------------------*/

void MainWindow::setTrailFadePercentage(double trail) {
  m_spinner->setTrailFadePercentage(trail);
}

/*----------------------------------------------------------------------------*/

void MainWindow::setRevolutionsPerSecond(int rps) {
  m_spinner->setRevolutionsPerSecond(rps);
}

/*----------------------------------------------------------------------------*/

void MainWindow::setNumberOfLines(int lines) {
  m_spinner->setNumberOfLines(lines);
}

/*----------------------------------------------------------------------------*/

void MainWindow::setLineLength(int length) { m_spinner->setLineLength(length); }

/*----------------------------------------------------------------------------*/

void MainWindow::setLineWidth(int width) { m_spinner->setLineWidth(width); }

/*----------------------------------------------------------------------------*/

void MainWindow::setInnerRadius(int radius) {
  m_spinner->setInnerRadius(radius);
}

/*----------------------------------------------------------------------------*/
