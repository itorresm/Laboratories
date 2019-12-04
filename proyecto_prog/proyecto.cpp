#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

struct Particle
{
  double Rx = 0.0, Ry = 0.0;
  double Vx = 0.0, Vy = 0.0;
  double Fx = 0.0, Fy = 0.0;
  double mass = 0.0;
};

const double M = 1.0;
const double Em = 1/std::pow(M_E, 2);
const double TF = 45.0;
const double DT = 0.1;
const double H = 0.01;

void initial_conditions(Particle & p, double b);
void force(Particle & p, double t, const std::vector<double> & dV);
void evolve(Particle & p, double t, double dt);
double potential(Particle & p);
void grad_potential(Particle & p, std::vector<double> & dV);
double angle(Particle & p);
void file(const std::vector<double> & rx, const std::vector<double> & ry,
	  std::string fname);
void save(Particle & p,
	  std::vector<double> & rx, std::vector<double> & ry,
	  std::vector<double> & vx, std::vector<double> & vy,
	  std::vector<double> & fx, std::vector<double> & fy);
	  
int main(void)
{
  double b = 0.0;
  double t = 0.0;

  std::vector<double> rx = {0};
  std::vector<double> ry = {0};
  std::vector<double> vx = {0};
  std::vector<double> vy = {0};
  std::vector<double> fx = {0};
  std::vector<double> fy = {0};
  std::vector<double> dV(2);

  std::string name;
  Particle p1;
  int count = 1;
  for(b = -0.4; b < -0.3; b += H)
    {
      name = "trayectoria_" + std::to_string(count) + ".txt";
      
      initial_conditions(p1, b);
      for(t = 0; t <= TF; t += DT)
	{
	  grad_potential(p1, dV);
	  force(p1, t, dV);
	  evolve(p1, t, DT);
	  save(p1, rx, ry, vx, vy, fx, fy);
	}
      file(rx, ry, name);
      rx = {0};
      ry = {0};
      vx = {0};
      vy = {0};
      fx = {0};
      fy = {0};
      ++count;
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

void save(Particle & p,
	  std::vector<double> & rx, std::vector<double> & ry,
	  std::vector<double> & vx, std::vector<double> & vy,
	  std::vector<double> & fx, std::vector<double> & fy)
{
  rx.push_back(p.Rx);
  ry.push_back(p.Ry);
  vx.push_back(p.Vx);
  vy.push_back(p.Vx);
  fx.push_back(p.Fx);
  fy.push_back(p.Fy);
}

void file(const std::vector<double> & rx, const std::vector<double> & ry,
	  std::string fname)
{
  std::ofstream fout(fname);
  for(int ii = 0; ii < int(rx.size()); ++ii)
    {
      fout << ii*0.1 << "\t" << rx[ii] << "\t" << ry[ii] << "\n";   
    }
  fout.close();
}
