//
// Created by i3alumba on 13.02.23.
//

#ifndef SMARTNUMBER_SMARTNUMBER_HPP
#define SMARTNUMBER_SMARTNUMBER_HPP

#include <string>
#include <variant>
#include <iostream>

namespace SmartMath {

    class EvaluationError : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override;
    };

    class ConversionError : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override;
    };

    double evaluate(const std::string &str);

    class SmartNumber {
    private:
        enum {
            INTEGER,
            LONG_LONG,
            DOUBLE
        } tag;

        std::variant<int, long long, double> value;

        void normalize();

    public:
        SmartNumber();

        SmartNumber(int number);

        SmartNumber(long long number);

        SmartNumber(double number);

        explicit SmartNumber(const std::string &number);

        ~SmartNumber();

        std::string type();

        SmartNumber operator+(const SmartNumber &other) const;

        SmartNumber operator-(const SmartNumber &other) const;

        SmartNumber operator*(const SmartNumber &other) const;

        SmartNumber operator/(const SmartNumber &other) const;

        bool operator==(const SmartNumber &other) const;

        bool operator!=(const SmartNumber &other) const;

        SmartNumber &operator=(const SmartNumber &other);

        SmartNumber &operator+=(const SmartNumber &other);

        SmartNumber &operator-=(const SmartNumber &other);

        SmartNumber &operator*=(const SmartNumber &other);

        SmartNumber &operator/=(const SmartNumber &other);

        friend std::istream &operator>>(const std::istream &in, const SmartNumber &number);

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


#endif //SMARTNUMBER_SMARTNUMBER_HPP
