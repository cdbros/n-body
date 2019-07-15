#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/widgets/ControlPanelWidget.h"
#include "src/widgets/SimView.h"
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
    std::unique_ptr<QHBoxLayout> m_horizontalLayout;
    std::unique_ptr<SimView> m_simView;
    std::unique_ptr<ControlPanelWidget> m_controlPanel;
    std::unique_ptr<QShortcut> m_closeShortcut;
};

#endif // MAINWINDOW_H
