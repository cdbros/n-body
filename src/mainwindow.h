#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "simview.h"
#include "ui_mainwindow.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);

  private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<SimView> simView;
};

#endif // MAINWINDOW_H
