/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 21:42:15 by ajeanne           #+#    #+#             */
/*   Updated: 2023/10/31 12:29:47 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _filename("default")  {
    
}

BitcoinExchange::BitcoinExchange(std::string filename) : _filename(filename)    {
    
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const & src)   {
    *this = src;
}

BitcoinExchange::~BitcoinExchange()   {
    
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const & src)    {
    std::map<std::string, float>  tmp = src.getExchange();
    
    if (this != &src)   {
        _filename = src.getFilename();
        _exchange.insert(tmp.begin(), tmp.end());
    }
    
    return (*this);
}

std::string BitcoinExchange::getFilename() const    {
    return (_filename);
}

std::map<std::string, float>  BitcoinExchange::getExchange() const    {
    return (_exchange);
}

void    BitcoinExchange::fillExchange(std::string const & csv)  {
    std::fstream        file;
    std::string         line;
    int                 coma;
    std::string         tmpS;
    std::string         tmpF;
    float               f;
    
    file.open(csv.c_str(), std::ios::in);
    if (!file.is_open())   {
        throw FailOpenFile();
    }
    while (getline(file, line))
    {        
        for (size_t i = 0; i < line.size(); i++)   {
            if (line[i] == ',') {
                coma = i;
                break;
            }
        }
        if (!isalpha(line[0]))  {
            tmpS = line.substr(0, coma);
            tmpF = line.substr(coma + 1, line.size());
            std::istringstream  iss(tmpF);
            if (!(iss >> f))
                throw WrongFile();
            _exchange.insert(std::pair<std::string, float>(tmpS, f));
        }
    }
    file.close();
}

void    BitcoinExchange::check(std::string const & txt)  {
    std::fstream        file;
    std::string         line;
    int                 coma;
    std::string         tmpS;
    std::string         tmpF;
    float               f;

    try
    {
        fillExchange("data.csv");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    file.open(txt.c_str(), std::ios::in);
    if (!file.is_open())
        throw FailOpenFile();
    while (getline(file, line)) {
        for (size_t i = 0; i < line.size(); i++)   {
            if (line[i] == '|') {
                coma = i;
                break;
            }
        }
        if (!isalpha(line[0]))  {
            if (coma > 3)   {
                tmpS = line.substr(0, coma - 1);
                tmpF = line.substr(coma + 2, line.size());
                if (isDateOk(tmpS)) {
                    std::istringstream  iss(tmpF);
                    if (iss >> f)    {
                        if (f < 0 || f > 1000)  {
                            if (f < 0)
                                std::cout << "Error: Not a positive number." << std::endl;
                            if (f > 1000)
                                std::cout << "Error: Too large number." << std::endl;
                        }
                        else
                            printCheck(tmpS, f);  
                    }
                    else
                        std::cout << "Error: Bad input => " << line << std::endl;
                }
                else
                    std::cout << "Error: Bad input => " << line << std::endl;
            }
            else
                std::cout << "Error: Bad input => " << line << std::endl;
        }
        coma = 0;
    }
    file.close();
}

bool    BitcoinExchange::isDateOk(std::string const & date) {
    std::string tmpS;
    int         tmpI;
    int         tmpI1;
    int         tmpI2;
    
    if (date.size() < 10)
        return (false);
    tmpS = date.substr(0, 4);    
    std::istringstream  iss(tmpS);
    if (!(iss >> tmpI))
        return (false);
    if (tmpI < 0)
        return (false);
    tmpS = date.substr(5, 2);
    std::istringstream  oss(tmpS);    
    if (!(oss >> tmpI1))
        return (false);
    if (tmpI1 > 31 || tmpI1 < 0)
        return (false);
    tmpS = date.substr(8, 2); 
    std::istringstream  pss(tmpS);
    if (!(pss >> tmpI2))
        return (false);
    if (tmpI2 > 12 || tmpI2 < 0)
        return (false);
    if ((tmpI < 2009) || (tmpI == 2009 && tmpI1 == 01 && tmpI2 < 02))
        return (false);
    if (tmpI > 2024)
        return (false);
    return (true);
}

void    BitcoinExchange::printCheck(std::string const & date, float value)   {

    for (std::map<std::string, float>::iterator it = _exchange.begin(); it != _exchange.end(); ++it)    {        
        if (it->first == date)  {
            std::cout << date << " => " << value << " = " << value * it->second << std::endl;
            return;
        }
    }
    

    int sep1 = date.find('-');
    std::map<std::string, float>::iterator itt = _exchange.end();
    itt--;
    
    if (atoi(_exchange.begin()->first.substr(0, 4).c_str()) > atoi(date.substr(0, sep1).c_str()))  {
        std::cout << date << " => " << value << " = " << value * _exchange.begin()->second << std::endl;
        return;
    }
    else if (atoi(itt->first.substr(0, 4).c_str()) < atoi(date.substr(0, sep1).c_str()))  {
        std::cout << date << " => " << value << " = " << value * _exchange.end()->second << std::endl;
        return;
    }
    
    std::map<std::string, float>::iterator itmp;
    std::map<std::string, float>::iterator last = _exchange.end();
    
    last--;

    for (std::map<std::string, float>::iterator it = _exchange.begin(); it != _exchange.end(); ++it)    {
        if (it->first.substr(0, 4) == date.substr(0,4) && it->first.substr(5, 2) == date.substr(5,2)) {
            if (it == last) {
                std::cout << date << " => " << value << " = " << value * it->second << std::endl;
                return;
            }
            else if (atoi(it->first.substr(8, 2).c_str()) < atoi(date.substr(8, 2).c_str()))    {
                itmp = it;
            }
            else    {
                std::cout << date << " => " << value << " = " << value * it->second << std::endl;
                return;
            }
        }
    }
}
