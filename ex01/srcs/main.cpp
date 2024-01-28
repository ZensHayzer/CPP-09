/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 05:54:29 by ajeanne           #+#    #+#             */
/*   Updated: 2023/12/14 02:47:35 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv) {
	if (argc == 2)  {
		std::string	arg = argv[1];

		if (calculate(arg))
			return (1);
	}
    else
        std::cout << "Error: Need 1 parameter." << std::endl;
    
    return (0);
}