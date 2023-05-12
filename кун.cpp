#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <random>
#include <chrono>
#include <functional>

using namespace std;
vector<vector<int>> Graph;
vector<int> match;
int n1, n2;
vector<char> Vertices;

template<typename Iter, typename Random>
Iter select_randomly(Iter start, Iter end, Random& Graph) {
    uniform_int_distribution<> dis(0, distance(start, end) - 1);
    advance(start, dis(Graph));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static random_device rd;
    static mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

void Array(vector<vector<int>> arr) {
    int l = 1;
    for (auto i = arr.begin(); i != arr.end(); ++i) {
        cout << l++ << " - {";
        for (auto j = i->begin(); j != i->end(); ++j) {
            cout << *j + 1;
            if (j == (i->end() - 1)) continue;
            cout << ", ";
        }
        cout << "}" << endl;
    }
    cout << endl;
}

bool kuhn(int x) {
    if (Vertices[x])  return false;
    Vertices[x] = true;
    for (size_t i = 0; i < Graph[x].size(); ++i) {
        int to = Graph[x][i];
        if (match[to] == -1 || kuhn(match[to])) {
            match[to] = x;
            return true;
        }
    }
    return false;
}

vector<vector<int>> generate(int n1, int n2) {
    auto result = vector<vector<int>>(n1, vector<int>(n2));
    for (int i = 0; i < n1; ++i) {
        vector<int> row;
        random_device d;
        mt19937 rng(d());
        uniform_int_distribution<mt19937::result_type> dist(0, n2 - 1);
        int number = dist(rng);
        auto second = vector<int>(n2);
        iota(second.begin(), second.end(), 0);
        for (int z = 0; z < number; ++z) {
            int rand = *select_randomly(second.begin(), second.end());
            row.push_back(rand);
            second.erase(remove(second.begin(), second.end(), rand), second.end());
        }
        result[i] = row;
    }
    return result;
}

int main() 
{
    setlocale(LC_ALL, "Rus");
    cout << "Граф: " << endl;

    n1 = 5; 
    n2 = n1; 
    Graph = generate(n1, n2); 


    match.assign(n2, -1);
    for (int x = 0; x < n1; ++x) {
        Vertices.assign(n1, false);
        kuhn(x);
    }

    Array(Graph); 

    cout << "Максимальные паросочетания: " << endl;
    for (int i = 0; i < n2; ++i)
        if (match[i] != -1)
            cout << match[i] + 1 << " - " << i + 1 << endl;
    cout << endl;

    n1 = 100;
    n2 = n1;
    int step = 100;
    int iterationsNumber = 15;

    return 0;
}