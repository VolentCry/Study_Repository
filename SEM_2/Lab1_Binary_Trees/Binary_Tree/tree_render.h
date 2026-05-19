#ifndef TREE_RENDER_H
#define TREE_RENDER_H

#include <QGraphicsScene>
#include "tree_logic.h"

void drawGraphicNode(QGraphicsScene* scene, int x, int y, int value, int activeValue);
void drawTreeVertical(TreeNode* root, QGraphicsScene* scene, int x, int y, int hOffset, int activeValue = -1);
void drawTreeHorizontal(TreeNode* root, QGraphicsScene* scene, int x, int y, int vOffset, int activeValue = -1);

#endif // TREE_RENDER_H