#include "tree_render.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>
#include <QFont>

const int NODE_RADIUS = 20;

void drawGraphicNode(QGraphicsScene* scene, int x, int y, int value, int activeValue) {
    // Если значение узла совпадает с активным - красим в зеленый, иначе в белый
    QBrush brush = (value == activeValue) ? QBrush(Qt::green) : QBrush(Qt::white);

    scene->addEllipse(x, y, NODE_RADIUS * 2, NODE_RADIUS * 2,
                      QPen(Qt::black, 2), brush);

    QGraphicsTextItem* text = scene->addText(QString::number(value));
    QFont font = text->font();
    font.setBold(true);
    text->setFont(font);

    qreal textWidth = text->boundingRect().width();
    qreal textHeight = text->boundingRect().height();
    text->setPos(x + NODE_RADIUS - textWidth / 2, y + NODE_RADIUS - textHeight / 2);
}

void drawTreeVertical(TreeNode* root, QGraphicsScene* scene, int x, int y, int hOffset, int activeValue) {
    if (!root) return;

    int nextY = y + 80;

    if (root->left) {
        int nextX = x - hOffset;
        scene->addLine(x + NODE_RADIUS, y + NODE_RADIUS,
                       nextX + NODE_RADIUS, nextY + NODE_RADIUS, QPen(Qt::black));
        drawTreeVertical(root->left, scene, nextX, nextY, hOffset / 2, activeValue); // Пробрасываем activeValue
    }
    if (root->right) {
        int nextX = x + hOffset;
        scene->addLine(x + NODE_RADIUS, y + NODE_RADIUS,
                       nextX + NODE_RADIUS, nextY + NODE_RADIUS, QPen(Qt::black));
        drawTreeVertical(root->right, scene, nextX, nextY, hOffset / 2, activeValue);
    }

    drawGraphicNode(scene, x, y, root->value, activeValue);
}

// Сделай то же самое для drawTreeHorizontal (пробрось activeValue рекурсивно и в drawGraphicNode)
void drawTreeHorizontal(TreeNode* root, QGraphicsScene* scene, int x, int y, int vOffset, int activeValue) {
    if (!root) return;
    int nextX = x + 80;
    if (root->left) {
        int nextY = y - vOffset;
        scene->addLine(x + NODE_RADIUS, y + NODE_RADIUS, nextX + NODE_RADIUS, nextY + NODE_RADIUS, QPen(Qt::black));
        drawTreeHorizontal(root->left, scene, nextX, nextY, vOffset / 2, activeValue);
    }
    if (root->right) {
        int nextY = y + vOffset;
        scene->addLine(x + NODE_RADIUS, y + NODE_RADIUS, nextX + NODE_RADIUS, nextY + NODE_RADIUS, QPen(Qt::black));
        drawTreeHorizontal(root->right, scene, nextX, nextY, vOffset / 2, activeValue);
    }
    drawGraphicNode(scene, x, y, root->value, activeValue);
}