/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:47:53 by ajeanne           #+#    #+#             */
/*   Updated: 2023/10/31 01:12:06 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc > 1)  {
        std::string tmp;
        for (int i = 1; i < argc; i++)  {
            for (int j = i + 1; j < argc; j++)  {
                if (atoi(argv[i]) == atoi(argv[j])) {
                    std::cout << "You cant put multiple times the same number." << std::endl;
                    return (1);
                }
            }
            tmp += argv[i];
            tmp += ' ';
        }
        
        PmergeMe    pmerg(tmp, argc - 1);
        try
        {
            pmerg.fillCont(tmp);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    else
        std::cout << "Error: Need 1 or more arguments." << std::endl;
}