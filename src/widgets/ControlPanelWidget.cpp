#include "ControlPanelWidget.h"
#include "Section.h"
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

    m_vLayout = std::make_unique<QVBoxLayout>(this);
    m_vLayout->setObjectName(QString::fromUtf8("controlPanelVLayout"));
    m_vLayout->setAlignment(Qt::AlignTop);

    m_section1 = std::make_unique<Section>("Section 1", 50, this);
    m_section1Layout = std::make_unique<QVBoxLayout>();
    m_section1Layout->addWidget(new QPushButton("This is section 1 button", m_section1.get()));
    m_section1->setContentLayout(*m_section1Layout);

    m_section2 = std::make_unique<Section>("Section 2", 50, this);
    m_section2Layout = std::make_unique<QVBoxLayout>();
    m_section2Layout->addWidget(new QPushButton("This is section 2 button", m_section2.get()));
    m_section2->setContentLayout(*m_section2Layout);

    m_section3 = std::make_unique<Section>("Section 3", 50, this);
    m_section3Layout = std::make_unique<QVBoxLayout>();
    m_section3Layout->addWidget(new QPushButton("This is section 3 button", m_section3.get()));
    m_section3->setContentLayout(*m_section3Layout);

    m_section4 = std::make_unique<Section>("Section 4", 50, this);
    m_section4Layout = std::make_unique<QVBoxLayout>();
    m_section4Layout->addWidget(new QPushButton("This is section 4 button", m_section4.get()));
    m_section4->setContentLayout(*m_section4Layout);

    m_vLayout->addWidget(m_section1.get());
    m_vLayout->addWidget(m_section2.get());
    m_vLayout->addWidget(m_section3.get());
    m_vLayout->addWidget(m_section4.get());
}
