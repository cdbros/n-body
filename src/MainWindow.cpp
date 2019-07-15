#include "MainWindow.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent} {
    if (objectName().isEmpty()) {
        setObjectName(QString::fromUtf8("MainWindow"));
    }

    setWindowTitle("N Body");
    resize(1280, 720);

    m_centralWidget = std::make_unique<QWidget>(this);
    m_centralWidget->setObjectName(QString::fromUtf8("centralWidget"));

    m_horizontalLayout = std::make_unique<QHBoxLayout>(m_centralWidget.get());
    m_horizontalLayout->setSpacing(0);
    m_horizontalLayout->setContentsMargins(0, 0, 0, 0);
    m_horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

    setCentralWidget(m_centralWidget.get());

    // simulation view and control panel
    m_simView = std::make_unique<SimView>(m_centralWidget.get());
    m_controlPanel = std::make_unique<ControlPanelWidget>(m_centralWidget.get());

    m_horizontalLayout->addWidget(m_simView.get());
    m_horizontalLayout->addWidget(m_controlPanel.get());

    m_closeShortcut = std::make_unique<QShortcut>(QKeySequence::Close, this);
    QObject::connect(m_closeShortcut.get(), &QShortcut::activated, this, [this]() { this->close(); });
}
