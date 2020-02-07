#include <iostream>
#include<stdlib.h>
#include "ic.h"


/*RAM access modifier*/
#define ENABLE 0
#define SET 1

/*CPU instructions*/
#define ADD 0
/* ADD instruction
   ADD <operand1> <operand2>
*/
#define COMPARE 1
/* COMPARE instruction
   Not defined
*/
#define IN 2
/* IN instruction
   IN <input variable stored>
*/
#define JUMP 3
/* JUMP instruction
   JUMP <address of jump to location>
*/
#define JUMP_IF 4
/* JUMP_IF instruction
   JUMP_IF <operand1> <operator> <operand2> <address of jump to location if condition if true>
*/
#define LOAD 5
/* LOAD instruction
   Not defined
*/
#define OUT 6
/* OUT instruction
   OUT <address of data to output>
*/
#define STORE 7
/* STORE instruction
   STORE <address of data> <address of location where data is to be stored>
*/
#define HALT 8
/* HALT instruction
   HALT
*/
#define EXIT 9
/* EXIT instruction
   EXIT
*/
#define DATA 10
/* DATA instruction
   DATA <type> <N values stored> <value1> <value2> <value3> ... <valueN>
*/

/*Relational operators*/
#define EQUAL 0
#define GREATER 1
#define SMALLER 2
#define GREATER_EQUAL 3
#define SMALLER_EQUAL 4
#define NOT_EQUAL 5

using namespace std;

/*clock cycle starts if clk = 1 and stops if clk = 0*/
int clk=1;

/*Main Memory*/
int ram[40] = {DATA,1,0,IN,0,STORE,4,26,OUT,2,STORE,2,14,ADD,0,1,0,STORE,16,2,STORE,2,24,JUMP_IF,0,SMALLER,0,8,HALT,EXIT};
/* addition program instructions
{IN,0,IN,0,STORE,1,12,STORE,3,12,ADD,0,0,0,OUT,13,HALT,EXIT}

addition program with try again
{DATA,1,1,IN,0,IN,0,STORE,4,14,STORE,6,15,ADD,0,0,0,OUT,16,IN,0,STORE,20,28,STORE,2,30,JUMP_IF,0,EQUAL,0,0,HALT,EXIT}

loop program with prints number till inputed N or for loop
{DATA,1,0,IN,0,STORE,4,26,OUT,2,STORE,2,14,ADD,0,1,0,STORE,16,2,STORE,2,24,JUMP_IF,0,SMALLER,0,8,HALT,EXIT}


*/

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
        cout<<_ram(_ram(pc + 1,ENABLE),ENABLE)<<"\n";
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
        pc = _ram(pc+1,ENABLE);

    }
    else if(inst == JUMP_IF)
    {
        if(_ram(pc+2,ENABLE) == 0)
        {
            if(_ram(pc+1,ENABLE) == _ram(pc+3,ENABLE))
            {
                pc = _ram(pc+4,ENABLE);
            }
            else
            {
                pc = pc + 5;
            }
        }
        else if(_ram(pc+2,ENABLE) == 1)
        {
            if(_ram(pc+1,ENABLE) > _ram(pc+3,ENABLE))
            {
                pc = _ram(pc+4,ENABLE);
            }
            else
            {
                pc = pc + 5;
            }
        }
        else if(_ram(pc+2,ENABLE) == 2)
        {
            if(_ram(pc+1,ENABLE) < _ram(pc+3,ENABLE))
            {
                pc = _ram(pc+4,ENABLE);
            }
            else
            {
                pc = pc + 5;
            }
        }
        else if(_ram(pc+2,ENABLE) == 3)
        {
            if(_ram(pc+1,ENABLE) >= _ram(pc+3,ENABLE))
            {
                pc = _ram(pc+4,ENABLE);
            }
            else
            {
                pc = pc + 5;
            }
        }
        else if(_ram(pc+2,ENABLE) == 4)
        {
            if(_ram(pc+1,ENABLE) <= _ram(pc+3,ENABLE))
            {
                pc = _ram(pc+4,ENABLE);
            }
            else
            {
                pc = pc + 5;
            }
        }
        else if(_ram(pc+2,ENABLE) == 5)
        {
            if(_ram(pc+1,ENABLE) != _ram(pc+3,ENABLE))
            {
                pc = _ram(pc+4,ENABLE);
            }
            else
            {
                pc = pc + 5;
            }
        }
        else
        {
            pc = 0;
        }


    }
    else if(inst == EXIT)
    {
        clk = 0;
        pc = pc + 1;
    }
    else if(inst == STORE)
    {
        _ram(_ram(pc+2,ENABLE),SET,_ram(_ram(pc+1,ENABLE),ENABLE));
        pc =  pc + 3;
    }
    else if(inst == DATA)
    {
        if(_ram(pc+1,ENABLE)==0)
        {
            pc = pc + 2;
        }
        else
        {
            pc = pc + _ram(pc+1,ENABLE) + 2;
        }
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
    cout<<ram[0]<<"\n";
    cout<<ram[1]<<"\n";
    cout<<ram[2]<<"\n";
    cout<<ram[3]<<"\n";
    cout<<ram[4]<<"\n";
    cout<<ram[5]<<"\n";
    cout<<ram[6]<<"\n";
    cout<<ram[7]<<"\n";
    cout<<ram[8]<<"\n";
    cout<<ram[9]<<"\n";
    cout<<ram[10]<<"\n";
    cout<<ram[11]<<"\n";
    cout<<ram[12]<<"\n";
    cout<<ram[13]<<"\n";
    cout<<ram[14]<<"\n";
    cout<<ram[15]<<"\n";
    cout<<ram[16]<<"\n";
    cout<<ram[17]<<"\n";

    return 0;
}
