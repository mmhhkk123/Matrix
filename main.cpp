#include <stdio.h>
#include <iostream>
#include "matrix.h"
#include <time.h>

using namespace std;
int Size = 0;

const char filename[40] = "inv_test_mult_100.csv"; //
const char checkfile[40] = "inv_test_mult_answer_100.csv";

void matrix_print(matrix_t *m)
{
    unsigned int i, j;

    for(i=0; i<m->row; i++)
    {
        for(j=0; j<m->col; j++)
            printf("%f    ", MATRIX(m, i, j));
        putchar('\n');
    }
}

float table[][4] =
{
    {1, 2, 3, 4},
    {6, 5, 4, 8},
    {8, 7, 9, 6},
    {2, 3, 4, 1}
};

float M3[3][3] = {
                   {4,  -2,   6},
                   {-2, 5,   7},
                   {6,   7,   20}
                  };
float M4[4][4] = {
                   {4,  2,  1,  5},
                   {8,  7,  2,  10},
                   {4,  8,  3,  6},
                   {6,  8,  4,  9}
                  };
float M5[5][5] = {
                  {1,   2,   5,    14,    4},
                  {2,   4,   50,    7,    2},
                  {5,   50,   6,   4.2,  3},
                  {14,   7,  4.2,  7.4, 0.2},
                  {4,    2,  3,   0.2,  1.3}
                };
float M6[5][5] = {
                  {1,   2,   3,    14,    4},
                  {0,   1,   50,    7,    3},
                  {1,   3,   2.1,   5,    2.1},
                  {0,   1,   4.2,   1,    1.3},
                  {1.1, 2,   3,     0.2,  1}
                };
float M16[16][16] = {
    {914.116136, 808.205876, 928.543882, 262.292519, 333.761528, 749.317513, 46.322676 , 291.385510, 250.730902, 464.544818, 977.510599, 304.259959, 29.366123 , 943.938669, 342.183839, 766.375137},
    {418.257248, 762.150097, 865.912770, 306.709086, 179.986942, 182.840557, 298.892424, 155.904665, 879.362180, 259.260054, 368.095879, 60.236247 , 532.080585, 380.589672, 862.041414, 134.761813},
    {654.354815, 191.665815, 775.435574, 335.495152, 15.809887 , 205.360524, 474.878188, 912.696991, 312.271948, 376.545077, 271.008246, 706.627031, 92.071470 , 627.361569, 9.716508  , 737.572867},
    {773.019479, 273.365439, 528.887640, 261.568379, 27.119040 , 899.588606, 694.759887, 311.381825, 14.625428 ,593.109647 , 424.812917, 510.617298, 971.300117, 710.370277, 923.824290, 856.952125},
    {490.743273, 653.425034, 245.633820, 114.988765, 22.386619 , 949.998489, 465.308827, 463.895434, 274.589763, 220.575531, 871.038255, 292.807698, 895.631165, 706.516309, 156.894046, 336.903461},
    {3.753988  , 368.082630, 444.458518, 788.423042, 795.155526, 223.124946, 818.851406, 315.191502, 712.000685, 136.867942, 331.514947, 473.493847, 504.828359, 603.139032, 510.160207, 6.160836  },
    {626.683505, 934.777102, 488.276060, 840.350010, 970.088593, 820.565159, 93.545199 , 566.369248, 356.837734, 279.689414, 463.678116, 673.255097, 227.820567, 581.322545, 107.877677, 288.207663},
    {707.373139, 766.756401, 641.603806, 95.052595 , 523.317528, 896.809385, 527.865465, 398.593364, 648.081228, 589.162027, 675.069037, 70.482869 , 675.355055, 371.494795, 880.636725, 352.362325},
    {59.495245 , 221.480496, 516.182745, 149.789526, 865.087366, 294.096641, 382.958950, 126.342089, 821.796029, 997.716216, 204.107120, 459.010017, 471.391137, 335.963603, 6.245076  , 838.006070},
    {990.223088, 616.659952, 279.548267, 274.839046, 564.068125, 202.173511, 977.719391, 838.899830, 484.904200, 281.131833, 63.193231 , 836.451697, 756.786082, 343.897359, 37.841278 , 522.400503},
    {417.084719, 721.985525, 285.542928, 642.327989, 968.348463, 681.989779, 7.414532  , 204.635090, 740.425516, 709.048810, 686.233751, 848.816499, 153.146283, 298.181109, 554.472408, 647.854653},
    {481.595579, 266.786306, 396.039607, 149.234470, 432.488238, 108.937392, 101.547510, 696.895304, 681.989043, 370.425691, 331.717474, 40.360613 , 711.455667, 249.620034, 668.307104, 213.448424},
    {856.174440, 158.864049, 177.279692, 784.635957, 158.359863, 109.520366, 282.580294, 198.736749, 287.751404, 498.285885, 72.907776 , 24.632360 , 306.555375, 607.690477, 320.634156, 798.005754},
    {677.399171, 135.304884, 838.217598, 446.479582, 397.486623, 475.935151, 820.333918, 363.622275, 984.910020, 361.087852, 522.002960, 573.377782, 109.982680, 909.358616, 705.900764, 913.587219},
    {450.825054, 641.388370, 121.933760, 79.431449 , 343.162737, 438.056507, 544.707760, 406.998765, 595.674913, 849.551292, 495.104024, 800.877729, 580.285013, 622.970300, 459.073596, 448.302092},
    {786.638182, 282.943143, 647.805712, 887.554177, 149.413614, 100.606141, 555.994850, 377.518425, 600.956343, 944.241178, 165.004173, 583.958472, 930.285650, 931.750821, 759.346640, 666.142013}
};


int main(int argc, char *argv[])
{
    clock_t start, finish;
    double time;
    start = clock();
    //readFile(filename, checkfile);

    finish = clock();
    time = (double) (finish - start) / CLOCKS_PER_SEC;

    /*  TIME COST */
    cout << "Solve the inverse of " <<  " inv_test_mult_100.csv cost " << time << "s." << endl;

    //return 0;


    matrix_t *m, *y, *mul, *chol, *l, *u;

    m = matrix_new();
    y = matrix_new();
    mul = matrix_new();
    chol = matrix_new();
    l = matrix_new();
    u = matrix_new();

    const int size = 4;
    matrix_reshape(m, size, size);
    matrix_reshape(y, size, size);
    matrix_reshape(chol, size, size);
    matrix_reshape(l, size, size);
    matrix_reshape(u, size, size);

    for(int i=0; i<m->row; i++)
    {
        for(int j=0; j<m->col; j++)
        {
            matrix_set(m, i, j, M4[i][j]);
        }
    }

//    for(int i=0; i<y->row; i++)
//    {
//        for(int j=0; j<y->col; j++)
//        {
//            matrix_set(y, i, j, M3[i][j]);
//        }
//    }




    matrix_cholesky(chol, m);
    matrix_lu(l, u, m);



    printf("cholesky:\n");
    matrix_print(chol);

    printf("L:\n");
    matrix_print(l);
    printf("U:\n");
    matrix_print(u);

    matrix_matmul(y, l, u);

    printf("L * U :\n");
    matrix_print(y);

    printf("m :\n");
    matrix_print(m);
    if(matrixIsEqual(m, y))
    {
        cout << "L U is right!!!" << endl;
    }


    matrix_delete(m);
    matrix_delete(y);
    matrix_delete(mul);
    finish = clock();
    time = (double) (finish - start) / CLOCKS_PER_SEC;
    cout << "COST: " << time << "s" << endl;


    return 0;
}
