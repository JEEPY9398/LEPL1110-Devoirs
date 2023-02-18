// Siberdt Hugo
// Sagdic Jean-Pierre

#include <stdio.h>
#include <math.h>
#include "glfem.h"


double integrate(double x[3], double y[3], double (*f) (double, double))
{
    double e[3] = {1/6, 1/6, 2/3};
    double n[3] = {1/6, 2/3, 1/6};
    double w[3] = {1/6, 1/6, 1/6};
    double J = fabs((x[1] - x[0]) * (y[2] - y[0]) - (x[2] - x[0]) * (y[1] - y[0]));

    double xLoc[3];
    double yLoc[3];
    for (int i = 0; i < 3; ++i) {
        xLoc[i] = (1 - e[i] - n[i])*x[0] + e[i]*x[1] + n[i]*x[2];
        yLoc[i] = (1 - e[i] - n[i])*y[0] + e[i]*y[1] + n[i]*y[2];
    }

    double I = 0;
    for (int i = 0; i < 3; ++i) {
        I += w[i]*f(xLoc[i],yLoc[i])*J;
    }

//
// ... A modifier :-)
//
//
// Pour dessiner l'element, les sommets du triangle :-)
// Decommenter la ligne pour dessiner aussi les points d'integration
//

  glfemSetColor(GLFEM_BLACK); glfemDrawElement(x,y,3);
  glfemSetColor(GLFEM_BLUE);  glfemDrawNodes(x,y,3);
  glfemSetColor(GLFEM_RED);   glfemDrawNodes(xLoc,yLoc,3);
    


    return I;
}

double integrateRecursive(double x[3], double y[3], double (*f)(double,double), int n)
{

//
// ... A modifier :-)
// y-compris la ligne juste en dessous :-)
//
    double I = integrate(x,y,f);
    
//
//
//    
     
    return I;
}
