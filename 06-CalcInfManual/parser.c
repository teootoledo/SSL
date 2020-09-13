// Parser --> GetToken --> Scanner
// Analizador sintáctico
// Prototipo

int tT[cEst][cTran] =

    {   //         0  1  2  3  4
        //         L  D  +  * EOF*/
        /* Q0  */ {2, 1, 4, 4, 3},
        /* Q1  */ {4, 1, 0, 0, 3},
        /* Q2  */ {2, 2, 0, 0, 3},
        /* FDT */ {3, 3, 3, 3, 3},
        /* ERR */ {4, 4, 4, 4, 4}};
