/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:39:04 by ajeanne           #+#    #+#             */
/*   Updated: 2023/09/29 20:50:44 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)  {
    if (argc == 2)  {    
        BitcoinExchange btc;
        try
        {
            btc.check(argv[1]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    else
        std::cout << "Could not open the file." << std::endl;
    
    return (0);
}