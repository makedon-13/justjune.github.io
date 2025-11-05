#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int>> graph;  // Список смежности графа
vector<int> parent;         // Родительские вершины в DFS-дереве
vector<bool> visited;       // Посещенные вершины
bool finished = false;      // Флаг для досрочного завершения

// Функция для восстановления и вывода пути между start и end
void find_path(int start, int end, const vector<int>& parent) {
    stack<int> path;
    // Восстанавливаем путь от start до end через родительские связи
    for (int v = end; v != start; v = parent[v]) {
        path.push(v); // Прибавляем вершины к пути
    }
    path.push(start); // Под конец Прибавим начальную вершину 
    
    // Выводим путь
    while (!path.empty()) {
        cout << path.top();
        path.pop();
        if (!path.empty()) cout << " -> ";
    }
}

// Обработка ребра (x, y) для обнаружения цикла
void process_edge(int x, int y) {
    if (parent[y] != x) { // Если y уже посещена и не является родителем x
        cout << "Cycle: ";
        find_path(y, x, parent);
        cout << " -> " << y << endl; // Замыкаем цикл
        finished = true; // Устанавливаем флаг для остановки обхода
    }
}

// DFS обход графа
void dfs(int v, int prev) {
    visited[v] = true;
    for (int u : graph[v]) {
        if (!visited[u]) {
            parent[u] = v; // Если вершина посещалась и явл-ся родителем запускаем DFS рекурсивно на u
            dfs(u, v);
            if (finished) return;
        } else if (u != prev) { // Если сосед посещен и не явл-ся родителем запускаем проверку ребра
            process_edge(v, u);
            if (finished) return;
        }
    }
}

int main() {
    // Пример построения графа
    int n = 5; // Количество вершин
    graph.resize(n);
    parent.resize(n, -1);
    visited.resize(n, false);

    // Добавление рёбер (неориентированный граф)
    graph[0].push_back(1);
    graph[1].push_back(0);
    graph[1].push_back(2);
    graph[2].push_back(1);
    graph[2].push_back(3);
    graph[3].push_back(2);
    graph[3].push_back(4);
    graph[4].push_back(3);
    graph[4].push_back(1); // Цикл: 1-2-3-4-1

    // Запуск DFS с первой вершины
    dfs(0, -1);

    if (!finished) {
        cout << "No cycles found" << endl;
    }

    return 0;
}
