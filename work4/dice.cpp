#include "work4.h"
#include <fstream>
#include <iostream>
#define output "output.txt"

using namespace std;
int main()
{
    FILE * fout = fopen(output,"w");
    int i,j;
    char *a;
    bool visited[60];
    int minx,miny,maxx,maxy,sum,maxsum;
    a = (char *)malloc(sizeof(char)*1000000);
    for (int times=0;times<1000;times++)
    {
        deal(a,&minx,&miny,&maxx,&maxy,&sum,visited);
    }
    for (i=minx;i<=maxx;i++)
    {
        for (j=miny;j<=maxy;j++)
        {
            if (a[i*1000+j]!=' ')
            {
                fprintf(fout,"%c",a[i*1000+j]);
            }
            else {fprintf(fout,"_");}
        }
        fprintf(fout,"\n");
    }
    string sample(""),pattern;
    cout<<endl<<sum<<endl;
}
