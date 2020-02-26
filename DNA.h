#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
using namespace std;

class DNA{
public:
  DNA();
  DNA(string fname);
  ~DNA();
  int readFile();
  void writeFile();
private:
  string m_fname;
  int m_A;
  int m_G;
  int m_C;
  int m_T;
  int m_sum;
  int m_lines;
  float m_mean;
  float m_variance;
};
