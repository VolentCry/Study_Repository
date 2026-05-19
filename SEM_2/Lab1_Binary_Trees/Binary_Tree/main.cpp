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

// Глобальный корень дерева
TreeNode* globalRoot = nullptr;

// Функция, которая ждет миллисекунды, но не "вешает" графический интерфейс
void delay(int millisecondsToWait) {
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

// Обновленная функция отрисовки сцены
void updateScene(QGraphicsScene* scene, bool isHorizontal = false, int activeValue = -1) {
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
    window.setWindowTitle("Визуализатор бинарного дерева");

    QVBoxLayout* mainLayout = new QVBoxLayout(&window);

    // Панель 1: Базовые операции
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

    // Панель 2: Обходы
    QHBoxLayout* bottomControls = new QHBoxLayout();
    QPushButton* btnPreOrder = new QPushButton("Прямой обход");
    QPushButton* btnInOrder = new QPushButton("Симметричный обход");
    QPushButton* btnPostOrder = new QPushButton("Обратный обход");
    QLabel* resultLabel = new QLabel("Результат: ");

    // Настраиваем шрифт для результата
    QFont font = resultLabel->font();
    font.setPointSize(12);
    font.setBold(true);
    resultLabel->setFont(font);

    bottomControls->addWidget(btnPreOrder);
    bottomControls->addWidget(btnInOrder);
    bottomControls->addWidget(btnPostOrder);
    bottomControls->addWidget(resultLabel);
    bottomControls->addStretch(); // Прижимает кнопки влево

    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);

    mainLayout->addLayout(topControls);
    mainLayout->addWidget(view);
    mainLayout->addLayout(bottomControls);

    bool isHorizontalView = false;

    // --- Обработчики базовых кнопок (остаются как раньше) ---
    QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
        bool ok;
        int val = inputField->text().toInt(&ok);
        if (ok) {
            globalRoot = insertNode(globalRoot, val);
            updateScene(scene, isHorizontalView);
            inputField->clear();
        }
    });

    QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
        bool ok;
        // Считываем число из текстового поля
        int val = inputField->text().toInt(&ok);
        if (ok) {
            // Вызываем функцию удаления из tree_logic
            globalRoot = deleteNode(globalRoot, val);

            // Перерисовываем сцену с новым состоянием дерева
            updateScene(scene, isHorizontalView);

            // Очищаем поле ввода
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
    // Общая лямбда для выполнения обхода и вывода текста
    auto runTraversal = [&](int type) {
        int n = countNodes(globalRoot);
        if (n == 0) {
            resultLabel->setText("Результат: Дерево пустое");
            return;
        }

        int* arr = new int[n];
        int index = 0;

        // Собираем последовательность
        if (type == 1) preOrderTraversal(globalRoot, arr, index);
        else if (type == 2) storeBSTNodes(globalRoot, arr, index);
        else if (type == 3) postOrderTraversal(globalRoot, arr, index);

        QString res = "Результат: ";

        // Запускаем визуализацию
        for (int i = 0; i < n; ++i) {
            // 1. Перерисовываем дерево, передавая текущее значение как активное (подсветится зеленым)
            updateScene(scene, isHorizontalView, arr[i]);

            // 2. Обновляем текстовую строку
            res += QString::number(arr[i]) + " ";
            resultLabel->setText(res);

            // 3. Ждем 600 миллисекунд (чтобы анимация была плавной)
            delay(600);
        }

        // Возвращаем дерево в обычное состояние (снимаем все подсветки)
        updateScene(scene, isHorizontalView, -1);

        delete[] arr;
    };

    QObject::connect(btnPreOrder, &QPushButton::clicked, [&]() { runTraversal(1); });
    QObject::connect(btnInOrder, &QPushButton::clicked, [&]() { runTraversal(2); });
    QObject::connect(btnPostOrder, &QPushButton::clicked, [&]() { runTraversal(3); });

    window.show();
    return a.exec();
}