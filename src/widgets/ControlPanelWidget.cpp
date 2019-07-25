#include "ControlPanelWidget.h"
#include <QLabel>
#include <QPushButton>

ControlPanelWidget::ControlPanelWidget(QWidget *parent) : QWidget{parent} {
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor::fromRgb(31, 34, 35));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    QSizePolicy spConfigPanel(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spConfigPanel.setHorizontalStretch(1);
    this->setSizePolicy(spConfigPanel);

    this->setObjectName(QString::fromUtf8("controlPanel"));

    auto vLayout = new QVBoxLayout(this);
    vLayout->setObjectName(QString::fromUtf8("controlPanelVLayout"));
    vLayout->setAlignment(Qt::AlignTop);

    auto section1 = new Section("Section 1", 50, this);
    auto section1Layout = new QVBoxLayout();
    section1Layout->addWidget(new QPushButton("This is section 1 button", section1));
    section1->setContentLayout(*section1Layout);

    auto section2 = new Section("Section 2", 50, this);
    auto section2Layout = new QVBoxLayout();
    section2Layout->addWidget(new QPushButton("This is section 2 button", section2));
    section2->setContentLayout(*section2Layout);

    auto section3 = new Section("Section 3", 50, this);
    auto section3Layout = new QVBoxLayout();
    section3Layout->addWidget(new QPushButton("This is section 3 button", section3));
    section3->setContentLayout(*section3Layout);

    auto section4 = new Section("Section 4", 50, this);
    auto section4Layout = new QVBoxLayout();
    section4Layout->addWidget(new QPushButton("This is section 4 button", section4));
    section4->setContentLayout(*section4Layout);

    vLayout->addWidget(section1);
    vLayout->addWidget(section2);
    vLayout->addWidget(section3);
    vLayout->addWidget(section4);
}
