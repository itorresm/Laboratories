#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

void print_data(std::vector<double> & w, std::vector<double> & I,
		std::string fname);
void gnuplot(void);

const int N = 12;

int main(void)
{
  double R = 6000;
  std::vector<double> w(N);
  std::vector<double> I(N);
  std::vector<double> V1 = {0.7, 1.4, 2.0, 2.5, 2.8, 3.0, 3.0, 2.8, 2.7,
			    2.5, 2.4, 2.2};
  std::vector<double> V2 = {0.2, 0.3, 0.5, 0.9, 1.5, 2.3, 1.8, 1.2, 1.0,
			    0.8, 0.7, 0.6};
    
  for(int ii = 0; ii < N; ++ii)
    {
      w[ii] = (150*(ii+1))*2*M_PI/1000;
      I[ii] = (V1[ii]/R)*(1e6) ; 
    }
  print_data(w, I, "osc1.txt");
  R = 1000;
  for(int ii = 0; ii < N; ++ii)
    {
      I[ii] = (V2[ii]/R)*(1e6);
    }
  print_data(w, I, "osc2.txt");
  gnuplot();
  
  return 0;
}

void print_data(std::vector<double> & w, std::vector<double> & I,
		std::string fname)
{
  std::ofstream fout(fname);
  fout.precision(10); fout.setf(std::ios::scientific);
  for(int ii = 0; ii < N; ++ii)
    {
      fout << w[ii] << " " << I[ii] << "\n";
    }
  fout.close();
}

void gnuplot(void)
{
  std::cout << "set term pdf" << "\n"
	    << "set out 'osc1.pdf'" << "\n"
	    << "unset key" << "\n"
	    << "set xlabel '{/Symbol w} (k rad/s)'" << "\n"
	    << "set ylabel 'I ({/Symbol u}A)'" << "\n"
	    << "set xrange [0:13]" << "\n"
	    << "set yrange [0:525]" << "\n"
	    << "f(x) = a*x**2+b*x+c" << "\n"
	    << "fit f(x) 'osc1.txt' u 1:2 via a,b,c" << "\n"
	    << "plot 'osc1.txt' u 1:2 w p ls 6 ps 2 lc rgb 'red',                               f(x) lc rgb 'blue'" << "\n"
    
	    << "reset" << "\n"
	    << "set term pdf" << "\n"
	    << "set out 'osc2.pdf'" << "\n"
	    << "unset key" << "\n"
	    << "set xlabel '{/Symbol w} (k rad/s)'" << "\n"
	    << "set ylabel 'I ({/Symbol u}A)' " << "\n"
	    << "set xrange [0:12]" << "\n"
	    << "set yrange [0:2350]" << "\n"
	    << "f(x) = a*x**2+b*x+c" << "\n"
	    << "fit f(x) 'osc2.txt' u 1:2 via a,b,c" << "\n"
	    << "plot 'osc2.txt' u 1:2 w p ls 6 ps 2 lc rgb 'red',                               f(x) lc rgb 'blue'" << "\n";
}
