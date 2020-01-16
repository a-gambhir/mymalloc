#include<stdio.h>
#include<stddef.h>
#include<sys/time.h>
#include "mymalloc.h"
//#include "mymalloc.c"


double testA() {

    int * a ;
    int i ;
    double output = 0 ;

    for (i = 0 ; i < 100 ; i++) {

        struct timeval start, finish ;
        gettimeofday(&start, NULL) ;

        int j ;

        for (j = 0 ; j < 150 ; j++) {

            a = malloc(1) ;
            free(a) ;

        }

        gettimeofday(&finish, NULL) ;

        output = output + (finish.tv_usec - start.tv_usec) ;

    }

    output = output / 100 ;

    return output ;

}

double testB() {

    int * b[150] ;
    int i, j ;
    double output = 0 ;

    for (i = 0 ; i < 100 ; i++) {

        struct timeval start, finish ;
        gettimeofday(&start, NULL) ;


        for (j = 0 ; j < 150 ; j++) {

            b[j] = malloc(1) ;

        }

        for (j = 0 ; j < 50 ; j++) {

          free(b[j]) ;

        }

        for (j = 50 ; j < 100 ; j++) {

            free(b[j]) ;

         }

        for (j = 100 ; j < 150 ; j++) {

            free(b[j]) ;

        }

        gettimeofday(&finish, NULL) ;

        output = output + (finish.tv_usec - start.tv_usec) ;

    }

    output = output / 100 ;

    return output ;

}

double testC() {

    double output = 0 ;
    int i ;

    for (i = 0 ; i < 100 ; i++) {

        struct timeval start, finish ;
        gettimeofday(&start, NULL) ;

        int * c[50] ;
        int allocCount = 0 ;
        while (allocCount < 50) {

            int rng = rand() % 2 ;

            if (rng == 0) {

                c[allocCount] = malloc(1) ;
                allocCount++ ;

            } else {

                if (allocCount > 0) {

                allocCount-- ;
                free(c[allocCount]) ;

                }

            }

        }

        while (allocCount > 0) {

            allocCount-- ;
            free(c[allocCount]) ;

        }

        gettimeofday(&finish, NULL) ;
        output = output + (finish.tv_usec - start.tv_usec) ;

    }

    output = output / 100 ;

    return output ;

}

double testD() {

    double output = 0 ;
    int i ;

    for (i = 0 ; i < 100 ; i++) {

        struct timeval start, finish ;
        gettimeofday(&start, NULL) ;

        int * d[50] ;
        int allocCount = 0 ;
        int sizeCount = 0 ;
        while (allocCount < 50) {

            int rng = rand() % 2 ;
            int randomSize = (rand() % 63) + 1 ;

            if (rng == 0) {

                d[allocCount] = malloc(1) ;
                allocCount++ ;
                sizeCount = sizeCount + randomSize ;

            } else {

                if (allocCount > 0) {

                allocCount-- ;
                free(d[allocCount]) ;

                }

            }

        }

        while (allocCount > 0) {

            allocCount-- ;
            free(d[allocCount]) ;

        }

        gettimeofday(&finish, NULL) ;
        output = output + (finish.tv_usec - start.tv_usec) ;

    }

    output = output / 100 ;

    return output ;

}

double testE() {

    double output = 0 ;

    int i = 0 ;

    for (i = 0 ; i < 100 ; i++) {

        struct timeval start, finish ;
        gettimeofday(&start, NULL) ;

        int *e[50] ;
        int j ;
        for (j = 0 ; j < 50 ; j++) {


            e[j] = malloc(1) ;

        }

        for (j = 0 ; j < 50 ; j += 2) {

            free(e[j]) ;

        }

        for (j = 1 ; j < 50 ; j += 2) {

            free(e[j]) ;

        }

        gettimeofday(&finish, NULL) ;
        output = output + (finish.tv_usec - start.tv_usec) ;

    }

    output = output / 100 ;

    return output ;

}

double testF() {

   double output = 0 ;

    int i = 0 ;

    for (i = 0 ; i < 100 ; i++) {

        struct timeval start, finish ;
        gettimeofday(&start, NULL) ;

        int *f[50] ;
        int j ;
        for (j = 0 ; j < 50 ; j++) {

            f[j] = malloc(1) ;

        }

        for (j = 0 ; j < 50 ; j += ((rand() % (8)) + 1)) {

            free(f[j]) ;

        }

        for (j = 1 ; j < 50 ; j++) {

            Node *p = (void *)f[j] ;
            p-- ;

            if (p->inUse == 1) {

             free(f[j]) ;

            }

        }

        gettimeofday(&finish, NULL) ;
        output = output + (finish.tv_usec - start.tv_usec) ;

    }

    output = output / 100 ;

    return output ;


}

int main(int argc, char ** argv) {

    printf("Workload A Runtime Mean: %.2f milliseconds\n", testA()) ;
    printf("Workload B Runtime Mean: %.2f milliseconds\n", testB()) ;
    printf("Workload C Runtime Mean: %.2f milliseconds\n", testC()) ;
    printf("Workload D Runtime Mean: %.2f milliseconds\n", testD()) ;
    printf("Workload E Runtime Mean: %.2f milliseconds\n", testE()) ;
    printf("Workload F Runtime Mean: %.2f milliseconds\n", testF()) ;


return ;

}
