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
        union value
        {
            int i_value;
            long long ll_value;
            double d_value;
            std::string s_value;
        };

    public:
        SmartNumber();

        SmartNumber(int number);

        SmartNumber(long long number);

        SmartNumber(double number);

        SmartNumber(std::string number);

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
