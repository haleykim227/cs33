//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name :
 * UCLA ID : 
 * Email :
 */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

void work_it_par(long *old, long *new) {
  int i, j, k, temp, one, two;
  int u, v, w;
  long compute_it;
  long aggregate=1.0;

  #pragma omp parallel for private(j,k,compute_it) reduction(+:aggregate)
  for (i=1; i<DIM-1; i++) {
      //one = i*DIM*DIM;
    for (j=1; j<DIM-1; j++) {
        //two = j*DIM*DIM;
      for (k=1; k<DIM-1; k++) {
        //compute_it = old[i*DIM*DIM+j*DIM+k] * we_need_the_func();
        //aggregate += compute_it / gimmie_the_func();
          compute_it = old[i*DIM*DIM+j*DIM*DIM+k] * we_need_the_func();
          aggregate += compute_it / gimmie_the_func();
      }
    }
  }

  printf("AGGR:%ld\n",aggregate);

    temp = 0;
#pragma omp parallel for private(j,k,u,v,w) reduction(+:temp)
  for (i=1; i<DIM-1; i++) {
      one = i*DIM*DIM;
    for (j=1; j<DIM-1; j++) {
        two = j*DIM;
      for (k=1; k<DIM-1; k++) {
          new[one+two+k] = 0;
        for (u=-1; u<=1; u++) {
            //three = u*DIM*DIM;
          for (v=-1; v<=1; v++) {
              //four = v*DIM;
            for (w=-1; w<=1; w++) {
               //new[i*DIM*DIM+j*DIM+k]+=old[(i+u)*DIM*DIM+(j+v)*DIM+(k+w)];
                //temp += old[(i+u)*DIM*DIM+(j+v)*DIM+(k+w)];
                temp += old[one+u*DIM*DIM+two+v*DIM+k+w];
                new[one+two+k] = temp;
            }
          }
        }
                      //new[i*DIM*DIM+j*DIM+k]+=old[(i+u)*DIM*DIM+(j+v)*DIM+(k+w)];
//                      new[one+two+k]+=old[(i+(-1))*three+(j+(-1))*DIM+(k+(-1))];
//                      new[one+two+k]+=old[(i+(-1))*three+(j+(-1))*DIM+(k+(0))];
//                      new[one+two+k]+=old[(i+(-1))*three+(j+(-1))*DIM+(k+(1))];
//                      new[one+two+k]+=old[(i+(-1))*three+(j+(0))*DIM+(k+(-1))];
//                      new[one+two+k]+=old[(i+(-1))*three+(j+(0))*DIM+(k+(0))];
//                      new[one+two+k]+=old[(i+(-1))*three+(j+(0))*DIM+(k+(1))];
//                      new[one+two+k]+=old[(i+(-1))*three+(j+(1))*DIM+(k+(-1))];
//                      new[one+two+k]+=old[(i+(-1))*three+(j+(1))*DIM+(k+(0))];
//                      new[one+two+k]+=old[(i+(-1))*three+(j+(1))*DIM+(k+(1))];
//                      new[one+two+k]+=old[(i+(0))*three+(j+(-1))*DIM+(k+(-1))];
//                      new[one+two+k]+=old[(i+(0))*three+(j+(-1))*DIM+(k+(0))];
//                      new[one+two+k]+=old[(i+(0))*three+(j+(-1))*DIM+(k+(1))];
//                      new[one+two+k]+=old[(i+(0))*three+(j+(0))*DIM+(k+(-1))];
//                      new[one+two+k]+=old[(i+(0))*three+(j+(0))*DIM+(k+(0))];
//                      new[one+two+k]+=old[(i+(0))*three+(j+(0))*DIM+(k+(1))];
//                      new[one+two+k]+=old[(i+(0))*three+(j+(1))*DIM+(k+(-1))];
//                      new[one+two+k]+=old[(i+(0))*three+(j+(1))*DIM+(k+(0))];
//                      new[one+two+k]+=old[(i+(0))*three+(j+(1))*DIM+(k+(1))];
//                      new[one+two+k]+=old[(i+(1))*three+(j+(-1))*DIM+(k+(-1))];
//                      new[one+two+k]+=old[(i+(1))*three+(j+(-1))*DIM+(k+(0))];
//                      new[one+two+k]+=old[(i+(1))*three+(j+(-1))*DIM+(k+(1))];
//                      new[one+two+k]+=old[(i+(1))*three+(j+(0))*DIM+(k+(-1))];
//                      new[one+two+k]+=old[(i+(1))*three+(j+(0))*DIM+(k+(0))];
//                      new[one+two+k]+=old[(i+(1))*three+(j+(0))*DIM+(k+(1))];
//                      new[one+two+k]+=old[(i+(1))*three+(j+(1))*DIM+(k+(-1))];
//                      new[one+two+k]+=old[(i+(1))*three+(j+(1))*DIM+(k+(0))];
//                      new[one+two+k]+=old[(i+(1))*three+(j+(1))*DIM+(k+(1))];
        new[one+two+k]/=27;
          
      }
    }
  }

#pragma omp parallel for private(j,k,u)
  for (i=1; i<DIM-1; i++) {
      //one = i*DIM*DIM;
    for (j=1; j<DIM-1; j++) {
        //two = j*DIM;
      for (k=1; k<DIM-1; k++) {
        u=(new[i*DIM*DIM+j*DIM+k]/100);
        if (u<=0) u=0;
        if (u>=9) u=9;
        histogrammy[u]++;
      }
    }
  }
}
