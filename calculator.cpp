#include "calculator.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

bool ReadNumber(Number& result) {
    std::string input;
    if (!(std::cin >> input)) {
        return false;
    }

    std::stringstream ss(input);
    Number value;
    if (ss >> value && ss.eof()) {
        result = value;
        return true;
    }
    std::cerr << "Error: Numeric operand expected" << std::endl;
    return false;
}

bool RunCalculatorCycle()
{
    Number curr_val = 0;
    bool memory_init = false;
    Number memory_val = 0;

    std::string command;

    while (std::cin >> command)
    {
        if (command == "q") {
            return true;
        } else if(command == "=") {
            std::cout << curr_val << std::endl;
        } else if (command == "c") {
            curr_val = 0;
        } else if (command == "s") {
            memory_val = curr_val;
            memory_init = true;
        } else if (command == "l") {
            if (!memory_init) {
                std::cerr << "Error: Memory is empty." << std::endl;
                return false;
            }
            curr_val = memory_val;
        } 
        
        else if (command == "+") {
            Number operand;
            if (!ReadNumber(operand)) {
                return  false;
            }
            curr_val = curr_val + operand;
        } else if(command == "-") {
            Number operand;
            if (!ReadNumber(operand)) {
                return false;
            }
            curr_val = curr_val - operand;
        } else if (command == "*") {
            Number operand;
            if (!ReadNumber(operand)) {
                return false;
            }
            curr_val = curr_val * operand;
        } else if (command == "/") {
            Number operand;
            if (!ReadNumber(operand)) {
                return false;
            }
            if (operand == 0) {
                std::cerr << "Error: Division by zero" << std::endl;
                return false;
            }
            curr_val = curr_val / operand;
        } else if (command == "**") {
            Number operand;
            if (!ReadNumber(operand)) {
                return false;
            }
            curr_val = pow(curr_val, operand);
        } else if (command == ":") {
            Number operand;
            if (!ReadNumber(operand)){
                return false;
            }
            curr_val = operand;
        } else {
            std::cerr << "Error: Unknown token " << command << std::endl;
            return false;
        }
    }

    return true;
}