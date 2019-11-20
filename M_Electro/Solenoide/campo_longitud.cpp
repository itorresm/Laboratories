#include <fstream>
#include <cmath>
#include <array>

int main(void)
{
  std::ofstream fout ("campo_longitud.txt");
  const int N = 14;
  double B_teo = ((4*M_PI*1e-7*460*2)/(0.14))*(1e4);
  std::array<double, N> B = {81.0, 93.1, 97.8, 100.2, 100.8, 100.6,
			     100.0, 92.0, 91.5, 90.0, 87.4, 82.2,
			     69.8, 54.8};
  fout.precision(6); fout.setf(std::ios::scientific);
  fout << "# Longitud (m)     Campo Magnetico (G)    B_exp/B_teo" << "\n";
  for (int ii = 0; ii < N; ++ii)
    {
      fout << "  "
	   << (ii-7)/100.0 << "     "
	   << B[ii] << "           "
	   << B[ii]/B_teo << "\n";
    }
  fout.close();
  return 0;
}
