
#ifndef CONTROLPANELWIDGET_H
#define CONTROLPANELWIDGET_H

#include <Section.h>
#include <QWidget>
#include <memory>

class ControlPanelWidget : public QWidget {
    Q_OBJECT

  public:
    explicit ControlPanelWidget(QWidget *parent = nullptr);
};

#endif // CONTROLPANELWIDGET_H
