//
// Created by i3alumba on 16.02.23.
//

#include "SmartMath.hpp"

SmartMath::BigInteger::BigInteger() {
    value = "";
}

SmartMath::BigInteger::BigInteger(int number) {
    value = std::to_string(number);
}

SmartMath::BigInteger::BigInteger(long long int number) {
    value = std::to_string(number);
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

SmartMath::BigInteger SmartMath::BigInteger::operator+(const SmartMath::BigInteger &other) const {
    return SmartMath::BigInteger();
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

