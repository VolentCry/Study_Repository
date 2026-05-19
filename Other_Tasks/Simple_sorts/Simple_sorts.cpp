#include <iostream>
#include <algorithm>

using namespace std;


template <typename T>
void printArray(T arr[], int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << "\n";
}


// 1. БЫСТРАЯ СОРТИРОВКА
int partition(int arr[], int low, int high) {
	int pivot = arr[high];
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++) {
		if (arr[j] <= pivot) {
			i++;
			int temp = 0;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	int temp2 = 0;
	temp2 = arr[i + 1];
	arr[i + 1] = arr[high];
	arr[high] = temp2;

	return (i + 1);
}

void quickSort(int arr[], int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}


void merge(int arr[], int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	// Динамическое выделение памяти для временных массивов
	int* L = new int[n1];
	int* R = new int[n2];

	for (int i = 0; i < n1; i++) L[i] = arr[left + i];
	for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		} else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) { 
		arr[k] = L[i]; 
		i++; 
		k++; 
	}

	while (j < n2) { 
		arr[k] = R[j]; 
		j++; 
		k++; 
	}

	delete[] L;
	delete[] R;
}

// 2. СОРТИРОВКА СЛИЯНИЕМ
void mergeSort(int arr[], int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}


// 3. БЛОЧНАЯ СОРТИРОВКА (Bucket Sort)
void bucketSort(float arr[], int n) {
	if (n <= 0) return;

	// Массив для хранения количества элементов в каждой корзине
	int* counts = new int[n]();

	// Двумерный динамический массив для корзин
	float** buckets = new float* [n];

	for (int i = 0; i < n; i++) {
		buckets[i] = new float[n];
	}

	// Распределяем элементы по корзинам
	for (int i = 0; i < n; i++) {
		int bucketIndex = n * arr[i];
		if (bucketIndex >= n) bucketIndex = n - 1;
		buckets[bucketIndex][counts[bucketIndex]++] = arr[i];
	}

	// сортировка вставкам
	for (int i = 0; i < n; i++) {
		int bucketSize = counts[i];
		for (int j = 1; j < bucketSize; j++) {
			float key = buckets[i][j];
			int k = j - 1;

			while (k >= 0 && buckets[i][k] > key) {
				buckets[i][k + 1] = buckets[i][k];
				k--;
			}
			buckets[i][k + 1] = key;
		}
	}

	int index = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < counts[i]; j++) {
			arr[index++] = buckets[i][j];
		}
	}

	// Освобождение памяти
	for (int i = 0; i < n; i++) {
		delete[] buckets[i];
	}
	delete[] buckets;
	delete[] counts;
}


// 4. СОРТИРОВКА ПОДСЧЁТОМ
void countingSort(int arr[], int n) {
	if (n <= 0) return;

	int max_val = *max_element(arr, arr + n);

	// Динамическое выделение памяти, инициализация нулями
	int* count = new int[max_val + 1]();
	int* output = new int[n];

	for (int i = 0; i < n; i++) count[arr[i]]++;
	for (int i = 1; i <= max_val; i++) count[i] += count[i - 1];

	for (int i = n - 1; i >= 0; i--) {
		output[count[arr[i]] - 1] = arr[i];
		count[arr[i]]--;
	}

	for (int i = 0; i < n; i++) arr[i] = output[i];

	// Освобождение памяти
	delete[] count;
	delete[] output;
}



int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8");

	// Исходные массивы для тестов
	int intArr[] = { 42, 12, 89, 27, 4, 15, 63, 8 };
	int nInt = sizeof(intArr) / sizeof(intArr[0]);

	float floatArr[] = { 0.897f, 0.565f, 0.656f, 0.1234f, 0.665f, 0.3434f };
	int nFloat = sizeof(floatArr) / sizeof(floatArr[0]);

	cout << "--- Тестирование алгоритмов сортировки ---\n\n";

	// Создаем копии исходных массивов для каждого теста
	int arrTest[8];
	float arrTestFloat[6];


	// --- 1. Быстрая сортировка (Quick Sort) ---
	
	//copy(intArr, intArr + nInt, arrTest);
	//cout << "Исходный массив: "; 
	//printArray(arrTest, nInt);
	//quickSort(arrTest, 0, nInt - 1);
	//cout << "Быстрая сортировка: "; 
	//printArray(arrTest, nInt);
	//cout << "\n";
	


	// --- 2. Сортировка слиянием (Merge Sort) ---

	
	//copy(intArr, intArr + nInt, arrTest);
	//cout << "Исходный массив: "; 
	//printArray(arrTest, nInt);
	//mergeSort(arrTest, 0, nInt - 1);
	//cout << "Сортировка слиянием: "; 
	//printArray(arrTest, nInt);
	//cout << "\n";
	

	// --- 3. Блочная сортировка (Bucket Sort) ---

	
	//copy(floatArr, floatArr + nFloat, arrTestFloat);
	//cout << "Исходный массив (float): "; 
	//printArray(arrTestFloat, nFloat);
	//bucketSort(arrTestFloat, nFloat);
	//cout << "Блочная сортировка: "; 
	//printArray(arrTestFloat, nFloat);
	//cout << "\n";
	

	// --- 4. Сортировка подсчётом (Counting Sort) ---

	
	//copy(intArr, intArr + nInt, arrTest);
	//cout << "Исходный массив: "; 
	//printArray(arrTest, nInt);
	//countingSort(arrTest, nInt);
	//cout << "Сортировка подсчётом: "; 
	//printArray(arrTest, nInt);
	//cout << "\n";
	

	return 0;
}