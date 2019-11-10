#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <cmath>

const double D = 0.115;
const double MU = 4*M_PI*1e-7;
const int N = 10; 

void print_data(std::array<double, N> & tangente, std::array<double, N> & B,
		std::string fname);

int main(void)
{
  std::array<double, N> tangente_15  = {0.10, 0.21, 0.29, 0.38, 0.53, 0.62,
					0.75, 0.81, 0.90, 0.97};
  std::array<double, N> tangente_10 = {0.10, 0.25, 0.36, 0.47, 0.58, 0.65,
				       0.78, 0.84, 0.87, 0.97};
  std::array<double, N> tangente_5 = {0.05, 0.18, 0.23, 0.36, 0.44, 0.53,
				      0.58, 0.67, 0.73, 0.78};
  std::array<double, N> B_15, B_10, B_5 = {0};
  
  for(int ii = 0; ii < N ; ++ii)
    {
      B_15[ii] = ((MU*15)/D)*(0.02*(ii+1))*1e4;
    }
  for(int ii = 0; ii < N ; ++ii)
    {
      B_10[ii] = ((MU*10)/D)*(0.03*(ii+1))*1e4;
    }
  for(int ii = 0; ii < N ; ++ii)
    {
      B_5[ii] = ((MU*5)/D)*(0.05*(ii+1))*1e4;
    }
  print_data(tangente_15, B_15, "terrestre_15.txt");
  print_data(tangente_10, B_10, "terrestre_10.txt");
  print_data(tangente_5, B_5, "terrestre_5.txt");
  
  return 0;
}

void print_data(std::array<double, N> & tangente, std::array<double, N> & B,
		std::string fname)
{
  std::ofstream fout(fname);
  fout.precision(10); fout.setf(std::ios::scientific);
  fout << "# Tangente" << "\t        " << "Campo del Solenoide" << "\n";
  for (int ii = 0; ii < N; ++ii)
    {
      fout << tangente[ii] << "\t" << B[ii] << "\n";
    }
  
}
  
  
