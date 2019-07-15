/*
    Elypson/qt-collapsible-section
    (c) 2016 Michael A. Voelkel - michael.alexander.voelkel@gmail.com

    This file is part of Elypson/qt-collapsible section.

    Elypson/qt-collapsible-section is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Elypson/qt-collapsible-section is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Elypson/qt-collapsible-section. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SECTION_H
#define SECTION_H

#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>

class Section : public QWidget {
    Q_OBJECT

  private:
    std::unique_ptr<QGridLayout> mainLayout;
    std::unique_ptr<QToolButton> toggleButton;
    std::unique_ptr<QFrame> headerLine;
    std::unique_ptr<QParallelAnimationGroup> toggleAnimation;
    std::unique_ptr<QScrollArea> contentArea;
    int animationDuration;

  public:
    explicit Section(const QString &title = "", int animationDuration = 100, QWidget *parent = nullptr);

    void setContentLayout(QLayout &contentLayout);
};

#endif // SECTION_H
