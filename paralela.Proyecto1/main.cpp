#include <iostream>
#include <fstream>
#include <queue>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;

const int LINE_LIMIT = 100;

queue<string> linesQueue;

mutex queueMutex;

// Productor: Lee líneas del archivo y las agrega a la cola
void producerThread(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        {
            lock_guard<mutex> lock(queueMutex);
            linesQueue.push(line);
        }
        // Si se alcanza el límite de líneas, dormir el hilo para dar tiempo a los consumidores
        if (linesQueue.size() >= LINE_LIMIT) {
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }

    file.close();
}

// Consumidor: Toma líneas de la cola, procesa y almacena palabras en la tabla de hash
void consumerThread(unordered_map<string, int>& wordCount) {
    string line;
    while (true) {
        {
            lock_guard<mutex> lock(queueMutex);
            if (linesQueue.empty()) {
                if (!wordCount.empty()) {
                    // Si la cola está vacía pero aún hay palabras sin procesar, seguir procesando
                    continue;
                } else {
                    // Si la cola está vacía y no hay palabras pendientes, salir
                    break;
                }
            }
            line = linesQueue.front();
            linesQueue.pop();
        }

        // Procesar la línea y actualizar la tabla de hash
        // Aquí debes implementar la lógica para dividir la línea en palabras y actualizar la tabla de hash
    }
}

// Función auxiliar para combinar dos tablas de hash
unordered_map<string, int> mergeWordCounts(const unordered_map<string, int>& count1, const unordered_map<string, int>& count2) {
    unordered_map<string, int> merged = count1;
    for (const auto& pair : count2) {
        merged[pair.first] += pair.second;
    }
    return merged;
}

// Función para ordenar la tabla de hash por valor
vector<pair<string, int>> sortWordCount(const unordered_map<string, int>& wordCount) {
    vector<pair<string, int>> sorted(wordCount.begin(), wordCount.end());
    sort(sorted.begin(), sorted.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });
    return sorted;
}

int main() {
    string filename = "archivo.txt"; // Cambia por el nombre de tu archivo
    vector<thread> consumerThreads;
    unordered_map<string, int> wordCount;

    // Iniciar el hilo productor
    thread producer(producerThread, ref(filename));

    // Iniciar hilos consumidores
    for (int i = 0; i < thread::hardware_concurrency(); ++i) {
        consumerThreads.emplace_back(consumerThread, ref(wordCount));
    }

    // Esperar a que todos los hilos terminen
    producer.join();
    for (auto& thread : consumerThreads) {
        thread.join();
    }

    // Combinar las tablas de hash
    unordered_map<string, int> combinedWordCount = wordCount;
    for (auto& thread : consumerThreads) {
        combinedWordCount = mergeWordCounts(combinedWordCount, wordCount);
    }

    // Ordenar y mostrar el conteo de palabras
    vector<pair<string, int>> sortedWordCount = sortWordCount(combinedWordCount);
    for (const auto& pair : sortedWordCount) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}