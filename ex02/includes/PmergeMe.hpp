/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:57:08 by ajeanne           #+#    #+#             */
/*   Updated: 2023/09/27 09:02:18 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <cctype>
#include <sstream>
#include <stdlib.h>
#include <ctime>

class PmergeMe  {
    public:
        PmergeMe();
        PmergeMe(std::string const & entry, int nbEntry);
        PmergeMe(PmergeMe const & src);
        ~PmergeMe();

        PmergeMe    &operator=(PmergeMe const & src);

        std::string         getEntry() const;
        std::list<int>      getLNumbers() const;
        std::vector<int>    getVNumbers() const;

        void                checkEntry(std::string const & entry);
        void                fillCont(std::string const & entry);
        
        // For List
        void                mergeInsertL(std::list<int> & lst);
        void                mergeL(std::list<int> & l, std::list<int> & r, std::list<int> & res);
        void                printResL();
        
        // For Vector
        void                mergeInsertV(std::vector<int> & vec);
        void                mergeV(std::vector<int> & l, std::vector<int> & r, std::vector<int> & res);
        void                printResV();
        
        class UnauthorizedChar : public std::exception {
            public:
                virtual const char* what() const throw()  {
                    return ("Error: '0123456789 ' are the only authorized character.");
                }
        };
        
        class NotInt : public std::exception {
            public:
                virtual const char* what() const throw()  {
                    return ("Error: Only positive integer are authorized.");
                }
        };
    private:
        int                 _nbEntry;
        std::string         _entry;
        std::string         _sorted;
        std::list<int>      _lNumbers;
        std::vector<int>    _vNumbers;
        double              _ltime;
        double              _vtime;
        
};

#endif