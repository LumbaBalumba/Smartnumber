//
// Created by i3alumba on 13.02.23.
//

#include "SmartNumber.hpp"
#include <set>
#include <cmath>
#include <limits>

typedef ssize_t index_t;

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

SmartMath::SmartNumber::~SmartNumber() = default;

static index_t sign_separate(const std::string &str, const std::set<char> &separators) {
    int balance = 0;
    for (index_t index = (index_t) str.size() - 1; index >= 0; --index) {
        if (str[index] == ')') {
            balance++;
        } else if (str[index] == '(') {
            balance--;
        } else if (separators.contains(str[index]) && balance == 0) {
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
        } else if (str[sign_index] == '-') {
            return evaluate(slice(str, 0, sign_index)) - evaluate(slice(str, sign_index + 1, (index_t) str.size()));
        }
    }
    signs.clear();
    signs.insert('*');
    signs.insert('/');
    signs.insert('^');
    sign_index = sign_separate(str, signs);
    if (sign_index >= 0) {
        if (str[sign_index] == '*') {
            return evaluate(slice(str, 0, sign_index)) * evaluate(slice(str, sign_index + 1, (index_t) str.size()));
        } else if (str[sign_index] == '/') {
            return evaluate(slice(str, 0, sign_index)) / evaluate(slice(str, sign_index + 1, (index_t) str.size()));
        } else if (str[sign_index] == '^') {
            return pow(evaluate(slice(str, 0, sign_index)), evaluate(slice(str, sign_index + 1, (index_t) str.size())));
        }
    }
    if (str[str.size() - 1] == ')') {
        if (str[0] == '(') {
            return evaluate(slice(str, 1, (index_t) str.size() - 1));
        } else {
            std::string tmp = slice(str, 0, 4);
            if (tmp == "sin(") {
                return sin(evaluate(slice(str, 4, (index_t) str.size() - 1)));
            } else if (tmp == "cos(") {
                return cos(evaluate(slice(str, 4, (index_t) str.size() - 1)));
            } else if (tmp == "tan(") {
                return tan(evaluate(slice(str, 4, (index_t) str.size() - 1)));
            } else if (tmp == "exp(") {
                return exp(evaluate(slice(str, 4, (index_t) str.size() - 1)));
            } else if (tmp == "log(") {
                return log(evaluate(slice(str, 4, (index_t) str.size() - 1)));
            }
            tmp = slice(str, 0, 5);
            if (tmp == "asin(") {
                return asin(evaluate(slice(str, 5, (index_t) str.size() - 1)));
            } else if (tmp == "acos(") {
                return acos(evaluate(slice(str, 5, (index_t) str.size() - 1)));
            } else if (tmp == "atan(") {
                return atan(evaluate(slice(str, 5, (index_t) str.size() - 1)));
            } else if (tmp == "sinh(") {
                return sinh(evaluate(slice(str, 5, (index_t) str.size() - 1)));
            } else if (tmp == "cosh(") {
                return cosh(evaluate(slice(str, 5, (index_t) str.size() - 1)));
            } else if (tmp == "tanh(") {
                return tanh(evaluate(slice(str, 5, (index_t) str.size() - 1)));
            } else if (tmp == "sqrt(") {
                return sqrt(evaluate(slice(str, 5, (index_t) str.size() - 1)));
            }
            tmp = slice(str, 0, 6);
            if (tmp == "floor(") {
                return floor(evaluate(slice(str, 6, (index_t) str.size() - 1)));
            }
        }
    }
    if (str[str.size() - 1] == '|' && str[0] == '|') {
        return fabs(evaluate(slice(str, 1, (index_t) str.size() - 1)));
    }
    char *eptr = nullptr;
    double res = strtod(str.c_str(), &eptr);
    if (*eptr || errno) {
        throw (EvaluationError());
    }
    return res;
}

const char *SmartMath::EvaluationError::what() const noexcept {
    return "Error while evaluating a string";
}

const char *SmartMath::ConversionError::what() const noexcept {
    return "Type conversion impossible for these types";
}
