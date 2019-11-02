#include <fstream>
#include <cmath>
#include <array>

int main (void)
{
  const int N = 10;
  std::ofstream fout("solenoide.txt");
  //fout << "Corriente (A)" << "\t" << "Campo (G)" << "\n";
  std::array<double, N> campo = {15.0, 29.2, 43.5,
				 56.6, 77.6, 87.8, 100.9, 115.2, 133.4, 148.1};
  for (int ii = 0; ii < N; ++ii)
    {
      fout << ii*0.3 + 0.3 << "\t" << campo[ii] << "\n";
    }
  fout.close();
  return 0;
}

