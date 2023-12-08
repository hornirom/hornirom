#include <stdio.h>

int isnum(char x) {

    switch(x) {
        case '1':
            return 1;
        case '2':
            return 1;
        case '3':
            return 1;
        case '4':
            return 1;
        case '5':
            return 1;
        case '6':
            return 1;
        case '7':
            return 1;
        case '8':
            return 1;
        case '9':
            return 1;
        case '0':
            return 1;
        default:
            return 0;

    }

}

int time(char x[], int *hours, int *minutes) {

    scanf("%s", x);
    if (x[1] != ':' && x[2] != ':') {
        printf("Nespravny vstup.\n");
        return 0;
    }
    else if (x[2] == ':') {
        if (isnum(x[0]) == 0
            || isnum(x[1]) == 0) {
            printf("Nespravny vstup.\n");
            return 0;
        }
        else {
            sscanf(&x[0], "%d", &*hours);
            //printf("%d ", *hours);
            if (*hours > 23 || *hours < 0) {
                printf("Nespravny vstup.\n");
                return 0;
            }

        }

        if (isnum(x[3]) == 0
            || isnum(x[4]) == 0) {
            printf("Nespravny vstup.\n");
            return 0;
        }
        else {
            sscanf(&x[3], "%d", &*minutes);
            //printf("%d\n", *minutes);
            if (*minutes > 59 || *minutes < 0) {
                printf("Nespravny vstup.\n");
                return 0;
            }

        }
    }
    else {
        if (isnum(x[0]) == 0) {
            printf("Nespravny vstup.\n");
            return 0;
        }
        else {
            sscanf(&x[0], "%d", &*hours);
            //printf("%d ", *hours);
            if (*hours < 0) {
                printf("Nespravny vstup.\n");
                return 0;
            }

        }

        if (isnum(x[2]) == 0
            || isnum(x[3]) == 0) {
            printf("Nespravny vstup.\n");
            return 0;
        }
        else {
            sscanf(&x[2], "%d", *&minutes);
            //printf("%d\n", *minutes);
            if (*minutes > 59 || *minutes < 0) {
                printf("Nespravny vstup.\n");
                return 0;
            }

        }
    }
    return 1;
}

int prestup(int prih, int prim, int odh, int odm) {

    int k = 0;
    //printf("%d %d\n%d %d\n", prih, prim, odh, odm);
    if ((prih < odh && prih+3 >= odh) || (prih == odh && prim+4 < odm) || (prih > 20 && odh < 3 && ((24 + odh)*60 + odm)-(prih*60 + prim)<=180)) k = 1;
    return k;

}

int main() {

    char priA[30], odA[30], priB[30], odB[30], priC[30], odC[30];
    int priAh = -1, priAmin = -1, odAh = -1, odAmin = -1, priBh = -1, priBmin = -1, odBh = -1, odBmin = -1, priCh = -1, priCmin = -1, odCh = -1, odCmin = -1;

    printf("Cas prijezdu vlaku A:\n");
    if (!time(priA, &priAh, &priAmin)) return 0;
    printf("Cas odjezdu vlaku A:\n");
    if (!time(odA, &odAh, &odAmin)) return 0;

    printf("Cas prijezdu vlaku B:\n");
    if (!time(priB, &priBh, &priBmin)) return 0;
    printf("Cas odjezdu vlaku B:\n");
    if (!time(odB, &odBh, &odBmin)) return 0;

    printf("Cas prijezdu vlaku C:\n");
    if (!time(priC, &priCh, &priCmin)) return 0;
    printf("Cas odjezdu vlaku C:\n");
    if (!time(odC, &odCh, &odCmin)) return 0;

    if (prestup(priAh, priAmin, odBh, odBmin) && prestup(priAh, priAmin, odCh, odCmin))
        printf("Z vlaku A lze prestoupit na vlaky B a C.\n");
    else if (prestup(priAh, priAmin, odBh, odBmin))
        printf("Z vlaku A lze prestoupit na vlak B.\n");
    else if (prestup(priAh, priAmin, odCh, odCmin))
        printf("Z vlaku A lze prestoupit na vlak C.\n");
    else printf("Z vlaku A nelze prestupovat.\n");

    if (prestup(priBh, priBmin, odAh, odAmin) && prestup(priBh, priBmin, odCh, odCmin))
        printf("Z vlaku B lze prestoupit na vlaky A a C.\n");
    else if (prestup(priBh, priBmin, odAh, odAmin))
        printf("Z vlaku B lze prestoupit na vlak A.\n");
    else if (prestup(priBh, priBmin, odCh, odCmin))
        printf("Z vlaku B lze prestoupit na vlak C.\n");
    else printf("Z vlaku B nelze prestupovat.\n");

    if (prestup(priCh, priCmin, odAh, odAmin) && prestup(priCh, priCmin, odBh, odBmin))
        printf("Z vlaku C lze prestoupit na vlaky A a B.\n");
    else if (prestup(priCh, priCmin, odAh, odAmin))
        printf("Z vlaku C lze prestoupit na vlak A.\n");
    else if (prestup(priCh, priCmin, odBh, odBmin))
        printf("Z vlaku C lze prestoupit na vlak B.\n");
    else printf("Z vlaku C nelze prestupovat.\n");

    return 0;
}
