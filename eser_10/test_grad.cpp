#include <iostream>
#include <cstdlib> 
#include "gradiente_coniugato.hpp"

int main(int argc, char **argv) 
{
  const double tol = 1.0e-15;
  unsigned int n = 5; 

  Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);
  if (std::abs(B.determinant()) < tol){
	  std::cout<< "fallito";
	  return EXIT_FAILURE;
  }

  Eigen::MatrixXd A = B.transpose() * B;
  Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);
  Eigen::VectorXd b = A * x_ex;
  Eigen::VectorXd x = Eigen::VectorXd::Zero(n);

  const unsigned int it_max = 10000;
  const double res_tol = 1.0e-12;
  double res_frac = 0.0;

  int it = gradiente_coniugato(A, b, x, res_tol, it_max, res_frac);
  
  if (it == -1){
	  std::cout<< "fallito perchè divisione con valore nullo";
  return EXIT_FAILURE;}

  double err_rel = (x_ex.norm() == 0.0) ? (x - x_ex).norm() :
                                          (x - x_ex).norm() / x_ex.norm();

 
  // ho messo lo static cast perchè mi segnalava errore 
  // comparison of integer expressions of different signedness: 'int' and 'unsigned int' [-Wsign-compare]
  if (err_rel <= res_tol && it <= static_cast<int>(n)) {
    std::cout<< "success";
	return EXIT_SUCCESS; 
	
  }
else{
	std::cout<< "fallito";
  return EXIT_FAILURE; 
}
}