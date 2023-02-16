//
// Created by i3alumba on 13.02.23.
//

#ifndef SMARTMATH_SMARTNUMBER_HPP
#define SMARTMATH_SMARTNUMBER_HPP

#include <string>
#include <variant>
#include <iostream>
#include <algorithm>

typedef ssize_t index_t;

namespace SmartMath {

    class EvaluationError : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override;
    };

    class ConversionError : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override;
    };

    class IncorrectInputError : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override;
    };


    double evaluate(const std::string &str);

    class BigInteger {
    private:
        std::string value;
        bool sign;

    public:
        BigInteger();

        BigInteger(int value);

        BigInteger(long long number);

        BigInteger(const BigInteger &other) = default;

        ~BigInteger() = default;

        BigInteger operator+(const BigInteger &other) const;

        BigInteger operator-(const BigInteger &other) const;

        BigInteger operator*(const BigInteger &other) const;

        BigInteger operator/(const BigInteger &other) const;

        BigInteger &operator+=(const BigInteger &other);

        BigInteger &operator-=(const BigInteger &other);

        BigInteger &operator*=(const BigInteger &other);

        BigInteger &operator/=(const BigInteger &other);

        BigInteger &operator=(const BigInteger &other) = default;

        bool operator==(const BigInteger &other) const;

        bool operator!=(const BigInteger &other) const;

        bool operator>(const BigInteger &other) const;

        bool operator>=(const BigInteger &other) const;

        bool operator<(const BigInteger &other) const;

        bool operator<=(const BigInteger &other) const;

        BigInteger operator-() const;

        BigInteger &operator++();

        BigInteger operator++(int);

        BigInteger &operator--();

        BigInteger operator--(int);


        friend std::istream &operator>>(std::istream &in, BigInteger &number) {
            std::string buffer;
            in >> buffer;
            for (auto &i: buffer) {
                if (i > '9' || i < '0') {
                    throw (IncorrectInputError());
                }
            }
            if (buffer == "0") {
                number.value = "";
            } else {
                std::reverse(buffer.begin(), buffer.end());
                number.value = buffer;
            }
            return in;
        }

        friend std::ostream &operator<<(std::ostream &out, const BigInteger &number) {
            if (number.value.empty()) {
                out << 0;
            } else {
                std::string buffer = number.value;
                std::reverse(buffer.begin(), buffer.end());
                out << buffer;
            }
            return out;
        }
    };

    class SmartNumber {
    private:
        enum {
            INTEGER,
            LONG_LONG,
            DOUBLE
        } tag;

        std::variant<int, long long, double> value;

    public:
        SmartNumber();

        SmartNumber(int number);

        SmartNumber(long long number);

        SmartNumber(double number);

        SmartNumber(const SmartNumber &other);

        explicit SmartNumber(const std::string &number);

        ~SmartNumber();

        [[nodiscard]] std::string type() const;

        SmartNumber operator+(const SmartNumber &other) const;

        SmartNumber operator-(const SmartNumber &other) const;

        SmartNumber operator*(const SmartNumber &other) const;

        SmartNumber operator/(const SmartNumber &other) const;

        bool operator==(const SmartNumber &other) const;

        bool operator!=(const SmartNumber &other) const;

        bool operator>(const SmartNumber &other) const;

        bool operator>=(const SmartNumber &other) const;

        bool operator<(const SmartNumber &other) const;

        bool operator<=(const SmartNumber &other) const;

        SmartNumber operator-() const;

        SmartNumber &operator++();

        SmartNumber operator++(int);

        SmartNumber &operator--();

        SmartNumber operator--(int);

        SmartNumber &operator=(const SmartNumber &other);

        SmartNumber &operator+=(const SmartNumber &other);

        SmartNumber &operator-=(const SmartNumber &other);

        SmartNumber &operator*=(const SmartNumber &other);

        SmartNumber &operator/=(const SmartNumber &other);

        friend std::istream &operator>>(std::istream &in, SmartNumber &number) {
            std::string buffer;
            in >> buffer;
            errno = 0;
            char *eptr = nullptr;
            long long i_value = strtoll(buffer.c_str(), &eptr, 10);
            if (!errno && !eptr) {
                if (i_value == (int) i_value) {
                    number = SmartNumber((int) i_value);
                    return in;
                } else {
                    number = SmartNumber(i_value);
                    return in;
                }
            }
            errno = 0;
            eptr = nullptr;
            double d_value = strtod(buffer.c_str(), &eptr);
            if (!errno && !eptr) {
                number = SmartNumber(d_value);
                return in;
            } else {
                number = SmartNumber(buffer);
                return in;
            }
        }

        friend std::ostream &operator<<(std::ostream &out, const SmartNumber &number) {
            switch (number.tag) {
                case SmartNumber::INTEGER: {
                    out << std::get<int>(number.value);
                    break;
                }
                case SmartNumber::LONG_LONG:
                    out << std::get<long long>(number.value);
                    break;
                case SmartNumber::DOUBLE:
                    out << std::get<double>(number.value);
                    break;
            }
            return out;
        }
    };

}

#endif //SMARTMATH_SMARTNUMBER_HPP
