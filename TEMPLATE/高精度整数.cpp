/*
算法：有符号高精度整数
简介：以 10^8 为进制存储整数，支持比较、加减乘及返回商和余数的长除法。
复杂度：设十进制位数为 d；比较/加减 O(d)，乘除 O(d²)，空间 O(d)。
约定：十进制字符串输入；除数非零，商向零截断，余数与被除数同号；operator[] 访问低位在前的 10^8 进制块。
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;

class BigInt {
    static constexpr int D = 8;
    static constexpr int B = 100000000;
    vector<int> d{0};
    bool neg = false;

    // 作用：规范高精度表示；输入：当前数位与符号；输出：无返回值，删去高位零，并将零的符号置为非负。
    void trim() {
        while (d.size() > 1 && d.back() == 0) d.pop_back();
        if (zero()) neg = false;
    }
    // 作用：比较绝对值；输入：高精度整数 a、b；输出：|a| 小于/等于/大于 |b| 时分别返回 -1/0/1。
    static int cmp_abs(const BigInt& a, const BigInt& b) {
        if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
        for (int i = int(a.size()) - 1; i >= 0; --i) {
            if (a.d[i] != b.d[i]) return a.d[i] < b.d[i] ? -1 : 1;
        }
        return 0;
    }

public:
    // 作用：构造零；输入：无；输出：值为 0 的高精度对象。
    BigInt() = default;
    // 作用：解析十进制整数；输入：带可选正负号的非空字符串 text；输出：规范化的高精度对象。
    explicit BigInt(const string& text) {
        assert(!text.empty());
        int begin = text[0] == '-' || text[0] == '+';
        neg = text[0] == '-';
        assert(begin < int(text.size()));
        for (int i = begin; i < int(text.size()); ++i) assert(text[i] >= '0' && text[i] <= '9');
        d.clear();
        for (int end = text.size(); end > begin; end -= D) {
            int start = max(begin, end - D);
            d.push_back(stoi(text.substr(start, end - start)));
        }
        trim();
    }
    // 作用：从机器整数构造；输入：有符号 64 位整数 value；输出：等值的高精度对象。
    BigInt(i64 value) : BigInt(to_string(value)) {}
    // 作用：从数位块构造；输入：低位在前且每块在 [0,B) 的 blocks、正号标志 positive；输出：规范化高精度对象。
    explicit BigInt(const vector<int>& blocks, bool positive = true) : d(blocks), neg(!positive) {
        if (d.empty()) d.push_back(0);
        for (int block : d) assert(block >= 0 && block < B);
        trim();
    }
    // 作用：读取数位块数；输入：当前高精度整数；输出：10^8 进制块的个数。
    size_t size() const { return d.size(); }
    // 作用：读取数位块；输入：从 0 开始的块下标 index；输出：该位置的 10^8 进制块，低位在前。
    int operator[](int index) const { return d.at(index); }
    // 作用：判断是否为零；输入：当前高精度整数；输出：为零时返回 true。
    bool zero() const { return d.size() == 1 && d[0] == 0; }
    // 作用：取绝对值；输入：当前高精度整数；输出：非负的绝对值副本。
    BigInt abs() const { return BigInt(d); }
    // 作用：转换十进制文本；输入：当前高精度整数；输出：带符号的十进制字符串。
    operator string() const {
        string res = neg ? "-" : "";
        res += to_string(d.back());
        for (int i = int(size()) - 2; i >= 0; --i) {
            string block = to_string(d[i]);
            res += string(D - block.size(), '0') + block;
        }
        return res;
    }
    // 作用：构造十进制幂；输入：非负指数 e；输出：高精度整数 10^e。
    static BigInt e(size_t e) {
        vector<int> blocks(e / D + 1);
        int top = 1;
        for (size_t i = 0; i < e % D; ++i) top *= 10;
        blocks.back() = top;
        return BigInt(blocks);
    }
    // 作用：取正值；输入：当前值；输出：当前对象的只读引用。
    const BigInt& operator+() const { return *this; }
    // 作用：取相反数；输入：当前值；输出：相反数副本。
    BigInt operator-() const {
        BigInt res = *this;
        if (!res.zero()) res.neg = !res.neg;
        return res;
    }
    // 作用：比较相等关系；输入：两个操作数；输出：按整数值比较的布尔结果。
    bool operator==(const BigInt& other) const { return neg == other.neg && d == other.d; }
    // 作用：比较不等关系；输入：两个操作数；输出：按整数值比较的布尔结果。
    bool operator!=(const BigInt& other) const { return !(*this == other); }
    // 作用：比较小于关系；输入：两个操作数；输出：按整数值比较的布尔结果。
    bool operator<(const BigInt& other) const {
        if (neg != other.neg) return neg;
        int cmp = cmp_abs(*this, other);
        return neg ? cmp > 0 : cmp < 0;
    }
    // 作用：比较小于等于关系；输入：两个操作数；输出：按整数值比较的布尔结果。
    bool operator<=(const BigInt& other) const { return !(other < *this); }
    // 作用：比较大于关系；输入：两个操作数；输出：按整数值比较的布尔结果。
    bool operator>(const BigInt& other) const { return other < *this; }
    // 作用：比较大于等于关系；输入：两个操作数；输出：按整数值比较的布尔结果。
    bool operator>=(const BigInt& other) const { return !(*this < other); }

    // 作用：高精度加法；输入：当前整数和 other；输出：精确的运算结果副本。
    BigInt operator+(const BigInt& other) const {
        if (neg == other.neg) {
            vector<int> res;
            int carry = 0;
            for (size_t i = 0; i < max(size(), other.size()) || carry; ++i) {
                if (i < size()) carry += d[i];
                if (i < other.size()) carry += other.d[i];
                res.push_back(carry % B);
                carry /= B;
            }
            return BigInt(res, !neg);
        }
        const BigInt *larger = this, *smaller = &other;
        if (cmp_abs(*larger, *smaller) < 0) swap(larger, smaller);
        vector<int> res(larger->size());
        int borrow = 0;
        for (size_t i = 0; i < larger->size(); ++i) {
            int value = larger->d[i] - borrow;
            if (i < smaller->size()) value -= smaller->d[i];
            borrow = value < 0;
            res[i] = value + borrow * B;
        }
        return BigInt(res, !larger->neg);
    }
    // 作用：高精度减法；输入：当前整数和 other；输出：精确的运算结果副本。
    BigInt operator-(const BigInt& other) const { return *this + (-other); }
    // 作用：高精度乘法；输入：当前整数和 other；输出：精确的运算结果副本。
    BigInt operator*(const BigInt& other) const {
        vector<int> res(size() + other.size());
        for (size_t i = 0; i < size(); ++i) {
            i64 carry = 0;
            for (size_t j = 0; j < other.size() || carry; ++j) {
                i64 value = res[i + j] + carry;
                if (j < other.size()) value += i64(d[i]) * other.d[j];
                res[i + j] = value % B;
                carry = value / B;
            }
        }
        return BigInt(res, neg == other.neg);
    }
    // 作用：长除法；输入：当前被除数和非零除数 other；输出：{向零截断的商, 与被除数同号的余数}。
    pair<BigInt, BigInt> operator/(const BigInt& other) const {
        assert(!other.zero());
        BigInt p = other.abs(), rem;
        string q;
        for (char digit : string(abs())) {
            rem = rem * BigInt(10) + BigInt(digit - '0');
            int count = 0;
            while (p <= rem) {
                rem = rem - p;
                ++count;
            }
            q += char('0' + count);
        }
        BigInt res(q);
        if (!res.zero()) res.neg = neg != other.neg;
        if (!rem.zero()) rem.neg = neg;
        return {res, rem};
    }
    // 作用：读取整数；输入：输入流和接收对象；输出：原输入流，并在成功读取时更新对象的值。
    friend istream& operator>>(istream& in, BigInt& value) {
        string text;
        if (in >> text) value = BigInt(text);
        return in;
    }
    // 作用：输出整数；输入：输出流和整数对象；输出：原输出流，并写入十进制代表值。
    friend ostream& operator<<(ostream& out, const BigInt& value) { return out << string(value); }
};

// ==================== 使用示例 ====================
// 作用：运行固定示例；输入：无外部输入；输出：下方标明的算法调用结果。
int main() {
    BigInt a("12345678901234567890"), b(10);
    cout << a + b << '\n'; // 12345678901234567900
    cout << a * b << '\n'; // 123456789012345678900
    auto [q, rem] = BigInt(-123) / b;
    cout << q << ' ' << rem << '\n'; // -12 -3
}
