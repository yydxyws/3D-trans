#include<iostream>
struct STU{
    char num [10];
    float score [3];
};

int main (){
    struct STU s [3] = {
        {"20021",90,95,85},
        {"20022",95,80,75},
        {"20023",100,95,90},
    },*p=s;
    int i;
    float sum = 0;
    for (i = 0; i < 3; i++)
        sum = sum + p->score[i];
    std::cout << sum;
}