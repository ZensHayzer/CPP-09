/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:05:26 by ajeanne           #+#    #+#             */
/*   Updated: 2023/09/27 09:16:11 by ajeanne          ###   ########.fr       */
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
    clock_t timeUsedS, timeUsedE;
    
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
    std::cout << "Before : " << _entry << std::endl;
    timeUsedS = clock();
    mergeInsertL(_lNumbers);
    timeUsedE = clock();
    _ltime = static_cast<double>(timeUsedE - timeUsedS) / CLOCKS_PER_SEC * 1000000;
    printResL();
    timeUsedS = clock();
    mergeInsertV(_vNumbers);
    timeUsedE = clock();
    _vtime = static_cast<double>(timeUsedE - timeUsedS) / CLOCKS_PER_SEC * 1000000;
    printResV();
    std::cout << "Time to process a range of " << _nbEntry << " elements with std::list : " << _ltime << " us" << std::endl;
    std::cout << "Time to process a range of " << _nbEntry << " elements with std::list : " << _vtime << " us" << std::endl;
}

void    PmergeMe::mergeInsertL(std::list<int> & lst)   {
    if (lst.size() <= 1) {
        return;
    }
    
    std::list<int>  l;
    std::list<int>  r;
    std::list<int>::iterator    it = lst.begin();

    advance(it, lst.size() / 2);
    l.assign(lst.begin(), it);
    r.assign(it, lst.end());
    mergeInsertL(l);
    mergeInsertL(r);
    lst.clear();
    mergeL(l, r, lst);
}

void    PmergeMe::mergeL(std::list<int> & l, std::list<int> & r, std::list<int> & res) {
    std::list<int>::iterator    itL = l.begin();
    std::list<int>::iterator    itR = r.begin();
    
    while(itL != l.end() && itR != r.end()) {
        if (*itL < *itR) {
            res.push_back(*itL);
            ++itL;
        }
        else    {
            res.push_back(*itR);
            ++itR;
        }
    }
    res.insert(res.end(), itL, l.end());
    res.insert(res.end(), itR, r.end());
}

void    PmergeMe::printResL()   {
    std::string         res;
    
    for (std::list<int>::iterator it = _lNumbers.begin(); it != _lNumbers.end(); ++it)  {
        std::stringstream   oss;

        oss << *it;
        res += oss.str();
        res += " ";
    }
    std::cout << "After List : " << res << std::endl;
}

void    PmergeMe::mergeInsertV(std::vector<int> & vec)  {
    if (vec.size() <= 1)    {
        return;
    }

    std::vector<int>    l;
    std::vector<int>    r;
    std::vector<int>::iterator  it = vec.begin();

    advance(it, vec.size() / 2);
    l.assign(vec.begin(), it);
    r.assign(it, vec.end());
    mergeInsertV(l);
    mergeInsertV(r);
    vec.clear();
    mergeV(l, r, vec);
}

void    PmergeMe::mergeV(std::vector<int> & l, std::vector<int> & r, std::vector<int> & res)    {
    std::vector<int>::iterator  itL = l.begin();
    std::vector<int>::iterator  itR = r.begin();
    
    while (itL != l.end() && itR != r.end())    {
        if (*itL < *itR)    {
            res.push_back(*itL);
            itL++;
        }
        else    {
            res.push_back(*itR);
            ++itR;
        }
    }
    res.insert(res.end(), itL, l.end());
    res.insert(res.end(), itR, r.end());
}

void    PmergeMe::printResV()   {
    std::string         res;
    
    for (std::vector<int>::iterator it = _vNumbers.begin(); it != _vNumbers.end(); ++it)  {
        std::stringstream   oss;

        oss << *it;
        res += oss.str();
        res += " ";
    }
    std::cout << "After Vector : " << res << std::endl;
}