//
// Created by i3alumba on 16.02.23.
//
#include "SmartMath.hpp"
#include <cmath>
#include <limits>

static const double eps = 0.00001;

SmartMath::SmartNumber::SmartNumber() {
    tag = INTEGER;
    value = 0;
}

SmartMath::SmartNumber::SmartNumber(int number) {
    tag = INTEGER;
    value = number;
}

SmartMath::SmartNumber::SmartNumber(long long int number) {
    tag = LONG_LONG;
    value = number;
}

SmartMath::SmartNumber::SmartNumber(double number) {
    tag = DOUBLE;
    value = number;
}

SmartMath::SmartNumber::SmartNumber(const std::string &number) {
    tag = DOUBLE;
    value = evaluate(number);
}


SmartMath::SmartNumber::SmartNumber(const SmartMath::BigInteger &number) {
    tag = BIG_INTEGER;
    value = number;
}

std::string SmartMath::SmartNumber::type() const {
    if (tag == INTEGER) {
        return "int";
    } else if (tag == LONG_LONG) {
        return "long long";
    } else if (tag == DOUBLE) {
        return "double";
    }
    return "undefined";
}

bool SmartMath::SmartNumber::operator==(const SmartMath::SmartNumber &other) const {
    if (tag != other.tag) {
        return false;
    }
    if (tag == INTEGER || tag == LONG_LONG) {
        return value == other.value;
    } else {
        return fabs(std::get<double>(value) - std::get<double>(other.value)) < eps;
    }
}

bool SmartMath::SmartNumber::operator!=(const SmartMath::SmartNumber &other) const {
    return !(*this == other);
}

SmartMath::SmartNumber SmartMath::SmartNumber::operator+(const SmartMath::SmartNumber &other) const {
    switch (tag) {
        case INTEGER: {
            switch (other.tag) {
                case INTEGER: {
                    long long res = std::get<int>(value) + std::get<int>(other.value);
                    if (res == (int) res) {
                        return {(int) res};
                    } else {
                        return {res};
                    }
                }
                case LONG_LONG: {
                    long long a = std::get<int>(value);
                    long long b = std::get<long long>(other.value);
                    if (a > std::numeric_limits<long long>::max() - b) {
                        return {std::numeric_limits<long long>::max()};
                    }
                    if (a < std::numeric_limits<long long>::min() - b) {
                        return {std::numeric_limits<long long>::min()};
                    }
                    return {a + b};
                }
                case DOUBLE: {
                    double a = std::get<int>(value);
                    double b = std::get<double>(other.value);
                    if (a > std::numeric_limits<double>::max() - b) {
                        return {std::numeric_limits<double>::max()};
                    }
                    if (a < -std::numeric_limits<double>::max() - b) {
                        return {-std::numeric_limits<double>::max()};
                    }
                    return {a + b};
                }
                case BIG_INTEGER: {
                    return BigInteger(std::get<int>(value)) + std::get<BigInteger>(value);
                }
            }
        }
        case LONG_LONG: {
            switch (other.tag) {
                case LONG_LONG: {
                    long long a = std::get<long long>(value);
                    long long b = std::get<long long>(other.value);
                    if (a > std::numeric_limits<long long>::max() - b) {
                        return {std::numeric_limits<long long>::max()};
                    }
                    if (a < std::numeric_limits<long long>::min() - b) {
                        return {std::numeric_limits<long long>::min()};
                    }
                    return {a + b};
                }
                case INTEGER: {
                    long long a = std::get<long long>(value);
                    long long b = std::get<int>(other.value);
                    if (a > std::numeric_limits<long long>::max() - b) {
                        return {std::numeric_limits<long long>::max()};
                    }
                    if (a < std::numeric_limits<long long>::min() - b) {
                        return {std::numeric_limits<long long>::min()};
                    }
                    return {a + b};
                }
                case DOUBLE: {
                    throw SmartMath::ConversionError();
                }
                case BIG_INTEGER: {
                    return BigInteger(std::get<long long>(value)) + std::get<BigInteger>(other.value);
                }
            }
        }
        case DOUBLE: {
            switch (other.tag) {
                case DOUBLE: {
                    double a = std::get<double>(value);
                    double b = std::get<double>(other.value);
                    if (a > std::numeric_limits<double>::max() - b) {
                        return {std::numeric_limits<double>::max()};
                    }
                    if (a < -std::numeric_limits<double>::max() - b) {
                        return {-std::numeric_limits<double>::max()};
                    }
                    return {a + b};
                }
                case INTEGER: {
                    double a = std::get<double>(value);
                    double b = std::get<int>(other.value);
                    if (a > std::numeric_limits<double>::max() - b) {
                        return {std::numeric_limits<double>::max()};
                    }
                    if (a < -std::numeric_limits<double>::max() - b) {
                        return {-std::numeric_limits<double>::max()};
                    }
                    return {a + b};
                }
                case LONG_LONG: {
                    throw ConversionError();
                }
                case BIG_INTEGER: {
                    throw ConversionError();
                }
            }
        }
        case BIG_INTEGER: {
            switch (other.tag) {
                case INTEGER: {
                    return BigInteger(std::get<int>(other.value)) + std::get<BigInteger>(value);
                }
                case LONG_LONG: {
                    return BigInteger(std::get<long long>(other.value)) + std::get<BigInteger>(value);
                }
                case BIG_INTEGER: {
                    return std::get<BigInteger>(other.value) + std::get<BigInteger>(value);
                }
                case DOUBLE: {
                    throw ConversionError();
                }
            }
        }
    }
    return {0};
}

SmartMath::SmartNumber SmartMath::SmartNumber::operator-(const SmartMath::SmartNumber &other) const {
    switch (tag) {
        case INTEGER: {
            switch (other.tag) {
                case INTEGER: {
                    long long res = std::get<int>(value) - std::get<int>(other.value);
                    if (res == (int) res) {
                        return {(int) res};
                    } else {
                        return {res};
                    }
                }
                case LONG_LONG: {
                    long long a = std::get<int>(value);
                    long long b = std::get<long long>(other.value);
                    if (a > std::numeric_limits<long long>::max() + b) {
                        return {std::numeric_limits<long long>::max()};
                    }
                    if (a < std::numeric_limits<long long>::min() + b) {
                        return {std::numeric_limits<long long>::min()};
                    }
                    return {a - b};
                }
                case DOUBLE: {
                    double a = std::get<int>(value);
                    double b = std::get<double>(other.value);
                    if (a > std::numeric_limits<double>::max() + b) {
                        return {std::numeric_limits<double>::max()};
                    }
                    if (a < -std::numeric_limits<double>::max() + b) {
                        return {-std::numeric_limits<double>::max()};
                    }
                    return {a - b};
                }
                case BIG_INTEGER: {
                    return BigInteger(std::get<int>(value)) + std::get<BigInteger>(other.value);
                }
            }
        }
        case LONG_LONG: {
            switch (other.tag) {
                case LONG_LONG: {
                    long long a = std::get<long long>(value);
                    long long b = std::get<long long>(other.value);
                    if (a > std::numeric_limits<long long>::max() + b) {
                        return {std::numeric_limits<long long>::max()};
                    }
                    if (a < std::numeric_limits<long long>::min() + b) {
                        return {std::numeric_limits<long long>::min()};
                    }
                    return {a - b};
                }
                case INTEGER: {
                    long long a = std::get<long long>(value);
                    long long b = std::get<int>(other.value);
                    if (a > std::numeric_limits<long long>::max() + b) {
                        return {std::numeric_limits<long long>::max()};
                    }
                    if (a < std::numeric_limits<long long>::min() + b) {
                        return {std::numeric_limits<long long>::min()};
                    }
                    return {a - b};
                }
                case DOUBLE: {
                    throw SmartMath::ConversionError();
                }
                case BIG_INTEGER: {
                    return BigInteger(std::get<long long>(value)) + std::get<BigInteger>(other.value);
                }
            }
        }
        case DOUBLE: {
            switch (other.tag) {
                case DOUBLE: {
                    double a = std::get<double>(value);
                    double b = std::get<double>(other.value);
                    if (a > std::numeric_limits<double>::max() + b) {
                        return {std::numeric_limits<double>::max()};
                    }
                    if (a < -std::numeric_limits<double>::max() + b) {
                        return {-std::numeric_limits<double>::max()};
                    }
                    return {a - b};
                }
                case INTEGER: {
                    double a = std::get<double>(value);
                    double b = std::get<int>(other.value);
                    if (a > std::numeric_limits<double>::max() + b) {
                        return {std::numeric_limits<double>::max()};
                    }
                    if (a < -std::numeric_limits<double>::max() + b) {
                        return {-std::numeric_limits<double>::max()};
                    }
                    return {a - b};
                }
                case LONG_LONG: {
                    throw ConversionError();
                }
                case BIG_INTEGER:
                    throw ConversionError();
            }
        }
        case BIG_INTEGER: {
            switch (other.tag) {
                case INTEGER: {
                    return std::get<BigInteger>(value) + BigInteger(std::get<int>(other.value));
                }
                case LONG_LONG: {
                    return std::get<BigInteger>(value) + BigInteger(std::get<long long>(other.value));
                }
                case BIG_INTEGER: {
                    return std::get<BigInteger>(value) + std::get<BigInteger>(other.value);
                }
                case DOUBLE: {
                    throw ConversionError();
                }
            }
        }
    }
    return {0};
}

SmartMath::SmartNumber SmartMath::SmartNumber::operator*(const SmartMath::SmartNumber &other) const {
    switch (tag) {
        case INTEGER: {
            switch (other.tag) {
                case INTEGER: {
                    long long res = std::get<int>(value) * std::get<int>(other.value);
                    if (res == (int) res) {
                        return {(int) res};
                    } else {
                        return {res};
                    }
                }
                case LONG_LONG: {
                    long long a = std::get<int>(value);
                    long long b = std::get<long long>(other.value);
                    if (a > std::numeric_limits<long long>::max() / b) {
                        return {std::numeric_limits<long long>::max()};
                    }
                    if (a < std::numeric_limits<long long>::min() / b) {
                        return {std::numeric_limits<long long>::min()};
                    }
                    return {a * b};
                }
                case DOUBLE: {
                    double a = std::get<int>(value);
                    double b = std::get<double>(other.value);
                    if (a > std::numeric_limits<double>::max() / b) {
                        return {std::numeric_limits<double>::max()};
                    }
                    if (a < -std::numeric_limits<double>::max() / b) {
                        return {-std::numeric_limits<double>::max()};
                    }
                    return {a * b};
                }
                case BIG_INTEGER: {
                    return BigInteger(std::get<int>(value)) + std::get<BigInteger>(other.value);
                }
            }
        }
        case LONG_LONG: {
            switch (other.tag) {
                case LONG_LONG: {
                    long long a = std::get<long long>(value);
                    long long b = std::get<long long>(other.value);
                    if (a > std::numeric_limits<long long>::max() / b) {
                        return {std::numeric_limits<long long>::max()};
                    }
                    if (a < std::numeric_limits<long long>::min() / b) {
                        return {std::numeric_limits<long long>::min()};
                    }
                    return {a * b};
                }
                case INTEGER: {
                    long long a = std::get<long long>(value);
                    long long b = std::get<int>(other.value);
                    if (a > std::numeric_limits<long long>::max() / b) {
                        return {std::numeric_limits<long long>::max()};
                    }
                    if (a < std::numeric_limits<long long>::min() / b) {
                        return {std::numeric_limits<long long>::min()};
                    }
                    return {a * b};
                }
                case DOUBLE: {
                    throw SmartMath::ConversionError();
                }
                case BIG_INTEGER: {
                    return BigInteger(std::get<long long>(value)) + std::get<BigInteger>(other.value);
                }
            }
        }
        case DOUBLE: {
            switch (other.tag) {
                case DOUBLE: {
                    double a = std::get<double>(value);
                    double b = std::get<double>(other.value);
                    if (a > std::numeric_limits<double>::max() / b) {
                        return {std::numeric_limits<double>::max()};
                    }
                    if (a < -std::numeric_limits<double>::max() / b) {
                        return {-std::numeric_limits<double>::max()};
                    }
                    return {a * b};
                }
                case INTEGER: {
                    double a = std::get<double>(value);
                    double b = std::get<int>(other.value);
                    if (a > std::numeric_limits<double>::max() / b) {
                        return {std::numeric_limits<double>::max()};
                    }
                    if (a < -std::numeric_limits<double>::max() / b) {
                        return {-std::numeric_limits<double>::max()};
                    }
                    return {a * b};
                }
                case LONG_LONG: {
                    throw ConversionError();
                }
                case BIG_INTEGER: {
                    throw ConversionError();
                }
            }
        }
        case BIG_INTEGER: {
            switch (other.tag) {
                case INTEGER: {
                    return BigInteger(std::get<int>(value)) + std::get<BigInteger>(other.value);
                }
                case LONG_LONG: {
                    return BigInteger(std::get<long long>(value)) + std::get<BigInteger>(other.value);
                }
                case BIG_INTEGER: {
                    return std::get<BigInteger>(value) + std::get<BigInteger>(other.value);
                }
                case DOUBLE: {
                    throw ConversionError();
                }
            }
        }
    }
    return {0};
}

SmartMath::SmartNumber SmartMath::SmartNumber::operator/(const SmartMath::SmartNumber &other) const {
    switch (tag) {
        case INTEGER: {
            switch (other.tag) {
                case INTEGER: {
                    int res = std::get<int>(value) / std::get<int>(other.value);
                    return {res};
                }
                case LONG_LONG: {
                    long long a = std::get<int>(value);
                    long long b = std::get<long long>(other.value);
                    return {a / b};
                }
                case DOUBLE: {
                    double a = std::get<int>(value);
                    double b = std::get<double>(other.value);
                    return {a / b};
                }
                case BIG_INTEGER: {
                    return BigInteger(std::get<int>(value)) + std::get<BigInteger>(other.value);
                }
            }
        }
        case LONG_LONG: {
            switch (other.tag) {
                case LONG_LONG: {
                    long long a = std::get<long long>(value);
                    long long b = std::get<long long>(other.value);
                    return {a / b};
                }
                case INTEGER: {
                    long long a = std::get<long long>(value);
                    long long b = std::get<int>(other.value);
                    return {a / b};
                }
                case DOUBLE: {
                    throw ConversionError();
                }
                case BIG_INTEGER: {
                    return BigInteger(std::get<long long>(value)) + std::get<BigInteger>(other.value);
                }
            }
        }
        case DOUBLE: {
            switch (other.tag) {
                case DOUBLE: {
                    double a = std::get<double>(value);
                    double b = std::get<double>(other.value);
                    return {a / b};
                }
                case INTEGER: {
                    double a = std::get<double>(value);
                    double b = std::get<int>(other.value);
                    return {a / b};
                }
                case LONG_LONG: {
                    throw ConversionError();
                }
                case BIG_INTEGER: {
                    throw ConversionError();
                }
            }
        }
        case BIG_INTEGER: {
            switch (other.tag) {
                case INTEGER: {
                    return BigInteger(std::get<int>(value)) + std::get<BigInteger>(other.value);
                }
                case LONG_LONG: {
                    return BigInteger(std::get<long long>(value)) + std::get<BigInteger>(other.value);
                }
                case BIG_INTEGER: {
                    return std::get<BigInteger>(value) + std::get<BigInteger>(other.value);
                }
                case DOUBLE: {
                    throw ConversionError();
                }
            }
        }
    }
    return {0};
}

SmartMath::SmartNumber &SmartMath::SmartNumber::operator=(const SmartMath::SmartNumber &other) {
    if (this == &other) {
        return *this;
    }
    tag = other.tag;
    value = other.value;
    return *this;
}

SmartMath::SmartNumber &SmartMath::SmartNumber::operator+=(const SmartMath::SmartNumber &other) {
    return *this = *this + other;
}

SmartMath::SmartNumber &SmartMath::SmartNumber::operator-=(const SmartMath::SmartNumber &other) {
    return *this = *this - other;
}

SmartMath::SmartNumber &SmartMath::SmartNumber::operator*=(const SmartMath::SmartNumber &other) {
    return *this = *this * other;
}

SmartMath::SmartNumber &SmartMath::SmartNumber::operator/=(const SmartMath::SmartNumber &other) {
    return *this = *this / other;
}

bool SmartMath::SmartNumber::operator>(const SmartMath::SmartNumber &other) const {
    SmartNumber tmp = *this - other;
    switch (tmp.tag) {
        case INTEGER: {
            return std::get<int>(tmp.value) > 0;
        }
        case LONG_LONG: {
            return std::get<long long>(tmp.value) > 0;
        }
        case DOUBLE: {
            return std::get<double>(tmp.value) > 0;
        }
        case BIG_INTEGER: {
            return std::get<BigInteger>(tmp.value) > 0;
        }
    }
    return true;
}

bool SmartMath::SmartNumber::operator>=(const SmartMath::SmartNumber &other) const {
    SmartNumber tmp = *this - other;
    switch (tmp.tag) {
        case INTEGER: {
            return std::get<int>(tmp.value) >= 0;
        }
        case LONG_LONG: {
            return std::get<long long>(tmp.value) >= 0;
        }
        case DOUBLE: {
            return std::get<double>(tmp.value) >= 0;
        }
        case BIG_INTEGER: {
            return std::get<BigInteger>(tmp.value) >= 0;
        }
    }
    return true;
}

bool SmartMath::SmartNumber::operator<(const SmartMath::SmartNumber &other) const {
    SmartNumber tmp = *this - other;
    switch (tmp.tag) {
        case INTEGER: {
            return std::get<int>(tmp.value) < 0;
        }
        case LONG_LONG: {
            return std::get<long long>(tmp.value) < 0;
        }
        case DOUBLE: {
            return std::get<double>(tmp.value) < 0;
        }
        case BIG_INTEGER: {
            return std::get<BigInteger>(tmp.value) < 0;
        }
    }
    return true;
}

bool SmartMath::SmartNumber::operator<=(const SmartMath::SmartNumber &other) const {
    SmartNumber tmp = *this - other;
    switch (tmp.tag) {
        case INTEGER: {
            return std::get<int>(tmp.value) <= 0;
        }
        case LONG_LONG: {
            return std::get<long long>(tmp.value) <= 0;
        }
        case DOUBLE: {
            return std::get<double>(tmp.value) <= 0;
        }
        case BIG_INTEGER: {
            return std::get<BigInteger>(tmp.value) <= 0;
        }
    }
    return true;
}

SmartMath::SmartNumber SmartMath::SmartNumber::operator-() const {
    return *this * -1;
}

SmartMath::SmartNumber &SmartMath::SmartNumber::operator++() {
    if (tag == INTEGER || tag == LONG_LONG) {
        return *this += 1;
    } else {
        throw ConversionError();
    }
}

SmartMath::SmartNumber SmartMath::SmartNumber::operator++(int) {
    if (tag == INTEGER || tag == LONG_LONG) {
        SmartNumber res = *this;
        *this += 1;
        return res;
    } else {

        throw ConversionError();
    }
}

SmartMath::SmartNumber &SmartMath::SmartNumber::operator--() {
    if (tag == INTEGER || tag == LONG_LONG) {
        return *this -= 1;
    } else {
        throw ConversionError();
    }
}

SmartMath::SmartNumber SmartMath::SmartNumber::operator--(int) {
    if (tag == INTEGER || tag == LONG_LONG) {
        SmartNumber res = *this;
        *this -= 1;
        return res;
    } else {

        throw ConversionError();
    }
}

SmartMath::SmartNumber::SmartNumber(const SmartMath::SmartNumber &other) = default;

SmartMath::SmartNumber::~SmartNumber() = default;


