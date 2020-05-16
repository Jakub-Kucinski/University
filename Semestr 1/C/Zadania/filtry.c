#include<stdio.h>
#include<string.h>
/*Jakub Kuciński, nr indeksu 309881, Lista zadań 2, zadanie 1., 17.10.2018, grupa środa 10-12 wstęp do programowania w C */

//int iso[18]={161, 198, 202, 163, 209, 211, 166, 172, 175, 177, 230, 234, 179, 241, 243, 182, 188, 191};

int main(int argc, char *argv[])
{
    if(argc<=1)
    {
        printf("Brak argumentow \n"); return 1;
    }
    if(strcmp(argv[1], "iso2utf")==0)
    {
        int c=getchar();
        while(c!=EOF)
        {
            if(c<=127)
                putchar(c);
            else
            {
                switch(c)
                {
                    case 161:
                        putchar(0xC4);
                        putchar(0x84);
                        break;
                    case 198:
                        putchar(0xC4);
                        putchar(0x86);
                        break;
                    case 202:
                        putchar(0xC4);
                        putchar(0x98);
                        break;
                    case 163:
                        putchar(0xC5);
                        putchar(0x81);
                        break;
                    case 209:
                        putchar(0xC5);
                        putchar(0x83);
                        break;
                    case 211:
                        putchar(0xC3);
                        putchar(0x93);
                        break;
                    case 166:
                        putchar(0xC5);
                        putchar(0x9A);
                        break;
                    case 172:
                        putchar(0xC5);
                        putchar(0xB9);
                        break;
                    case 175:
                        putchar(0xC5);
                        putchar(0xBB);
                        break;
                    case 177:
                        putchar(0xC4);
                        putchar(0x85);
                        break;
                    case 230:
                        putchar(0xC4);
                        putchar(0x87);
                        break;
                    case 234:
                        putchar(0xC4);
                        putchar(0x99);
                        break;
                    case 179:
                        putchar(0xC5);
                        putchar(0x82);
                        break;
                    case 241:
                        putchar(0xC5);
                        putchar(0x84);
                        break;
                    case 243:
                        putchar(0xC3);
                        putchar(0xB3);
                        break;
                    case 182:
                        putchar(0xC5);
                        putchar(0x9B);
                        break;
                    case 188:
                        putchar(0xC5);
                        putchar(0xBA);
                        break;
                    case 191:
                        putchar(0xC5);
                        putchar(0xBC);
                        break;
                }
            }
            c=getchar();
        }
        return 0;
    }
    int a;
    if(strcmp(argv[1], "utf2iso")==0)
    {
        int c=getchar();
        while(c!=EOF)
        {
            if(c!=0xC4 && c!=0xC5 && c!=0xC3)
                putchar(c);
            else
            {
                switch(c)
                {
                    case 0xC4:
                        a=getchar();
                        switch(a){
                        case 0x84:
                            putchar(161);
                            break;
                        case 0x86:
                            putchar(198);
                            break;
                        case 0x98:
                            putchar(202);
                            break;
                        case 0x85:
                            putchar(177);
                            break;
                        case 0x87:
                            putchar(230);
                            break;
                        case 0x99:
                            putchar(234);
                            break;
                        }
                        break;
                    case 0xC5:
                        a=getchar();
                        switch(a){
                        case 0x81:
                            putchar(163);
                            break;
                        case 0x83:
                            putchar(209);
                            break;
                        case 0x9A:
                            putchar(166);
                            break;
                        case 0xB9:
                            putchar(172);
                            break;
                        case 0xBB:
                            putchar(175);
                            break;
                        case 0x82:
                            putchar(179);
                            break;
                        case 0x84:
                            putchar(241);
                            break;
                        case 0x9B:
                            putchar(182);
                            break;
                        case 0xBA:
                            putchar(188);
                            break;
                        case 0xBC:
                            putchar(191);
                            break;
                        }
                        break;
                    case 0xC3:
                        a=getchar();
                        switch(a){
                        case 0x93:
                            putchar(211);
                            break;
                        case 0xB3:
                            putchar(243);
                            break;
                        }
                        break;
                }
            }
            c=getchar();
        }
        return 0;
    }
}
