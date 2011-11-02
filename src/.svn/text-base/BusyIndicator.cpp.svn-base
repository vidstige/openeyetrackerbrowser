/*
   Copyright 2011 Tobii Technology AB

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "BusyIndicator.h"

#include <QDebug>
#include <QPainter>
#include <QPixmapCache>
#include <QGradient>

BusyIndicator::BusyIndicator(QWidget *parent) :
    QWidget(parent),
    startAngle(0),
    m_style(StyleArc)
{
    QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    policy.setHeightForWidth(true);
    setSizePolicy(policy);

    timer.setInterval(50);
    connect(&timer, SIGNAL(timeout()), this, SLOT(rotate()));
    timer.start();
}

void BusyIndicator::rotate()
{
    startAngle += 30;
    startAngle %= 360;
    update();
}

void BusyIndicator::setIndicatorStyle(IndicatorStyle style)
{
    m_style = style;
    update();
}

const BusyIndicator::IndicatorStyle BusyIndicator::indicatorStyle() const
{
    return m_style;
}


QPixmap BusyIndicator::generatePixmap(int side)
{
    QPixmap pixmap(QSize(side, side));
    pixmap.fill(QColor(255, 255, 255, 0));

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.translate(side / 2, side / 2);
    painter.scale(side / 200.0, side / 200.0);

    switch (m_style) {
    case StyleRect:
        drawRectStyle(&painter);
        break;
    case StyleEllipse:
        drawEllipseStyle(&painter);
        break;
    case StyleArc:
        drawArcStyle(&painter);
        break;
    }
    return pixmap;
}

void BusyIndicator::drawRectStyle(QPainter *painter)
{
    QColor color = palette().color(QPalette::WindowText);
    QBrush brush(color);
    painter->setPen(Qt::NoPen);

    painter->rotate(startAngle);

    float angle = 0;
    while (angle < 360) {
        painter->setBrush(brush);
        painter->drawRect(-8, -100, 16, 35);

        painter->rotate(30);
        angle += 30;

        color.setAlphaF(angle / 360);
        brush.setColor(color);
    }
}

void BusyIndicator::drawEllipseStyle(QPainter *painter)
{
    QColor color = palette().color(QPalette::WindowText);
    QBrush brush(color);
    painter->setPen(Qt::NoPen);

    painter->rotate(startAngle);

    float angle = 0;
    while (angle < 360) {
        painter->setBrush(brush);
        painter->drawEllipse(-10, -100, 30, 30);

        painter->rotate(30);
        angle += 30;

        color.setAlphaF(angle / 360);
        brush.setColor(color);
    }
}

void BusyIndicator::drawArcStyle(QPainter *painter)
{
    QColor color = palette().color(QPalette::WindowText);
    QConicalGradient gradient(0, 0, -startAngle);
    gradient.setColorAt(0, color);
    color.setAlpha(0);
    gradient.setColorAt(0.8, color);
    color.setAlpha(255);
    gradient.setColorAt(1, color);

    QPen pen;
    pen.setWidth(30);
    pen.setBrush(QBrush(gradient));
    painter->setPen(pen);

    painter->drawArc(-85, -85, 170, 170, 0 * 16, 360 * 16);
}

void BusyIndicator::paintEvent(QPaintEvent *)
{
    QString key = QString("%1:%2:%3:%4:%5")
            .arg(metaObject()->className())
            .arg(width())
            .arg(height())
            .arg(startAngle)
            .arg(m_style);

    QPixmap pixmap;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int side = qMin(width(), height());

    if(!QPixmapCache::find(key, &pixmap)) {
        pixmap = generatePixmap(side);
        QPixmapCache::insert(key, pixmap);
    }

    painter.translate(width() / 2 - side / 2, height() / 2 - side / 2);

    painter.drawPixmap(0, 0, side, side, pixmap);
}

QSize BusyIndicator::minimumSizeHint() const
{
    return QSize(20, 20);
}

QSize BusyIndicator::sizeHint() const
{
    return QSize(30, 30);
}
