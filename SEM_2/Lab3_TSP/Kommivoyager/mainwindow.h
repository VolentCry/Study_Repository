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
    void runTSP(); // Слот для запуска алгоритма коммивояжёра
    void clearCanvas();

private:
    // Кнопки панели управления
    QPushButton *btnAddVertex;
    QPushButton *btnDeleteVertex;
    QPushButton *btnAddEdge;
    QPushButton *btnPreset;
    QPushButton *btnTSP;

    // Компоненты правой панели (статистика и матрица)
    QLabel *lblVertexCount;
    QLabel *lblEdgeCount;
    QTableWidget *matrixWidget;
    QPushButton *btnClearCanvas; // Единственная нижняя кнопка

    // Графика
    QGraphicsScene *scene;
    QGraphicsView *view;

    QMap<QString, VisualNode*> vertices;
    QTimer *animationTimer;
    QList<VisualNode*> currentAnimationPath; // Очередь вершин для анимации

    // Вспомогательные функции
    void resetColors();
    void startAnimation(const QList<VisualNode*> &path);

    GraphMode currentGraphMode = GraphMode::None;
    void checkGraphState();

    void createNodeVisual(const QString &name, int x, int y);
    void createEdgeVisual(const QString &from, const QString &to, int weight, bool isDirected);

    void updateMatrix(); // Обновляет матрицу и счетчики
};

#endif // MAINWINDOW_H