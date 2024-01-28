/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 21:29:08 by ajeanne           #+#    #+#             */
/*   Updated: 2023/09/25 02:49:24 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <exception>
#include <limits.h>
#include <float.h>
#include <stdlib.h>

class BitcoinExchange   {
    public:
        BitcoinExchange();
        BitcoinExchange(std::string filename);
        BitcoinExchange(BitcoinExchange const & src);
        ~BitcoinExchange();
        
        BitcoinExchange &operator=(BitcoinExchange const & src);
        
        std::string                     getFilename() const;
        std::map<std::string, float>    getExchange() const;
        
        void                            fillExchange(std::string const & csv);
        void                            check(std::string const & txt);
        bool                            isDateOk(std::string const & date);
        void                            printCheck(std::string const & date, float value);

        class FailOpenFile : public std::exception {
            public:
                virtual const char* what() const throw()  {
                    return ("Could not open the file.");
                }
        };

        class WrongFile : public std::exception {
            public:
                virtual const char* what() const throw()  {
                    return ("Wrong file format.");
                }
        };

    private:
        std::string                 _filename;
        std::map<std::string, float>  _exchange;
};

#endif