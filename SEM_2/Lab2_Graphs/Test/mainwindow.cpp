#include "mainwindow.h"
#include "visualnode.h"
#include "visualedge.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // --- 1. Верхняя панель ---
    QGridLayout *topGrid = new QGridLayout();

    btnAddVertex = new QPushButton("Добавить вершину", this);
    btnDeleteVertex = new QPushButton("Удалить вершину", this);
    btnAddEdge = new QPushButton("Добавить ребро", this);
    btnPreset = new QPushButton("Пресет графа", this);
    btnDFS = new QPushButton("DFS", this);
    btnBFS = new QPushButton("BFS", this);
    btnDijkstra = new QPushButton("Алгоритм Дейкстры", this);
    btnFloyd = new QPushButton("Алгоритм Флойда", this);

    // Размещение кнопок
    topGrid->addWidget(btnAddVertex, 0, 0);
    topGrid->addWidget(btnAddEdge, 0, 1);
    topGrid->addWidget(btnDFS, 0, 2);
    topGrid->addWidget(btnDijkstra, 0, 3);
    topGrid->addWidget(btnDeleteVertex, 1, 0);
    topGrid->addWidget(btnPreset, 1, 1);
    topGrid->addWidget(btnBFS, 1, 2);
    topGrid->addWidget(btnFloyd, 1, 3);

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
    matrixWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // Запрещаем ручное редактирование

    btnClearCanvas = new QPushButton("Очистить холст", this);
    btnRandomGraph = new QPushButton("Рандомный граф", this);
    btnClearCanvas->setMinimumHeight(40);
    btnRandomGraph->setMinimumHeight(40);

    // Слой для кнопок правой панели
    QHBoxLayout *bottomButtonsLayout = new QHBoxLayout();
    bottomButtonsLayout->addWidget(btnClearCanvas);
    bottomButtonsLayout->addWidget(btnRandomGraph);

    // Добавляем всё в правую панель
    rightPanel->addWidget(lblVertexCount);
    rightPanel->addWidget(lblEdgeCount);
    rightPanel->addWidget(matrixWidget);
    rightPanel->addLayout(bottomButtonsLayout);

    // --- 4. Основная компановка панелей ---
    QHBoxLayout *mainSplit = new QHBoxLayout();
    mainSplit->addWidget(view, 2); // Холст с графом
    mainSplit->addLayout(rightPanel, 1); // Правая панель

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topGrid);
    mainLayout->addLayout(mainSplit);

    centralWidget->setLayout(mainLayout);

    // --- 5. Подключение сигналов для кнопок ---
    connect(btnAddVertex, &QPushButton::clicked, this, &MainWindow::addVertex);
    connect(btnDeleteVertex, &QPushButton::clicked, this, &MainWindow::deleteVertex);
    connect(btnAddEdge, &QPushButton::clicked, this, &MainWindow::addEdge);
    connect(btnPreset, &QPushButton::clicked, this, &MainWindow::loadPreset);
    connect(btnDFS, &QPushButton::clicked, this, &MainWindow::runDFS);
    connect(btnBFS, &QPushButton::clicked, this, &MainWindow::runBFS);
    connect(btnDijkstra, &QPushButton::clicked, this, &MainWindow::runDijkstra);
    connect(btnFloyd, &QPushButton::clicked, this, &MainWindow::runFloyd);
    connect(btnClearCanvas, &QPushButton::clicked, this, &MainWindow::clearCanvas);
    connect(btnRandomGraph, &QPushButton::clicked, this, &MainWindow::generateRandomGraph);

    this->resize(1000, 600);
    this->setWindowTitle("Визуальный Редактор Графов");
    updateMatrix(); // Первоначальная отрисовка пустой матрицы

    // Инициализация таймера для анимации
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

    updateMatrix(); // Перерисовываем матрицу после удаления
}

void MainWindow::addEdge()
{
    // Добавление ребра
    bool ok1, ok2, ok3;
    QString name1 = QInputDialog::getText(this, "Ребро", "Откуда:", QLineEdit::Normal, "", &ok1);
    if (!ok1 || !vertices.contains(name1)) return;

    QString name2 = QInputDialog::getText(this, "Ребро", "Куда:", QLineEdit::Normal, "", &ok2);
    if (!ok2 || !vertices.contains(name2)) return;

    int weight = QInputDialog::getInt(this, "Вес", "Вес ребра:", 1, -1000, 1000, 1, &ok3);
    if (!ok3) return;

    bool isDirected = false;

    // Если в графе нет рёбер, то выбираем нужный тип графа (ориентированный/неориентированный)
    if (currentGraphMode == GraphMode::None) {
        QStringList items;
        items << "Неориентированное" << "Ориентированное (Стрелка)";
        bool okType;
        QString item = QInputDialog::getItem(this, "Тип графа", "Выберите тип ребра:", items, 0, false, &okType);
        if (!okType) return; // Отменили создание

        isDirected = (item == "Ориентированное (Стрелка)");
        currentGraphMode = isDirected ? GraphMode::Directed : GraphMode::Undirected;
    } else {
        // используем уже установленный режим, если таковой имеется
        isDirected = (currentGraphMode == GraphMode::Directed);
    }

    createEdgeVisual(name1, name2, weight, isDirected);
    updateMatrix();
}

void MainWindow::loadPreset()
{
    // Очищаем всё
    qDeleteAll(vertices);
    vertices.clear();
    scene->clear();

    currentGraphMode = GraphMode::Undirected; // Явное указание типа графа

    // Создаем пресет:
    // Вершины
    createNodeVisual("1", 200, 0);
    createNodeVisual("2", 10, 310);
    createNodeVisual("3", 280, 220);
    createNodeVisual("4", -130, 250);
    createNodeVisual("5", -110, 110);
    createNodeVisual("6", -40, -25);

    // Рёбра
    createEdgeVisual("1", "3", 8, false);
    createEdgeVisual("3", "2", 57, false);
    createEdgeVisual("1", "2", 34, false);
    createEdgeVisual("1", "5", 2, false);
    createEdgeVisual("2", "5", 5, false);
    createEdgeVisual("6", "1", 21, false);
    createEdgeVisual("6", "5", 13, false);
    createEdgeVisual("4", "5", 3, false);
    createEdgeVisual("4", "2", 45, false);

    updateMatrix();
}

void MainWindow::createNodeVisual(const QString &name, int x, int y)
{
    // Визуализация ребра
    VisualNode *node = new VisualNode(name);
    node->setPos(x, y);
    scene->addItem(node);
    vertices[name] = node;
}

// --- Построение матрицы смежности и обновление небольшой статистики по графу ---
void MainWindow::updateMatrix()
{
    QStringList keys = vertices.keys();
    keys.sort(); // Сортируем имена по алфавиту для красоты
    int n = keys.size();

    // 1. Обновляем счетчики
    lblVertexCount->setText("Количество вершин: " + QString::number(n));

    int edgeCount = 0;
    for (VisualNode *node : vertices) {
        edgeCount += node->edges().size();
    }
    lblEdgeCount->setText("Количество рёбер: " + QString::number(edgeCount / 2));

    // 2. Настраиваем размеры матрицы
    matrixWidget->setRowCount(n);
    matrixWidget->setColumnCount(n);
    matrixWidget->setHorizontalHeaderLabels(keys);
    matrixWidget->setVerticalHeaderLabels(keys);
    matrixWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 3. Заполняем матрицу
    for (int i = 0; i < n; ++i) {
        VisualNode *srcNode = vertices[keys[i]];

        for (int j = 0; j < n; ++j) {
            VisualNode *destNode = vertices[keys[j]];
            QString cellValue = "∞";

            if (i == j) {
                cellValue = "0"; // Расстояние до самой себя
            } else {
                // Ищем ребро между этими двумя вершинами
                for (VisualEdge *edge : srcNode->edges()) {
                    if ((edge->sourceNode() == srcNode && edge->destNode() == destNode) ||
                        (edge->sourceNode() == destNode && edge->destNode() == srcNode))
                    {
                        cellValue = QString::number(edge->weight());
                        break;
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
    // Функция принудительного очищения графика от анимаций поиска и алгоритмов
    // Если анимация еще работает, останавливаем её
    if (animationTimer->isActive()) {
        animationTimer->stop();
    }

    // Очищаем очередь анимации, чтобы старые шаги не смешались с новыми
    currentAnimationPath.clear();

    // Возвращаем всем вершинам стандартный цвет
    for (VisualNode *node : vertices) {
        node->setColor(QColor("#a1c4fd"));
    }
}

void MainWindow::startAnimation(const QList<VisualNode*> &path)
{
    resetColors();
    currentAnimationPath = path;
    animationTimer->start(500); // Задержка на каждом шаге анимации
}

void MainWindow::processNextAnimationStep()
{
    if (currentAnimationPath.isEmpty()) {
        animationTimer->stop(); // Отсановка таймера
        QMessageBox::information(this, "Готово", "Алгоритм завершил работу!");
        return;
    }

    // Достаем следующую вершину и красим её в зеленый
    VisualNode *node = currentAnimationPath.takeFirst();
    node->setColor(Qt::green);
}


void MainWindow::runBFS()
{
    resetColors(); // Сброс цветов

    if (vertices.isEmpty()) return;

    bool ok;
    QString startName = QInputDialog::getText(this, "BFS", "Стартовая вершина:", QLineEdit::Normal, "", &ok);
    if (!ok || !vertices.contains(startName)) return;

    VisualNode *startNode = vertices[startName];

    QList<VisualNode*> path;
    QQueue<VisualNode*> queue;
    QSet<VisualNode*> visited;

    queue.enqueue(startNode);
    visited.insert(startNode);

    while (!queue.isEmpty()) {
        VisualNode *curr = queue.dequeue();
        path.append(curr);

        for (VisualEdge *edge : curr->edges()) {
            VisualNode *neighbor = nullptr;

            // Определяем соседа с учетом направления ребра
            if (edge->sourceNode() == curr) {
                neighbor = edge->destNode();
            } else if (!edge->isDirected() && edge->destNode() == curr) {
                neighbor = edge->sourceNode();
            }

            if (neighbor != nullptr && !visited.contains(neighbor)) {
                visited.insert(neighbor);
                queue.enqueue(neighbor);
            }
        }
    }

    startAnimation(path);
}

void MainWindow::runDFS()
{
    resetColors(); // Сброс цветов

    if (vertices.isEmpty()) return;

    bool ok;
    QString startName = QInputDialog::getText(this, "DFS", "Стартовая вершина:", QLineEdit::Normal, "", &ok);
    if (!ok || !vertices.contains(startName)) return;

    VisualNode *startNode = vertices[startName];

    QList<VisualNode*> path;
    QStack<VisualNode*> stack;
    QSet<VisualNode*> visited;

    stack.push(startNode);

    while (!stack.isEmpty()) {
        VisualNode *curr = stack.pop();

        if (!visited.contains(curr)) {
            visited.insert(curr);
            path.append(curr);

            // Добавляем соседей в стек
            for (VisualEdge *edge : curr->edges()) {
                VisualNode *neighbor = nullptr;
                if (edge->sourceNode() == curr) {
                    neighbor = edge->destNode();
                } else if (!edge->isDirected() && edge->destNode() == curr) {
                    neighbor = edge->sourceNode(); // Если неориентированный, то можем идти в обратную сторону
                }

                if (neighbor) {
                    stack.push(neighbor);
                }
            }
        }
    }
    startAnimation(path); // запуск визуала


// Дейкстера
void MainWindow::runDijkstra()
{
    resetColors(); // Сброс цветов

    if (vertices.isEmpty()) return;

    bool ok1, ok2;
    QString startName = QInputDialog::getText(this, "Дейкстра", "Откуда (имя):", QLineEdit::Normal, "", &ok1);
    if (!ok1 || !vertices.contains(startName)) return;

    QString endName = QInputDialog::getText(this, "Дейкстра", "Куда (имя):", QLineEdit::Normal, "", &ok2);
    if (!ok2 || !vertices.contains(endName)) return;

    VisualNode *startNode = vertices[startName];
    VisualNode *endNode = vertices[endName];

    QMap<VisualNode*, int> dist; // Минимальное расстояние до вершины
    QMap<VisualNode*, VisualNode*> prev; // Предыдущая вершина
    QList<VisualNode*> unvisited = vertices.values();

    // Инициализация
    for (VisualNode *node : unvisited) {
        dist[node] = 1e9;
        prev[node] = nullptr;
    }
    dist[startNode] = 0;

    // Основной цикл
    while (!unvisited.isEmpty()) {
        // Ищем непосещенную вершину с минимальным известным расстоянием
        VisualNode *u = nullptr;
        int minDist = 1e9;
        for (VisualNode *node : unvisited) {
            if (dist[node] < minDist) {
                minDist = dist[node];
                u = node;
            }
        }

        // Если оставшиеся недостижимы или мы дошли до цели — прерываем
        if (u == nullptr || minDist == 1e9 || u == endNode) break;

        unvisited.removeOne(u);

        // Обновляем расстояния для соседей
        for (VisualEdge *edge : u->edges()) {
            VisualNode *v = (edge->sourceNode() == u) ? edge->destNode() : edge->sourceNode();

            if (unvisited.contains(v)) {
                int alt = dist[u] + edge->weight();
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                }
            }
        }
    }

    // Восстановление пути от endNode к startNode
    QList<VisualNode*> path;
    VisualNode *curr = endNode;

    // Проверяем, существует ли путь
    if (prev[curr] != nullptr || curr == startNode) {
        while (curr != nullptr) {
            path.prepend(curr);
            curr = prev[curr];
        }

        // резульат, запуск визуала
        QMessageBox::information(this, "Дейкстра", QString("Кратчайший путь найден!\nДлина пути: %1").arg(dist[endNode]));
        startAnimation(path);
    } else {
        QMessageBox::warning(this, "Дейкстра", "Путь между этими вершинами не существует.");
    }
}

// Флойд
void MainWindow::runFloyd()
{
    resetColors(); // Сброс цветов

    if (vertices.isEmpty()) return;

    bool ok1, ok2;
    QString startName = QInputDialog::getText(this, "Флойд", "Откуда (имя):", QLineEdit::Normal, "", &ok1);
    if (!ok1 || !vertices.contains(startName)) return;

    QString endName = QInputDialog::getText(this, "Флойд", "Куда (имя):", QLineEdit::Normal, "", &ok2);
    if (!ok2 || !vertices.contains(endName)) return;

    VisualNode *startNode = vertices[startName];
    VisualNode *endNode = vertices[endName];

    QList<VisualNode*> nodes = vertices.values();

    // Матрица расстояний и матрица следующих шагов для восстановления пути
    QMap<VisualNode*, QMap<VisualNode*, int>> dist;
    QMap<VisualNode*, QMap<VisualNode*, VisualNode*>> next;

    // 1. Инициализация матриц
    for (VisualNode *u : nodes) {
        for (VisualNode *v : nodes) {
            dist[u][v] = 1e9; // Бесконечность
            next[u][v] = nullptr;
        }
        dist[u][u] = 0;

        // Записываем веса прямых рёбер
        for (VisualEdge *edge : u->edges()) {
            VisualNode *neighbor = (edge->sourceNode() == u) ? edge->destNode() : edge->sourceNode();
            dist[u][neighbor] = edge->weight();
            next[u][neighbor] = neighbor;
        }
    }

    // 2. Основной цикл Флойда-Уоршелла (перебираем промежуточные вершины 'k')
    for (VisualNode *k : nodes) {
        for (VisualNode *i : nodes) {
            for (VisualNode *j : nodes) {
                if (dist[i][k] < 1e9 && dist[k][j] < 1e9) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k]; // Обновляем маршрут
                    }
                }
            }
        }
    }

    // 3. Восстановление пути
    if (dist[startNode][endNode] == 1e9) {
        QMessageBox::warning(this, "Флойд-Уоршелл", "Путь между этими вершинами не существует.");
        return;
    }

    QList<VisualNode*> path;
    VisualNode *curr = startNode;
    path.append(curr);

    while (curr != endNode) {
        curr = next[curr][endNode];
        path.append(curr);
    }

    QMessageBox::information(this, "Флойд-Уоршелл", QString("Кратчайший путь вычислен матричным методом!\nДлина пути: %1").arg(dist[startNode][endNode]));
    startAnimation(path);
}

void MainWindow::createEdgeVisual(const QString &from, const QString &to, int weight, bool isDirected)
{
    if (!vertices.contains(from) || !vertices.contains(to)) return;
    VisualNode *src = vertices[from];
    VisualNode *dest = vertices[to];

    // Передаем isDirected в конструктор ребра
    VisualEdge *edge = new VisualEdge(src, dest, weight, isDirected);
    scene->addItem(edge);
    src->addEdge(edge);
    dest->addEdge(edge);

    connect(edge, &VisualEdge::weightChanged, this, &MainWindow::updateMatrix);
}

void MainWindow::checkGraphState()
{
    // Сбрасывает тип графа, если пользователь удаляет все рёбра и вершины
    int totalEdges = 0;
    for (VisualNode *node : vertices) {
        totalEdges += node->edges().size();
    }
    if (totalEdges == 0) {
        currentGraphMode = GraphMode::None;
    }
}

// Очистка холста от текущего графа
void MainWindow::clearCanvas()
{
    // Удаляем все объекты вершин, рёбра сами подтянутся
    qDeleteAll(vertices);
    vertices.clear();
    scene->clear();

    // сбрасываем тип графа
    currentGraphMode = GraphMode::None;

    updateMatrix();
}

// Генерация случайного графа
void MainWindow::generateRandomGraph()
{
    clearCanvas(); // очищаем старый граф

    // Случайное количество вершин (от 5 до 8)
    int numNodes = QRandomGenerator::global()->bounded(5, 9);

    // Случайный тип графа (0 - неориентированный, 1 - ориентированный)
    bool isDirected = QRandomGenerator::global()->bounded(0, 2) == 1;
    currentGraphMode = isDirected ? GraphMode::Directed : GraphMode::Undirected;

    // 1. Создаем вершины
    QStringList nodeNames;
    for (int i = 0; i < numNodes; ++i) {
        QString name = QString::number(i + 1);
        // Разбрасываем вершины по экрану случайным образом
        int x = QRandomGenerator::global()->bounded(-250, 250);
        int y = QRandomGenerator::global()->bounded(-200, 200);
        createNodeVisual(name, x, y);
        nodeNames << name;
    }

    // 2. Генерируем случайные связи
    // Количество ребер: от V до V*2
    int numEdges = QRandomGenerator::global()->bounded(numNodes, numNodes * 2 + 1);

    for (int i = 0; i < numEdges; ++i) {
        // Выбираем две случайные вершины
        QString from = nodeNames[QRandomGenerator::global()->bounded(numNodes)];
        QString to = nodeNames[QRandomGenerator::global()->bounded(numNodes)];

        if (from == to) continue; // Избегаем петель

        int weight = QRandomGenerator::global()->bounded(1, 51); // Вес от 1 до 50

        // Проверяем, нет ли уже такого ребра
        bool edgeExists = false;
        for (VisualEdge *e : vertices[from]->edges()) {
            if (e->destNode()->name() == to) {
                edgeExists = true;
                break;
            }
            if (!isDirected && e->sourceNode()->name() == to) {
                edgeExists = true;
                break;
            }
        }

        if (!edgeExists) {
            createEdgeVisual(from, to, weight, isDirected);
        }
    }

    updateMatrix();
}