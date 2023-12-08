#include <stdio.h>

int main ( int argc, char * argv []) {
    printf("ml' nob:\n");
    const char* arr[12] = {
            "Qapla'\nnoH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n",
            "Qapla'\nbortaS bIr jablu'DI' reH QaQqu' nay'.\n",
            "Qapla'\nQu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n",
            "Qapla'\nbISeH'eghlaH'be'chugh latlh Dara'laH'be'.\n",
            "Qapla'\nqaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n",
            "Qapla'\nSuvlu'taHvIS yapbe' HoS neH.\n",
            "Qapla'\nHa'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n",
            "Qapla'\nHeghlu'meH QaQ jajvam.\n",
            "Qapla'\nleghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n",
            "Qih mi' %d\n",
            "Neh mi'\n",
            "bIjatlh 'e' yImev\n"
    };
    float number;
    if (scanf("%f", &number) == 1) {
        if (int(number) >= 0 and int(number) <= 8) {
            if (number != 0 and number != 1 and number != 2 and number != 3 and number != 4 and number != 5 and number != 6 and number != 7 and number != 8) {
                printf("%s\n", arr[11]);
            }
            else {
                printf("%s\n", arr[int(number)]);
            }
        }
        else if (int(number) > 8 or int(number) < 0) {
            printf(arr[9], int(number));
            printf("\n");
        }

    }
    else printf("%s\n", arr[10]);

    //system ( "pause" );
    return 0;
}
