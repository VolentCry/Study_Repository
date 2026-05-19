#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

#include "tree_logic.h"
#include "tree_render.h"

// корень дерева
TreeNode* globalRoot = nullptr;

void delay(int millisecondsToWait) {
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void updateScene(QGraphicsScene* scene, bool isHorizontal = false, int activeValue = -1) {
    // отрисовка сцены
    scene->clear();
    if (isHorizontal) {
        drawTreeHorizontal(globalRoot, scene, 50, 300, 150, activeValue);
    } else {
        drawTreeVertical(globalRoot, scene, 400, 50, 200, activeValue);
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QWidget window;
    window.resize(900, 700);
    window.setWindowTitle("Лабораторная работа №2 - Бинарные деревья");

    QVBoxLayout* mainLayout = new QVBoxLayout(&window);

    // Панель 1: основные кнопочки
    QHBoxLayout* topControls = new QHBoxLayout();
    QLineEdit* inputField = new QLineEdit();
    inputField->setPlaceholderText("Введите число...");
    QPushButton* btnAdd = new QPushButton("Добавить");
    QPushButton* btnDelete = new QPushButton("Удалить");
    QPushButton* btnBalance = new QPushButton("Балансировать");
    QPushButton* btnToggleView = new QPushButton("Сменить вид");

    topControls->addWidget(inputField);
    topControls->addWidget(btnAdd);
    topControls->addWidget(btnDelete);
    topControls->addWidget(btnBalance);
    topControls->addWidget(btnToggleView);

    // Панель 2: алгоритмы + поиск макс. элемента
    QVBoxLayout* bottomPanelLayout = new QVBoxLayout(); // Главный контейнер для низа
    QHBoxLayout* traversalsRow = new QHBoxLayout(); // 1 ряд
    QHBoxLayout* searchRow = new QHBoxLayout(); // 2 ряд

    QPushButton* btnPreOrder = new QPushButton("Прямой обход");
    QPushButton* btnInOrder = new QPushButton("Симметричный обход");
    QPushButton* btnPostOrder = new QPushButton("Обратный обход");
    QPushButton* btnFindMax = new QPushButton("Поиск макс. элемента");

    QLabel* resultLabel = new QLabel("Результат: ");
    QFont font = resultLabel->font();
    font.setPointSize(12);
    font.setBold(true);
    resultLabel->setFont(font);

    // Первый ряд
    traversalsRow->addWidget(btnPreOrder);
    traversalsRow->addWidget(btnInOrder);
    traversalsRow->addWidget(btnPostOrder);
    traversalsRow->addStretch();

    // Второй ряд
    searchRow->addWidget(btnFindMax);
    searchRow->addWidget(resultLabel);
    searchRow->addStretch();

    bottomPanelLayout->addLayout(traversalsRow);
    bottomPanelLayout->addLayout(searchRow);

    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);

    // Добавление всего в окно приложения
    mainLayout->addLayout(topControls);
    mainLayout->addWidget(view);
    mainLayout->addLayout(bottomPanelLayout);

    bool isHorizontalView = false;

    QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
        // Добавление вершины
        bool ok;
        int val = inputField->text().toInt(&ok);
        if (ok) {
            globalRoot = insertNode(globalRoot, val);
            updateScene(scene, isHorizontalView);
            inputField->clear();
        }
    });

    QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
        // Удаление вершины
        bool ok;
        int val = inputField->text().toInt(&ok);
        if (ok) {
            globalRoot = deleteNode(globalRoot, val);
            updateScene(scene, isHorizontalView);
            inputField->clear();
        }
    });

    QObject::connect(btnBalance, &QPushButton::clicked, [&]() {
        globalRoot = balanceTree(globalRoot);
        updateScene(scene, isHorizontalView);
    });

    QObject::connect(btnToggleView, &QPushButton::clicked, [&]() {
        isHorizontalView = !isHorizontalView;
        updateScene(scene, isHorizontalView);
    });

    // --- Обрабокта обхода (с анимацией) ---
    auto runTraversal = [&](int type) {
        int n = countNodes(globalRoot);
        if (n == 0) {
            resultLabel->setText("Результат: Дерево пустое");
            return;
        }

        int* arr = new int[n];
        int index = 0;

        if (type == 1) preOrderTraversal(globalRoot, arr, index);
        else if (type == 2) storeBSTNodes(globalRoot, arr, index);
        else if (type == 3) postOrderTraversal(globalRoot, arr, index);

        QString res = "Результат: ";

        // запуск визуала
        for (int i = 0; i < n; ++i) {
            updateScene(scene, isHorizontalView, arr[i]);
            res += QString::number(arr[i]) + " ";
            resultLabel->setText(res);
            delay(600);
        }

        // Возвращаем дерево в обычное состояние
        updateScene(scene, isHorizontalView, -1);
        delete[] arr;
    };

    QObject::connect(btnPreOrder, &QPushButton::clicked, [&]() { runTraversal(1); });
    QObject::connect(btnInOrder, &QPushButton::clicked, [&]() { runTraversal(2); });
    QObject::connect(btnPostOrder, &QPushButton::clicked, [&]() { runTraversal(3); });

    QObject::connect(btnFindMax, &QPushButton::clicked, [&]() {
        // Ппоиск максимального элемента (+закрашивание)
        if (!globalRoot) {
            resultLabel->setText("Результат: Дерево пустое");
            return;
        }

        TreeNode* maxNode = findMax(globalRoot);

        // результаты + визуал
        if (maxNode) {
            resultLabel->setText("Максимальный элемент: " + QString::number(maxNode->value));
            updateScene(scene, isHorizontalView, maxNode->value);
            delay(2000); // Длительность подсветки
            updateScene(scene, isHorizontalView, -1);
        }
    });

    window.show();
    return a.exec();
}