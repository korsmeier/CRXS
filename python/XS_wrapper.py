"""@package XS_wrapper
    Documentation of the module XS_wrapper.
    
    The module provides an interface to CRXS. It allows to access antiproton and antideuteron production cross sections.
    It provides cross section for any kind of initial states. The parametrizations are given in the CM frame, the LAB (ISM) frame. Finally, it provides the energy-dependent (i.e. angularly integrated) XS in the LAB frame. 
    
    """

import numpy  as np
import scipy.integrate   as     integrate
import math

import cpp.xs_wrapper    as xs_cpp


# ------------------------------------------------------------- #
#  Cross secion definitions:                                    #
#                                                               #
#  Name convention: T_XY_Z_F_P                                  #
#                                                               #
#     T     type                                                #
#           inv :   Lorentz invariant XS, E d^3 sigma/dp^3      #
#           dE  :   Energy-differential XS, d sigma/dE          #
#     XY    projectile X and target Y                           #
#     Z     product                                             #
#     F     frame (CM or LAB=ISM)                               #
#     P     parametrizationa and description                    #
#                                                               #
# ------------------------------------------------------------- #

_parametrization={'KORSMEIER_I':1,'KORSMEIER_II':2,'WINKLER':3,'DI_MAURO_I':4,'DI_MAURO_II':5}
_product        ={'P_BAR':1,'D_BAR':2,'HE_BAR':3}
_coalescence    ={'FIXED_P0':1,'ENERGY_DEP__VAN_DOETINCHEM':2}

# ---------------- #
#   ANTIPROTON     #
# ---------------- #


def inv_AA_pbar_CM(s, xF, pT_pbar, A_projectile=1, N_projectile=0, A_target=1, N_target=0, parametrization='KORSMEIER_II'):
    """
        Invariant cross section for general projectile and target nucleus for different XS parametrization
        
        \param double s               CM energy, squared.
        \param doulbe xF              Feynman scaling (2*pL_pbar/sqrt(s) in CMF)
        \param doulbe pT_pbar         Transverse momentum of the antiproton
        \param int    A_projectile    Mass number of the projectile
        \param int    N_projectile    Number of neutrons in the projectile
        \param int    A_target        Mass number of the target
        \param int    N_target        Number of neutrons in the target
        \param string parametrization Cross section parametrization [KORSMEIER_II (default), KORSMEIER_I, WINKLER, DI_MAURO_I, DI_MAURO_II]
        
        \return double XS             Cross section in mbarn/GeV^2
        """

    return xs_cpp.inv_AA_pbar_CM(s, xF, pT_pbar, int(A_projectile), int(N_projectile), int(A_target), int(N_target), _parametrization[parametrization])




def inv_AA_pbar_LAB(Tn_proj_LAB, T_pbar_LAB, eta_LAB, A_projectile=1, N_projectile=0, A_target=1, N_target=0, parametrization='KORSMEIER_II'):
    """
        Invariant cross section for general projectile and target nucleus for different XS parametrization
        as function of LAB frame kinetic variables
        
        \param double Tn_proj_LAB      Kinetic energy per nucleus of the prjectile (in the LAB frame)
        \param doulbe T_pbar_LAB       Kinetic energy of the antiproton (in the LAB frame)
        \param doulbe eta_LAB          Pseudo rapidity of the antiproton (in the LAB frame)
        \param int    A_projectile     Mass number of the projectile
        \param int    N_projectile     Number of neutrons in the projectile
        \param int    A_target         Mass number of the target
        \param int    N_target         Number of neutrons in the target
        \param string parametrization  Cross section parametrization [KORSMEIER_II (default), KORSMEIER_I, WINKLER, DI_MAURO_I, DI_MAURO_II]
        
        \return double XS              Cross section in mbarn/GeV^2
        """
    return xs_cpp.inv_AA_pbar_LAB(Tn_proj_LAB, T_pbar_LAB, eta_LAB, int(A_projectile), int(N_projectile), int(A_target), int(N_target), _parametrization[parametrization])


def dE_AA_pbar_LAB(Tn_proj_LAB, T_pbar_LAB, A_projectile=1, N_projectile=0, A_target=1, N_target=0, parametrization='KORSMEIER_II'):
    """
        Energy-differential cross section for general projectile and target nucleus for different XS parametrization
        as function of LAB frame kinetic variables.
        This cross section is integrated over all angles.
        
        \param double Tn_proj_LAB      Kinetic energy per nucleus of the prjectile (in the LAB frame)
        \param doulbe T_pbar_LAB       Kinetic energy of the antiproton (in the LAB frame)
        \param int    A_projectile     Mass number of the projectile
        \param int    N_projectile     Number of neutrons in the projectile
        \param int    A_target         Mass number of the target
        \param int    N_target         Number of neutrons in the target
        \param string parametrization  Cross section parametrization [KORSMEIER_II (default), KORSMEIER_I, WINKLER, DI_MAURO_I, DI_MAURO_II]
        
        \return double XS              Cross section in mbarn/GeV
        """
    return xs_cpp.dE_AA_pbar_LAB(Tn_proj_LAB, T_pbar_LAB, int(A_projectile), int(N_projectile), int(A_target), int(N_target), _parametrization[parametrization])


def dE_AA_pbar_LAB_incNbarAndHyperon(Tn_proj_LAB, T_pbar_LAB, A_projectile=1, N_projectile=0, A_target=1, N_target=0, parametrization='KORSMEIER_II'):
    """
        Energy-differential cross section including antineutrons and antihyperons for general projectile and target nucleus
        and for different XS parametrization as function of LAB frame kinetic variables.
        This cross section is integrated over all angles.
        
        This function should only be used for the parametrizations: Winkler, Korsmeier_I and Korsmeier_II.
        For diMauro apply a global factor 2.3 instead.
        
        \param double Tn_proj_LAB      Kinetic energy per nucleus of the prjectile (in the LAB frame)
        \param doulbe T_pbar_LAB       Kinetic energy of the antiproton (in the LAB frame)
        \param int    A_projectile     Mass number of the projectile
        \param int    N_projectile     Number of neutrons in the projectile
        \param int    A_target         Mass number of the target
        \param int    N_target         Number of neutrons in the target
        \param string parametrization  Cross section parametrization [KORSMEIER_II (default), KORSMEIER_I, WINKLER, DI_MAURO_I, DI_MAURO_II]
        
        \return double XS              Cross section in mbarn/GeV
        """
    return xs_cpp.dE_AA_pbar_LAB_incNbarAndHyperon(Tn_proj_LAB, T_pbar_LAB, int(A_projectile), int(N_projectile), int(A_target), int(N_target), _parametrization[parametrization])





# ---------------- #
#   ANTIDEUTERON   #
# ---------------- #


def inv_AA_Dbar_CM(s, xF, pT_Dbar, A_projectile=1, N_projectile=0, A_target=1, N_target=0, parametrization='KORSMEIER_II', coalescence='ENERGY_DEP__VAN_DOETINCHEM'):
    """
        Invariant antideuteron production cross section for general projectile and target nucleus for different XS parametrization
        
        
        We calculat the cross section in the analytic coalescence model. With the formula:
        
                  3                                                   3                   3
                 d    sigma                m               3         d  sigma            d  sigma
                  dbar               1      D    4pi  pcoal                  pbar                nbar
        E      ------------  =  -------- -----  ---  ------   E     ------------  E     ------------
         dbar       3           sigmaTot m  m    3      1      pbar      3         nbar      3
                  dk                      p  n                         dk                  dk
                    dbar                                                 pbar                nbar
        
        with:
        
         3              3                 /   3                        3                                                              \
        d  sigma       d  sigma           |  d  sigma                 d  sigma                                                        |
                pbar           nbar     1 |          pbar                     nbar                                                    |
        ------------   ------------  =  - |  ------------(sS, vk    ) ------------ (sS - 2E    , vk    )  +  ({pbar} < - > {nbar})    |
             3              3           2 |       3             pbar       3               pbar    nbar                               |
           dk             dk              |     dk                       dk                                                           |
             pbar           nbar          \       pbar                     nbar                                                       /
        
        
        The parameter p_coal is defined as abs(p_proton - p_neutron)/2. (Note that there is also a different notation,
        without the factor 2., in the literature)
        
        There are two options for the coalesence momentum (cf. to option \param int coalescence):
        
        1) Fixed to 80 MeV, which is the value tuned to the aleph experiment. If you prefer a different (fixed) value
        you can rescale the whole XS with (p_coal/80 MeV)^3.
        2) The energy-dependent coalescence momentum suggested in DOI 10.1103/PhysRevD.98.023012.
        
        We recommend option 2)
        
        
        \param double s               CM energy, squared.
        \param doulbe xF              Feynman scaling (2*pL_Dbar/sqrt(s) in CMF)
        \param doulbe pT_Dbar         Transverse momentum of the antideuteron
        \param int    A_projectile    Mass number of the projectile
        \param int    N_projectile    Number of neutrons in the projectile
        \param int    A_target        Mass number of the target
        \param int    N_target        Number of neutrons in the target
        \param string parametrization Cross section parametrization [KORSMEIER_II (default), KORSMEIER_I, WINKLER, DI_MAURO_I, DI_MAURO_II]
        \param string coalescence     Coalescence model, from[FIXED_P0 (default), ENERGY_DEP__VAN_DOETINCHEM], cf. inv_AA_Dbar_CM
        
        \return double XS             Cross section in mbarn/GeV^2
        """
    
    return xs_cpp.inv_AA_Dbar_CM(s, xF, pT_Dbar, int(A_projectile), int(N_projectile), int(A_target), int(N_target), _parametrization[parametrization], _coalescence[coalescence])




def inv_AA_Dbar_LAB(Tn_proj_LAB, T_Dbar_LAB, eta_LAB, A_projectile=1, N_projectile=0, A_target=1, N_target=0, parametrization='KORSMEIER_II', coalescence='ENERGY_DEP__VAN_DOETINCHEM'):
    """
        Invariant antideuteron production cross section for general projectile and target nucleus for different XS parametrization
        as function of LAB frame kinetic variables
        
        \param double Tn_proj_LAB      Kinetic energy per nucleus of the prjectile (in the LAB frame)
        \param doulbe T_Dbar_LAB       Kinetic energy of the antideuteron (in the LAB frame)
        \param doulbe eta_LAB          Pseudo rapidity of the antideuteron (in the LAB frame)
        \param int    A_projectile     Mass number of the projectile
        \param int    N_projectile     Number of neutrons in the projectile
        \param int    A_target         Mass number of the target
        \param int    N_target         Number of neutrons in the target
        \param string parametrization  Cross section parametrization [KORSMEIER_II (default), KORSMEIER_I, WINKLER, DI_MAURO_I, DI_MAURO_II]
        \param string coalescence      Coalescence model, from[FIXED_P0 (default), ENERGY_DEP__VAN_DOETINCHEM], cf. inv_AA_Dbar_CM
        
        \return double XS              Cross section in mbarn/GeV^2
        """
    return xs_cpp.inv_AA_Dbar_LAB(Tn_proj_LAB, T_Dbar_LAB, eta_LAB, int(A_projectile), int(N_projectile), int(A_target), int(N_target), _parametrization[parametrization], _coalescence[coalescence])


def dEn_AA_Dbar_LAB(Tn_proj_LAB, T_Dbar_LAB, A_projectile=1, N_projectile=0, A_target=1, N_target=0, parametrization='KORSMEIER_II', coalescence='ENERGY_DEP__VAN_DOETINCHEM'):
    """
        Energy-differential antideuteron production cross section for general projectile and target nucleus for different XS parametrization
        as function of LAB frame kinetic variables.
        This cross section is integrated over all angles.
        
        \param double Tn_proj_LAB      Kinetic energy per nucleus of the prjectile (in the LAB frame)
        \param doulbe Tn_Dbar_LAB      Kinetic energy per nucleus of the antideuteron (in the LAB frame)
        \param int    A_projectile     Mass number of the projectile
        \param int    N_projectile     Number of neutrons in the projectile
        \param int    A_target         Mass number of the target
        \param int    N_target         Number of neutrons in the target
        \param string parametrization  Cross section parametrization [KORSMEIER_II (default), KORSMEIER_I, WINKLER, DI_MAURO_I, DI_MAURO_II]
        \param string coalescence      Coalescence model, from[FIXED_P0 (default), ENERGY_DEP__VAN_DOETINCHEM], cf. inv_AA_Dbar_CM
        
        \return double XS              Cross section in mbarn/GeV
        """
    return xs_cpp.dEn_AA_Dbar_LAB(Tn_proj_LAB, T_Dbar_LAB, int(A_projectile), int(N_projectile), int(A_target), int(N_target), _parametrization[parametrization], _coalescence[coalescence])








