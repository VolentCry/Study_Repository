#ifndef VISUALEDGE_H
#define VISUALEDGE_H

#include <QObject>
#include <QGraphicsLineItem>

class VisualNode;

class VisualEdge : public QObject, public QGraphicsLineItem
{
    Q_OBJECT

public:
    VisualEdge(VisualNode *source, VisualNode *dest, int weight, bool isDirected);
    ~VisualEdge();

    void adjust();

    int weight() const { return m_weight; } // Хранение веса
    bool isDirected() const { return m_isDirected; } // Геттер для алгоритмов
    VisualNode* sourceNode() const { return m_source; }
    VisualNode* destNode() const { return m_dest; }

signals:
    void weightChanged(); // Возможность смена веса у уже нарисованного ребра

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // Отрисовка ребра
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override; // Дабл клик ЛКМ для изменение веса ребра

private:
    VisualNode *m_source;
    VisualNode *m_dest;
    int m_weight;
    bool m_isDirected; // Храним тип ребра
};

#endif // VISUALEDGE_H