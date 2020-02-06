#include <iostream>
#include<stdlib.h>
#include "ic.h"


/*RAM access modifier*/
#define ENABLE 0
#define SET 1

/*CPU instructions*/
#define ADD 0
#define COMPARE 1
#define IN 2
#define JUMP 3
#define JUMP_IF 4
#define LOAD 5
#define OUT 6
#define STORE 7
#define HALT 8
#define EXIT 9

using namespace std;

/*clock cycle starts if clk = 1 and stops if clk = 0*/
int clk=1;

/*Main Memory*/
int ram[18] = {IN,0,IN,0,STORE,1,11,STORE,
,12,ADD,0,0,0,OUT,13,HALT,EXIT};
/*              0 1  2 3   4   5 6   7    8 9  10  111213 14 15 16  17
int bus[4];

/*Registers*/
int pc=0;
int ir=0;
int mar=0;
int mdr=0;
int acc=0;

int add(int a,int b)
{
    int c;
    return c = a+b;
}
int _ram(int addr,int choice)
{
        return ram[addr];
}

void _ram(int addr,int choice,int data)
{
    if(choice == SET)
    {
        ram[addr] =  data;
    }
}

void instruction(int inst=0)
{
   if(inst == ADD)
   {
        _ram(pc + 3,SET,add(_ram(pc+1,ENABLE),_ram(pc+2,ENABLE)));
        pc = pc + 4;
   }
   else if(inst == OUT)
   {
       cout<<_ram(_ram(pc + 1,ENABLE),ENABLE);
       pc = pc +2;
   }
   else if(inst == HALT)
   {


       pc = pc + 1;
       system("pause");

   }
   else if(inst == IN)
   {
       int temp=0;
       cin>>temp;
       _ram(pc+1,SET,temp);
       pc =  pc + 2;
   }
   else if(inst == JUMP)
   {
     int temp = _ram(_ram(pc+1,ENABLE),ENABLE);
     pc  = temp;
   }
   else if(inst == EXIT)
   {
       clk = 0;
       pc = pc + 1;
   }
   else if(inst == STORE)
   {
       _ram(_ram(pc+2,ENABLE),SET,_ram(pc+1,ENABLE));
       pc =  pc + 3;
   }

}

void alu()
{

}

void control_unit()
{
  instruction(_ram(pc,ENABLE));
}
int main()
{
    while(clk)
    {
        if(clk==0)
        {
            break;
        }
        control_unit();
    }

    return 0;
}
