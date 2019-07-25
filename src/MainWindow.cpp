#include "MainWindow.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent} {
    if (objectName().isEmpty()) {
        setObjectName(QString::fromUtf8("MainWindow"));
    }

    setWindowTitle("N Body Simulation");
    resize(1280, 720);

    m_centralWidget = std::make_unique<QWidget>(this);
    m_centralWidget->setObjectName(QString::fromUtf8("centralWidget"));

    auto horizontalLayout = new QHBoxLayout(m_centralWidget.get());
    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

    setCentralWidget(m_centralWidget.get());

    // simulation view and control panel
    auto simView = new SimView(m_centralWidget.get());
    auto controlPanel = new ControlPanelWidget(m_centralWidget.get());

    horizontalLayout->addWidget(simView);
    horizontalLayout->addWidget(controlPanel);

    m_closeShortcut = std::make_unique<QShortcut>(QKeySequence::Close, this);

    QObject::connect(m_closeShortcut.get(), &QShortcut::activated, this, [this]() { this->close(); });
}
