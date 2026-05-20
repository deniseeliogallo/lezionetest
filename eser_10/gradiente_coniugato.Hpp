#pragma once
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <cmath>

double condA(const Eigen::MatrixXd& A)
{
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
  Eigen::VectorXd singularValuesA = svd.singularValues();
  return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}

int gradiente_coniugato(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, Eigen::VectorXd& x, double res_tol, unsigned int it_max, double& res_frac)
{
  Eigen::VectorXd res = b - A * x;
  Eigen::VectorXd p = res;
  
  const double res_norm_0 = res.norm();
  unsigned int it = 0;

  while (it < it_max && res.norm() > res_tol * res_norm_0)
  {
    Eigen::VectorXd Ap = A * p;
    double pAp = p.dot(Ap);
    
    if (pAp == 0.0){
      std::cerr << "Errore: divisione con un fattore nullo!" << std::endl;
      return -1; 
    }
    
    const double alpha_k = (p.dot(res)) / pAp;
    x = x + alpha_k * p;
    res = b - A * x;
    
    double beta_k = (Ap.dot(res)) / pAp;
    p = res - beta_k * p;

    it++;
  }

  // Passiamo indietro il rapporto del residuo 
  res_frac = res.norm() / res_norm_0;
  return it;
}