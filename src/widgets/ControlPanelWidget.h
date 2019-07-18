
#ifndef CONTROLPANELWIDGET_H
#define CONTROLPANELWIDGET_H

#include <QWidget>
#include <memory>
#include <src/widgets/Section.h>

class ControlPanelWidget : public QWidget {
    Q_OBJECT

  public:
    explicit ControlPanelWidget(QWidget *parent = nullptr);

  private:
    std::unique_ptr<QVBoxLayout> m_vLayout;
    std::unique_ptr<Section> m_section1;
    std::unique_ptr<QVBoxLayout> m_section1Layout;
    std::unique_ptr<Section> m_section2;
    std::unique_ptr<QVBoxLayout> m_section2Layout;
    std::unique_ptr<Section> m_section3;
    std::unique_ptr<QVBoxLayout> m_section3Layout;
    std::unique_ptr<Section> m_section4;
    std::unique_ptr<QVBoxLayout> m_section4Layout;
};

#endif // CONTROLPANELWIDGET_H
