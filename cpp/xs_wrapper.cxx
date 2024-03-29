#include "xs_wrapper.h"
#include "xs.h"
#include "crxs.h"
#include "xs_definitions.h"
#include <iostream>


void SetIntegrationMethod( int method ){
    CRXS::CRXS_config::SetupIntegrationMethod(method);
};
void SetTrapezeIntegrationSteps( int steps ){
    CRXS::Integration::SetTrapezeIntegrationSteps( steps );
};

double tot_pp__diMauro(double s){
    return CRXS::XS_definitions::tot_pp__diMauro( s );
};
double el_pp__diMauro (double s){
    return CRXS::XS_definitions::el_pp__diMauro( s );
};


// pbar
double inv_AA_pbar_CM( double s, double xF, double pT_pbar, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization){
    return CRXS::XS::inv_AA_pbar_CM( s, xF, pT_pbar, A_projectile, N_projectile, A_target, N_target, parametrization);
};
double inv_AA_pbar_LAB( double Tn_proj_LAB, double T_pbar_LAB, double eta_LAB, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization ){
    return CRXS::XS::inv_AA_pbar_LAB( Tn_proj_LAB, T_pbar_LAB, eta_LAB, A_projectile, N_projectile, A_target, N_target, parametrization );
};
double dE_AA_pbar_LAB( double Tn_proj_LAB, double T_pbar_LAB, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization){
    return CRXS::XS::dE_AA_pbar_LAB( Tn_proj_LAB, T_pbar_LAB, A_projectile, N_projectile, A_target, N_target, parametrization);
};
double dE_AA_pbar_LAB_incNbarAndHyperon(double Tn_proj_LAB, double T_pbar_LAB, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization){
    return CRXS::XS::dE_AA_pbar_LAB_incNbarAndHyperon( Tn_proj_LAB,  T_pbar_LAB, A_projectile, N_projectile, A_target, N_target, parametrization);
};

void SetRestrictedParameterSpace_LAB( double Tp, double Tpbar, double eta ){
    CRXS::XS::SetRestrictedParameterSpace_LAB( Tp, Tpbar, eta );
};
void RemoveRestrictedParameterSpace_LAB(  ){
    CRXS::XS::RemoveRestrictedParameterSpace_LAB(  );
};

void SetRestrictedParameterSpace_CM( double s, double xF, double pT ){
    CRXS::XS::SetRestrictedParameterSpace_CM( s, xF, pT );
};
void RemoveRestrictedParameterSpace_CM(  ){
    CRXS::XS::RemoveRestrictedParameterSpace_CM(  );
};

void SetRestricted_pp( bool is_pp ){
    CRXS::XS::SetRestricted_pp( is_pp );
};



// Dbar
double inv_AA_Dbar_CM( double s, double xF_Dbar, double pT_Dbar, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization, int coalescence){
    return CRXS::XS::inv_AA_Dbar_CM( s, xF_Dbar, pT_Dbar, A_projectile, N_projectile, A_target, N_target, parametrization, coalescence);
};
double inv_AA_Dbar_LAB( double Tn_proj_LAB, double Tn_Dbar_LAB, double eta_LAB, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization, int coalescence){
    return CRXS::XS::inv_AA_Dbar_LAB( Tn_proj_LAB, Tn_Dbar_LAB, eta_LAB, A_projectile, N_projectile, A_target, N_target, parametrization, coalescence);
};
double dEn_AA_Dbar_LAB( double Tn_proj_LAB, double Tn_Dbar_LAB, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization, int coalescence ){
    return CRXS::XS::dEn_AA_Dbar_LAB( Tn_proj_LAB, Tn_Dbar_LAB, A_projectile, N_projectile, A_target, N_target, parametrization, coalescence );
};

double dEn_DbarA_Dbar_LAB( double Tn_proj_LAB, double Tn_Dbar_LAB, int A_target, int N_target, int parametrization ){
    return CRXS::XS::dEn_DbarA_Dbar_LAB( Tn_proj_LAB, Tn_Dbar_LAB, A_target, N_target, parametrization );
};

// p
double inv_AA_p_CM( double s, double xF, double pT_p, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization){
    return CRXS::XS::inv_AA_p_CM( s, xF, pT_p, A_projectile, N_projectile, A_target, N_target, parametrization);
};
double inv_AA_p_LAB( double Tn_proj_LAB, double T_p_LAB, double eta_LAB, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization ){
    return CRXS::XS::inv_AA_p_LAB( Tn_proj_LAB, T_p_LAB, eta_LAB, A_projectile, N_projectile, A_target, N_target, parametrization );
};
double dE_AA_p_LAB( double Tn_proj_LAB, double T_p_LAB, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization){
    return CRXS::XS::dE_AA_p_LAB( Tn_proj_LAB, T_p_LAB, A_projectile, N_projectile, A_target, N_target, parametrization);
};

void set_C_winkler_self(double* C_array, int len_C_array){
    for (int i=0; i<len_C_array; i++) {
        std::cout << CRXS::XS_definitions::XS_definitions::Winkler_SELF_C1_to_C16[i] << std::endl;
        CRXS::XS_definitions::XS_definitions::Winkler_SELF_C1_to_C16[i] = C_array[i];
    }
};

void set_D_winkler_self(double* D_array, int len_D_array){
    for (int i=0; i<len_D_array; i++) {
        CRXS::XS_definitions::XS_definitions::Winkler_SELF_D1_to_D2[i] = D_array[i];
    }
};
