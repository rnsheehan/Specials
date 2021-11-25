# Import libraries
# You should try an import the bare minimum of modules
import sys # access system routines
import os
import glob
import re

import math
import scipy
import numpy as np
import matplotlib.pyplot as plt

# add path to our file
sys.path.append('c:/Users/robertsheehan/Programming/Python/Common/')
sys.path.append('c:/Users/robertsheehan/Programming/Python/Plotting/')

import Common
import Plotting

MOD_NAME_STR = "Plots" # use this in exception handling messages
       
def Voigt_plot():
    # make a plot of the various computed Voigt functions
    # R. Sheehan 25 - 11 - 2021

    FUNC_NAME = ".Voigt_plot()" # use this in exception handling messages
    ERR_STATEMENT = "Error: " + MOD_NAME_STR + FUNC_NAME

    try:

        #filenames = glob.glob('Voigt_h*G_1_x0_0*')
        #filenames = glob.glob('Voigt_h_1*G*x0_0*')
        filenames = glob.glob('Voigt_h_1*G_1*x*')
        
        if filenames:
            # import the datasets
            hv_data = []; marks = []; labels = [];
            count = 0; 
            for f in filenames:
                vals = Common.extract_values_from_string(f)
                print(vals)
                data = np.loadtxt(f, unpack = True)
                hv_data.append(data);
                #labels.append('h = %(v1)s'%{"v1":vals[0]});
                #labels.append('G = %(v1)s'%{"v1":vals[1]});
                labels.append('$x_{0}$ = %(v1)s'%{"v1":vals[3].replace('.','')});
                marks.append(Plotting.labs_lins[count])
                count = count + 1
            #title = 'Voigt_G_%(v1)s_x0_%(v2)s'%{"v1":vals[1], "v2":vals[3].replace('.','')}
            #plottitle = ' G = %(v1)s, x0 = %(v2)s'%{"v1":vals[1], "v2":vals[3].replace('.','')}
            #title = 'Voigt_h_%(v1)s_x0_%(v2)s'%{"v1":vals[0], "v2":vals[3].replace('.','')}
            #plottitle = 'h = %(v1)s, x0 = %(v2)s'%{"v1":vals[0], "v2":vals[3].replace('.','')}
            title = 'Voigt_h_%(v1)s_G_%(v2)s'%{"v1":vals[0], "v2":vals[1]}
            plottitle = 'h = %(v1)s, G = %(v2)s'%{"v1":vals[0], "v2":vals[1]}
            
            # plot the original data with the fitted function                
            args = Plotting.plot_arg_multiple()
            
            args.loud = True
            args.crv_lab_list = labels
            args.mrk_list = marks
            args.x_label = 'X'
            args.y_label = 'Y'
            args.fig_name = title
            args.plt_title = plottitle
            
            Plotting.plot_multiple_curves(hv_data, args)
            
        else:
            ERR_STATEMENT = ERR_STATEMENT + "\nFile: " + filename + " not found"
            raise Exception
    except Exception as e:
        print(ERR_STATEMENT)
        print(e)

def main():
    pass

if __name__ == '__main__':
    main()

    pwd = os.getcwd() # get current working directory
    
    print(pwd)
    
    Voigt_plot()
    
