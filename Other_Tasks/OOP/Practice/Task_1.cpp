#include <iostream>
#include <string>
using namespace std;

struct Dimensions 
{
    float x;
    float y;
    float z;
};

class PrintModel 
{
    friend bool canFitOnBed(const PrintModel& m1, const PrintModel& m2, float bedWidth, float bedDepth);

public:
    PrintModel() {
        // Конструктор по умолчанию
        ++totalModelsLoaded;
        model_name = "test_model";
        Dimensions prof{0.0, 0.0, 0.0};
        profile = prof;
        layer_cnt = 0;
        layerTime = new int[0];
    }

    PrintModel(string model_name, float x, float y, float z, unsigned l_cnt) {
        // Конструктор с параметрами
        ++totalModelsLoaded;
        this->model_name = model_name;
        Dimensions prof{x, y, z};
        profile = prof;
        layer_cnt = l_cnt;
        layerTime = new int[l_cnt];

        for (int i = 0; i < layer_cnt; i++) {
            layerTime[i] = 10; // секунд
        }
    }

    PrintModel(const PrintModel &model) {
        // Констурктор копирования
        ++totalModelsLoaded;
        model_name = model.model_name;
        profile = model.profile;
        layer_cnt = model.layer_cnt;
        layerTime = new int[layer_cnt];

        // Копируем данные из оригинала
        for (int i = 0; i < layer_cnt; i++) {
            layerTime[i] = 10;
        }
    }

    ~PrintModel() {
        // Деструктор
        --totalModelsLoaded;
        delete[] layerTime;
    }

    // =============== Геттеры ===============
    string GetModelName() {
        return model_name;
    }

    Dimensions GetDimensions() {
        return profile;
    }

    unsigned GetLayerCount() {
        return layer_cnt;
    }

    int* GetLayerTime() {
        return layerTime;
    }

    // =============== Сеттеры ===============
    void SetModelName(string model_name) {
        this->model_name = model_name;
    }

    void SetDimensions(Dimensions profile) {
        this->profile = profile;
    }

    void SetLayerCount(unsigned layer_cnt) {
        this->layer_cnt = layer_cnt;
    }

    void printInfo() const {
        cout << "Model name: " << model_name << "\tLayer count: " << layer_cnt << endl;
        cout << "Dimensions\tX: " << profile.x << " Y: " << profile.y << " Z: " << profile.z << endl;   
    }

    static void ShowModelsCnt() {
        cout << "Number of models in the program: " << totalModelsLoaded << endl;
    }

    void ChangeLayerTime(unsigned num_of_layer, unsigned new_time) {
        if (num_of_layer >= layer_cnt) { return; }

        layerTime[num_of_layer] = new_time;
    }

    int InfoAboutPrintTime() {
        int all_time = 0;
        for (int i = 0; i < layer_cnt; i++) {
            all_time += layerTime[i];
        }
        return all_time;
    }

private:
    static inline unsigned totalModelsLoaded{};
    string model_name;
    Dimensions profile;
    unsigned layer_cnt;
    int* layerTime;
};


bool canFitOnBed(const PrintModel& m1, const PrintModel& m2, float bedWidth, float bedDepth) {
    // Проверяем, влезут ли они, если поставить их рядом по оси X
    bool fitOnX = (m1.profile.x + m2.profile.x <= bedWidth) && 
                  (max(m1.profile.y, m2.profile.y) <= bedDepth);

    // Проверяем, влезут ли они, если поставить их друг за другом по оси Y
    bool fitOnY = (max(m1.profile.x, m2.profile.x) <= bedWidth) && 
                  (m1.profile.y + m2.profile.y <= bedDepth);

    return fitOnX || fitOnY;
}

int main() {
    const PrintModel myCalibrationCube("Cube", 110.0, 110.0, 110.0, 110); // Константный класс

    // Простые примеры и махинации с размерами
    PrintModel model_1("House", 10.123, 4.3434, 90.0, 300);
    cout << "Time of print for " << model_1.GetModelName() << ": " <<  model_1.InfoAboutPrintTime() << " seconds.\n";
    model_1.ChangeLayerTime(149, 180);
    cout << "New time of print for " << model_1.GetModelName() << ": " <<  model_1.InfoAboutPrintTime() << " seconds.\n";
    PrintModel model_2("House 2", 111.526, 87.6904, 930.0001, 5080);
    
    cout << endl;

    // Копирование классов и изменение размера
    PrintModel model_3(model_1);
    cout << "Model 3: " << model_3.InfoAboutPrintTime() << endl;
    model_3.ChangeLayerTime(19, 5);
    cout << "Model 3: " << model_3.InfoAboutPrintTime() << endl;
    cout << "Model 1: " << model_1.InfoAboutPrintTime() << " - dont change!" << endl;

    cout << endl;

    // Статическая функция
    PrintModel::ShowModelsCnt();

    cout << endl;

    // Константная функция
    myCalibrationCube.printInfo();

    cout << endl;

    cout << canFitOnBed(model_1, model_2, 500.0, 50.0) << endl;
    cout << canFitOnBed(model_1, model_2, 5000.0, 5500.0) << endl;


    return 0;
}