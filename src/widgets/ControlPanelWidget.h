
#ifndef CONTROLPANELWIDGET_H
#define CONTROLPANELWIDGET_H

#include <QWidget>
#include <Section.h>
#include <memory>

class ControlPanelWidget : public QWidget {
    Q_OBJECT

  public:
    explicit ControlPanelWidget(QWidget *parent = nullptr);
};

#endif // CONTROLPANELWIDGET_H
