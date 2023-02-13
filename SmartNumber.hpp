//
// Created by i3alumba on 13.02.23.
//

#ifndef SMARTNUMBER_SMARTNUMBER_HPP
#define SMARTNUMBER_SMARTNUMBER_HPP

#include <string>
#include <climits>

namespace SmartNumber
{
    class SmartNumber
    {
    private:
        char state;

        void *value_ptr;

        void
        normalize();

    public:
        SmartNumber();

        explicit SmartNumber(int number);

        explicit SmartNumber(long long number);

        explicit SmartNumber(double number);

        explicit SmartNumber(const std::string &number);

        ~SmartNumber();

        std::string
        type();

        SmartNumber
        operator+(const SmartNumber &other);

        SmartNumber
        operator-(const SmartNumber &other);

        SmartNumber
        operator*(const SmartNumber &other);

        SmartNumber
        operator/(const SmartNumber &other);

        SmartNumber
        operator==(const SmartNumber &other);

        SmartNumber
        operator!=(const SmartNumber &other);

        SmartNumber &
        operator+=(const SmartNumber &other);

        SmartNumber &
        operator-=(const SmartNumber &other);

        SmartNumber &
        operator*=(const SmartNumber &other);

        SmartNumber &
        operator/=(const SmartNumber &other);
    };
}


#endif //SMARTNUMBER_SMARTNUMBER_HPP
