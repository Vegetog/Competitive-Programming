import numpy as np
import matplotlib.pyplot as plt
plt.rcParams['font.sans-serif'] = ['Microsoft YaHei', 'SimHei', 'Arial Unicode MS']

# 适应度函数
def fun(x):
    return np.sum(x)

# 选择函数（锦标赛选择）
def select_pop(population):
    n = len(population)
    idx1, idx2 = np.random.choice(n, 2, replace=False)
    if population[idx1]['y'] < population[idx2]['y']:
        return population[idx1]
    else:
        return population[idx2]

# 交叉函数（单点交叉）
def cross_pop(x1, x2):
    n = len(x1)
    s = np.random.randint(1, n)
    y1 = np.concatenate((x1[:s], x2[s:]))
    y2 = np.concatenate((x2[:s], x1[s:]))
    return y1, y2

# 变异函数（单点变异）
def mutate_pop(x, mu):
    if np.random.random() <= mu:
        s = np.random.randint(len(x))
        x[s] = 1 - x[s]
    return x

# 主遗传算法
def genetic_algorithm():
    n_var = 100  # x的长度
    n_pop = 30   # 种群规模
    max_it = 2000  # 最大迭代次数
    n_pc = 0.8   # 子代规模的比例
    n_c = round(n_pop * n_pc / 2) * 2  # 子代规模
    n_mu = 0.01  # 变异概率

    # 初始化种群
    population = [{'x': np.random.randint(0, 2, n_var), 'y': 0} for _ in range(n_pop)]
    for p in population:
        p['y'] = fun(p['x'])

    best_fitness = []

    for it in range(1, max_it + 1):
        # 生成子代
        offspring = []
        for _ in range(n_c // 2):
            p1 = select_pop(population)
            p2 = select_pop(population)
            c1, c2 = cross_pop(p1['x'], p2['x'])
            offspring.extend([{'x': c1, 'y': 0}, {'x': c2, 'y': 0}])

        # 变异和评估子代
        for child in offspring:
            child['x'] = mutate_pop(child['x'], n_mu)
            child['y'] = fun(child['x'])

        # 合并父代和子代，选择最优的n_pop个体
        population.extend(offspring)
        population.sort(key=lambda x: x['y'])
        population = population[:n_pop]

        best_fitness.append(population[0]['y'])
        
        if it % 100 == 0 or it == 1 or population[0]['y'] == 0:
            print(f"迭代次数：{it}, 最小值为： {population[0]['y']}")

        if population[0]['y'] == 0:
            print("找到全局最优解！")
            break

    return population, best_fitness

# 运行算法
final_population, fitness_history = genetic_algorithm()

# 绘制适应度变化曲线
plt.figure(figsize=(12, 6))
plt.plot(range(1, len(fitness_history) + 1), fitness_history, 'b-')
plt.title('最佳适应度值随代数的变化')
plt.xlabel('代数')
plt.ylabel('最佳适应度值')
plt.grid(True)
plt.show()
