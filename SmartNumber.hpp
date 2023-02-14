//
// Created by i3alumba on 13.02.23.
//

#ifndef SMARTNUMBER_SMARTNUMBER_HPP
#define SMARTNUMBER_SMARTNUMBER_HPP

#include <string>
#include <climits>

namespace SmartMath {
    double evaluate(const std::string &str);

    class SmartNumber {
    private:
        enum {
            INTEGER,
            LLONG,
            DOUBLE
        } tag;

        union v_union {
            int i_value{};
            long long l_value;
            double d_value;

            v_union() {}

            ~v_union() {}
        } value;

        void
        normalize();

    public:
        SmartNumber();

        explicit SmartNumber(int number);

        explicit SmartNumber(long long number);

        explicit SmartNumber(double number);

        ~SmartNumber();

        char *type();

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
