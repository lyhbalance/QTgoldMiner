#include "data.h"

data::data()
{

}
int data::gameNumber=2;
int data::money=0;
int data::stoneBookMoney=0;
bool data::IfThreeleaves=false;
int data ::diamondAddMoney=0;
int data::bombNumber=0;
double data::bigGoldSpeed=0.3;
double data::smallGoldSpeed=0.8;
double data::stoneSpeed=0.4;
double data::luckyBagSpeed=0.5;
double data::diamondSpeed=1;
double data::boneSpeed=0.9;
double data::pigSpeed=0.9;
double data::strength=1;

void data::clearall()
{
    data::stoneBookMoney=0;
    data::IfThreeleaves=false;
    data ::diamondAddMoney=0;
    data::strength=1;

}
