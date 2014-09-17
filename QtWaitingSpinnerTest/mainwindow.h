#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QtWaitingSpinner;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void showColourDialog();
  void launchBlockingSpinner();

  void setColor(QColor color);
  void setRoundness(double roundness);
  void setMinimumTrailOpacity(double minOpacity);
  void setTrailFadePercentage(double trail);
  void setRevolutionsPerSecond(int rps);
  void setNumberOfLines(int lines);
  void setLineLength(int length);
  void setLineWidth(int width);
  void setInnerRadius(int radius);

private:
  Ui::MainWindow *ui;
  QtWaitingSpinner *m_spinner;
};

#endif // MAINWINDOW_H
