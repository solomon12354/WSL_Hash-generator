#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define INT_SIZE sizeof(int)        // Size of int in bytes
#define INT_BITS INT_SIZE * 8 - 1   // Size of int in bits - 1
unsigned int LeftRotate(unsigned int num, unsigned int rotation)
{
    int DROPPED_MSB;

    // The effective rotation
    rotation %= INT_BITS;


    // Loop till rotation becomes 0
    while(rotation--)
    {
        // Get MSB of num before it gets dropped
        DROPPED_MSB = (num >> INT_BITS) & 1;

        // Left rotate num by 1 and
        // Set its dropped MSB as new LSB
        num = (num << 1) | DROPPED_MSB;
    }

    return num;
}
unsigned int gcd(unsigned int a,unsigned int b){
    int min = a;
    if(a==b){
        return a;
    }
    if(a>b){
        min = b;
    }
    for(int i=min;i>=1;i--){
        if(a%i==0&&b%i==0){
            return i;
        }
    }

}
void hashcode(char* password,unsigned int *hashcodes){
    unsigned int hash[4] = {0x00112233,0x44332211,0x55667788,0x99008877};
    unsigned int k[64];
    unsigned int a=0;
    unsigned int b=0;
    unsigned int c=(unsigned int)abs(sin((double)hash[0])*pow(2,32));
    unsigned int d=0;
    unsigned int length = strlen(password);
    for(int i=0;i<64;i++){
        k[i] = (unsigned int)floor(abs(cos(hash[i%4]%(i+2))*pow(2,32)));
    }
    if(length%32!=0){
        for(int i=length;i<length-(length%32)+32;i++){
            *(password+i) = 0x00000001;
        }
    }
    for(int j=0;j<strlen(password);j++){
        hash[j%4] = hash[j%4]+ (unsigned int)*(password+j);
    }

    for(int i=0;i<64;i++){
        unsigned int temp = hash[0];
        hash[0] = hash[1];
        hash[1] = (hash[1]^hash[2])+LeftRotate(temp+hash[3],k[i]);
        hash[2] = hash[3];
        hash[3] = temp;
        a = (hash[0]^b)%17;
        b = (hash[1]&c)%5;
        c = LeftRotate(hash[2],3)%23;
        d = (unsigned int)(cos((double)(i)+gcd(b,c))*pow(2,32))%29;
    }

    for(int i=0;i<4;i++){
        *(hashcodes+i) = hash[i];
    }
}
void printHash(unsigned int hash[4]){
    for(int i=0;i<4;i++){
        printf("%.8x ",hash[i]);
    }
    printf("\n");
}
int main()
{
    while (1) {
        char password[100000] = {0};
        unsigned int hash[4] = {0};
        printf("Input your password:");
        gets(password);
        printf("%s\n",password);
        hashcode(password,hash);
        printHash(hash);
    }
    system("PAUSE");
    return 0;
}
