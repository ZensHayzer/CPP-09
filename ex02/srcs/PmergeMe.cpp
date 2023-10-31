/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:05:26 by ajeanne           #+#    #+#             */
/*   Updated: 2023/10/31 02:27:50 by ajeanne          ###   ########.fr       */
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
		_pairsV.insert(_pairsV.end(), src._pairsV.begin(), src._pairsV.end());
		_pairsD.insert(_pairsD.end(), src._pairsD.begin(), src._pairsD.end());
		_dNumbers.insert(_dNumbers.end(), src._dNumbers.begin(), src._dNumbers.end());
		_vNumbers.insert(_vNumbers.end(), src._vNumbers.begin(), src._vNumbers.end());
		_nbEntry = src.getNbEntry();
		_vtime = src.getVTime();
		_dtime = src.getDTime();
	}

	return (*this);
}

std::string PmergeMe::getEntry() const  {
	return (_entry);
}

std::string PmergeMe::getSorted() const  {
	return (_sorted);
}

int PmergeMe::getNbEntry() const  {
	return (_nbEntry);
}

double PmergeMe::getDTime() const  {
	return (_dtime);
}

double PmergeMe::getVTime() const  {
	return (_vtime);
}

std::deque<int>  PmergeMe::getDNumbers() const {
	return (_dNumbers);
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
	clock_t timeUsedS, timeUsedE;
	(void)_nbEntry;
	
	checkEntry(entry);
	for (size_t i = 0; i < entry.size(); i++)   {
		if (i != 0 && isdigit(entry[i - 1]) && entry[i] == ' ') {
			std::istringstream   iss(entry.substr(cnt, i - cnt));
			
			if (iss >> tmp) {
				_dNumbers.push_back(tmp);
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
	timeUsedS = clock();
	mergeListV(_vNumbers);
	timeUsedE = clock();
	_vtime = static_cast<double>(timeUsedE - timeUsedS) / CLOCKS_PER_SEC * 1000000;
	timeUsedS = clock();
	mergeListD(_dNumbers);
	timeUsedE = clock();
	_dtime = static_cast<double>(timeUsedE - timeUsedS) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process a range of " << _nbEntry << " elements with std::list : " << _vtime << " us" << std::endl;
	std::cout << "Time to process a range of " << _nbEntry << " elements with std::vector : " << _dtime << " us" << std::endl;
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

void    PmergeMe::createPairsD(std::deque<int> & vec) {
	for (std::deque<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
		if (it + 1 != vec.end())    {
			_pairsD.push_back(std::make_pair(*it, *(it + 1)));
			++it;
		}
		else    {
			_pairsD.push_back(std::make_pair(*it, *it));
		}
	}
}

void	PmergeMe::swapPair(std::pair<int, int> & p)	{
	int	tmp;

	tmp = p.first;
	p.first = p.second;
	p.second = tmp;
}

std::vector<std::pair<int, int> >   PmergeMe::fordJohnsonSortV(std::vector<std::pair<int, int> > & vec)   {
	std::vector<std::pair<int, int> >   tmp;
	std::vector<std::pair<int, int> >   tmp1;
	std::vector<std::pair<int, int> >   tmp2;
	std::pair<int, int>   last;

	// Swap pair
	for (std::vector<std::pair<int, int> >::iterator it = vec.begin(); it != vec.end(); ++it)	{
		if (it->first < it->second)
			swapPair(*it);
	}

	if (vec.size() <= 1)
		return (vec);
	
	// Make pairs of first
	for (std::vector<std::pair<int, int> >::iterator it = vec.begin(); it != vec.end(); ++it)	{
		if (it + 1 != vec.end())	{
			tmp.push_back(std::make_pair(it->first, (it + 1)->first));
			++it;
		}
	}
	
	tmp1 = fordJohnsonSortV(tmp);
	
	for (std::vector<std::pair<int, int> >::iterator it = tmp1.begin(); it != tmp1.end(); ++it)	{
		for (std::vector<std::pair<int, int> >::iterator itf = vec.begin(); itf != vec.end(); ++itf)	{
			if (it->first == itf->first)	{
				tmp2.push_back(*itf);
				break;
			}
		}
	}
	for (std::vector<std::pair<int, int> >::iterator it = tmp1.begin(); it != tmp1.end(); ++it)	{
		if (it->first != it->second)	{
			for (std::vector<std::pair<int, int> >::iterator it1 = tmp2.begin(); it1 != tmp1.end(); ++it1)	{
				if (it1 == tmp2.end())	{
					for (std::vector<std::pair<int, int> >::iterator it2 = vec.begin(); it2 != vec.end(); ++it2)	{
						if (it->second == it2->first)	{
							tmp2.push_back(*it2);
							break;
						}
					}
					break;
				}
				else if (it->second > it1->first)	{
					for (std::vector<std::pair<int, int> >::iterator it2 = vec.begin(); it2 != vec.end(); ++it2)	{
						if (it->second == it2->first)	{
							tmp2.insert(it1, *it2);
							break;
						}
					}
					break;
				}
			}
		}
	}
	if (vec.size() % 2 == 1)	{
		last = vec[vec.size() - 1];
		for (std::vector<std::pair<int, int> >::iterator it = tmp2.begin(); it != tmp2.end(); ++it)	{
			if (it + 1 == tmp2.end())	{
				tmp2.push_back(last);
				break;
			}
			else if (it->first < last.first)	{
				tmp2.insert(it, last);
				break;
			}
		}
	}

	return (tmp2);
}

std::deque<std::pair<int, int> >   PmergeMe::fordJohnsonSortD(std::deque<std::pair<int, int> > & vec)   {
	std::deque<std::pair<int, int> >   tmp;
	std::deque<std::pair<int, int> >   tmp1;
	std::deque<std::pair<int, int> >   tmp2;
	std::pair<int, int>   last;

	// Swap pair
	for (std::deque<std::pair<int, int> >::iterator it = vec.begin(); it != vec.end(); ++it)	{
		if (it->first < it->second)
			swapPair(*it);
	}

	if (vec.size() <= 1)
		return (vec);
	
	// Make pairs of first
	for (std::deque<std::pair<int, int> >::iterator it = vec.begin(); it != vec.end(); ++it)	{
		if (it + 1 != vec.end())	{
			tmp.push_back(std::make_pair(it->first, (it + 1)->first));
			++it;
		}
	}
	
	tmp1 = fordJohnsonSortD(tmp);
	
	for (std::deque<std::pair<int, int> >::iterator it = tmp1.begin(); it != tmp1.end(); ++it)	{
		for (std::deque<std::pair<int, int> >::iterator itf = vec.begin(); itf != vec.end(); ++itf)	{
			if (it->first == itf->first)	{
				tmp2.push_back(*itf);
				break;
			}
		}
	}
	for (std::deque<std::pair<int, int> >::iterator it = tmp1.begin(); it != tmp1.end(); ++it)	{
		if (it->first != it->second)	{
			for (std::deque<std::pair<int, int> >::iterator it1 = tmp2.begin(); it1 != tmp1.end(); ++it1)	{
				if (it1 == tmp2.end())	{
					for (std::deque<std::pair<int, int> >::iterator it2 = vec.begin(); it2 != vec.end(); ++it2)	{
						if (it->second == it2->first)	{
							tmp2.push_back(*it2);
							break;
						}
					}
					break;
				}
				else if (it->second > it1->first)	{
					for (std::deque<std::pair<int, int> >::iterator it2 = vec.begin(); it2 != vec.end(); ++it2)	{
						if (it->second == it2->first)	{
							tmp2.insert(it1, *it2);
							break;
						}
					}
					break;
				}
			}
		}
	}
	if (vec.size() % 2 == 1)	{
		last = vec[vec.size() - 1];
		std::cout << "LAST = " << last.first << " " << last.second << std::endl;
		for (std::deque<std::pair<int, int> >::iterator it = tmp2.begin(); it != tmp2.end(); ++it)	{
			if (it + 1 == tmp2.end())	{
				tmp2.push_back(last);
				break;
			}
			else if (it->first < last.first)	{
				tmp2.insert(it, last);
				break;
			}
		}
	}

	return (tmp2);
}

void    PmergeMe::mergeListV(std::vector<int> & vec)	{
	std::vector<std::pair<int, int> >	afterFJ;
	std::vector<int>					res;
	
	createPairsV(vec);
	afterFJ = fordJohnsonSortV(_pairsV);
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

void    PmergeMe::mergeListD(std::deque<int> & vec)	{
	std::deque<std::pair<int, int> >	afterFJ;
	std::deque<int>					res;
	
	createPairsD(vec);
	afterFJ = fordJohnsonSortD(_pairsD);
	for (std::deque<std::pair<int, int> >::iterator it = afterFJ.begin(); it != afterFJ.end(); ++it)	{
		res.push_back(it->first);
	}
	for (std::deque<std::pair<int, int> >::iterator it = afterFJ.begin(); it != afterFJ.end(); ++it)	{
		for(std::deque<int>::iterator it1 = res.begin(); it1 != res.end(); ++it1)	{
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
	printResD(res);
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

void    PmergeMe::printResD(std::deque<int> vPrint) {
	std::string tmp = "";
	
	for (std::deque<int>::iterator it = vPrint.begin(); it != vPrint.end(); ++it)    {
		std::ostringstream  iss;
		iss << *it;
		
		tmp += iss.str();
		tmp += ' ';
	}

	std::cout << "After with std::deque : " << tmp << std::endl;
}