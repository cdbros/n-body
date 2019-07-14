#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "control_panel_widget.h"
#include "simview.h"
#include <QHBoxLayout>
#include <QMainWindow>
#include <memory>

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);

  private:
    std::unique_ptr<QWidget> centralWidget;
    std::unique_ptr<QHBoxLayout> horizontalLayout;
    std::unique_ptr<SimView> simView;
    std::unique_ptr<ControlPanelWidget> controlPanel;
};

#endif // MAINWINDOW_H
