#include "mainwindow.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent} {
    if (this->objectName().isEmpty()) {
        this->setObjectName(QString::fromUtf8("MainWindow"));
    }

    this->setWindowTitle("N Body");
    this->resize(640, 480);

    centralWidget = std::make_unique<QWidget>(this);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));

    horizontalLayout = std::make_unique<QHBoxLayout>(centralWidget.get());
    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

    this->setCentralWidget(centralWidget.get());

    // simulation view and control panel
    simView = std::make_unique<SimView>(centralWidget.get());
    controlPanel = std::make_unique<ControlPanelWidget>(centralWidget.get());

    horizontalLayout->addWidget(simView.get());
    horizontalLayout->addWidget(controlPanel.get());
}
