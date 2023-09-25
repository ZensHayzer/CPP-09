/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 05:53:31 by ajeanne           #+#    #+#             */
/*   Updated: 2023/09/25 08:42:33 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() : _entry("default")  {
    
}

RPN::RPN(std::string const & entry) : _entry(entry) {
    
}

RPN::RPN(RPN const & src)   {
    *this = src;
}

RPN::~RPN() {
    
}

RPN &RPN::operator=(RPN const & src)    {
    if (this != &src)   {
        _entry = src.getEntry();
        copyStackI(src.getNumbers(), _numbers);
        copyStackC(src.getOperators(), _operators);
    }
    
    return (*this);
}

std::string RPN::getEntry() const   {
    return (_entry);
}

std::stack<int>    RPN::getNumbers() const {
    return (_numbers);
}

std::stack<char>   RPN::getOperators() const   {
    return (_operators);
}

void    RPN::entryOk(std::string const & entry)  {
    std::string listChar = "0123456789+-/* ";
    
    for (size_t i = 0; i < entry.size(); i++)   {
        if (i < entry.size() - 1 && isdigit(entry[i] && entry[i + 1]))
            throw NotUnderTen();
        if (listChar.find(entry[i]) == std::string::npos)
            throw CharNotSupported();
    }
}

void    RPN::fillVec(std::string const & entry)  {
    std::string operators = "+-/*";
    
    for (size_t i = entry.size(); i > 0; --i)   {
        if (isdigit(entry[i]))
            _numbers.push(entry[i] - 48);
        else if (operators.find(entry[i]) != std::string::npos)
            _operators.push(entry[i]);
    }
    if (isdigit(entry[0]))
        _numbers.push(entry[0] - 48);
    else if (operators.find(entry[0]) != std::string::npos)
        _operators.push(entry[0]);
    
    if (_numbers.size() != _operators.size() + 1)
        throw WrongNumbersOperator();
}

int RPN::calculate(int a, int b, char o) {
    switch (o)
    {
    case '+':
        return (a + b);
    case '-':
        return (a - b);
    case '/':
        if (b == 0)
            throw DivisionZero();
        return (a / b);
    case '*':
        return (a * b);
    }
    
    return (0);
}

void    RPN::doCalc(std::string const & entry)   {
    long    res;
    int     nb1;
    int     nb2;
    

    entryOk(entry);
    fillVec(entry);

    nb1 = _numbers.top();
    _numbers.pop();
    nb2 = _numbers.top();
    _numbers.pop();
    res = calculate(nb1, nb2, _operators.top());
    _operators.pop();
    while(_numbers.size() >= 2) {
        nb2 = _numbers.top();
        _numbers.pop();
        res = calculate(res, nb2, _operators.top());
        _operators.pop();
    }
    
    if (_numbers.size() == 1)   {
        nb2 = _numbers.top();
        _numbers.pop();
        res = calculate(res, nb2, _operators.top());
        _operators.pop();
    }

    std::cout << "The result is : " << res << std::endl;
}

void    RPN::copyStackI(std::stack<int> stack, std::stack<int> stack1)   {
    std::stack<int> tmp;
    size_t          size = stack.size();
    
    for (size_t i = 0; i < size; i++)   {
        tmp.push(stack.top());
        stack.pop();
    }
    for (size_t i = 0; i < size; i++)   {
        stack1.push(tmp.top());
        tmp.pop();
    }
}

void    RPN::copyStackC(std::stack<char> stack, std::stack<char> stack1)   {
    std::stack<char> tmp;
    size_t          size = stack.size();
    
    for (size_t i = 0; i < size; i++)   {
        tmp.push(stack.top());
        stack.pop();
    }
    for (size_t i = 0; i < size; i++)   {
        stack1.push(tmp.top());
        tmp.pop();
    }
}