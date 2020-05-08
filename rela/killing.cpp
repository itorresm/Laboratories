//Eigen found at: http://eigen.tuxfamily.org/index.php?title=Main_Page#Download
//compile with: g++ -std=c++11 -I /path/to/Eigen killing.cpp
#include <iostream>
#include <Eigen>

double prodint(Eigen::MatrixXd &A, Eigen::MatrixXd &B);
void conm(Eigen::MatrixXd &A, Eigen::MatrixXd &B, Eigen::MatrixXd &C);

int main (void)
{
  Eigen::MatrixXd Jx(4,4);
  Eigen::MatrixXd Jy(4,4);
  Eigen::MatrixXd Jz(4,4);
  Eigen::MatrixXd Kx(4,4);
  Eigen::MatrixXd Ky(4,4);
  Eigen::MatrixXd Kz(4,4);

  Eigen::MatrixXd K(6,6);
  
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
  
  K << prodint(Jx,Jx), prodint(Jx,Jy), prodint(Jx,Jz), prodint(Jx,Kx),
    prodint(Jx,Ky), prodint(Jx,Kz), prodint(Jy,Jx), prodint(Jy,Jy),
    prodint(Jy,Jz), prodint(Jy,Kx), prodint(Jy,Ky), prodint(Jy,Kz),
    prodint(Jz,Jx), prodint(Jz,Jy), prodint(Jz,Jz), prodint(Jz,Kx),
    prodint(Jz,Ky), prodint(Jz,Kz), prodint(Kx,Jx), prodint(Kx,Jy),
    prodint(Kx,Jz), prodint(Kx,Kx), prodint(Kx,Ky), prodint(Kx,Kz),
    prodint(Ky,Jx), prodint(Ky,Jy), prodint(Ky,Jz), prodint(Ky,Kx),
    prodint(Ky,Ky), prodint(Ky,Kz), prodint(Kz,Jx), prodint(Kz,Jy),
    prodint(Kz,Jz), prodint(Kz,Kx), prodint(Kz,Ky), prodint(Kz,Kz);
  Eigen::MatrixXd A;
  conm(Kx,Ky, A);
  std::cout << K << std::endl;
  std::cout << "\n";
  std::cout << K.inverse() << std::endl;
  std::cout << "\n";
  std::cout << A << std::endl;
  
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

void conm(Eigen::MatrixXd &A, Eigen::MatrixXd &B, Eigen::MatrixXd &C)
{
  C = A*B - B*A;
}
