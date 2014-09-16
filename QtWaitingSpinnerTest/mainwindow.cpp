#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QHBoxLayout>
#include "../QtWaitingSpinner.h"

/*----------------------------------------------------------------------------*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_spinner(NULL) {
  ui->setupUi(this);

  /* This spinner will be embedded in a layout. */
  m_spinner = new QtWaitingSpinner(this);

  QVBoxLayout *spinnerLayout = new QVBoxLayout;
  spinnerLayout->insertWidget(0, m_spinner);
  m_spinner->start();
  spinnerLayout->insertStretch(0);
  spinnerLayout->addStretch();

  ui->horizontalLayoutFrame->insertLayout(1, spinnerLayout);

  QColorDialog *colorDialog = new QColorDialog(Qt::black, this);
  colorDialog->setWindowFlags(Qt::Widget);

  /* Required in order to behave well as an embedded widget. */
  colorDialog->setOptions(QColorDialog::DontUseNativeDialog |
                          QColorDialog::NoButtons);
  connect(colorDialog, SIGNAL(currentColorChanged(QColor)), this,
          SLOT(setColor(QColor)));

  ui->horizontalLayoutMain->insertWidget(0, colorDialog);
}

/*----------------------------------------------------------------------------*/

MainWindow::~MainWindow() { delete ui; }

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
