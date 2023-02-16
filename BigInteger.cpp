//
// Created by i3alumba on 16.02.23.
//

#include "SmartMath.hpp"
#include <algorithm>

SmartMath::BigInteger::BigInteger() {
    value = "";
}

SmartMath::BigInteger::BigInteger(int number) {
    std::string buffer = std::to_string(number);
    if (buffer == "0") {
        value = "";
    } else {
        std::reverse(buffer.begin(), buffer.end());
        value = buffer;
    }
}

SmartMath::BigInteger::BigInteger(long long number) {
    std::string buffer = std::to_string(number);
    if (buffer == "0") {
        value = "";
    } else {
        std::reverse(buffer.begin(), buffer.end());
        value = buffer;
    }
}

bool SmartMath::BigInteger::operator==(const SmartMath::BigInteger &other) const {
    return value == other.value;
}

bool SmartMath::BigInteger::operator!=(const SmartMath::BigInteger &other) const {
    return value != other.value;
}

SmartMath::BigInteger &SmartMath::BigInteger::operator+=(const SmartMath::BigInteger &other) {
    return *this = *this + other;
}

SmartMath::BigInteger &SmartMath::BigInteger::operator-=(const SmartMath::BigInteger &other) {
    return *this = *this - other;
}

SmartMath::BigInteger &SmartMath::BigInteger::operator*=(const SmartMath::BigInteger &other) {
    return *this = *this * other;
}

SmartMath::BigInteger &SmartMath::BigInteger::operator/=(const SmartMath::BigInteger &other) {
    return *this = *this / other;
}

inline static int get(const std::string &str, index_t index) {
    if (index >= (index_t) str.size()) {
        return 0;
    } else {
        return str[index] - '0';
    }
}

SmartMath::BigInteger SmartMath::BigInteger::operator+(const SmartMath::BigInteger &other) const {
    SmartMath::BigInteger res;
    bool overflow = false;
    for (index_t index = 0; index < (index_t) value.size() || index < (index_t) other.value.size(); ++index) {
        int n1 = get(value, index), n2 = get(other.value, index);
        int res_n = n1 + n2 + (overflow ? 1 : 0);
        if (res_n >= 10) {
            res_n -= 10;
            overflow = true;
        } else {
            overflow = false;
        }
        res.value += (char) (res_n + '0');
    }
    if (overflow) {
        res.value += '1';
    }
    return res;
}

SmartMath::BigInteger SmartMath::BigInteger::operator-(const SmartMath::BigInteger &other) const {
    return SmartMath::BigInteger();
}

SmartMath::BigInteger SmartMath::BigInteger::operator*(const SmartMath::BigInteger &other) const {
    return SmartMath::BigInteger();
}

SmartMath::BigInteger SmartMath::BigInteger::operator/(const SmartMath::BigInteger &other) const {
    return SmartMath::BigInteger();
}

