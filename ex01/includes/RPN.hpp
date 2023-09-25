/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 05:23:25 by ajeanne           #+#    #+#             */
/*   Updated: 2023/09/25 08:38:23 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <vector>
#include <cctype>
#include <stack>
#include <string>
#include <algorithm>

class RPN   {
    public:
        RPN();
        RPN(std::string const & entry);
        RPN(RPN const & src);
        ~RPN();
        
        RPN &operator=(RPN const & src);
        
        std::string         getEntry() const;
        std::stack<int>    getNumbers() const;
        std::stack<char>   getOperators() const;

        void                entryOk(std::string const & entry);
        void                fillVec(std::string const & entry);
        int                 calculate(int a, int b, char o);
        void                doCalc(std::string const & entry);
        void                copyStackI(std::stack<int> stack, std::stack<int> stack1);
        void                copyStackC(std::stack<char> stack, std::stack<char> stack1);

        class NotUnderTen : public std::exception {
            public:
                virtual const char* what() const throw()  {
                    return ("Error: All numbers has to be under 10.");
                }
        };

        class CharNotSupported : public std::exception {
            public:
                virtual const char* what() const throw()  {
                    return ("Error: 0123456789 /*-+ are the only chars autorized.");
                }
        };
        
        class WrongNumbersOperator : public std::exception {
            public:
                virtual const char* what() const throw()  {
                    return ("Error: Check your number of operator.");
                }
        };

        class DivisionZero : public std::exception {
            public:
                virtual const char* what() const throw()  {
                    return ("Error: Can't divide by 0.");
                }
        };
        
    private:
        std::string         _entry;
        std::stack<int>    _numbers;
        std::stack<char>   _operators;
};

#endif