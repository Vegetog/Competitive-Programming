/*
算法：__int128 读写与整数平方根
简介：以字符串读写有符号 128 位整数，并计算非负 64 位整数的向下取整平方根。
复杂度：读写 d 位数 O(d)；平方根 O(log x)；空间 O(d)。
约定：GCC/Clang 扩展；输入十进制整数须在有符号 __int128 范围内；平方根参数非负。
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;
using i128 = __int128;
using u128 = unsigned __int128;

// 作用：从流读取十进制 128 位整数；输入：in 和接收变量 value；输出：成功返回 true 并写入 value，读不到返回 false。
bool read128(istream& in, i128& value) {
    string token;
    if (!(in >> token)) return false;
    int begin = token[0] == '-' || token[0] == '+';
    bool neg = token[0] == '-';
    u128 mag = 0;
    assert(begin < int(token.size()));
    for (int i = begin; i < int(token.size()); ++i) {
        assert(token[i] >= '0' && token[i] <= '9');
        mag = mag * 10 + (token[i] - '0');
    }
    // 避免直接对最小负数的绝对值做有符号转换或取反。
    value = neg && mag ? -i128(mag - 1) - 1 : i128(mag);
    return true;
}

// 作用：转为十进制字符串；输入：有符号 128 位整数 value；输出：带符号的十进制表示。
string str128(i128 value) {
    bool neg = value < 0;
    u128 mag = neg ? u128(-(value + 1)) + 1 : u128(value);
    string res;
    do {
        res += char('0' + mag % 10);
        mag /= 10;
    } while (mag);
    if (neg) res += '-';
    reverse(res.begin(), res.end());
    return res;
}

// 作用：求整数平方根；输入：非负 value；输出：⌊√value⌋。
i64 isqrt(i64 value) {
    assert(value >= 0);
    i64 left = 0, right = min(value, 3037000499LL), ans = 0;
    while (left <= right) {
        i64 middle = left + (right - left) / 2;
        if (middle == 0 || middle <= value / middle) {
            ans = middle;
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return ans;
}

// ==================== 使用示例 ====================
// 作用：运行固定示例；输入：无外部输入；输出：下方标明的算法调用结果。
int main() {
    istringstream in("-123456789012345678901234567890");
    i128 value;
    read128(in, value);
    cout << str128(value) << '\n';                // -123456789012345678901234567890
    cout << isqrt(9223372036854775807LL) << '\n'; // 3037000499
}
