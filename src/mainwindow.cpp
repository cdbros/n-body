#include "mainwindow.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent}, ui{std::make_unique<Ui::MainWindow>()} {
    ui->setupUi(this);

    simView = std::make_unique<SimView>(ui->centralWidget);
    simView->setObjectName(QString::fromUtf8("simView"));
    ui->horizontalLayout->addWidget(simView.get());

    QSizePolicy spSimView(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spSimView.setHorizontalStretch(2);
    ui->simView->setSizePolicy(spSimView);

    QSizePolicy spConfigPanel(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spConfigPanel.setHorizontalStretch(1);
    ui->configPanel->setSizePolicy(spConfigPanel);
}
