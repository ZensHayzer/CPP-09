/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:05:26 by ajeanne           #+#    #+#             */
/*   Updated: 2023/10/10 15:07:15 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _entry("default"), _sorted("default")    {
	
}

PmergeMe::PmergeMe(std::string const & entry, int nbEntry) : _nbEntry(nbEntry), _entry(entry), _sorted("")   {
	
}

PmergeMe::PmergeMe(PmergeMe const & src)    {
	*this = src;
}

PmergeMe::~PmergeMe()   {
	
}

PmergeMe    &PmergeMe::operator=(PmergeMe const & src)  {
	if (this != &src)   {
		_entry = src.getEntry();
		_lNumbers.insert(_lNumbers.end(), src._lNumbers.begin(), src._lNumbers.end());
		_vNumbers.insert(_vNumbers.end(), src._vNumbers.begin(), src._vNumbers.end());
	}

	return (*this);
}

std::string PmergeMe::getEntry() const  {
	return (_entry);
}

std::list<int>  PmergeMe::getLNumbers() const {
	return (_lNumbers);
}

std::vector<int>    PmergeMe::getVNumbers() const   {
	return (_vNumbers);
}

void    PmergeMe::checkEntry(std::string const & entry)   {
	std::string authorizedChar = "0123456789 ";

	for (size_t i = 0; i < entry.size(); i++)   {
		if (authorizedChar.find(entry[i]) == std::string::npos)
			throw UnauthorizedChar();
	}
}

void    PmergeMe::fillCont(std::string const & entry)   {
	int cnt = 0, tmp = 0;
	std::vector<std::pair<int, int> >   tmp2;
	// clock_t timeUsedS, timeUsedE;
	
	checkEntry(entry);
	for (size_t i = 0; i < entry.size(); i++)   {
		if (i != 0 && isdigit(entry[i - 1]) && entry[i] == ' ') {
			std::istringstream   iss(entry.substr(cnt, i - cnt));
			
			if (iss >> tmp) {
				_lNumbers.push_back(tmp);
				_vNumbers.push_back(tmp);
			}
			else
				throw NotInt();
			if (i + 1 < entry.size())
				cnt = i + 1;
			if (i + 1 < entry.size())
				i++;
		}
	}
	mergeList(_vNumbers);
	//for (std::vector<std::pair<int, int> >::iterator it = tmp2.begin(); it != tmp2.end(); ++it)    {
	//	std::cout << "FIN " << it->first << " " << it->second << std::endl;
	//}
	//std::cout << "////////////////////////////////" << std::endl;
	// std::cout << "Before : " << _entry << std::endl;
	// timeUsedS = clock();
	// printResV(mergeSortV(_vNumbers));
	// timeUsedE = clock();
	// _ltime = static_cast<double>(timeUsedE - timeUsedS) / CLOCKS_PER_SEC * 1000000;
	// timeUsedS = clock();
	// // mergeInsertV(_vNumbers);
	// timeUsedE = clock();
	// _vtime = static_cast<double>(timeUsedE - timeUsedS) / CLOCKS_PER_SEC * 1000000;
	// // printResV();
	// std::cout << "Time to process a range of " << _nbEntry << " elements with std::list : " << _ltime << " us" << std::endl;
	// std::cout << "Time to process a range of " << _nbEntry << " elements with std::vector : " << _vtime << " us" << std::endl;
}

void    PmergeMe::createPairsV(std::vector<int> & vec) {
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
		if (it + 1 != vec.end())    {
			_pairsV.push_back(std::make_pair(*it, *(it + 1)));
			++it;
		}
		else    {
			_pairsV.push_back(std::make_pair(*it, *it));
		}
	}
}

int	tourIN = 0;
int tourOUT = 0;

std::vector<std::pair<int, int> >   PmergeMe::fordJohnsonSort(std::vector<std::pair<int, int> > & vec)   {
	
	std::vector<std::pair<int, int> >   tmp;
	std::vector<std::pair<int, int> >   tmp1;
	std::vector<std::pair<int, int> >   tmp2;
	int                                 iTmp;
	//bool                                imp = false;
	
	//if (vec.size() % 2 > 0)
	//    imp = true;
	tourIN++;
	std::cout << " IN Tour : " << tourIN << std::endl;
	for (std::vector<std::pair<int, int> >::iterator it = vec.begin(); it != vec.end(); ++it)    {
		std::cout << it->first << " " << it->second << std::endl;
	}
	std::cout << "----------------" << std::endl;
	for (size_t i = 0; i < vec.size(); i++)   {
		if (vec[i].first < vec[i].second)   {
			iTmp = vec[i].first;
			vec[i].first = vec[i].second;
			vec[i].second = iTmp;
		}
	}
	
	 if (vec.size() <= 1)    {
		return (vec);
	}
	
	for (size_t i = 0; i < vec.size(); i++)   {
		if (i + 1 < vec.size()) {
			tmp.push_back(std::make_pair(vec[i].first, vec[i + 1].first));
			i++;
		}
		else    {
			tmp.push_back(std::make_pair(vec[i].first, vec[i].first));
		}
	}
	
	tmp1 = fordJohnsonSort(tmp);
	
	tourOUT++;
	
	int tmpSwt = 0;
	
	std::cout << " OUT Tour : " << tourOUT << std::endl;
	for (std::vector<std::pair<int, int> >::iterator it = tmp1.begin(); it != tmp1.end(); ++it)    {
		std::cout << it->first << " " << it->second << std::endl;
	}
	std::cout << "----------------" << std::endl;
	if (vec.size() <= _pairsV.size())   {
		for (std::vector<std::pair<int, int> >::iterator it = tmp1.begin(); it != tmp1.end(); ++it)    {
			if (it + 1 != tmp1.end() && it->second < (it + 1)->second && (it->first != it->second && (it + 1)->first != (it + 1)->second))	{
				tmpSwt = it->second;
				it->second = (it + 1)->second;
				(it + 1)->second = tmpSwt;
			}	
			for (std::vector<std::pair<int, int> >::iterator it1 = vec.begin(); it1 != vec.end(); ++it1)    {
				if (it->first == it1->first)    {
					tmp2.push_back(*it1);
				}
			}
		}
	}
	if (vec.size() <= _pairsV.size())   {
		for (std::vector<std::pair<int, int> >::iterator it = tmp1.begin(); it != tmp1.end(); ++it)    {
			for (std::vector<std::pair<int, int> >::iterator it2 = vec.begin(); it2 != vec.end(); ++it2)    {
				if (it->first != it->second  && it->second == it2->first)    {
					tmp2.push_back(*it2);
				}
			}
		}
	}
	std::cout << " BF return Tour : " << tourOUT << std::endl;
	for (std::vector<std::pair<int, int> >::iterator it = tmp2.begin(); it != tmp2.end(); ++it)    {
		std::cout << it->first << " " << it->second << std::endl;
	}
	std::cout << "----------------" << std::endl;
	return (tmp2);
}

void    PmergeMe::mergeList(std::vector<int> & vec)	{
	std::vector<std::pair<int, int> >	afterFJ;
	std::vector<int>					res;
	
	createPairsV(vec);
	afterFJ = fordJohnsonSort(_pairsV);
	for (std::vector<std::pair<int, int> >::iterator it = afterFJ.begin(); it != afterFJ.end(); ++it)	{
		res.push_back(it->first);
	}
	for (std::vector<std::pair<int, int> >::iterator it = afterFJ.begin(); it != afterFJ.end(); ++it)	{
		for(std::vector<int>::iterator it1 = res.begin(); it1 != res.end(); ++it1)	{
			if (*it1 < it->second && it->first != it->second)	{
				res.insert(it1, it->second);
				break;
			}
			else if (it1 + 1 == res.end() && it->first != it->second)	{
				res.push_back(it->second);
				break;
			}
		}
	}
	printResV(res);
}


void    PmergeMe::printResV(std::vector<int> vPrint) {
	std::string tmp = "";
	
	for (std::vector<int>::iterator it = vPrint.begin(); it != vPrint.end(); ++it)    {
		std::ostringstream  iss;
		iss << *it;
		
		tmp += iss.str();
		tmp += ' ';
	}

	std::cout << "After with std::vector : " << tmp << std::endl;
}