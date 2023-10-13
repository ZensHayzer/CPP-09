/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:57:08 by ajeanne           #+#    #+#             */
/*   Updated: 2023/10/06 18:46:51 by ajeanne          ###   ########.fr       */
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
#include <utility>

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
		
		// For Vector
		void    createPairsV(std::vector<int> & vec);
		std::vector<std::pair<int, int> >    fordJohnsonSort(std::vector<std::pair<int, int> > & vec);
		void    printResV(std::vector<int> vPrint);
		void    mergeList(std::vector<int> & vec);
		
		// For List
		void    mergeL(std::vector<int> & vec, int left, int mid, int right);
		void    divSortL(std::vector<int> & vec, int left, int right);
		void    mergeSortL(std::vector<int> & vec);
		void    printResL();
		
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
		std::vector<std::pair<int, int> >    _pairsV;
		double              _ltime;
		double              _vtime;
		
};

#endif