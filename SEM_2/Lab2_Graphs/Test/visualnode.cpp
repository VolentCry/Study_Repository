#include "visualnode.h"
#include "visualedge.h"
#include <QPainter>
#include <QGraphicsScene>

VisualNode::VisualNode(const QString &name, QGraphicsItem *parent)
    : QGraphicsEllipseItem(-Radius/2, -Radius/2, Radius, Radius, parent), // Центрируем круг
    m_name(name)
{
    // Настройки внешнего вида круга
    setPen(QPen(Qt::black, 2)); // Черный контур
    setBrush(QBrush(QColor("#a1c4fd"))); // Светло-голубая заливка

    // Делаем объект перетаскиваемым мышкой и выделяемым
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    // Создаем текст
    m_textItem = new QGraphicsTextItem(m_name, this);
    m_textItem->setDefaultTextColor(Qt::black);

    // Центрируем текст внутри круга
    QRectF textRect = m_textItem->boundingRect();
    m_textItem->setPos(-textRect.width() / 2, -textRect.height() / 2);
}

QString VisualNode::name() const
{
    return m_name;
}

void VisualNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Рисуем базовый эллипс (круг)
    QGraphicsEllipseItem::paint(painter, option, widget);
}

void VisualNode::addEdge(VisualEdge *edge) { edgeList << edge; }

void VisualNode::removeEdge(VisualEdge *edge) { edgeList.removeAll(edge); }

QVariant VisualNode::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged) {
        for (VisualEdge *edge : edgeList) {
            edge->adjust(); // Просим все связанные ребра перерисоваться
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

VisualNode::~VisualNode()
{
    while (!edgeList.isEmpty()) {
        VisualEdge *edge = edgeList.takeFirst();

        // Находим «другую» вершину этого ребра
        VisualNode *otherNode = (edge->sourceNode() == this) ? edge->destNode() : edge->sourceNode();

        if (otherNode) {
            // Сообщаем другой вершине, что этого ребра больше нет,
            // чтобы она не пыталась к нему обратиться.
            otherNode->removeEdge(edge);
        }

        // Удаляем ребро со сцены и из памяти
        if (scene()) scene()->removeItem(edge);
        delete edge;
    }
}

void VisualNode::setColor(const QColor &color)
{
    setBrush(QBrush(color)); // Меняем цвет заливки
    update(); // Даем команду перерисовать себя на сцене
}