// Siberdt Hugo
// Sagdic Jean-Pierre

// Sources: https://perso.uclouvain.be/vincent.legat/zouLab/epl1110.php?action=loginCheck (consulté le 18/02/2023)

#include "glfem.h"


double integrate(double x[3], double y[3], double (*f) (double, double))
{
    double xi [3] = {1.0/6.0 ,2.0/3.0 ,1.0/6.0};
    double eta [3] = {1.0/6.0 ,1.0/6.0 ,2.0/3.0};
    double w [3] = {1.0/6.0 ,1.0/6.0 ,1.0/6.0};
    double xLoc[3];
    double yLoc[3];
    double I = 0.0;

    double J = (x[1] - x[0]) * (y[2] - y[0]) - (x[2] - x[0]) * (y[1] - y[0]);

    for (int i = 0; i < 3; ++i) {
        xLoc[i] =  x[0] * (1 - xi[i] - eta[i]) + eta[i] * x[1] + xi[i] * x[2];
        yLoc[i] =  y[0] * (1 - xi[i] - eta[i]) + eta[i] * y[1] + xi[i] * y[2];
    }

    for (int i = 0; i < 3; ++i) {
        if(J > 0){
            I += w[i] * f(xLoc[i],yLoc[i]) * J;
        }
        else{
            I += w[i] * f(xLoc[i],yLoc[i]) * (-J);
        }
    }

    glfemSetColor(GLFEM_BLACK); glfemDrawElement(x,y,3);
    glfemSetColor(GLFEM_BLUE);  glfemDrawNodes(x,y,3);
    glfemSetColor(GLFEM_RED);   glfemDrawNodes(xLoc,yLoc,3);

    return I;
}

double integrateRecursive(double x[3], double y[3], double (*f)(double,double), int n) {

    int triangles[4][3] = {{0 , 3 , 5} , {3 , 4 , 5}, {3 , 1 , 4} , {5 , 4 , 2}};
    double xi[6] = {0.0 ,1.0 ,0.0 ,0.5 ,0.5 ,0.0};
    double eta[6] = {0.0 ,0.0 ,1.0 ,0.0 ,0.5 ,0.5};
    double I = 0.0;
    double xLoc[3];
    double yLoc[3];

    if (n <= 0) {
        return integrate(x, y, f);
    }
    else {
        for(int i = 0; i < 4; i++){

            for(int j = 0; j < 3; j++){
                xLoc[j] =  x[0] * (1 - xi[triangles[i][j]] - eta[triangles[i][j]]) + eta[triangles[i][j]] * x[1] + xi[triangles[i][j]] * x[2];
                yLoc[j] =  y[0] * (1 - xi[triangles[i][j]] - eta[triangles[i][j]]) + eta[triangles[i][j]] * y[1] + xi[triangles[i][j]] * y[2];
            }

            I += integrateRecursive(xLoc, yLoc, f, n-1);
        }
        return I;
    }
}
