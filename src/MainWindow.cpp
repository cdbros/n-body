#include "MainWindow.h"
#include <QHBoxLayout>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent} {
    if (objectName().isEmpty()) {
        setObjectName(QString::fromUtf8("MainWindow"));
    }

    setWindowTitle("N Body");
    resize(1280, 720);

    centralWidget = std::make_unique<QWidget>(this);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));

    horizontalLayout = std::make_unique<QHBoxLayout>(centralWidget.get());
    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

    setCentralWidget(centralWidget.get());

    // simulation view and control panel
    simView = std::make_unique<SimView>(centralWidget.get());
    controlPanel = std::make_unique<ControlPanelWidget>(centralWidget.get());

    horizontalLayout->addWidget(simView.get());
    horizontalLayout->addWidget(controlPanel.get());
}
