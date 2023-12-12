#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#define pb push_back
#define pp pop_back
using namespace std;

int numberOfPages, pageFault=0, memorySize=3, recent=0, least= 0;
vector <int> pages;
vector <int> memory(memorySize,-1);

void readFile()
{
    int value;
    while(cin>>value)
    {
        pages.pb(value);
    }
    numberOfPages = pages.size(); 
}

int findPage(int page)
{
    for(int i=0 ; i<memorySize ; i++)
    {
        if(memory[i] == page)
        {
            return i;
        }
    }
    return -1;
}

void showMemory()
{
    for(int i=0 ; i<memorySize ; i++)
    {
        if(memory[i] != -1)
        {
            cout<<memory[i]<<" ";
        }
    }
}

int main()
{
    freopen("Input.txt","r",stdin);
    freopen("Output.txt","w",stdout);
    readFile();
    for(int i=0 , index ; i<numberOfPages;i++)
    {
        int flag = 0;
        cout<<pages[i]<<" : ";
        index = findPage(pages[i]);
        if(index == -1)
        {
            memory[recent] = pages[i];
            recent = (recent+1) % memorySize;
            flag =1;
        }
        else
        {
            pageFault++;
            if(recent == index)
            {
                recent = (recent+1) % memorySize;
            }
        }
        showMemory();
        if(flag == 0)
        {
            cout<<"(No change)"<<endl;
        }
        else
        {
            cout<<endl;
        }
    }
    cout<<"Page faults : "<<pageFault;
}