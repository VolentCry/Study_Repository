#ifndef VISUALNODE_H
#define VISUALNODE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>
#include <QList>

class VisualEdge;

class VisualNode : public QGraphicsEllipseItem
{
public:
    static const int Radius = 40;
    VisualNode(const QString &name, QGraphicsItem *parent = nullptr);
    QString name() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    // Основные методы для работы с рёбрами
    void addEdge(VisualEdge *edge);
    void removeEdge(VisualEdge *edge);
    void setColor(const QColor &color);

    const QList<VisualEdge*>& edges() const { return edgeList; }

    ~VisualNode();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    QString m_name;
    QGraphicsTextItem *m_textItem;
    QList<VisualEdge *> edgeList;
};

#endif // VISUALNODE_H