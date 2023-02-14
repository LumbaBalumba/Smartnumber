//
// Created by i3alumba on 13.02.23.
//

#ifndef SMARTNUMBER_SMARTNUMBER_HPP
#define SMARTNUMBER_SMARTNUMBER_HPP

#include <string>
#include <climits>
#include <variant>

namespace SmartMath {

    class EvaluationError : public std::exception {
    public:
        const char * what() const noexcept override;
    };

    double evaluate(const std::string &str);

    class SmartNumber {
    private:
        enum {
            INTEGER,
            LLONG,
            DOUBLE
        } tag;

        std::variant<int, long long, double> value;

        void
        normalize();

    public:
        SmartNumber();

        explicit SmartNumber(int number);

        explicit SmartNumber(long long number);

        explicit SmartNumber(double number);

        explicit SmartNumber(const std::string &number);

        ~SmartNumber();

        std::string type();

        SmartNumber operator+(const SmartNumber &other);

        SmartNumber operator-(const SmartNumber &other);

        SmartNumber operator*(const SmartNumber &other);

        SmartNumber operator/(const SmartNumber &other);

        bool operator==(const SmartNumber &other);

        bool operator!=(const SmartNumber &other);

        SmartNumber &operator+=(const SmartNumber &other);

        SmartNumber &operator-=(const SmartNumber &other);

        SmartNumber &operator*=(const SmartNumber &other);

        SmartNumber &operator/=(const SmartNumber &other);
    };
}


#endif //SMARTNUMBER_SMARTNUMBER_HPP
