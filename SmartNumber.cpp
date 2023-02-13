//
// Created by i3alumba on 13.02.23.
//

#include "SmartNumber.hpp"

SmartNumber::SmartNumber::SmartNumber()
{
    state = 'i';
    value_ptr = new int;
    *(int *) value_ptr = 0;
}

SmartNumber::SmartNumber::SmartNumber(int number)
{
    state = 'i';
    value_ptr = new int;
    *(int *) value_ptr = number;
}

SmartNumber::SmartNumber::SmartNumber(long long int number)
{
    state = 'l';
    value_ptr = new long long;
    *(long long *) value_ptr = number;
}

SmartNumber::SmartNumber::SmartNumber(double number)
{
    state = 'd';
    value_ptr = new double;
    *(double *) value_ptr = number;
}

SmartNumber::SmartNumber::SmartNumber(std::string number)
{
    state = 's';
    value_ptr = new std::string;
    *(std::string *) value_ptr = number;
}


