#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "widgets/ControlPanelWidget.h"
#include "widgets/SimView.h"
#include <QHBoxLayout>
#include <QMainWindow>
#include <QShortcut>
#include <memory>

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);

  private:
    std::unique_ptr<QWidget> m_centralWidget;
    std::unique_ptr<QShortcut> m_closeShortcut;
};

#endif // MAINWINDOW_H
