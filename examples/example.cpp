#include "iostream"
#include "math.h"
#include "xs.h"
#include "xs_definitions.h"

using namespace  CRXS;

int main(){
    
    
    std::cout << "XS_definitions::el_pbarp(10)" << std::endl;
    std::cout <<  XS_definitions::el_pbarp(10)  << std::endl;
    
    std::cout << "XS::dEn_DbarA_Dbar_LAB(100, 3, 10, 1, 0)" << std::endl;
    std::cout <<  XS::dEn_DbarA_Dbar_LAB(100, 3, 10, 1, 0)  << std::endl;
    
    
    std::cout << "XS::inv_AA_pbar_LAB(100, 3, 10, 1, 0, 1, 0, 2)" << std::endl;
    std::cout <<  XS::inv_AA_pbar_LAB(100, 3, 10, 1, 0, 1, 0, 2)  << std::endl;
    std::cout << "XS::dE_AA_pbar_LAB_incNbarAndHyperon(100, 3)"   << std::endl;
    std::cout <<  XS::dE_AA_pbar_LAB_incNbarAndHyperon(100, 3)    << std::endl;
    std::cout << "XS::dE_AA_p_LAB(100, 3)"   << std::endl;
    std::cout <<  XS::dE_AA_p_LAB(100, 3)    << std::endl;

    std::cout << "XS::inv_AA_Dbar_LAB(100, 3, 10, 1, 0, 1, 0, 2, 1)" << std::endl;
    std::cout <<  XS::inv_AA_Dbar_LAB(100, 3, 10, 1, 0, 1, 0, 2, 1)  << std::endl;
    
    std::cout << "XS::dEn_AA_Dbar_LAB(100, 10, -1, 0, 1, 0, 2, 1)" << std::endl;
    std::cout <<  XS::dEn_AA_Dbar_LAB(100, 10, -1, 0, 1, 0, 2, 1)  << std::endl;
    
    
};
