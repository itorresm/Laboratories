#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

struct Particle
{
  double Rx = 0.0, Ry = 0.0;
  double Vx = 0.0, Vy = 0.0;
  double Fx = 0.0, Fy = 0.0;
  double mass = 0.0;
};

const double M = 1.0;
const double Em = 1/std::pow(M_E, 2);
const double TF = 40.1;
const double DT = 0.1;
const double H = 1;

void initial_conditions(Particle & p, double b);
void force(Particle & p, double t, const std::vector<double> & dV);
void evolve(Particle & p, double t, double dt);
void print(Particle & p, double t);
double potential(Particle & p);
void grad_potential(Particle & p, std::vector<double> & dV);
double angle(Particle & p); 

int main(void)
{
  //std::cout.precision(10); std::cout.setf(std::ios::scientific);
  double b = -0.3905;
  double t = 0.0;
  std::vector<double> dV(2);
  
  Particle p1;
  initial_conditions(p1, b);
  for(t = 0; t <= TF; t += DT)
    {
      grad_potential(p1, dV);
      force(p1, t, dV);
      evolve(p1, t, DT);
      print(p1, t);
    }
  return 0;
}

void initial_conditions(Particle & p, double b)
{
  p.mass = M;
  p.Rx = 3.0;
  p.Ry = b;
  p.Vx = -std::sqrt(2.0*(0.260*Em-potential(p))/M);
  p.Vy = 0.0;
}

void force(Particle & p, double t, const std::vector<double> & dV)
{
  p.Fx = p.Fy = 0.0;

  p.Fx += -dV[0];
  p.Fy += -dV[1];
}

void evolve(Particle & p, double t, double dt)
{
  p.Rx = p.Rx + p.Vx*dt + p.Fx*dt*dt/(2.0*p.mass);
  p.Ry = p.Ry + p.Vy*dt + p.Fy*dt*dt/(2.0*p.mass);

  p.Vx = p.Vx + p.Fx*dt/(p.mass);
  p.Vy = p.Vy + p.Fy*dt/(p.mass);
}

void print(Particle & p, double t)
{
  std::cout << t << "\t"
	    << p.Rx << "\t"
	    << p.Ry << "\t"
	    << p.Vx << "\t"
	    << p.Vy << "\t"
	    << p.Fx << "\t"
	    << p.Fy << "\t"
	    << angle(p) << "\t"
	    << p.mass << "\n";
}

double potential(Particle & p)
{
  return p.Rx*p.Rx*p.Ry*p.Ry*std::pow(M_E, -(p.Rx*p.Rx+p.Ry*p.Ry));
}

void grad_potential(Particle & p, std::vector<double> & dV)
{
  dV[0]=2.0*p.Rx*p.Ry*p.Ry*std::pow(M_E,-(p.Rx*p.Rx+p.Ry*p.Ry))*(1-p.Rx*p.Rx);  
  dV[1]=2.0*p.Rx*p.Rx*p.Ry*std::pow(M_E,-(p.Rx*p.Rx+p.Ry*p.Ry))*(1-p.Ry*p.Ry);
}

double angle(Particle & p)
{
  return (std::acos(p.Vx/std::sqrt(2.0*(0.260*Em-potential(p))/M)))*180/M_PI;
}
