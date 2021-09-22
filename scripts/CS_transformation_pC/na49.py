#! /usr/bin/env python

import glob
import math
import numpy as np
import os
CRACS = os.environ['CRACS']+'/scripts/CS_transformation_pp'

print CRACS

import sys
sys.path.append(CRACS)

import CRACS_CS_transformations as t


def readTab( file, err_scale, tab=1 ):
    global f, fScale

    line = '\n#\n#\n# Tab '+str(tab)+'\n'
    f.write( line )


    line  = '#*  '
    line += str('sqrt(s)'   ).ljust(20)+' '
    line += str('pT'        ).ljust(20)+' '
    line += str('xR'        ).ljust(20)+' '
    line += str('pT'        ).ljust(20)+' '
    line += str('xf'        ).ljust(20)+' '
    line += str('inv CS'    ).ljust(20)+' '
    line += str('CS_stat'   ).ljust(20)+' '
    line += str('CS_sys'    ).ljust(20)+' '
    line += str('err_scale' ).ljust(20)+'\n'
    f.write( line )



    tab1 = np.genfromtxt( file )
    for i in range( len(tab1[:,0]) ):
        CS   =  tab1[i,3]
        stat =  tab1[i,4]*CS*0.01
        sys  =  tab1[i,5]*CS*0.01
        scale = tab1[i,6]*0.01
        
        s   = t.s__from_pLAB(tab1[i,0])
        pT  = tab1[i,1]
        xF  = tab1[i,2]
        
        sig = np.sign(xF)
        
        if sig == 0:
            sig = 1

        xR  = t.x_R__from_s_pT_xF(s, pT, xF)*sig
        
        line = '   '
        line += str(np.sqrt(s)  ).ljust(20)+' '
        line += str(pT          ).ljust(20)+' '
        line += str(xR          ).ljust(20)+' '
        line += str(pT          ).ljust(20)+' '
        line += str(xF          ).ljust(20)+' '
        line += str(CS          ).ljust(20)+' '
        line += str(stat        ).ljust(20)+' '
        line += str(sys         ).ljust(20)+' '
        line += str(scale       ).ljust(20)+'\n'
        f.write( line )

    f.write( '#\n#End Tab '+str(tab)+'\n#' )




fScale=0.065

def write(data_dir, res_dir):
    global f, fScale
    f = open(res_dir+'/converted_na49.txt', 'w')

    line = '# NA49, DOI:10.1140/epjc/s10052-013-2364-3\n'
    f.write( line )
    line = '# p + C -> pbar + X \n #'
    f.write( line )

    readTab( data_dir+'/na49.txt', fScale   )


    f.close()














