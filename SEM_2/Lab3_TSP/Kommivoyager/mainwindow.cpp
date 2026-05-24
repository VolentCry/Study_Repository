#include "mainwindow.h"
#include "visualnode.h"
#include "visualedge.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QHeaderView>
#include <functional>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // --- 1. Верхняя панель управления ---
    QGridLayout *topGrid = new QGridLayout();

    btnAddVertex = new QPushButton("Добавить вершину", this);
    btnDeleteVertex = new QPushButton("Удалить вершину", this);
    btnAddEdge = new QPushButton("Добавить ребро", this);
    btnPreset = new QPushButton("Пресет графа", this);
    btnTSP = new QPushButton("Алгоритм Коммивояжёра", this);

    topGrid->addWidget(btnAddVertex, 0, 0);
    topGrid->addWidget(btnAddEdge, 0, 1);
    topGrid->addWidget(btnTSP, 0, 2);
    topGrid->addWidget(btnDeleteVertex, 1, 0);
    topGrid->addWidget(btnPreset, 1, 1);

    // --- 2. Левая панель (Холст графа) ---
    scene = new QGraphicsScene(this);
    scene->setSceneRect(-2000, -2000, 4000, 4000);

    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setDragMode(QGraphicsView::RubberBandDrag);

    // --- 3. Правая панель (Статистика, матрица) ---
    QVBoxLayout *rightPanel = new QVBoxLayout();

    lblVertexCount = new QLabel("Количество вершин: 0", this);
    lblEdgeCount = new QLabel("Количество рёбер: 0", this);
    lblVertexCount->setFont(QFont("Arial", 12));
    lblEdgeCount->setFont(QFont("Arial", 12));

    matrixWidget = new QTableWidget(this);
    matrixWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    btnClearCanvas = new QPushButton("Очистить холст", this);
    btnClearCanvas->setMinimumHeight(40);

    rightPanel->addWidget(lblVertexCount);
    rightPanel->addWidget(lblEdgeCount);
    rightPanel->addWidget(matrixWidget);
    rightPanel->addWidget(btnClearCanvas); // Добавляем кнопку очистки прямо в панель

    // --- 4. Основная компоновка ---
    QHBoxLayout *mainSplit = new QHBoxLayout();
    mainSplit->addWidget(view, 2);
    mainSplit->addLayout(rightPanel, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topGrid);
    mainLayout->addLayout(mainSplit);

    centralWidget->setLayout(mainLayout);

    // --- 5. Подключение сигналов ---
    connect(btnAddVertex, &QPushButton::clicked, this, &MainWindow::addVertex);
    connect(btnDeleteVertex, &QPushButton::clicked, this, &MainWindow::deleteVertex);
    connect(btnAddEdge, &QPushButton::clicked, this, &MainWindow::addEdge);
    connect(btnPreset, &QPushButton::clicked, this, &MainWindow::loadPreset);
    connect(btnTSP, &QPushButton::clicked, this, &MainWindow::runTSP);
    connect(btnClearCanvas, &QPushButton::clicked, this, &MainWindow::clearCanvas);

    this->resize(1200, 800);
    this->setWindowTitle("Визуализатор задачи Коммивояжёра");
    updateMatrix();

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &MainWindow::processNextAnimationStep);
}

MainWindow::~MainWindow() {}

void MainWindow::addVertex()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Новая вершина", "Имя:", QLineEdit::Normal, "", &ok);
    if (!ok || name.trimmed().isEmpty()) return;
    name = name.trimmed();
    if (vertices.contains(name)) return;

    int x = QRandomGenerator::global()->bounded(-200, 200);
    int y = QRandomGenerator::global()->bounded(-150, 150);
    createNodeVisual(name, x, y);
    updateMatrix();
}

void MainWindow::deleteVertex()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Удаление", "Имя вершины:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    name = name.trimmed();

    if (!vertices.contains(name)) return;

    VisualNode *nodeToDelete = vertices.take(name);
    scene->removeItem(nodeToDelete);
    delete nodeToDelete;

    checkGraphState();
    updateMatrix();
}

void MainWindow::addEdge()
{
    bool ok1, ok2, ok3;
    QString name1 = QInputDialog::getText(this, "Ребро", "Откуда:", QLineEdit::Normal, "", &ok1);
    if (!ok1 || !vertices.contains(name1)) return;

    QString name2 = QInputDialog::getText(this, "Ребро", "Куда:", QLineEdit::Normal, "", &ok2);
    if (!ok2 || !vertices.contains(name2)) return;

    int weight = QInputDialog::getInt(this, "Вес", "Вес ребра:", 1, -1000, 1000, 1, &ok3);
    if (!ok3) return;

    bool isDirected = false;

    if (currentGraphMode == GraphMode::None) {
        QStringList items;
        items << "Неориентированное" << "Ориентированное (Стрелка)";
        bool okType;
        QString item = QInputDialog::getItem(this, "Тип графа", "Выберите тип ребра:", items, 0, false, &okType);
        if (!okType) return;

        isDirected = (item == "Ориентированное (Стрелка)");
        currentGraphMode = isDirected ? GraphMode::Directed : GraphMode::Undirected;
    } else {
        isDirected = (currentGraphMode == GraphMode::Directed);
    }

    createEdgeVisual(name1, name2, weight, isDirected);
    updateMatrix();
}

void MainWindow::loadPreset()
{
    clearCanvas();
    currentGraphMode = GraphMode::Undirected;

    createNodeVisual("1", 0, -150);
    createNodeVisual("2", -200, 0);
    createNodeVisual("3", 200, 0);
    createNodeVisual("4", -100, 200);
    createNodeVisual("5", 100, 200);
    createNodeVisual("6", 150, -220);
    createNodeVisual("7", -150, -220);

    createEdgeVisual("1", "3", 8, false);
    createEdgeVisual("3", "2", 57, false);
    createEdgeVisual("1", "2", 34, false);
    createEdgeVisual("3", "5", 2, false);
    createEdgeVisual("2", "5", 5, false);
    createEdgeVisual("6", "1", 21, false);
    createEdgeVisual("6", "3", 13, false);
    createEdgeVisual("4", "5", 3, false);
    createEdgeVisual("4", "2", 45, false);
    createEdgeVisual("1", "7", 15, false);
    createEdgeVisual("2", "7", 50, false);
    createEdgeVisual("4", "3", 30, false);

    updateMatrix();
}

void MainWindow::createNodeVisual(const QString &name, int x, int y)
{
    VisualNode *node = new VisualNode(name);
    node->setPos(x, y);
    scene->addItem(node);
    vertices[name] = node;
}

void MainWindow::createEdgeVisual(const QString &from, const QString &to, int weight, bool isDirected)
{
    if (!vertices.contains(from) || !vertices.contains(to)) return;
    VisualNode *src = vertices[from];
    VisualNode *dest = vertices[to];

    VisualEdge *edge = new VisualEdge(src, dest, weight, isDirected);
    scene->addItem(edge);
    src->addEdge(edge);
    dest->addEdge(edge);

    connect(edge, &VisualEdge::weightChanged, this, &MainWindow::updateMatrix);
}

void MainWindow::updateMatrix()
{
    QStringList keys = vertices.keys();
    keys.sort();
    int n = keys.size();

    lblVertexCount->setText("Количество вершин: " + QString::number(n));

    int edgeCount = 0;
    for (VisualNode *node : vertices) {
        edgeCount += node->edges().size();
    }
    lblEdgeCount->setText("Количество рёбер: " + QString::number(currentGraphMode == GraphMode::Directed ? edgeCount : edgeCount / 2));

    matrixWidget->setRowCount(n);
    matrixWidget->setColumnCount(n);
    matrixWidget->setHorizontalHeaderLabels(keys);
    matrixWidget->setVerticalHeaderLabels(keys);
    matrixWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < n; ++i) {
        VisualNode *srcNode = vertices[keys[i]];

        for (int j = 0; j < n; ++j) {
            VisualNode *destNode = vertices[keys[j]];
            QString cellValue = "∞";

            if (i == j) {
                cellValue = "0";
            } else {
                for (VisualEdge *edge : srcNode->edges()) {
                    if (edge->isDirected()) {
                        if (edge->sourceNode() == srcNode && edge->destNode() == destNode) {
                            cellValue = QString::number(edge->weight());
                            break;
                        }
                    } else {
                        if ((edge->sourceNode() == srcNode && edge->destNode() == destNode) ||
                            (edge->sourceNode() == destNode && edge->destNode() == srcNode))
                        {
                            cellValue = QString::number(edge->weight());
                            break;
                        }
                    }
                }
            }
            QTableWidgetItem *item = new QTableWidgetItem(cellValue);
            item->setTextAlignment(Qt::AlignCenter);
            matrixWidget->setItem(i, j, item);
        }
    }
}

void MainWindow::resetColors()
{
    if (animationTimer->isActive()) {
        animationTimer->stop();
    }
    currentAnimationPath.clear();

    for (VisualNode *node : vertices) {
        node->setColor(QColor("#a1c4fd"));
    }
}

void MainWindow::startAnimation(const QList<VisualNode*> &path)
{
    resetColors();
    currentAnimationPath = path;
    animationTimer->start(600);
}

void MainWindow::processNextAnimationStep()
{
    if (currentAnimationPath.isEmpty()) {
        animationTimer->stop();
        QMessageBox::information(this, "Готово", "Обход завершен!");
        return;
    }

    VisualNode *node = currentAnimationPath.takeFirst();
    node->setColor(Qt::green);
}

// Рекурсивный алгоритм поиска кратчайшего замкнутого пути (задача Коммивояжёра)
void MainWindow::runTSP()
{
    resetColors();

    int n = vertices.size();
    if (n < 2) {
        QMessageBox::warning(this, "Коммивояжёр", "Недостаточно вершин для построения маршрута.");
        return;
    }

    bool ok;
    QString startName = QInputDialog::getText(this, "Коммивояжёр", "Стартовая вершина:", QLineEdit::Normal, "", &ok);
    if (!ok || !vertices.contains(startName)) return;

    VisualNode *startNode = vertices[startName];
    QList<VisualNode*> nodes = vertices.values();

    QMap<VisualNode*, QMap<VisualNode*, int>> cost;
    for (VisualNode *u : nodes) {
        for (VisualNode *v : nodes) {
            cost[u][v] = 1e9;
        }
        for (VisualEdge *edge : u->edges()) {
            if (edge->isDirected()) {
                if (edge->sourceNode() == u) {
                    cost[u][edge->destNode()] = edge->weight();
                }
            } else {
                VisualNode *neighbor = (edge->sourceNode() == u) ? edge->destNode() : edge->sourceNode();
                cost[u][neighbor] = edge->weight();
            }
        }
    }

    int minPathCost = 1e9;
    QList<VisualNode*> bestPath;

    // Рекурсивный перебор с отсечением (Branch and Bound)
    std::function<void(VisualNode*, int, int, QList<VisualNode*>&, QSet<VisualNode*>&)> backtrack =
        [&](VisualNode* curr, int visitedCount, int currentCost, QList<VisualNode*>& currentPath, QSet<VisualNode*>& visited) {

            if (currentCost >= minPathCost) return;

            if (visitedCount == n) {
                if (cost[curr][startNode] != 1e9) {
                    int totalCost = currentCost + cost[curr][startNode];
                    if (totalCost < minPathCost) {
                        minPathCost = totalCost;
                        bestPath = currentPath;
                        bestPath.append(startNode);
                    }
                }
                return;
            }

            for (VisualNode* next : nodes) {
                if (!visited.contains(next) && cost[curr][next] != 1e9) {
                    visited.insert(next);
                    currentPath.append(next);

                    backtrack(next, visitedCount + 1, currentCost + cost[curr][next], currentPath, visited);

                    currentPath.removeLast();
                    visited.remove(next);
                }
            }
        };

    QList<VisualNode*> currentPath;
    QSet<VisualNode*> visited;

    currentPath.append(startNode);
    visited.insert(startNode);

    backtrack(startNode, 1, 0, currentPath, visited);

    if (minPathCost == 1e9) {
        QMessageBox::warning(this, "Коммивояжёр", "Полный замкнутый цикл обхода (Гамильтонов цикл) не существует.");
    } else {
        // Формируем текстовую строку пути (вывод последовательности маршрута)
        QStringList pathNames;
        for (VisualNode *node : bestPath) {
            pathNames << node->name();
        }
        QString routeStr = pathNames.join(" -> ");

        // Вывод результатов
        QMessageBox::information(this, "Коммивояжёр",
                                 QString("Оптимальный маршрут найден!\n\n"
                                         "Маршрут: %1\n"
                                         "Стоимость обхода: %2")
                                     .arg(routeStr)
                                     .arg(minPathCost));

        startAnimation(bestPath);
    }
}

void MainWindow::checkGraphState()
{
    int totalEdges = 0;
    for (VisualNode *node : vertices) {
        totalEdges += node->edges().size();
    }
    if (totalEdges == 0 && vertices.isEmpty()) {
        currentGraphMode = GraphMode::None;
    }
}

void MainWindow::clearCanvas()
{
    qDeleteAll(vertices);
    vertices.clear();
    scene->clear();
    currentGraphMode = GraphMode::None;
    updateMatrix();
}