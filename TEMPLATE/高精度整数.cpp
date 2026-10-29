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

class BigInteger {
    static constexpr int kDigits = 8;
    static constexpr int kBase = 100000000;
    vector<int> digits{0};
    bool negative = false;

    void trim() {
        while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
        if (is_zero()) negative = false;
    }
    static int compare_absolute(const BigInteger& a, const BigInteger& b) {
        if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
        for (int i = int(a.size()) - 1; i >= 0; --i) {
            if (a.digits[i] != b.digits[i]) return a.digits[i] < b.digits[i] ? -1 : 1;
        }
        return 0;
    }

public:
    BigInteger() = default;
    explicit BigInteger(const string& text) {
        assert(!text.empty());
        int begin = text[0] == '-' || text[0] == '+';
        negative = text[0] == '-';
        assert(begin < int(text.size()));
        for (int i = begin; i < int(text.size()); ++i) assert(text[i] >= '0' && text[i] <= '9');
        digits.clear();
        for (int end = text.size(); end > begin; end -= kDigits) {
            int start = max(begin, end - kDigits);
            digits.push_back(stoi(text.substr(start, end - start)));
        }
        trim();
    }
    BigInteger(i64 value) : BigInteger(to_string(value)) {}
    explicit BigInteger(const vector<int>& blocks, bool positive = true)
        : digits(blocks), negative(!positive) {
        if (digits.empty()) digits.push_back(0);
        for (int block : digits) assert(block >= 0 && block < kBase);
        trim();
    }
    size_t size() const { return digits.size(); }
    int operator[](int index) const { return digits.at(index); }
    bool is_zero() const { return digits.size() == 1 && digits[0] == 0; }
    BigInteger abs_value() const { return BigInteger(digits); }
    operator string() const {
        string result = negative ? "-" : "";
        result += to_string(digits.back());
        for (int i = int(size()) - 2; i >= 0; --i) {
            string block = to_string(digits[i]);
            result += string(kDigits - block.size(), '0') + block;
        }
        return result;
    }
    static BigInteger e(size_t exponent) {
        vector<int> blocks(exponent / kDigits + 1);
        int top = 1;
        for (size_t i = 0; i < exponent % kDigits; ++i) top *= 10;
        blocks.back() = top;
        return BigInteger(blocks);
    }
    const BigInteger& operator+() const { return *this; }
    BigInteger operator-() const {
        BigInteger result = *this;
        if (!result.is_zero()) result.negative = !result.negative;
        return result;
    }
    bool operator==(const BigInteger& other) const {
        return negative == other.negative && digits == other.digits;
    }
    bool operator!=(const BigInteger& other) const { return !(*this == other); }
    bool operator<(const BigInteger& other) const {
        if (negative != other.negative) return negative;
        int comparison = compare_absolute(*this, other);
        return negative ? comparison > 0 : comparison < 0;
    }
    bool operator<=(const BigInteger& other) const { return !(other < *this); }
    bool operator>(const BigInteger& other) const { return other < *this; }
    bool operator>=(const BigInteger& other) const { return !(*this < other); }

    BigInteger operator+(const BigInteger& other) const {
        if (negative == other.negative) {
            vector<int> result;
            int carry = 0;
            for (size_t i = 0; i < max(size(), other.size()) || carry; ++i) {
                if (i < size()) carry += digits[i];
                if (i < other.size()) carry += other.digits[i];
                result.push_back(carry % kBase);
                carry /= kBase;
            }
            return BigInteger(result, !negative);
        }
        const BigInteger *larger = this, *smaller = &other;
        if (compare_absolute(*larger, *smaller) < 0) swap(larger, smaller);
        vector<int> result(larger->size());
        int borrow = 0;
        for (size_t i = 0; i < larger->size(); ++i) {
            int value = larger->digits[i] - borrow;
            if (i < smaller->size()) value -= smaller->digits[i];
            borrow = value < 0;
            result[i] = value + borrow * kBase;
        }
        return BigInteger(result, !larger->negative);
    }
    BigInteger operator-(const BigInteger& other) const { return *this + (-other); }
    BigInteger operator*(const BigInteger& other) const {
        vector<int> result(size() + other.size());
        for (size_t i = 0; i < size(); ++i) {
            i64 carry = 0;
            for (size_t j = 0; j < other.size() || carry; ++j) {
                i64 value = result[i + j] + carry;
                if (j < other.size()) value += i64(digits[i]) * other.digits[j];
                result[i + j] = value % kBase;
                carry = value / kBase;
            }
        }
        return BigInteger(result, negative == other.negative);
    }
    pair<BigInteger, BigInteger> operator/(const BigInteger& other) const {
        assert(!other.is_zero());
        BigInteger divisor = other.abs_value(), remainder;
        string quotient;
        for (char digit : string(abs_value())) {
            remainder = remainder * BigInteger(10) + BigInteger(digit - '0');
            int count = 0;
            while (divisor <= remainder) {
                remainder = remainder - divisor;
                ++count;
            }
            quotient += char('0' + count);
        }
        BigInteger result(quotient);
        if (!result.is_zero()) result.negative = negative != other.negative;
        if (!remainder.is_zero()) remainder.negative = negative;
        return {result, remainder};
    }
    friend istream& operator>>(istream& input, BigInteger& value) {
        string text;
        if (input >> text) value = BigInteger(text);
        return input;
    }
    friend ostream& operator<<(ostream& output, const BigInteger& value) {
        return output << string(value);
    }
};

// ==================== 使用示例 ====================
int main() {
    BigInteger a("12345678901234567890"), b(10);
    cout << a + b << '\n'; // 12345678901234567900
    cout << a * b << '\n'; // 123456789012345678900
    auto [quotient, remainder] = BigInteger(-123) / b;
    cout << quotient << ' ' << remainder << '\n'; // -12 -3
}
