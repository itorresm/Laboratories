#include <iostream>
#include <cmath>
#include <vector>

const double M = 1.0;
const double Em = 1.0/(std::pow(M_E, 2));

void rk4(std::vector<double> & data, double t, double h);
double f(const std::vector<double> & r, int id);

int main(void)
{
  double b = 0.0;
  std::vector<double> r = {0, b};
  return 0;
}

void rk4(std::vector<double> & data, double t, double h)
{
  std::vector<double> k1, k2, k3, k4, aux;
  k1.resize(data.size());
  k2.resize(data.size());
  k3.resize(data.size());
  k4.resize(data.size());
  aux.resize(data.size());
  // k1
  for(int ii = 0; ii < data.size(); ++ii)
    {
      k1[ii] = h*f(ii, t, data);
    }
  // k2 aux
  for(int ii = 0; ii < data.size(); ++ii)
    {
      aux[ii] = data[ii] + k1[ii]/2;
    }
  //k2
  for(int ii = 0; ii < data.size(); ++ii)
    {
      k2[ii] = h*f(ii, t + h/2, aux);
    }
  // k3 aux
  for(int ii = 0; ii < data.size(); ++ii)
    {
      aux[ii] = data[ii] + k2[ii]/2;
    }
  //k3
  for(int ii = 0; ii < data.size(); ++ii)
    {
      k3[ii] = h*f(ii, t + h/2, aux);
    }
  // k4 aux
  for(int ii = 0; ii < data.size(); ++ii)
    {
      aux[ii] = data[ii] + k3[ii];
    }
  //k4
  for(int ii = 0; ii < data.size(); ++ii)
    {
      k4[ii] = h*f(ii, t + h, aux);
    }
  // write new data
  for(int ii = 0; ii < data.size(); ++ii)
    {
      data[ii] = data[ii] + (k1[ii] + 2*k2[ii] + 2*k3[ii] + k4[ii])/6.0;
    }
}

double f(const std::vector<double> & r, int id, fptr devpot)
{
  if (id == 0)
    {
      return r[1];
    }
  else if (id == 1)
    {
      return -devpot()/M;
    }
}
