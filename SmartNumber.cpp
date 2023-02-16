//
// Created by i3alumba on 16.02.23.
//
#include "SmartMath.hpp"
#include "SmartMath.hpp"
#include <set>
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
                    throw (SmartMath::ConversionError());
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
                    throw (ConversionError());
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
                    throw (SmartMath::ConversionError());
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
                    throw (ConversionError());
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
                    throw (SmartMath::ConversionError());
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
                    throw (ConversionError());
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
                    throw (SmartMath::ConversionError());
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
                    throw (ConversionError());
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

SmartMath::SmartNumber::SmartNumber(const SmartMath::SmartNumber &other) = default;

SmartMath::SmartNumber::~SmartNumber() = default;


