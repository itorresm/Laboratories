#include <iostream>
#include <cmath>
#include <vector>

const double M = 1.0;
const double Em = 1.0/(std::pow(M_E, 2));

void rk4(std::vector<double> & data, double h, double t, int c);
double f(const std::vector<double> & data, int id, double t, int c);
double potential(const std::vector<double> & r);
void grad_potential(const std::vector<double> & r, std::vector<double> & dV);
double mag(std::vector<double> & v);

int main(void)
{
  std::cout.precision(16); std::cout.setf(std::ios::scientific);
  double b = 0.0;
  //for(double b = -3; b <= 3; ++b)
  //{
      const double T = 6;
      const double H = 1;
      const double X0 = 3;
      const double Y0 = b;
      const double VX0 = 0;
      const double VY0 = std::sqrt(2.0*((0.260*Em)-potential(data))/M);
      std::vector<double> r????????????
	???????????????????
      std::vector<double> data = {X0, VX0};
      rk4(data, H, T, r, 1);
      std::cout << "\t"; 
      data = {Y0, V0};
      rk4(data, H, T, r, 1);
      //}
  //std::cout << f(data, 1, T, r, 0) << " " << f(data, 1, T, r, 1) << std::endl;
  return 0;
}
  
void rk4(std::vector<double> & data, double h, double t, int c)
{
 std::vector<double> k1, k2, k3, k4, aux;
  k1.resize(data.size());
  k2.resize(data.size());
  k3.resize(data.size());
  k4.resize(data.size());
  aux.resize(data.size());

  const int N = (t)/h;
  for (int nt = 0; nt < N; ++nt)
    {
      double t = h*nt;
      // k1
      for(int ii = 0; ii < int(data.size()); ++ii)
	{
	  k1[ii] = h*f(data, ii, t, c);
	}
      // k2 aux
      for(int ii = 0; ii < int(data.size()); ++ii)
	{
	  aux[ii] = data[ii] + k1[ii]/2;
	}
      //k2
      for(int ii = 0; ii < int(data.size()); ++ii)
	{
	  k2[ii] = h*f(aux, ii, t + h/2, c);
	}
      // k3 aux
      for(int ii = 0; ii < int(data.size()); ++ii)
	{
	  aux[ii] = data[ii] + k2[ii]/2;
	}
      //k3
      for(int ii = 0; ii < int(data.size()); ++ii)
	{
	  k3[ii] = h*f(aux, ii, t + h/2, c);
	}
      // k4 aux
      for(int ii = 0; ii < int(data.size()); ++ii)
	{
	  aux[ii] = data[ii] + k3[ii];
	}
      //k4
      for(int ii = 0; ii < int(data.size()); ++ii)
	{
	  k4[ii] = h*f(aux, ii, t + h, c);
	}
      // write new y
      for(int ii = 0; ii < int(data.size()); ++ii)
	{
	  data[ii] = data[ii] + (k1[ii] + 2*k2[ii] + 2*k3[ii] + k4[ii])/6.0;
	}
      std::cout << data[0] << std::endl;
    }
}

double f(const std::vector<double> & data, int id, double t, int c)
{
  std::vector<double> dV(2);
  grad_potential(data, dV);
  if (id == 0)
    {
      return data[1];
    }
  else if (id == 1)
    {
      return -dV[c]/M;
    }
  else
    {
      std::cerr << "Error!!!!!!! Id does not exist -> " << id << std::endl;
      exit(1);
    }
}

double potential(const std::vector<double> & r)
{
  return r[0]*r[0]*r[1]*r[1]*std::pow(M_E, -(r[0]*r[0]+r[1]*r[1]));
}
 
void grad_potential(const std::vector<double> & r, std::vector<double> & dV)
{
  dV[0] = 2.0*r[0]*r[1]*r[1]*std::pow(M_E, -(r[0]*r[0]+r[1]*r[1]))*(1-r[0]*r[0]);  
  dV[1] = 2.0*r[0]*r[0]*r[1]*std::pow(M_E, -(r[0]*r[0]+r[1]*r[1]))*(1-r[1]*r[1]);
}

double mag(std::vector<double> & v)
{
  double sum = 0.0;
  for(const auto x : v)
    {
      sum += std::pow(x, 2);
    }
  return std::sqrt(sum);
}
