#include "calculator.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>

bool ReadNumber(Number& result)
{
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
    Number currentValue = 0;
    bool memoryInitialized = false;
    Number memoryValue = 0;
    bool firstToken = true;

    std::string command;
    while (std::cin >> command)
    {
        if (firstToken) {
            std::stringstream ss(command);
            Number value;
            if (ss >> value && ss.eof()) {
                currentValue = value;
                firstToken = false;
                continue;
            } else {
                std::cerr << "Error: Numeric operand expected" << std::endl;
                return false;
            }
        }

        if (command == "q") {
            return true;
        } else if(command == "=") {
            std::cout << currentValue << std::endl;
        } else if (command == "c") {
            currentValue = 0;
        } else if (command == "s") {
            memoryValue = currentValue;
            memoryInitialized = true;
        } else if (command == "l") {
            if (!memoryInitialized) {
                std::cerr << "Error: Memory is empty" << std::endl;
                return false;
            }
            currentValue = memoryValue;
        } 
        
        else if (command == "+") {
            Number operand;
            if (!ReadNumber(operand)) {
                return false;
            }
            currentValue += operand;
        } else if(command == "-") {
            Number operand;
            if (!ReadNumber(operand)) {
                return false;
            }
            currentValue -= operand;
        } else if (command == "*") {
            Number operand;
            if (!ReadNumber(operand)) {
                return false;
            }
            currentValue *= operand;
        } else if (command == "/") {
            Number operand;
            if (!ReadNumber(operand)) {
                return false;
            }
            if (operand == 0) {
                currentValue = std::numeric_limits<Number>::infinity();
            } else {
                currentValue /= operand;
            }
        } else if (command == "**") {
            Number operand;
            if (!ReadNumber(operand)) {
                return false;
            }
            currentValue = std::pow(currentValue, operand);
        } else if (command == ":") {
            Number operand;
            if (!ReadNumber(operand)) {
                return false;
            }
            currentValue = operand;
        } else {
            std::stringstream ss(command);
            Number value;
            if (ss >> value && ss.eof()) {
                std::cerr << "Error: Numeric operand expected" << std::endl;
                return false;
            } else {
                std::cerr << "Error: Unknown token " << command << std::endl;
                return false;
            }
        }
    }

    return true;
}