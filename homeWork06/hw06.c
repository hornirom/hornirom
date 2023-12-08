#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    char phoneNumber[21];
    char * name;
} TelephoneDirectory;

int isRightNumber ( char * x, int i, size_t length ) {
    //printf("%s | %d\n", x, length);
    while ( x[i] != '\0') {
        if ( !isdigit(x[i]) ) {
            return 0;
        }
        i++;
    }
    return 1;
}

int isInDirectory ( char * phone, char * name, TelephoneDirectory * directory, int count ) {
    for ( int i = 0; i < count; i++ ) {
        if ( strlen(name) != strlen(directory[i].name) || strlen(phone) != strlen(directory[i].phoneNumber)) continue;
        if (strcmp(directory[i].name, name) == 0 && strcmp(directory[i].phoneNumber, phone) == 0) {
            return 1;
        }
//        int j = 0;
//        while ( phone[j] != '\0' ) {
//            if ( phone[j] != directory[count].phoneNumber[j] ) break;
//            j++;
//        }
//        int k = 0;
//        while ( name[k] != '\0' ) {
//            if ( name[k] != directory[count].name[k] ) break;
//            k++;
//        }
//        if ( phone[j] == '\0' && name[k] == '\0' ) return 1;
    }
    return 0;
}

int isPrefixFound ( const char * x, const char * searchCode, int i ) {
    if ( strlen(x) < strlen(searchCode) - 2 ) return 0;
    while ( searchCode[i] != '\0' ) {
        if ( searchCode[i] != x[i - 2] ) return 0;
        i++;
    }
    return 1;
}

char decoding ( char i ) {
    if ( ((int)i > 67 && (int)i < 71) || ((int)i > 99 && (int)i < 103) ) return '3';
    if ( ((int)i > 64 && (int)i < 68) || ((int)i > 96 && (int)i < 100) ) return '2';
    if ( ((int)i > 70 && (int)i < 74) || ((int)i > 102 && (int)i < 106) ) return '4';
    if ( ((int)i > 73 && (int)i < 77) || ((int)i > 105 && (int)i < 109) ) return '5';
    if ( ((int)i > 76 && (int)i < 80) || ((int)i > 108 && (int)i < 112) ) return '6';
    if ( (int)i == ' ' ) return '1';
    if ( ((int)i > 79 && (int)i < 84) || ((int)i > 111 && (int)i < 116) ) return '7';
    if ( ((int)i > 83 && (int)i < 87) || ((int)i > 115 && (int)i < 119) ) return '8';
    if ( ((int)i > 86 && (int)i < 91) || ((int)i > 118 && (int)i < 123) ) return '9';
    return '0';
}

int isNameFound ( const char * x, char * searchCode, int i ) {
    if ( strlen(x) < strlen(searchCode) - 2 ) return 0;
    while ( searchCode[i] != '\0' ) {
        if (decoding(x[i - 2]) != searchCode[i] ) return 0;
        i++;
    }
    return 1;
}

int main() {
    int count = 0;
    int size = 20;
    TelephoneDirectory * directory;
    directory = (TelephoneDirectory *) calloc(size, sizeof(TelephoneDirectory));//67


    while( 1 ) {
        char rule;
        TelephoneDirectory input;
        char * mainString;
        int sizeM = 16;
        mainString = (char*) calloc(sizeM,sizeof(char));
        char c = getchar();
        int t = 0;
        while( c != '\n' && c != EOF ) {
            if( t + 2 == sizeM ) {
                sizeM *= 2;
                mainString = (char*) realloc(mainString, sizeM * sizeof(char));
            }
            mainString[t] = c;
            c = getchar();
            t++;
        }
        mainString[t] = '\0';
        //mainString = getString();
        size_t length = strlen(mainString);
        if ( length == 0 ) {
            free(mainString);
            break;
        }
        else if ( length < 3 ) {
            printf("Nespravny vstup.\n");
            free(mainString);
            continue;
        }
        else {
            rule = mainString[0];
            if ( rule != '+' && rule != '?' ) {
                printf("Nespravny vstup.\n");
                free(mainString);
                continue;
            }
            else {
                if ( mainString[1] != ' ' || mainString[2] == ' ' ) {
                    printf("Nespravny vstup.\n");
                    free(mainString);
                    continue;
                }
                else if ( rule == '+' ) {
                    int index = 2, k = 0;
                    int sizeName = 20, l = 0;
                    input.name = (char *) calloc ( sizeName, sizeof(char) );
                    while ( index < 22 && mainString[index] != ' ' ) {
                        input.phoneNumber[index - 2] = mainString[index];
                        if (!isdigit(mainString[index])) {
                            k = 1;
                            break;
                        }
                        index++;
                    }
                    if( k == 1 ) {
                        free(mainString);
                        free(input.name);
                        printf("Nespravny vstup.\n");
                        continue;
                    }
                    input.phoneNumber[index - 2] = '\0';
                    //printf("INDEX %d | %s\n", index, input.phoneNumber);
                    if ( index - 2 > 20 || index >= (int)length - 1 || mainString[index] != ' ' || mainString[index + 1] == ' ' ) {
                        free(mainString);
                        free(input.name);
                        printf("Nespravny vstup.\n");
                        continue;
                    }
                    else {
                        
                        for ( int i = index + 1; i < (int)length; i++ ) {
                            if ( !isalpha(mainString[i]) && mainString[i] != ' ' ) {
                                l = 1;
                                break;
                            }
                            if ( sizeName == i + 1 - index + 1 ) {
                                sizeName *= 2;
                                input.name = (char *) realloc( input.name, sizeName * sizeof(char) );
                            }
                            input.name[i - index - 1] = mainString[i];
                        }
                        input.name[length - index - 1] = '\0';
                        if ( l == 1 || mainString[length-1] == ' ' ) {
                            printf("Nespravny vstup.\n");
                            free(input.name);
                            free(mainString);
                            continue;
                        }
                        else {
                            if (isInDirectory(input.phoneNumber, input.name, directory, count)) {
                                printf("Kontakt jiz existuje.\n");
                                free(input.name);
                                free(mainString);
                                continue;
                            }
                            else {
                                printf("OK\n");
                                if ( size == count + 1 ) {
                                    size *= 2;
                                    directory = (TelephoneDirectory *) realloc(directory, size * sizeof(TelephoneDirectory));
                                }
                                directory[count] = input;
                                count++;
                                //free(input->name);
                            }
                        }
                        //free(input);
                        //printf("%s %s\n", input.phoneNumber, input.name);
                    }
                }
                else if ( rule == '?' ) {
                    if (!isRightNumber(mainString, 2, length)) {
                        free(mainString);
                        printf("Nespravny vstup.\n");
                        continue;
                    }
                    else {
                        int summary = 0;
                        int * indexArray;
                        indexArray = (int*) calloc(count, sizeof(int));
                        for ( int i = 0; i < count; i++ ) {
                            if (isPrefixFound((directory+i)->phoneNumber, mainString, 2) || isNameFound((directory+i)->name, mainString, 2)) {
                                indexArray[summary] = i;
                                summary++;
                                //printf("%s%s\n", directory[i].phoneNumber, directory[i].name);
                            }
                        }
                        if ( summary <= 10 ) {
                            for ( int i = 0; i < summary; i++ ) {
                                printf("%s %s\n", (directory+indexArray[i])->phoneNumber, (directory+indexArray[i])->name);
                            }
                        }
                        printf("Celkem: %d\n", summary);
                        free(indexArray);
                    }
                }
            }
        }
        free(mainString);
    }
    //free(input.name);
    for ( int i = 0; i < count; i++ ) {
        free(directory[i].name);
    }
    free(directory);
    return 0;
}
