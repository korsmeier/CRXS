#ifndef CRXS__XS_H
#define CRXS__XS_H

#include "linAlg_tools.h"

namespace CRXS {
    
    enum parametrization{
        KORSMEIER_I    =  1,
        KORSMEIER_II   =  2,
        WINKLER        =  3,
        DI_MAURO_I     =  4,
        DI_MAURO_II    =  5,
        ANDERSON       =  6,
        WINKLER_SELF   =  7,
        DI_MAURO_SELF  =  8,
        APPROX_1_OVER_T=  9,
        WINKLER_II     = 10,
        KORSMEIER_III  = 11
    };
    enum product{
        P_BAR    = 1,
        D_BAR    = 2,
        HE3_BAR  = 3,
        HE4_BAR  = 4
    };
    
    enum coalescence{
        FIXED_P0                   = 1,
        ENERGY_DEP__VAN_DOETINCHEM = 2,
        PT_DEP                     = 3
    };
    
    class XS{
        
    public:
        
        
        //!Convert LAB frame kinetic variable to the CM frame. (The LAB frame is the ISM rest frame.)
        /*!
         *
         *  \param double Tn_proj_LAB    Kinetic energy per nucleus of the prjectile (in the LAB frame)
         *  \param doulbe T_prod_LAB     Kinetic energy of the product (in the LAB frame)
         *  \param doulbe eta_LAB        Pseudo rapidity of the product (in the LAB frame)
         *
         *  \param doulbe &s             Returns: CM energy
         *  \param doulbe &E_prod        Returns: Antiproton (total) energy
         *  \param doulbe &pT_prod       Returns: Product transverse momentum
         *  \param doulbe &x_F           Returns: Product Feynman scaling variable
         *
         *  \param int    product        Product (from enum [P_BAR, D_BAR, HE_BAR])
         *  \return bool                 True if conversion successful
         */
        static bool convert_LAB_to_CM( const double T_p_LAB, const double T_prod_LAB, const double eta_LAB, double &s, double &E_prod, double &pT_prod, double &x_F, int product=P_BAR );
        
         //!Invariant antiproton production cross section for general projectile and target nucleus for different XS parametrization
         /*!
          *  \param double s               CM energy, squared.
          *  \param doulbe xF              Feynman scaling (2*pL_pbar/sqrt(s) in CMF)
          *  \param doulbe pT_pbar         Transverse momentum of the antiproton
          *  \param int    A_projectile    Mass number of the projectile
          *  \param int    N_projectile    Number of neutrons in the projectile
          *  \param int    A_target        Mass number of the target
          *  \param int    N_target        Number of neutrons in the target
          *  \param int    parametrization Cross section parametrization, enum from[KORSMEIER_II (default), KORSMEIER_I, WINKLER, DI_MAURO_I, DI_MAURO_II, WINKLER_SELF, DI_MAURO_SELF]
          *
          *  \return double XS             Cross section in mbarn/GeV^2
          */
        static double inv_AA_pbar_CM( double s, double xF, double pT_pbar, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization);

        //! Invariant antiproton production cross section for general projectile and target nucleus for different XS parametrization as function of LAB frame kinetic variables
        /*!
         *
         *  \param double Tn_proj_LAB      Kinetic energy per nucleus of the prjectile (in the LAB frame)
         *  \param doulbe T_pbar_LAB       Kinetic energy of the antiproton (in the LAB frame)
         *  \param doulbe eta_LAB          Pseudo rapidity of the antiproton (in the LAB frame)
         *  \param int    A_projectile     Mass number of the projectile
         *  \param int    N_projectile     Number of neutrons in the projectile
         *  \param int    A_target         Mass number of the target
         *  \param int    N_target         Number of neutrons in the target
         *  \param int    parametrization  Cross section parametrization [Korsmeier_II (default), Korsmeier_I, Winkler, diMauro_I, diMauro_II]
         *
         *  \return double XS              Cross section in mbarn/GeV^2
         */
        static double inv_AA_pbar_LAB( double Tn_proj_LAB, double T_pbar_LAB, double eta_LAB, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization );
        
        
        //! Energy-differential antiproton production cross section for general projectile and target nucleus for different XS parametrization as function of LAB frame kinetic variables.
        /*!
         *  This cross section is integrated over all angles.
         *
         *  \param double Tn_proj_LAB      Kinetic energy per nucleus of the prjectile (in the LAB frame)
         *  \param doulbe T_pbar_LAB       Kinetic energy of the antiproton (in the LAB frame)
         *  \param int    A_projectile     Mass number of the projectile
         *  \param int    N_projectile     Number of neutrons in the projectile
         *  \param int    A_target         Mass number of the target
         *  \param int    N_target         Number of neutrons in the target
         *  \param int    parametrization  Cross section parametrization, enum from[KORSMEIER_II (default), KORSMEIER_I, WINKLER, DI_MAURO_I, DI_MAURO_II, WINKLER_SELF, DI_MAURO_SELF]
         *
         *  \return double XS              Cross section in mbarn/GeV
         */
        static double dE_AA_pbar_LAB( double Tn_proj_LAB, double T_pbar_LAB, int A_projectile=1, int N_projectile=0, int A_target=1, int N_target=0, int parametrization=KORSMEIER_II);
        //! Helper function for dE_AA_pbar_LAB
        static double integrand__dE_AA_pbar_LAB (double eta_LAB, void* parameters  );
        
        
        
         //!Energy-differential antiproton production cross section including antineutrons and antihyperons for general projectile and target nucleus and for different XS parametrization as function of LAB frame kinetic variables. This cross section is integrated over all angles.
         /*!
          *    Depending on the parametrization,
          *    taken from:   Korsmeier, et al.; 2018;
          *                  Production cross sections of cosmic antiprotons in the light of new data from the NA61 and LHCb experiments;
          *                  DOI: 10.1103/PhysRevD.97.103019
          *
          *    taken from:   Winkler, M. W.; 2017;
          *                  Cosmic Ray Antiprotons at High Energies;
          *                  arXiv:1701.04866
          
          *     For di Mauro we apply a global factor 2.3 instead.
          *
          *     In the case of di Mauro parametrizations the antihyperon contribution is set to 0.
          *     The nuclear scaling for AA initial states is done as explained in XS_definitions::factor__AA.
          *
          *  \param double Tn_proj_LAB      Kinetic energy per nucleus of the prjectile (in the LAB frame)
          *  \param doulbe T_pbar_LAB       Kinetic energy of the antiproton (in the LAB frame)
          *  \param int    A_projectile     Mass number of the projectile
          *  \param int    N_projectile     Number of neutrons in the projectile
          *  \param int    A_target         Mass number of the target
          *  \param int    N_target         Number of neutrons in the target
          *  \param int    parametrization  Cross section parametrization, enum from[KORSMEIER_II (default), KORSMEIER_I, WINKLER, DI_MAURO_I, DI_MAURO_II, WINKLER_SELF, DI_MAURO_SELF]
          *
          *  \return double XS              Cross section in mbarn/GeV
          */
        static double dE_AA_pbar_LAB_incNbarAndHyperon(double Tn_proj_LAB, double T_pbar_LAB, int A_projectile=1, int N_projectile=0, int A_target=1, int N_target=0, int parametrization=KORSMEIER_II);
        
        
        
        //!Invariant proton production cross section for general projectile and target nucleus for different XS parametrization
        /*!
         *  \param double s               CM energy, squared.
         *  \param doulbe xF              Feynman scaling (2*pL_p/sqrt(s) in CMF)
         *  \param doulbe pT_p            Transverse momentum of the proton
         *  \param int    A_projectile    Mass number of the projectile
         *  \param int    N_projectile    Number of neutrons in the projectile
         *  \param int    A_target        Mass number of the target
         *  \param int    N_target        Number of neutrons in the target
         *  \param int    parametrization Cross section parametrization, enum from[ANDERSON]
         *
         *  \return double XS             Cross section in mbarn/GeV^2
         */
        static double inv_AA_p_CM( double s, double xF, double pT_p, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization);
        
        //! Invariant proton production cross section for general projectile and target nucleus for different XS parametrization as function of LAB frame kinetic variables
        /*!
         *
         *  \param double Tn_proj_LAB      Kinetic energy per nucleus of the prjectile (in the LAB frame)
         *  \param doulbe T_p_LAB          Kinetic energy of the proton (in the LAB frame)
         *  \param doulbe eta_LAB          Pseudo rapidity of the proton (in the LAB frame)
         *  \param int    A_projectile     Mass number of the projectile
         *  \param int    N_projectile     Number of neutrons in the projectile
         *  \param int    A_target         Mass number of the target
         *  \param int    N_target         Number of neutrons in the target
         *  \param int    parametrization  Cross section parametrization [ANDERSON]
         *
         *  \return double XS              Cross section in mbarn/GeV^2
         */
        static double inv_AA_p_LAB( double Tn_proj_LAB, double T_p_LAB, double eta_LAB, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization );
        
        
        //! Energy-differential proton production cross section for general projectile and target nucleus for different XS parametrization as function of LAB frame kinetic variables.
        /*!
         *  This cross section is integrated over all angles.
         *
         *  \param double Tn_proj_LAB      Kinetic energy per nucleus of the prjectile (in the LAB frame)
         *  \param doulbe T_p_LAB          Kinetic energy of the proton (in the LAB frame)
         *  \param int    A_projectile     Mass number of the projectile
         *  \param int    N_projectile     Number of neutrons in the projectile
         *  \param int    A_target         Mass number of the target
         *  \param int    N_target         Number of neutrons in the target
         *  \param int    parametrization  Cross section parametrization, enum from[ANDERSON]
         *
         *  \return double XS              Cross section in mbarn/GeV
         */
        static double dE_AA_p_LAB( double Tn_proj_LAB, double T_p_LAB, int A_projectile=1, int N_projectile=0, int A_target=1, int N_target=0, int parametrization=ANDERSON);
        //! Helper function for dE_AA_p_LAB
        static double integrand__dE_AA_p_LAB (double eta_LAB, void* parameters  );
        
        
        
        //!Invariant antideuteron production cross section for general projectile and target nucleus for different XS parametrization
        /*!
         *
         *      Coalesence momentum from the paper:
         *          Deuteron and Antideuteron Production Simulation in Cosmic-ray Interactions
         *          Diego-Mauricio Gomez-Coral, et al.,
         *          (DOI 10.1103/PhysRevD.98.023012)
         *
         *      Taken from Eq. (5) with parameters of Korsmeier, et al.
         *      The parameter p_coal is defined as abs(p_proton - p_neutron)/2. (Note that there is also a different notation,
         *      without the factor 2., in the literature)
         *
         *
         *  \param  double s              CM energy, squared (in the nucleon-nucleon frame).
         *  \return double                Coalescence momentum
         */
        static double p_coal__VonDoetinchen( double s );
        
        
       //!Function for getting the coalescence momentum using a rescaling with PT.
       /*!
        *
        *      Coalesence momentum from the paper:
        *          Deuteron and Antideuteron Production Simulation in Cosmic-ray Interactions
        *          Diego-Mauricio Gomez-Coral, et al.,
        *          (DOI 10.1103/PhysRevD.98.023012)
        *
        *      Taken from Eq. (5) with parameters of Korsmeier, et al.
        *      The parameter p_coal is defined as abs(p_proton - p_neutron)/2. (Note that there is also a different notation,
        *      without the factor 2., in the literature)
        *
        *
        *  \param  double s              CM energy, squared (in the nucleon-nucleon frame).
        *  \return double                Coalescence momentum
        */
       static double p_coal__pTdep( double pToverA, double p0_val=0.160 );
        
        
        //!Invariant antideuteron production cross section for general projectile and target nucleus for different XS parametrization
        /*!
         *      We calculat the cross section in the analytic coalescence model. With the formula:
         *
         *
         *
         *                 3                                                   3                   3
         *                d    sigma                m               3         d  sigma            d  sigma
         *                 dbar               1      D    4pi  pcoal                  pbar                nbar
         *        E      ------------  =  -------- -----  ---  ------   E     ------------  E     ------------
         *         dbar       3           sigmaTot m  m    3      1      pbar      3         nbar      3
         *                  dk                      p  n                         dk                  dk
         *                    dbar                                                 pbar                nbar
         *
         *        with:
         *
         *         3              3                 /   3                        3                                                              \
         *        d  sigma       d  sigma           |  d  sigma                 d  sigma                                                        |
         *                pbar           nbar     1 |          pbar                     nbar                                                    |
         *        ------------   ------------  =  - |  ------------(sS, vk    ) ------------ (sS - 2E    , vk    )  +  ({pbar} < - > {nbar})    |
         *             3              3           2 |       3             pbar       3               pbar    nbar                               |
         *           dk             dk              |     dk                       dk                                                           |
         *             pbar           nbar          \       pbar                     nbar                                                       /
         *
         *
         *      The parameter p_coal is defined as abs(p_proton - p_neutron).
         *
         *      There are two options for the coalesence momentum (cf. to option \param int coalescence):
         *
         *          1) Fixed to 80 MeV, which is the value tuned to the aleph experiment. If you prefer a different (fixed) value
         *             you can rescale the whole XS with (p_coal/80 MeV)^3.
         *          2) The energy-dependent coalescence momentum suggested in DOI 10.1103/PhysRevD.98.023012.
         *          3) A coalescence momentum that changes with transverse momentum as found in https://doi.org/10.1140/epjc/s10052-020-8256-4.
         *
         *      We recommend option 2)
         *
         *      The parameter p_coal is defined as abs(p_proton - p_neutron).
         *
         *
         *      If the massnumber \param int A_projectile is set to -1 we assume an antiproton projectile. In this case
         *      the antiproton production cross section is replaced and approximated by the cross section from
         *                  Anderson, et al.; 1967;
         *                  PROTON AND PION SPECTRA FROM PROTON-PROTON INTERACTIONS AT 10, 20, AND 30 BeV/c*;
         *                  DOI: https://doi.org/10.1103/PhysRevLett.19.198 .
         *      The assumption is that the "p p -> p" XS is equal to the "pbar p -> pbar" XS.
         *
         *      The cross section contains the contribution from antineutrons and antihyperons.
         *      In the case of DI_MAURO parametrizations the antihyperon contribution is set to 0.
         *      The nuclear scaling for AA initial states is done as explained in XS_definitions::factor__AA.
         *
         *  \param double s               CM energy, squared (in the nucleon-nucleon frame).
         *  \param doulbe xF              Feynman scaling (2*pL_pbar/sqrt(s) in CMF, i.e. the nucleon-nucleon frame)
         *  \param doulbe pT_Dbar         Transverse momentum of the antideuteron
         *  \param int    A_projectile    Mass number of the projectile, if A_projectile is negative we use an antiproton as projectile
         *  \param int    N_projectile    Number of neutrons in the projectile
         *  \param int    A_target        Mass number of the target
         *  \param int    N_target        Number of neutrons in the target
         *  \param int    parametrization Cross section parametrization, enum from[KORSMEIER_II (default), KORSMEIER_I, WINKLER, DI_MAURO_I, DI_MAURO_II]
         *  \param int    coalescence     Coalescence model, enum from[FIXED_P0 (default), ENERGY_DEP__VAN_DOETINCHEM]
         *  \param int    p0_val.          Coalescence momentum in GeV
         *
         *  \return double XS             Cross section in mbarn/GeV^2
         */
        static double inv_AA_Dbar_CM( double s, double xF_Dbar, double pT_Dbar, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization, int coalescence, double p0_val=0.160 );
        
        //! Invariant antideuteron production cross section for general projectile and target nucleus for different XS parametrization as function of LAB frame kinetic variables
        /*!
         *  \param double Tn_proj_LAB      Kinetic energy per nucleus of the prjectile (in the LAB frame)
         *  \param doulbe Tn_Dbar_LAB      Kinetic energy of the antideuteron (in the LAB frame)
         *  \param doulbe eta_LAB          Pseudo rapidity of the antideuteron (in the LAB frame)
         *  \param int    A_projectile     Mass number of the projectile, if A_projectile is negative we use an antiproton as projectile
         *  \param int    N_projectile     Number of neutrons in the projectile
         *  \param int    A_target         Mass number of the target
         *  \param int    N_target         Number of neutrons in the target
         *  \param int    parametrization  Cross section parametrization [Korsmeier_II (default), Korsmeier_I, Winkler, diMauro_I, diMauro_II]
         *  \param int    coalescence      Coalescence model, enum from[FIXED_P0 (default), ENERGY_DEP__VAN_DOETINCHEM], cf. inv_AA_Dbar_CM
         *  \param int    p0_val.          Coalescence momentum in GeV
         *
         *  \return double XS              Cross section in mbarn/GeV^2
         */
        static double inv_AA_Dbar_LAB( double Tn_proj_LAB, double Tn_Dbar_LAB, double eta_LAB, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization, int coalescence, double p0_val=0.160 );
        //! Helper function for inv_AA_Dbar_LAB
        static double integrand__dE_AA_Dbar_LAB (double eta_LAB, void* parameters  );
        
        
        //! Energy-differential antideuteron production cross section for general projectile and target nucleus for different XS parametrization as function of LAB frame kinetic variables. The cross section contains the contribution from antineutrons and antihyperons. In the case of DI_MAURO parametrizations the antihyperon contribution is set to 0. The nuclear scaling for AA initial states is done as explained in XS_definitions::factor__AA.
        /*!
         *  This cross section is integrated over all angles.
         *
         *  \param double Tn_proj_LAB      Kinetic energy per nucleus of the prjectile (in the LAB frame)
         *  \param doulbe Tn_Dbar_LAB      Kinetic energy per nucleus of the antideuteron (in the LAB frame)
         *  \param int    A_projectile     Mass number of the projectile, if A_projectile is negative we use an antiproton as projectile
         *  \param int    N_projectile     Number of neutrons in the projectile
         *  \param int    A_target         Mass number of the target
         *  \param int    N_target         Number of neutrons in the target
         *  \param int    parametrization  Cross section parametrization, enum from[KORSMEIER_II (default), KORSMEIER_I, WINKLER, DI_MAURO_I, DI_MAURO_II]
         *  \param int    coalescence      Coalescence model, enum from[FIXED_P0 (default), ENERGY_DEP__VAN_DOETINCHEM], cf. inv_AA_Dbar_CM
         *  \param int    p0_val.          Coalescence momentum in GeV
         *
         *  \return double XS              Cross section in mbarn/GeV
         */
        static double dEn_AA_Dbar_LAB( double Tn_proj_LAB, double Tn_Dbar_LAB, int A_projectile=1, int N_projectile=0, int A_target=1, int N_target=0, int parametrization=KORSMEIER_II, int coalescence=ENERGY_DEP__VAN_DOETINCHEM, double p0_val=0.160 );
        
        
        //! Energy-differential antideuteron cross section for non-annihilating antideuteron reactions on p, A.
        /*!
         *  This cross section is integrated over all angles.
         *
         *  There are two standard ways to approximated this cross section which has never been measured.
         *  The energy-differential shape of the XS is either approximated by a the p+p->p+X reaction or
         *  or taken to be flat.
         *  In any case the cross section is normalized to the non-annihilating XS of pbar+D->D+X (see XS_definitions::nar_pbarD).
         *
         *  \param doulbe Tn_Dbar_proj_LAB      Kinetic energy per nucleus of the projectile antideuteron (in the LAB frame)
         *  \param double Tn_Dbar_prod_LAB      Kinetic energy per nucleus of the product    antideuteron (in the LAB frame)
         *  \param int    A_target              Mass number of the target
         *  \param int    N_target              Number of neutrons in the target
         *  \param int    parametrization       Way to approximate the cross section parametrization [ANDERSON, APPROX_1_OVER_T]
         *
         *  \return double XS              Cross section in mbarn/GeV
         */
        static double dEn_DbarA_Dbar_LAB( double Tn_Dbar_proj_LAB, double Tn_Dbar_prod_LAB, int A_target=1, int N_target=0, int parametrization=ANDERSON );
        
        
        //!Invariant antihelion production cross section for general projectile and target nucleus for different XS parametrization
        /*!
         *      We calculat the cross section in the analytic coalescence model. With the formula:
         *
         *      The parameter p_coal is defined as abs(p_proton - p_neutron).
         *
         *      There are three options for the coalesence momentum (cf. to option \param int coalescence):
         *
         *          1) Fixed to 80 MeV, which is the value tuned to the aleph experiment. If you prefer a different (fixed) value
         *             you can rescale the whole XS with (p_coal/80 MeV)^3.
         *          2) The energy-dependent coalescence momentum suggested in DOI 10.1103/PhysRevD.98.023012.
         *          3) A coalescence momentum that changes with transverse momentum as found in https://doi.org/10.1140/epjc/s10052-020-8256-4.
         *
         *      We recommend option 2)
         *
         *
         *      If the massnumber \param int A_projectile is set to -1 we assume an antiproton projectile. In this case
         *      the antiproton production cross section is replaced and approximated by the cross section from
         *                  Anderson, et al.; 1967;
         *                  PROTON AND PION SPECTRA FROM PROTON-PROTON INTERACTIONS AT 10, 20, AND 30 BeV/c*;
         *                  DOI: https://doi.org/10.1103/PhysRevLett.19.198 .
         *      The assumption is that the "p p -> p" XS is equal to the "pbar p -> pbar" XS.
         *
         *      The cross section contains the contribution from antineutrons and antihyperons.
         *      In the case of DI_MAURO parametrizations the antihyperon contribution is set to 0.
         *      The nuclear scaling for AA initial states is done as explained in XS_definitions::factor__AA.
         *
         *  \param double s               CM energy, squared (in the nucleon-nucleon frame).
         *  \param doulbe xF              Feynman scaling (2*pL_pbar/sqrt(s) in CMF, i.e. the nucleon-nucleon frame)
         *  \param doulbe pT_Hebar        Transverse momentum of the antihelion
         *  \param int    A_projectile    Mass number of the projectile, if A_projectile is negative we use an antiproton as projectile
         *  \param int    N_projectile    Number of neutrons in the projectile
         *  \param int    A_target        Mass number of the target
         *  \param int    N_target        Number of neutrons in the target
         *  \param int    parametrization Cross section parametrization, enum from[KORSMEIER_II (default), KORSMEIER_I, WINKLER, DI_MAURO_I, DI_MAURO_II]
         *  \param int    coalescence     Coalescence model, enum from[FIXED_P0 (default), ENERGY_DEP__VAN_DOETINCHEM]
         *  \param int    p0_val.          Coalescence momentum in GeV
         *
         *  \return double XS             Cross section in mbarn/GeV^2
         */
        static double inv_AA_He3bar_CM( double s, double xF_Hebar, double pT_Hebar, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization, int coalescence, double p0_val=0.160 );
        
        //! Invariant antihelion production cross section for general projectile and target nucleus for different XS parametrization as function of LAB frame kinetic variables
        /*!
         *  \param double Tn_proj_LAB      Kinetic energy per nucleus of the prjectile (in the LAB frame)
         *  \param doulbe Tn_Hebar_LAB     Kinetic energy of the antihelion (in the LAB frame)
         *  \param doulbe eta_LAB          Pseudo rapidity of the antihelion (in the LAB frame)
         *  \param int    A_projectile     Mass number of the projectile, if A_projectile is negative we use an antiproton as projectile
         *  \param int    N_projectile     Number of neutrons in the projectile
         *  \param int    A_target         Mass number of the target
         *  \param int    N_target         Number of neutrons in the target
         *  \param int    parametrization  Cross section parametrization [Korsmeier_II (default), Korsmeier_I, Winkler, diMauro_I, diMauro_II]
         *  \param int    coalescence      Coalescence model, enum from[FIXED_P0 (default), ENERGY_DEP__VAN_DOETINCHEM], cf. inv_AA_Dbar_CM
         *  \param int    p0_val.          Coalescence momentum in GeV
         *
         *  \return double XS              Cross section in mbarn/GeV^2
         */
        static double inv_AA_He3bar_LAB( double Tn_proj_LAB, double Tn_Hebar_LAB, double eta_LAB, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization, int coalescence, double p0_val=0.160 );
        //! Helper function for inv_AA_Hebar_LAB
        static double integrand__dE_AA_He3bar_LAB (double eta_LAB, void* parameters  );
        
        
        //! Energy-differential antihelion production cross section for general projectile and target nucleus for different XS parametrization as function of LAB frame kinetic variables. The cross section contains the contribution from antineutrons and antihyperons. In the case of DI_MAURO parametrizations the antihyperon contribution is set to 0. The nuclear scaling for AA initial states is done as explained in XS_definitions::factor__AA.
        /*!
         *  This cross section is integrated over all angles.
         *
         *  \param double Tn_proj_LAB      Kinetic energy per nucleus of the prjectile (in the LAB frame)
         *  \param doulbe Tn_Hebar_LAB     Kinetic energy per nucleus of the antihelion (in the LAB frame)
         *  \param int    A_projectile     Mass number of the projectile, if A_projectile is negative we use an antiproton as projectile
         *  \param int    N_projectile     Number of neutrons in the projectile
         *  \param int    A_target         Mass number of the target
         *  \param int    N_target         Number of neutrons in the target
         *  \param int    parametrization  Cross section parametrization, enum from[KORSMEIER_II (default), KORSMEIER_I, WINKLER, DI_MAURO_I, DI_MAURO_II]
         *  \param int    coalescence      Coalescence model, enum from[FIXED_P0 (default), ENERGY_DEP__VAN_DOETINCHEM], cf. inv_AA_Dbar_CM
         *  \param int    p0_val.          Coalescence momentum in GeV
         *
         *  \return double XS              Cross section in mbarn/GeV
         */
        static double dEn_AA_He3bar_LAB( double Tn_proj_LAB, double Tn_Hebar_LAB, int A_projectile=1, int N_projectile=0, int A_target=1, int N_target=0, int parametrization=KORSMEIER_II, int coalescence=ENERGY_DEP__VAN_DOETINCHEM, double p0_val=0.160 );
        
        
        //! Energy-differential antihelion cross section for non-annihilating antihelion reactions on p, A.
        /*!
         *  This cross section is integrated over all angles.
         *
         *  There are two standard ways to approximated this cross section which has never been measured.
         *  The energy-differential shape of the XS is either approximated by a the p+p->p+X reaction or
         *  or taken to be flat.
         *  In any case the cross section is normalized to the non-annihilating XS of pbar+He->He+X (see XS_definitions::nar_pbarD).
         *
         *  \param doulbe Tn_Hebar_proj_LAB     Kinetic energy per nucleus of the projectile antihelion (in the LAB frame)
         *  \param double Tn_Hebar_prod_LAB     Kinetic energy per nucleus of the product    antihelion (in the LAB frame)
         *  \param int    A_target              Mass number of the target
         *  \param int    N_target              Number of neutrons in the target
         *  \param int    parametrization       Way to approximate the cross section parametrization [ANDERSON, APPROX_1_OVER_T]
         *
         *  \return double XS              Cross section in mbarn/GeV
         */
        static double dEn_He3barA_He3bar_LAB( double Tn_Hebar_proj_LAB, double Tn_Hebar_prod_LAB, int A_target=1, int N_target=0, int parametrization=ANDERSON );
        
        
       //!Invariant antihelion production cross section for general projectile and target nucleus for different XS parametrization
       /*!
        *      We calculat the cross section in the analytic coalescence model following eq. 4 of https://arxiv.org/abs/1711.08465.
        *
        *      The parameter p_coal is defined as abs(p_proton - p_neutron)
        *
        *      There are three options for the coalesence momentum (cf. to option \param int coalescence):
        *
        *          1) Fixed to 160 MeV, which is the value tuned to the aleph experiment. If you prefer a different (fixed) value
        *             you can rescale the whole XS with (p_coal/160 MeV)^3.
        *          2) The energy-dependent coalescence momentum suggested in DOI 10.1103/PhysRevD.98.023012.
        *          3) A coalescence momentum that changes with transverse momentum as found in https://doi.org/10.1140/epjc/s10052-020-8256-4.
        *
        *      We recommend option 2)
        *
        *      If the massnumber \param int A_projectile is set to -1 we assume an antiproton projectile. In this case
        *      the antiproton production cross section is replaced and approximated by the cross section from
        *                  Anderson, et al.; 1967;
        *                  PROTON AND PION SPECTRA FROM PROTON-PROTON INTERACTIONS AT 10, 20, AND 30 BeV/c*;
        *                  DOI: https://doi.org/10.1103/PhysRevLett.19.198 .
        *      The assumption is that the "p p -> p" XS is equal to the "pbar p -> pbar" XS.
        *
        *      The cross section contains the contribution from antineutrons and antihyperons.
        *      In the case of DI_MAURO parametrizations the antihyperon contribution is set to 0.
        *      The nuclear scaling for AA initial states is done as explained in XS_definitions::factor__AA.
        *
        *  \param double s               CM energy, squared (in the nucleon-nucleon frame).
        *  \param doulbe xF              Feynman scaling (2*pL_pbar/sqrt(s) in CMF, i.e. the nucleon-nucleon frame)
        *  \param doulbe pT_Hebar        Transverse momentum of the antihelion
        *  \param int    A_projectile    Mass number of the projectile, if A_projectile is negative we use an antiproton as projectile
        *  \param int    N_projectile    Number of neutrons in the projectile
        *  \param int    A_target        Mass number of the target
        *  \param int    N_target        Number of neutrons in the target
        *  \param int    parametrization Cross section parametrization, enum from[KORSMEIER_II (default), KORSMEIER_I, WINKLER, DI_MAURO_I, DI_MAURO_II]
        *  \param int    coalescence     Coalescence model, enum from[FIXED_P0 (default), ENERGY_DEP__VAN_DOETINCHEM]
        *  \param int    p0_val.          Coalescence momentum in GeV
        *
        *  \return double XS             Cross section in mbarn/GeV^2
        */
       static double inv_AA_He4bar_CM( double s, double xF_Hebar, double pT_Hebar, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization, int coalescence, double p0_val=0.160 );
       
       //! Invariant antihelion production cross section for general projectile and target nucleus for different XS parametrization as function of LAB frame kinetic variables
       /*!
        *  \param double Tn_proj_LAB      Kinetic energy per nucleus of the prjectile (in the LAB frame)
        *  \param doulbe Tn_Hebar_LAB     Kinetic energy of the antihelion (in the LAB frame)
        *  \param doulbe eta_LAB          Pseudo rapidity of the antihelion (in the LAB frame)
        *  \param int    A_projectile     Mass number of the projectile, if A_projectile is negative we use an antiproton as projectile
        *  \param int    N_projectile     Number of neutrons in the projectile
        *  \param int    A_target         Mass number of the target
        *  \param int    N_target         Number of neutrons in the target
        *  \param int    parametrization  Cross section parametrization [Korsmeier_II (default), Korsmeier_I, Winkler, diMauro_I, diMauro_II]
        *  \param int    coalescence      Coalescence model, enum from[FIXED_P0 (default), ENERGY_DEP__VAN_DOETINCHEM], cf. inv_AA_Dbar_CM
        *  \param int    p0_val.          Coalescence momentum in GeV
        *
        *  \return double XS              Cross section in mbarn/GeV^2
        */
       static double inv_AA_He4bar_LAB( double Tn_proj_LAB, double Tn_Hebar_LAB, double eta_LAB, int A_projectile, int N_projectile, int A_target, int N_target, int parametrization, int coalescence, double p0_val=0.160 );
       //! Helper function for inv_AA_Hebar_LAB
       static double integrand__dE_AA_He4bar_LAB (double eta_LAB, void* parameters  );
       
       
       //! Energy-differential antihelion production cross section for general projectile and target nucleus for different XS parametrization as function of LAB frame kinetic variables. The cross section contains the contribution from antineutrons and antihyperons. In the case of DI_MAURO parametrizations the antihyperon contribution is set to 0. The nuclear scaling for AA initial states is done as explained in XS_definitions::factor__AA.
       /*!
        *  This cross section is integrated over all angles.
        *
        *  \param double Tn_proj_LAB      Kinetic energy per nucleus of the prjectile (in the LAB frame)
        *  \param doulbe Tn_Hebar_LAB     Kinetic energy per nucleus of the antihelion (in the LAB frame)
        *  \param int    A_projectile     Mass number of the projectile, if A_projectile is negative we use an antiproton as projectile
        *  \param int    N_projectile     Number of neutrons in the projectile
        *  \param int    A_target         Mass number of the target
        *  \param int    N_target         Number of neutrons in the target
        *  \param int    parametrization  Cross section parametrization, enum from[KORSMEIER_II (default), KORSMEIER_I, WINKLER, DI_MAURO_I, DI_MAURO_II]
        *  \param int    coalescence      Coalescence model, enum from[FIXED_P0 (default), ENERGY_DEP__VAN_DOETINCHEM], cf. inv_AA_Dbar_CM
        *  \param int    p0_val.          Coalescence momentum in GeV
        *
        *  \return double XS              Cross section in mbarn/GeV
        */
       static double dEn_AA_He4bar_LAB( double Tn_proj_LAB, double Tn_Hebar_LAB, int A_projectile=1, int N_projectile=0, int A_target=1, int N_target=0, int parametrization=KORSMEIER_II, int coalescence=ENERGY_DEP__VAN_DOETINCHEM, double p0_val=0.160 );
       
       
       //! Energy-differential antihelion cross section for non-annihilating antihelion reactions on p, A.
       /*!
        *  This cross section is integrated over all angles.
        *
        *  There are two standard ways to approximated this cross section which has never been measured.
        *  The energy-differential shape of the XS is either approximated by a the p+p->p+X reaction or
        *  or taken to be flat.
        *  In any case the cross section is normalized to the non-annihilating XS of pbar+He->He+X (see XS_definitions::nar_pbarD).
        *
        *  \param doulbe Tn_Hebar_proj_LAB     Kinetic energy per nucleus of the projectile antihelion (in the LAB frame)
        *  \param double Tn_Hebar_prod_LAB     Kinetic energy per nucleus of the product    antihelion (in the LAB frame)
        *  \param int    A_target              Mass number of the target
        *  \param int    N_target              Number of neutrons in the target
        *  \param int    parametrization       Way to approximate the cross section parametrization [ANDERSON, APPROX_1_OVER_T]
        *
        *  \return double XS              Cross section in mbarn/GeV
        */
       static double dEn_He4barA_He4bar_LAB( double Tn_Hebar_proj_LAB, double Tn_Hebar_prod_LAB, int A_target=1, int N_target=0, int parametrization=ANDERSON );
        //! Function to set the parameter values of the di Mauro parametrization yourself.
        /*!
         *  The nameing of the parameters corresponds to the definition
         *                  di Mauro, et al.; 2014;
         *                  A new evaluation of the antiproton production cross section for cosmic ray studies;
         *                  DOI: 10.1103/PhysRevD.90.085017
         *  in Eq. (13). The input parameter array double* C is expected to have a length of 19 and contains:
         *    - C[0] is a dummy
         *    - C[1] to C[11] are the variables of Eq. (13)
         *    - C[12] to C[15] are the isospin variables, this is described as in Winkler (2017), his variables C_1  to C_4
         *    - C[16] to C[18] are the hyperon variables, this is described as in Winkler (2017), his variables C_14 to C_16
         *
         *  \param double* C               Array of parameters, expected length: 19. For details see above.
         *
         */
        static void Set_SELF_C_parameters_diMauro(double* C);
        
        
        //! Function to set the parameter values of the Winkler parametrization yourself.
        /*!
         *  The nameing of the parameters corresponds to the definition
         *                  Winkler, M. W.; 2017;
         *                  Cosmic Ray Antiprotons at High Energies;
         *                  arXiv:1701.04866
         *  The input parameter array double* C is expected to have a length of 17 and contains:
         *    - C[0] is a dummy
         *    - C[1] to C[16] are the variables named as in Winkler (2017)
         *
         *  \param double* C               Array of parameters, expected length: 17. For details see above.
         *
         */
        static void Set_SELF_C_parameters_Winkler(double* C);
        
        
        //! Function to set the parameter values of the di Mauro parametrization yourself.
        /*!
         *  The nameing of the parameters corresponds to the definition
         *                  Korsmeier, et al.; 2018;
         *                  Production cross sections of cosmic antiprotons in the light of new data from the NA61 and LHCb experiments;
         *                  DOI: 10.1103/PhysRevD.97.103019
         *  The input parameter array double* D is expected to have a length of 3 and contains:
         *    - D[0] is a dummy
         *    - D[1] and D[2] are the variables named as in Korsmeier, et al.; 2018
         *
         *  \param double* D               Array of parameters, expected length: 3. For details see above.
         *
         */
        static void Set_SELF_D_parameters_diMauro(double* D);
        
        
        //! Function to set the parameter values of the Winkler parametrization yourself.
        /*!
         *  The nameing of the parameters corresponds to the definition
         *                  Korsmeier, et al.; 2018;
         *                  Production cross sections of cosmic antiprotons in the light of new data from the NA61 and LHCb experiments;
         *                  DOI: 10.1103/PhysRevD.97.103019
         *  The input parameter array double* D is expected to have a length of 3 and contains:
         *    - D[0] is a dummy
         *    - D[1] and D[2] are the variables named as in Korsmeier, et al.; 2018
         *
         *  \param double* D               Array of parameters, expected length: 3. For details see above.
         *
         */
        static void Set_SELF_D_parameters_Winkler(double* D);
        
        
        
        static bool     fIsRestricted_pp;
        static void     SetRestricted_pp     ( bool is_pp ){fIsRestricted_pp=is_pp;};
        
        static bool     isInRestricted_CM                  ( double s, double xf, double pT );
        static void     SetRestrictedParameterSpace_CM     ( double s, double xf, double pT );
        static void     RemoveRestrictedParameterSpace_CM  (  );
        static int      fRestrictedParameterSpace_CM;
        static double   fRestrictedParameterSpace_CM__s    [103];
        static double   fRestrictedParameterSpace_CM__xf   [103];
        static double   fRestrictedParameterSpace_CM__pT   [103];
        
        
        
        static bool     isInRestricted_LAB                  ( double Tp, double Tpbar, double eta );
        static void     SetRestrictedParameterSpace_LAB     ( double Tp, double Tpbar, double eta );
        static void     RemoveRestrictedParameterSpace_LAB  (  );
        static int      fRestrictedParameterSpace_LAB;
        static double   fRestrictedParameterSpace_LAB__Tp   [103];
        static double   fRestrictedParameterSpace_LAB__Tpbar[103];
        static double   fRestrictedParameterSpace_LAB__eta  [103];
        
        //        static double fRestrictedParameterSpace_LAB__Tp_Tpbar_eta[100][3];
        
        

    private:
        
        


        
    };
}

#endif




