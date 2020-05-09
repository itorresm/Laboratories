//Eigen found at: http://eigen.tuxfamily.org/index.php?title=Main_Page#Download
//compile with: g++ -std=c++11 -I /path/to/Eigen killing.cpp
#include <iostream>
#include <Eigen>

double prodint(Eigen::MatrixXd &A, Eigen::MatrixXd &B);
void change(int a, Eigen::MatrixXd &C);
Eigen::MatrixXd conm(Eigen::MatrixXd &A, Eigen::MatrixXd &B);


int main (void)
{
  Eigen::MatrixXd K(6,6);
  Eigen::MatrixXd A, B;
  Eigen::MatrixXd C, D;

  K.array();
  for(int ii = 0; ii < 6; ++ii)
    {
      change(ii, A);
      for(int jj = 0; jj < 6; ++ jj)
	{
	  change(jj, B);
	  K(6*ii+jj) = prodint(A,B);
	}
    }
  
  std::cout << "Metrica de Killing" << "\n" << K << "\n \n"
   	    << "Metrica inversa de Killing" << "\n" << K.inverse() << "\n \n";
    
  for(int ii = 0; ii < 6; ++ii)
    {
      change(ii, C);
      for(int jj = 0; jj < 6; ++ jj)
	{
	  change(jj, D);
	  std::cout << conm(C,D) << "\n" <<  std::endl;
	}
    }

    return 0;
}

double prodint(Eigen::MatrixXd &A, Eigen::MatrixXd &B)
{
  double t = 0;
  Eigen::MatrixXd C;
  C = A*B;
  t = C.trace();
  return t/2.0;
}

Eigen::MatrixXd conm(Eigen::MatrixXd &A, Eigen::MatrixXd &B)
{
  return A*B - B*A;
}
void change(int a, Eigen::MatrixXd &C)
{
  Eigen::MatrixXd Jx(4,4);
  Eigen::MatrixXd Jy(4,4);
  Eigen::MatrixXd Jz(4,4);
  Eigen::MatrixXd Kx(4,4);
  Eigen::MatrixXd Ky(4,4);
  Eigen::MatrixXd Kz(4,4);
  
  Jx << 0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 1,
    0, 0, -1, 0;
  
  Jy << 0, 0, 0, 0,
    0, 0, 0, -1,
    0, 0, 0, 0,
    0, 1, 0, 0;
  
  Jz << 0, 0, 0, 0,
    0, 0, 1, 0,
    0, -1, 0, 0,
    0, 0, 0, 0;
  
  Kx << 0, -1, 0, 0,
    -1, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0;
  
  Ky << 0, 0, -1, 0,
    0, 0, 0, 0,
    -1, 0, 0, 0,
    0, 0, 0, 0;
  
  Kz << 0, 0, 0, -1,
    0, 0, 0, 0,
    0, 0, 0, 0,
    -1, 0, 0, 0;
  
  if (a == 0) C = Jx;
  if (a == 1) C = Jy;
  if (a == 2) C = Jz;
  if (a == 3) C = Kx;
  if (a == 4) C = Ky;
  if (a == 5) C = Kz;
}
