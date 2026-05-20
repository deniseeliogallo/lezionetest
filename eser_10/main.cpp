#include <iostream>
#include "gradiente_coniugato.hpp" 

int main(int argc, char **argv) 
{
  const double tol = 1.0e-15;
  unsigned int n = 3;

  Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);
  if (std::abs(B.determinant()) < tol)
    return -1;

  Eigen::MatrixXd A = B.transpose() * B;
  Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);
  Eigen::VectorXd b = A * x_ex;

  Eigen::VectorXd x = Eigen::VectorXd::Zero(n);
  
  const unsigned int it_max = 10000;
  const double res_tol = 1.0e-12;
  double res_frac = 0.0;

  std::cout.precision(2);
  std::cout << std::scientific << "Matrix Cond: " << condA(A) << std::endl;

  
  int it = gradiente_coniugato(A, b, x, res_tol, it_max, res_frac);
  if (it == -1) return -1;

  const auto err_rel = (x_ex.norm() == 0.0) ? (x - x_ex).norm() :
                                              (x - x_ex).norm() / x_ex.norm();

  std::cout.precision(4);
  std::cout << std::scientific << "it/it_max: " << it << "/" << it_max << std::endl;
  std::cout << std::scientific << "res/res_tol: " << res_frac << "/" << res_tol << std::endl;
  std::cout << std::scientific << "err_rel: " << err_rel << std::endl;
  std::cout << std::scientific << "soluzione:\n" << x << std::endl;

  return 0;
}