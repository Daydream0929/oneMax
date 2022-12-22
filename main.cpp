#include <iostream>
#include <vector>
#include <numeric>
#include <time.h>
#include <stdlib.h>

using namespace std;

const int population = 20;   // 种群规模
const int n = 30;           // n的长度
const int iteration = 100;  // 代数限制
const double muteProb = 0.01;  // 变异概率
const double crossProb = 0.50;  // 交叉概率

vector<vector<int>> parents(population, vector<int>(n));  // 父代
vector<vector<int>> children(population, vector<int>(n));  // 子代
vector<int> maxFitness(iteration);  // 种群中每一代的最大适应度
vector<int> avgFitness(iteration);  // 种群中每一代的平均适应度
vector<int> fitness(population);  // 种群中每个个体的适应度

int cal_fitness(int i) {    //计算第i个种群的适应度，在这里返回1的个数即可
    int res = 0;
    for (int j = 0; j < n; j ++ ) {
        if (parents[i][j] == 1) {
            res ++;
        }
    }
    return res;
}

void update_fitness() {  // 更新种群中所有个体的适应度
    for (int i = 0; i < population; i ++ ) {
        fitness[i] = cal_fitness(i);
    }
}

void init() {  //初始化种群
    for (int i = 0; i < population; i ++ ) {
        for (int j = 0; j < n; j ++ ) {
            parents[i][j] = rand() % 2;   //随机生成一个整数并对其取模
        }
    }
}

pair<int, int> select() {  // 选择
    pair<int, int> par;
    int a, b;
    int sum = accumulate(fitness.begin(), fitness.end(), 0);
    double t1 = 1.0 * sum * (rand() / (double)RAND_MAX);
    double t2 = 1.0 * sum * (rand() / (double)RAND_MAX);
    int t = 0;
    for (int i = 0; i < fitness.size(); i ++ ) {
        t += fitness[i];
        if (t1 <= t) {
            a = i;
            break;
        }
    }
    t = 0;
    for (int i = 0; i < fitness.size(); i ++ ) {
        t += fitness[i];
        if (t2 <= t) {
            b = i;
            break;
        }
    }
    return {a, b};
}

pair<vector<int>, vector<int>> crossover(int p1, int p2) {  // 均匀交叉
    vector<int> c1 = parents[p1], c2 = parents[p2];
    for (int i = 0; i < n; i ++ ) {
        double t = rand() / (double) RAND_MAX;
        if (t < crossProb) {
            swap(c1[i], c2[i]);
        }
    }
    return {c1, c2};
}

void mutation(vector<int>&c) {  // 变异
    for (int i = 0; i < n; i ++ ) {
        double t = rand() / (double) RAND_MAX;
        if (t < muteProb) {
            c[i] ^= 1;
        }
    }
}

void update_parents() { // 更新父代
    parents = children;
    update_fitness();
}

int main() {
    srand((unsigned)time(NULL));  // 设置随机数种子
    init();  // 初始化种群
    int generation = 0;
    while (generation <= iteration) {
        generation ++;  // 迭代次数 + 1

        update_fitness();  // 计算父代的适应度

        for (int i = 0; i < population / 2; i ++ ) {
            auto p = select();  // select

            auto c = crossover(p.first, p.second);  // crossover

            mutation(c.first);  // mutation
            mutation(c.second);

            children[i * 2] = c.first;
            children[i * 2 + 1] = c.second;

            update_parents();  //  update
        }

        for (int i = 0; i < population; i ++ ) {
            cout << fitness[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
