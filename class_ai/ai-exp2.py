from typing import List, Set, Dict, Tuple
import time

class Clause:
    """
    表示逻辑子句的类
    一个子句是由文字（literals）通过析取（∨，或）连接而成的
    例如：P ∨ Q ∨ ~R 就是一个子句
    """
    
    def __init__(self, literals, explanation=""):
        """
        初始化一个子句对象
        
        Args:
            literals: 文字集合，可以包含原子命题或其否定
                     例如：{'P', '~Q', 'R'} 表示 P ∨ ~Q ∨ R
            explanation: 解释说明文本，用于追踪子句的来源或推导过程
        """
        # 使用 set 存储文字以确保唯一性，并方便进行集合运算
        self.literals = set(literals)
        # 子句的唯一标识符，用于追踪和引用
        self.id = None
        # 存储这个子句的解释或推导来源
        self.explanation = explanation
    
    def __str__(self):
        """
        将子句转换为字符串表示
        
        Returns:
            str: 子句的字符串形式，文字之间用 ∨ 连接
                 如果有解释文本，会附加在后面的括号中
        例如：
            'P ∨ ~Q ∨ R  (从前提1和前提2归结得到)'
        """
        # 对文字进行排序以保持一致的显示顺序
        base = ' ∨ '.join(sorted(self.literals))
        if self.explanation:
            return f"{base}  ({self.explanation})"
        return base
    
    def __eq__(self, other):
        """
        比较两个子句是否相等
        
        Args:
            other: 另一个子句对象
        
        Returns:
            bool: 如果两个子句包含相同的文字集合则返回True
        """
        return self.literals == other.literals
    
    def __len__(self):
        """
        返回子句中文字的数量
        
        Returns:
            int: 子句中文字的个数
        """
        return len(self.literals)
    
    def __hash__(self):
        """
        计算子句的哈希值
        使用 frozenset 是因为 set 本身是不可哈希的
        这允许子句对象可以用作字典的键或存储在集合中
        
        Returns:
            int: 子句的哈希值
        """
        return hash(frozenset(self.literals))


class ResolutionStep:
    def __init__(self, clause1, clause2, resolvent, literal_resolved, step_num):
        self.clause1 = clause1
        self.clause2 = clause2
        self.resolvent = resolvent
        self.literal_resolved = literal_resolved
        self.step_num = step_num
    
    def __str__(self):
        return f"""
步骤 {self.step_num}:
输入子句:
    C1: {str(self.clause1)}
    C2: {str(self.clause2)}
消解文字: {self.literal_resolved}
结果: {str(self.resolvent)}
"""

class ResolutionStats:
    def __init__(self):
        self.total_steps = 0
        self.total_attempts = 0
        self.successful_resolutions = 0
        self.start_time = None
        self.end_time = None
        self.generated_clauses = set()
        self.resolution_steps = []
        
    def start(self):
        self.start_time = time.time()
        
    def end(self):
        self.end_time = time.time()
        
    def add_step(self, step: ResolutionStep):
        self.total_steps += 1
        self.resolution_steps.append(step)
        self.generated_clauses.add(step.resolvent)
        
    def print_summary(self):
        print("\n=== Resolution 统计信息 ===")
        print(f"总步骤数: {self.total_steps}")
        print(f"总消解尝试次数: {self.total_attempts}")
        print(f"成功的消解次数: {self.successful_resolutions}")
        print(f"生成的唯一子句数: {len(self.generated_clauses)}")
        if self.start_time and self.end_time:
            print(f"耗时: {(self.end_time - self.start_time):.4f} 秒")
        print("========================\n")

def resolve(clause1: Clause, clause2: Clause, stats: ResolutionStats) -> List[Tuple[Clause, str]]:
    resolvents = []
    stats.total_attempts += 1
    
    # 遍历第一个子句中的所有文字
    for lit1 in clause1.literals:
        # 生成补文字
        complement = '~' + lit1 if not lit1.startswith('~') else lit1[1:]
        # 检查补文字是否在第二个子句中
        if complement in clause2.literals:
            # 执行归结：合并两个子句并移除互补文字
            new_literals = clause1.literals.union(clause2.literals) - {lit1, complement}
            stats.successful_resolutions += 1
            if new_literals:
                # 如果归结结果不为空，创建新的子句
                resolvents.append((Clause(new_literals), lit1))
            else:
                # 如果归结结果为空，表示得到了空子句，证明完成
                resolvents.append((Clause({'□'}, "空子句 - 证明完成"), lit1))
                
    return resolvents

def has_complementary_literals(clause1: Clause, clause2: Clause) -> bool:
    # 检查两个子句是否包含互补的文字
    for lit in clause1.literals:
        complement = '~' + lit if not lit.startswith('~') else lit[1:]
        if complement in clause2.literals:
            return True
    return False

def two_pointer_resolution(clauses: List[Clause], goal: Clause) -> Tuple[bool, ResolutionStats]:
    stats = ResolutionStats()
    stats.start()
    
    # 否定目标子句
    negated_goal = Clause(
        {'~' + lit if not lit.startswith('~') else lit[1:] for lit in goal.literals},
        "目标的否定"
    )
    all_clauses = clauses + [negated_goal]
    
    # 为每个子句分配唯一ID
    for i, clause in enumerate(all_clauses):
        clause.id = i + 1
    
    used_pairs = set()
    # 按子句长度排序，优化性能
    all_clauses.sort(key=len)
    
    print("初始子句集:")
    for clause in all_clauses:
        print(f"C{clause.id}: {str(clause)}")
    print("\n消解过程:")
    
    # 双指针遍历所有可能的子句对
    i = 0
    while i < len(all_clauses):
        j = i + 1
        while j < len(all_clauses):
            if (i, j) not in used_pairs:
                used_pairs.add((i, j))
                
                clause1, clause2 = all_clauses[i], all_clauses[j]
                # 检查是否有互补文字
                if has_complementary_literals(clause1, clause2):
                    resolvents = resolve(clause1, clause2, stats)
                    
                    for resolvent, resolved_literal in resolvents:
                        # 检查新子句是否已存在，并控制子句长度
                        if resolvent not in all_clauses and len(resolvent.literals) <= max(len(clause1.literals), len(clause2.literals)):
                            resolvent.id = len(all_clauses) + 1
                            step = ResolutionStep(
                                clause1, 
                                clause2, 
                                resolvent,
                                resolved_literal,
                                stats.total_steps + 1
                            )
                            stats.add_step(step)
                            print(step)
                            all_clauses.append(resolvent)
                            
                            # 检查是否得到空子句
                            if '□' in resolvent.literals:
                                stats.end()
                                return True, stats
            j += 1
        i += 1
    
    stats.end()
    return False, stats


# 测试用例
initial_clauses = [
    Clause({'~L', '~Howl'}, "浅睡眠者不能有会嚎叫的东西"),
    Clause({'~H', 'Howl'}, "所有的狗都会嚎叫"),
    Clause({'C', 'H'}, "John要么有猫要么有狗"),
    Clause({'~C', '~M'}, "有猫的人不能有老鼠"),
    Clause({'L'}, "John是浅睡眠者")
]

goal = Clause({'~M'}, "要证明：John不会有老鼠")

success, stats = two_pointer_resolution(initial_clauses, goal)

stats.print_summary()

print(f"\n最终结果: 证明{'成功' if success else '失败'}")

# 添加符号说明
print("\n符号说明:")
print("L: 浅睡眠者")
print("H: 有狗")
print("C: 有猫")
print("M: 有老鼠")
print("Howl: 会嚎叫")
print("~: 表示否定")
print("∨: 表示或")
print("□: 空子句（表示矛盾，即证明成功）")