/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:57:08 by ajeanne           #+#    #+#             */
/*   Updated: 2023/10/31 02:25:38 by ajeanne          ###   ########.fr       */
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
#include <deque>

class PmergeMe  {
	public:
		PmergeMe();
		PmergeMe(std::string const & entry, int nbEntry);
		PmergeMe(PmergeMe const & src);
		~PmergeMe();

		PmergeMe    &operator=(PmergeMe const & src);

		std::string         getEntry() const;
		std::string         getSorted() const;
		int			        getNbEntry() const;
		double				getDTime() const;
		double				getVTime() const;
		std::deque<int>     getDNumbers() const;
		std::vector<int>    getVNumbers() const;

		void                checkEntry(std::string const & entry);
		void                fillCont(std::string const & entry);
		
		// For Vector
		void    createPairsV(std::vector<int> & vec);
		std::vector<std::pair<int, int> >    fordJohnsonSortV(std::vector<std::pair<int, int> > & vec);
		void	swapPair(std::pair<int, int> & p);
		void    printResV(std::vector<int> vPrint);
		void    mergeListV(std::vector<int> & vec);
		
		// For Deque
		void    createPairsD(std::deque<int> & vec);
		std::deque<std::pair<int, int> >    fordJohnsonSortD(std::deque<std::pair<int, int> > & vec);
		void    printResD(std::deque<int> dPrint);
		void    mergeListD(std::deque<int> & vec);
		
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
		std::deque<int>     _dNumbers;
		std::vector<int>    _vNumbers;
		std::vector<std::pair<int, int> >    _pairsV;
		std::deque<std::pair<int, int> >     _pairsD;
		double              _dtime;
		double              _vtime;
		
};

#endif