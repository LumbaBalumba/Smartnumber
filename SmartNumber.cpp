//
// Created by i3alumba on 13.02.23.
//

#include "SmartNumber.hpp"
#include <set>

typedef ssize_t index_t;

SmartMath::SmartNumber::SmartNumber() {
    tag = INTEGER;
    value.i_value = 0;
}

SmartMath::SmartNumber::SmartNumber(int number) {
    tag = INTEGER;
    value.i_value = number;
}

SmartMath::SmartNumber::SmartNumber(long long int number) {
    tag = LLONG;
    value.l_value = number;
}

SmartMath::SmartNumber::SmartNumber(double number) {
    tag = DOUBLE;
    value.d_value = number;
}

SmartMath::SmartNumber::~SmartNumber() = default;

static index_t sign_separate(const std::string &str, const std::set<char> &separators) {
    long balance = 0;
    for (index_t index = (index_t) str.size() - 1; index >= 0; --index) {
        if (str[index] == ')') {
            balance++;
        } else if (str[index] == '(') {
            balance--;
        } else if (separators.contains(str[index]) && balance) {
            return index;
        }
    }
    return -1;
}

static std::string slice(const std::string &str, index_t left, index_t right) {
    std::string res;
    for (index_t index = left; index < right; ++index) {
        res += str[index];
    }
    return res;
}

double SmartMath::evaluate(const std::string &str) {
    std::set<char> signs;
    signs.insert('+');
    signs.insert('-');
    index_t sign_index = sign_separate(str, signs);
    if (sign_index >= 0) {
        if (str[sign_index] == '+') {
            return evaluate(slice(str, 0, sign_index)) + evaluate(slice(str, sign_index + 1, (index_t) str.size()));
        } else {
            return evaluate(slice(str, 0, sign_index)) - evaluate(slice(str, sign_index + 1, (index_t) str.size()));
        }
    }
    signs.clear();
    signs.insert('*');
    signs.insert('/');
    sign_index = sign_separate(str, signs);
    if (sign_index >= 0) {
        if (str[sign_index] == '*') {
            return evaluate(slice(str, 0, sign_index)) * evaluate(slice(str, sign_index + 1, (index_t) str.size()));
        } else {
            return evaluate(slice(str, 0, sign_index)) / evaluate(slice(str, sign_index + 1, (index_t) str.size()));
        }
    }
    if (str[0] == '(' && str[str.size() - 1] == ')') {
        return evaluate(slice(str, 1, (index_t) str.size() - 1));
    }
    return strtod(str.c_str(), nullptr);
}