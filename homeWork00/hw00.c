#include <iostream>

int main ( int argc, char * argv []) {
    printf("ml' nob:\n");
    const char* arr[12] = {
            "noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n",
            "bortaS bIr jablu'DI' reH QaQqu' nay'.\n",
            "Qu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n",
            "bISeH'eghlaH'be'chugh latlh Dara'laH'be'.\n",
            "qaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n",
            "Suvlu'taHvIS yapbe' HoS neH.\n",
            "Ha'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n",
            "Heghlu'meH QaQ jajvam.\n",
            "leghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n",
            "Qih mi' %d\n",
            "Neh mi'\n",
            "bIjatlh 'e' yImev\n"
    };
    float number;
    if (scanf("%f", &number) == 1) {
        printf("Qapla'\n");
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

    system ( "pause" );
    return 0;
}
