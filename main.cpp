#include <iostream>
#include <vector>

using namespace std;

const int population = 20;   // 种群规模
const int n = 30;           // n的长度
const int iteration = 100;  // 代数限制
const double muteProb = 0.01;  // 变异概率
const double crossProb = 0.99;  // 交叉概率

vector<vector<int>> parents(n, vector<int>(population));  // 父代
vector<int> maxFitness(iteration);  // 种群中每一代的最大适应度
vector<int> avgFitness(iteration);  // 种群中每一代的平均适应度
vector<int> fitness(population);  // 种群中每个个体的适应度
vector<double> probability(population);  // 根据个体适应度

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

void update_probability() {  //轮盘赌更新每个个体的概率
    int sum = 0;
    for (auto fit : fitness) {
        sum += fit;
    }
    for (int i = 0; i < population; i ++) {
        probability[i] = (double)fitness[i] * 1.0 / sum;
    }
}

void init() {  //初始化种群
    for (int i = 0; i < population; i ++ ) {
        for (int j = 0; j < n; j ++ ) {
            parents[i][j] = rand() % 2;   //随机生成一个整数并对其取模
        }
    }
}

int main() {
    init();  // 初始化种群

    int generation = 0;
    while (generation <= iteration) {
        generation ++;  // 迭代次数 + 1

        update_fitness();  // 计算父代的适应度
        update_probability();  // 根据父代的适应度更新轮盘赌概率

        vector<vector<int>> children(n, vector<int>(population));  // 定义子代
        for (int i = 0; i < population; i ++ ) {
            cout << probability[i] << ' ';
        }
        cout << endl;

    }
    return 0;
}
