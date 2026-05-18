#include "visualedge.h"
#include "visualnode.h"
#include <qmath.h>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>


VisualEdge::VisualEdge(VisualNode *source, VisualNode *dest, int weight, bool isDirected)
    : m_source(source), m_dest(dest), m_weight(weight), m_isDirected(isDirected)
{
    setZValue(-1); // Рёбра всегда под вершинами
    setPen(QPen(Qt::black, 2));
    adjust();
}

void VisualEdge::adjust()
{
    if (!m_source || !m_dest) return;

    // Линия проводится между центрами вершин
    QLineF line(m_source->pos(), m_dest->pos());
    setLine(line);
}

void VisualEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!m_source || !m_dest) return;

    // Рисуем саму линию
    painter->setPen(pen());
    painter->drawLine(line());

    // Если ребро ориентированное, то рисуем стрелочку
    if (m_isDirected) {
        double angle = std::atan2(-line().dy(), line().dx());

        // Отступаем от центра конечной вершины на её радиус (чтобы стрелка не пряталась под круг)
        int nodeRadius = 20;
        QPointF endPoint = line().p2() - QPointF(cos(angle) * nodeRadius, -sin(angle) * nodeRadius);

        // Расчет крыльев стрелки
        qreal arrowSize = 12;
        QPointF arrowP1 = endPoint - QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = endPoint - QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize, cos(angle + M_PI - M_PI / 3) * arrowSize);

        // Рисуем закрашенный треугольник
        painter->setBrush(Qt::black);
        painter->drawPolygon(QPolygonF() << endPoint << arrowP1 << arrowP2);
    }

    // Рисуем вес ребра посередине линии
    QPointF textPos = line().center();
    painter->setBrush(Qt::white);
    painter->setPen(Qt::black);
    painter->drawEllipse(textPos, 10, 10);
    painter->drawText(textPos.x() - 5, textPos.y() + 5, QString::number(m_weight));
}


void VisualEdge::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    // Проверяем, что кликнули именно ЛКМ
    if (event->button() == Qt::LeftButton) {
        bool ok;
        // Вызываем такое же окошко, как при создании ребра
        int newWeight = QInputDialog::getInt(nullptr, "Изменение веса",
                                             "Введите новый вес ребра:",
                                             m_weight, -1000, 1000, 1, &ok);

        // Если пользователь нажал ОК и вес действительно изменился
        if (ok && newWeight != m_weight) {
            m_weight = newWeight;
            update(); // Перерисовываем само ребро (цифру на нем)
            emit weightChanged(); // Отправляем сигнал главному окну для перерисовки матрицы
        }
    }
    QGraphicsLineItem::mouseDoubleClickEvent(event);
}

VisualEdge::~VisualEdge()
{
    // При удалении ребра оно должно отвязаться от своих вершин
    if (m_source) m_source->removeEdge(this);
    if (m_dest) m_dest->removeEdge(this);
}