#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTableWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMap>
#include <QTimer>
#include <QQueue>
#include <QStack>
#include <QSet>

class VisualNode;

enum class GraphMode {
    None,
    Undirected,
    Directed
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addVertex();
    void deleteVertex();
    void loadPreset();
    void addEdge();
    void processNextAnimationStep();
    void runDFS();
    void runBFS();
    void runDijkstra();
    void runFloyd();
    void clearCanvas();
    void generateRandomGraph();

private:
    // Кнопки по макету
    QPushButton *btnAddVertex;
    QPushButton *btnDeleteVertex;
    QPushButton *btnAddEdge;
    QPushButton *btnPreset;
    QPushButton *btnDFS;
    QPushButton *btnBFS;
    QPushButton *btnDijkstra;
    QPushButton *btnFloyd;

    // Компоненты правой панели (статистика и матрица)
    QLabel *lblVertexCount;
    QLabel *lblEdgeCount;
    QTableWidget *matrixWidget;
    QPushButton *btnClearCanvas;
    QPushButton *btnRandomGraph;

    // Графика
    QGraphicsScene *scene;
    QGraphicsView *view;

    QMap<QString, VisualNode*> vertices;
    QTimer *animationTimer;
    QList<VisualNode*> currentAnimationPath; // Очередь вершин для анимации

    // Вспомогательные функции
    void resetColors(); // Метод для сброса цветов перед новым алгоритмом
    void startAnimation(const QList<VisualNode*> &path);

    GraphMode currentGraphMode = GraphMode::None;
    void checkGraphState();

    void createNodeVisual(const QString &name, int x, int y);

    // ВАЖНО: Убедись, что здесь есть bool isDirected!
    void createEdgeVisual(const QString &from, const QString &to, int weight, bool isDirected);

    void updateMatrix();// Обновляет матрицу и счетчики
};

#endif // MAINWINDOW_H