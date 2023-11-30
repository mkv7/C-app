#ifndef _PROJECT__H_
#define _PROJECT__H_


typedef struct //Structure declaration.
{
    char name[100]; //Member (char variable)
    float price;    //Member (float variable)
    float revenue;  //Member (float variable)
} Game;

typedef struct //Structure declaration.
{
    Game *games;
    int count;      //Member (int variable)
    int capacity;   //Member (int variable)
} GameShop;


#endif //! _PROJECT__H_