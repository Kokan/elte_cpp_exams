#include <iostream>
#include "amatrix.h"
#include <string>
#include <algorithm>

struct Subjects
{
  int max;

  Subjects():max(0) {}

  void operator()(const std::pair<char, int>& p)
  {
    std::cout << ' ' << p.first
              << ":" << p.second
              << std::endl;
    if (p.second > max)
      max = p.second;
  }
};

struct Print
{
  int best;

  Print():best(0) {}

  template <class Element>
  void operator()(const Element& e)
  {
     std::cout << e.first << ":" << std::endl;
     int i = std::for_each(e.second.begin(), e.second.end(), Subjects()).max;
     if (i > best)
       best = i;
  }


};

const int max = 10000;

int main()
{
  int yourMark = 1;
  /* 2-es
  AssocMatrix<std::string, char, int> my_marks;
  my_marks.insert("Analizis", 'g', 4);
  my_marks.insert("Analizis", 'e', 5);
  my_marks.insert("C++", 'g', 2);
  const AssocMatrix<std::string, char, int> cmarks = my_marks;
  
  AssocMatrix<int, int, double> test;
  for(int i = 0; i < max; ++i)
    test.insert(i, i, 5.2);
  
  yourMark = cmarks.rows();
  */
  /* 3-as
  AssocMatrix<std::string, char, int> test2;
  for(int i = 0; i <= max; ++i)
    test2.insert("Testing", 'T', i);
  
  if (4 == cmarks.at("Analizis", 'g') && 
      max == test2.at("Testing", 'T'))
  {
    ++my_marks("C++",'g'); 
    yourMark = test2.rows() + my_marks.rows();
  }
  */
  /* 4-es
  if (2 == cmarks("C++",'g'))
    yourMark = cmarks.cols() + my_marks.cols();
  */
  /* 5-os
  yourMark = std::for_each(cmarks.begin(), cmarks.end(), Print()).best;
  std::endl(std::cout);
  */
  std::cout << "Your mark is " << yourMark << std::endl;
}
