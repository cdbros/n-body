#include "ControlPanelWidget.h"

ControlPanelWidget::ControlPanelWidget(QWidget *parent) : QWidget{parent} {
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    QSizePolicy spConfigPanel(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spConfigPanel.setHorizontalStretch(1);
    this->setSizePolicy(spConfigPanel);

    this->setObjectName(QString::fromUtf8("controlPanel"));
}
