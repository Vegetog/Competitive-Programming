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

bool read_i128(istream& input, i128& value) {
    string token;
    if (!(input >> token)) return false;
    int begin = token[0] == '-' || token[0] == '+';
    bool negative = token[0] == '-';
    u128 magnitude = 0;
    assert(begin < int(token.size()));
    for (int i = begin; i < int(token.size()); ++i) {
        assert(token[i] >= '0' && token[i] <= '9');
        magnitude = magnitude * 10 + (token[i] - '0');
    }
    // 避免直接对最小负数的绝对值做有符号转换或取反。
    value = negative && magnitude ? -i128(magnitude - 1) - 1 : i128(magnitude);
    return true;
}

string to_string_i128(i128 value) {
    bool negative = value < 0;
    u128 magnitude = negative ? u128(-(value + 1)) + 1 : u128(value);
    string result;
    do {
        result += char('0' + magnitude % 10);
        magnitude /= 10;
    } while (magnitude);
    if (negative) result += '-';
    reverse(result.begin(), result.end());
    return result;
}

i64 integer_sqrt(i64 value) {
    assert(value >= 0);
    i64 left = 0, right = min(value, 3037000499LL), answer = 0;
    while (left <= right) {
        i64 middle = left + (right - left) / 2;
        if (middle == 0 || middle <= value / middle) {
            answer = middle;
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return answer;
}

// ==================== 使用示例 ====================
int main() {
    istringstream input("-123456789012345678901234567890");
    i128 value;
    read_i128(input, value);
    cout << to_string_i128(value) << '\n';               // -123456789012345678901234567890
    cout << integer_sqrt(9223372036854775807LL) << '\n'; // 3037000499
}
