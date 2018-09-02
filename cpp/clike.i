%module clike
%include "std_string.i"

%{
    #define SWIG_FILE_WITH_INIT
    #include "clike.h"
    #include "string"
%}

%include "numpy.i"

%init %{
    import_array();
%}


%apply (double* IN_ARRAY1, int DIM1) {(double* C_array, int len_C_array)};

double inv_pp_pbar_CM__Winkler( double s, double E_pbar_d, double pT_pbar, double* C_array, int len_C_array );

double deltaHyperon( double s, double* C_array, int len_C_array );
double deltaIsospin( double s, double* C_array, int len_C_array );


double inv_pp_pbar_CM__diMauro( double s, double E_pbar, double pT_pbar, double* C_array, int len_C_array );
double el_pp__diMauro (double s);
double tot_pp__diMauro(double s);

double pbar_overlap_function_projectile(double x_F);
double pbar_overlap_function_target    (double x_F);

