#include <iostream>
#include<time.h>
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

using namespace std;

int ram[16] = {ADD,01,01,0,OUT,3};
int bus[4];
int pc=0;
int ir=0;
int mar=0;
int mdr=0;
int acc=0;

int _ram(int addr,int choice)
{
    if(choice ==  ENABLE)
    {
        return ram[addr];
    }
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
        pc = pc + 4;

        _ram(pc - 1,SET,parallel_adder(_ram(pc-3,ENABLE),_ram(pc-2,ENABLE)));
   }
   else if(inst == OUT)
   {

       cout<<_ram(pc+1,ENABLE);
   }

}
void add()
{

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
    while(1)
    {

        control_unit();
    }

    return 0;
}