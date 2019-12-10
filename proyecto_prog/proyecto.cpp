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
const double H = 0.001;
const double BA = -0.3920;
const double BB = -0.3770;

void initial_conditions(Particle & p, double b);
void force(Particle & p, double t, const std::vector<double> & dV);
void evolve(Particle & p, double t, double dt);
double potential(Particle & p);
void grad_potential(Particle & p, std::vector<double> & dV);
double angle(Particle & p);
void file(const std::vector<double> & rx, const std::vector<double> & ry,
	  const std::vector<double> & ang, double & b, std::string fname);
void save(Particle & p,
	  std::vector<double> & rx, std::vector<double> & ry,
	  std::vector<double> & vx, std::vector<double> & vy,
	  std::vector<double> & fx, std::vector<double> & fy,
	  std::vector<double> & ang);
void start_gnuplot_ang(void);
void gnuplot_ang(void);
void gnuplot_tray(void);
 
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
  std::vector<double> ang = {0};
  std::vector<double> dV(2);

  std::string name;
  Particle p1;
  int count = 1;
  for(b = BA; b < BB; b += H)
    {
      name = "trayectoria_" + std::to_string(count) + ".txt";
      
      initial_conditions(p1, b);
      for(t = 0; t <= TF; t += DT)
	{
	  grad_potential(p1, dV);
	  force(p1, t, dV);
	  evolve(p1, t, DT);
	  save(p1, rx, ry, vx, vy, fx, fy, ang);
	}
      file(rx, ry, ang, b, name);
      rx = {0};
      ry = {0};
      vx = {0};
      vy = {0};
      fx = {0};
      fy = {0};
      ang = {0};
      ++count;
    }
  start_gnuplot_ang();
  gnuplot_ang();
  gnuplot_tray();
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
  if((p.Vx > 0 and p.Vy > 0) or (p.Vx < 0 and p.Vy < 0))
    {
      return (std::acos(p.Vx/std::sqrt(2.0*(0.260*Em-potential(p))/M)))/1.0;
    }
  else if((p.Vx > 0 and p.Vy < 0) or (p.Vx < 0 and p.Vy > 0))
    {
      return (-std::acos(p.Vx/std::sqrt(2.0*(0.260*Em-potential(p))/M)))/1.0;
    }
  else
    {
      return (std::acos(p.Vx/std::sqrt(2.0*(0.260*Em-potential(p))/M)))/1.0;
    }
}

void save(Particle & p,
	  std::vector<double> & rx, std::vector<double> & ry,
	  std::vector<double> & vx, std::vector<double> & vy,
	  std::vector<double> & fx, std::vector<double> & fy,
	  std::vector<double> & ang)
{
  rx.push_back(p.Rx);
  ry.push_back(p.Ry);
  vx.push_back(p.Vx);
  vy.push_back(p.Vx);
  fx.push_back(p.Fx);
  fy.push_back(p.Fy);
  ang.push_back(angle(p));
}

void file(const std::vector<double> & rx, const std::vector<double> & ry,
	  const std::vector<double> & ang, double & b, std::string fname)
{
  std::ofstream fout(fname);
  for(int ii = 0; ii < int(rx.size()); ++ii)
    {
      fout << ii*0.1 << "\t" << rx[ii] << "\t" << ry[ii] << "\t"
	   << ang[ii] << "\t" << b <<  "\n";  
    }
  fout.close();
}

void start_gnuplot_ang(void)
{
  std::cout << "reset" << "\n"
	    << "set term pdf" << "\n"
	    << "set out 'angulo.pdf'" << "\n"
	    << "unset key" << "\n"
	    << "set xrange [0:45]" << "\n"
	    << "set yrange [-3:3]" << "\n"
	    << "set xlabel 't'" << "\n"
	    << "set ylabel '{/Symbol f}(rad)'" << "\n";
}

void gnuplot_ang(void)
{
  std::cout << "plot";
  for(int ii = 1; ii <= int((BB-BA)/H); ++ii)
    {
      std::cout << " 'trayectoria_" << ii << ".txt'"
		<< "u 1:4 w p ls -1  lw 0.001,";
    }
  std::cout <<  "\n";
}

void gnuplot_tray(void)
{
  // Gnuplot para trayectorias
  std::cout << "reset" << "\n"
	    << "set term png" << "\n"
	    << "set out 'trayectoria.png'" << "\n"
	    << "f(x,y) = x**2*y**2*exp(-(x**2+y**2))" << "\n"
	    << "set contour" << "\n"
	    << "set cntrparam levels incre 0.03,0.01,0.13" << "\n"
	    << "set view map" << "\n"
	    << "set isosample 100,100" << "\n"
	    << "unset key" << "\n"
	    << "set xrange [-3:3]" << "\n"
	    << "set yrange [-3:3]" << "\n"
	    << "set xlabel 'x'" <<  "\n"
	    << "set ylabel 'y'" <<  "\n"
	    << "splot f(x,y) lc rgb 'white',"
	    << " 'trayectoria_5.txt'"
	    << " u 2:3:1 lc rgb 'red' lw 0.00001,"
	    << " 'trayectoria_6.txt'"
	    << " u 2:3:1 lc rgb 'cyan' lw 0.00001,"
	    << " 'trayectoria_7.txt'"
	    << " u 2:3:1 lc rgb 'green' lw 0.00001";    
  std::cout << "\n";
}
