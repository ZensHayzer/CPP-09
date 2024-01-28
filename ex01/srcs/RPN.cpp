/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 05:53:31 by ajeanne           #+#    #+#             */
/*   Updated: 2023/12/14 02:48:16 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	calculate(std::string arg)  {
	std::istringstream	list(arg);
	std::stack<int>		resS;
	int					check = 0;

	std::string	tmp;
	while (list >> tmp) {
		std::stringstream	numbList(tmp);
		int					number = 0;
		int					_a;
		int					_b;

		if (numbList >> number) {
			resS.push(number);
			check++;
			if (check == 3){
				std::cout<<"Error: Too much consecutive digit in arg"<<std::endl;
				return (1);
			}
		}
		else if ((tmp.find("+") != std::string::npos || tmp.find("/") != std::string::npos
			|| tmp.find("*") != std::string::npos || tmp.find("-") != std::string::npos)
			&& resS.size() > 1) {
			_b = resS.top();
			resS.pop();
			_a = resS.top();
			resS.pop();
			if (tmp == "+") {
				check = 0;
				resS.push(_a + _b);
			}
			else if (tmp == "-")    {
				check = 0;
				resS.push(_a - _b);
			}
			else if (tmp == "*")    {
				check = 0;
				resS.push(_a * _b);
			}
			else if (tmp == "/")    {
				check = 0;
				if (_b == 0)
					return (std::cout<<"Error: No divide by 0"<<std::endl, 1);
				resS.push(_a / _b);
			}
			else
				return (std::cout<<"Error: Wrong Operator"<<std::endl, 1);
		}
		else    {
			std::cout << "Error: Use number, +, -, *, /, only." << std::endl;
			return (1);
		}
	}
	std::cout << resS.top() << std::endl;
	return (0);
}