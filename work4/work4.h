#include <stdio.h>
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <time.h>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#define input "input.txt"
#define output "output.txt"
#define OX 500
#define OY 500
#define ndebug
int FURY;//!!!!!
using  std::string;
using  std::wstring;
using namespace std;
string strs[60];
int n;
ifstream fin(input);
FILE * fout = fopen(output,"w");
int skeleton[60],core;
bool visited[60];
set<int> alphabet[26];
int minx,miny,maxx,maxy;
int sum=0;
char a[1000][1000];
void transferv()
{
    int i,j,tmp;
    for (i=minx;i<maxx;i++)
    {
        for (j=miny;j<(miny+maxy)/2;j++)
        {
            tmp = a[i][maxy-j+miny];a[i][maxy-j+miny]=a[i][j];a[i][j]=tmp;
        }
    }
}
void transferh()
{
    int i,j,tmp;
    for (i=miny;i<maxy;i++)
    {
        for (j=minx;j<(minx+maxx)/2;j++)
        {
            tmp = a[maxx-j+minx][i];a[maxx-j+minx][i]=a[j][i];a[j][i]=tmp;
        }
    }
}
string reverse(string sample)
{
    string tmp;
    int i;
    for (i=sample.length()-1;i>=0;i--){tmp.append(1,sample[i]);}
    return tmp;
}
string trim(string sample)
{
    int t;
    t = 0;
    while(sample[t]==' '){t++;}
    sample = sample.erase(0,t);
    t = 0;
    while(sample[sample.length()-1-t]==' '){t++;}
    sample = sample.erase(sample.length()-t,t);
    return sample;
}
int compare (string pattern,string ith)
{
    int i,now = 0;
    int start=-1;
    if (ith.length()<=FURY){return -1;}
    for (i=0;i<pattern.length();i++)
    {
        if (pattern[i]==ith[now]||ith[i]==' ')
        {
            now++;
            if (now==1){start=i;}
            if (now==ith.length()){return start;}
        }
        else{now=0;}
    }
    return -1;
}
void ExpandArea(int x,int y,int z,int w)
{
    if (min(x,z)<minx) {minx = min(x,z);}
    if (max(x,z)>maxx) {maxx = max(x,z);}
    if (min(y,w)<miny) {miny = min(y,w);}
    if (max(y,w)>maxy) {maxy = max(y,w);}
}
void plot()
{
    int i,j,k,crux,product;
    memset(visited,0,60*sizeof(bool));
    visited[core]=true;
    //FURY=1;//!!!!
    for (i=0;i<1000;i++)
    {
        for (j=0;j<1000;j++)
        {
            a[i][j]=' ';
        }
    }
    minx=OX;
    maxx=OX+strs[core].length()-1;
    miny=OY;
    maxy=OY;
    for (i=strs[core].length()-1;i>=0;i--)
    {
        a[OX+i][OY]=strs[core][i];
        if (skeleton[i]==-1) {continue;}
        visited[i]=true;
        crux = 0;product = 1000000;
        for (j=0;j<strs[skeleton[i]].length();j++)
        {
            if (strs[skeleton[i]][j]==strs[core][i])
            {
                if ((j-strs[skeleton[i]].length()/2)*(j-strs[skeleton[i]].length()/2)<product)
                {
                    crux = j;
                    product = (j-strs[skeleton[i]].length()/2)*(j-strs[skeleton[i]].length()/2);
                }
            }
        }
        crux = strs[skeleton[i]].find(strs[core][i]);
        for (j=0;j<strs[skeleton[i]].length();j++)
        {
            a[OX+i+j-crux][OY+j-crux]=(char)strs[skeleton[i]][j];
            ExpandArea(OX+i+j-crux,OY+j-crux,OX+i+j-crux,OY+j-crux);
        }
    }

    //extend diag

    string sample,pattern,t;
    int start,pos,shift;

    for (i=minx;i<=maxx;i++)
    {
        sample = "";
        for (j=maxy;j>=max(miny,maxy-(maxx-i));j--)
        {
            sample.append(1,a[i+maxy-j][j]);
        }
        sample = trim(sample);
        for (j=0;j<n;j++)
        {
            if (visited[j]) {continue;}
            pattern = strs[j];
            pos = compare(pattern,sample);
            if (pos>=0)
            {
                for (k=maxy;k>=max(miny,maxy-(maxx-i));k--)
                {
                    if (a[i+maxy-k][k]!=' '){shift = k;break;}
                }
                shift = maxy-shift;
                for (k=0;k<pattern.length();k++)
                {
                    a[i-pos+k+shift][maxy+pos-k-shift] = pattern[k];
                }
                ExpandArea(i-pos+k-1+shift,maxy+pos-k+1-shift,i-pos+shift,maxy+pos-shift);
                visited[j]=true;
                sum++;
                break;
            }
            pattern = reverse(strs[j]);
            pos = compare(pattern,sample);
            if (pos>=0)
            {
                for (k=maxy;k>=max(miny,maxy-(maxx-i));k--)
                {
                    if (a[i+maxy-k][k]!=' '){shift = k;break;}
                }
                shift = maxy-shift;
                for (k=0;k<pattern.length();k++)
                {
                    a[i-pos+k+shift][maxy+pos-k-shift] = pattern[k];
                }
                ExpandArea(i-pos+k-1+shift,maxy+pos-k+1-shift,i-pos+shift,maxy+pos-shift);
                sum++;
                visited[j]=true;
                break;
            }

        }
    }


#ifndef ndebug
    for (i=minx;i<=maxx;i++)
    {
        for (j=miny;j<=maxy;j++)
        {
            if (a[i][j]!=' ')
            {
                cout<<a[i][j];
            }
            else {cout<<'-';}
        }string sample(""),pattern;
        cout<<endl;
    }
    cout<<sum<<endl;
#endif // ndebug    //extend vertical

    for (i=miny;i<=maxy;i++)
    {
        sample = "";
        for (j=minx;j<=maxx;j++)
        {
            sample.append(1,a[j][i]);
        }
        sample = trim(sample);
        for (j=0;j<n;j++)
        {
            if (visited[j]) {continue;}
            pattern = strs[j];
            pos = compare(pattern,sample);
            if (pos>=0)
            {
                for (k=minx;k<=maxx;k++)
                {
                    if (a[k][i]!=' '){shift = k;break;}
                }
                shift = shift-minx;
                for (k=0;k<pattern.length();k++)
                {
                    a[minx+k-pos+shift][i]=pattern[k];
                }
                ExpandArea(minx+k-1-pos+shift,i,minx-pos+shift,i);
                sum++;
                visited[j]=true;
                break;
            }
            pattern = reverse(strs[j]);
            pos = compare(pattern,sample);
            if (pos>=0)
            {
                for (k=minx;k<=maxx;k++)
                {
                    if (a[k][i]!=' '){shift = k;break;}
                }
                shift = shift-minx;
                for (k=0;k<pattern.length();k++)
                {
                    a[minx+k-pos+shift][i]=pattern[k];
                }
                ExpandArea(minx+k-1-pos+shift,i,minx-pos+shift,i);
                sum++;
                visited[j]=true;
                break;
            }
        }
    }

#ifndef ndebug
    for (i=minx;i<=maxx;i++)
    {
        for (j=miny;j<=maxy;j++)
        {
            if (a[i][j]!=' ')
            {
                cout<<a[i][j];
            }
            else {cout<<'-';}
        }string sample(""),pattern;
        cout<<endl;
    }
    cout<<sum<<endl;
#endif // ndebug
    //extend horizontal
    FURY = 0;//!!!
    for (i=minx;i<=maxx;i++)
    {
        sample = "";
        for (j=miny;j<=maxy;j++)
        {
            sample.append(1,a[i][j]);
        }
        sample = trim(sample);
        for (j=0;j<n;j++)
        {
            if (visited[j]) {continue;}
            pattern = strs[j];
            pos = compare(pattern,sample);
            if (pos>=0)
            {
                for (k=minx;k<=maxx;k++)
                {
                    if (a[i][k]!=' '){shift = k;break;}
                }
                shift = shift-miny;
                for (k=0;k<pattern.length();k++)
                {
                    a[i][miny+k+shift-pos]=pattern[k];
                }
                ExpandArea(i,miny+k-1+shift-pos,i,miny+shift-pos);
                sum++;
                visited[j]=true;
                break;
            }
            pattern = reverse(strs[j]);
            pos = compare(pattern,sample);
            if (pos>=0)
            {
                for (k=minx;k<=maxx;k++)
                {
                    if (a[i][k]!=' '){shift = k;break;}
                }
                shift = shift-miny;
                for (k=0;k<pattern.length();k++)
                {
                    a[i][miny+k+shift-pos]=pattern[k];
                }
                ExpandArea(i,miny+k-1+shift-pos,i,miny+shift-pos);
                sum++;
                visited[j]=true;
                break;
            }
        }
    }

#ifndef ndebug
    for (i=minx;i<=maxx;i++)
    {
        for (j=miny;j<=maxy;j++)
        {
            if (a[i][j]!=' ')
            {
                cout<<a[i][j];
            }
            else {cout<<'-';}
        }string sample(""),pattern;
        cout<<endl;
    }
    cout<<sum<<endl;
#endif // ndebug
    set<int>::iterator index;
    maxx+=2;miny-=2;
    for (i=minx;i<=maxx;i++)
    {
        for(j=maxy;j>=miny;j--)
        {
            if (a[i][j]!=' ')
            {
                for (index = alphabet[a[i][j]-65].begin();index != alphabet[a[i][j]-65].end();index++)
                {
                    if (visited[*index]) {continue;}
                    if (strs[*index][0]!=a[i][j]&&strs[*index][strs[*index].length()-1]!=a[i][j]) {continue;}
                    if (i-minx<=strs[*index].length()&&maxy-j<=strs[*index].length()) {continue;}
                    sum++;visited[*index] = true;
                    break;
                }
                sample = strs[*index];
                if (index==alphabet[a[i][j]-65].end()) {break;}
                if ((i-minx)>(maxy-j))
                {
                    for (k=0;k<sample.length();k++)
                    {
                        a[i+k][j] = sample[k];
                    }
                }
                else
                {
                    for (k=0;k<sample.length();k++)
                    {
                        a[i][j-k] = sample[k];
                    }
                }
            }
        }
    }
#ifndef ndebug
    for (i=minx;i<=maxx;i++)
    {
        for (j=miny;j<=maxy;j++)
        {
            if (a[i][j]!=' ')
            {
                cout<<a[i][j];
            }
            else {cout<<'-';}
        }string sample(""),pattern;
        cout<<endl;
    }
    cout<<sum<<endl;
#endif // ndebug

}

void init()
{
    int i,j,randomi;
    string tmp;
    srand((int)time(0));
    fin>>n;
    for (i=0;i!=n;i++){fin>>strs[i];}
    for (i=0;i!=n;i++)
    {
        randomi = rand()%n;
        tmp = strs[randomi];strs[randomi] = strs[i];strs[i] = tmp;
    }
    for (i=0;i!=n;i++)
    {
        for (j=0;j<strs[i].length();j++)
        {
            if (alphabet[int(strs[i][j])-65].find(i)==alphabet[int(strs[i][j])-65].end())
            {
                alphabet[int(strs[i][j])-65].insert(i);
            }
        }
    }

}
void set_skeleton()
{
    int i,j,seed,tmpsum,maxestimation=0;
    bool chosen[60];
    set<int>::iterator index;
    int tmpskeleton[60];
    srand((int)time(0));
    for (i=0;i<n;i++)
    {
        tmpsum=0;
        for (j=0;j<n;j++) {chosen[j]=false;tmpskeleton[j]=-1;}
        chosen[i] = true;
        for (j=0;j<strs[i].length();j++)
        {
            for (index = alphabet[strs[i][j]-65].begin();index != alphabet[strs[i][j]-65].end();index++)
            {
                if (chosen[*index]) {continue;}
                chosen[*index] = true;
                tmpskeleton[j] = *index;
                tmpsum++;
                break;
            }
        }
        seed = rand()%n/2;
        if (tmpsum+seed>maxestimation) {for (j=0;j<n;j++) {maxestimation=tmpsum+seed;core=i;skeleton[j]=tmpskeleton[j];sum=tmpsum;}}
    }
}
void deal(char *oa,int *ominx,int *ominy,int *omaxx,int *omaxy,int *osum,bool *ovisited)
{
    init();
    set_skeleton();
    plot();
    int i,j;
    int x,y,x0,y0,sqrt,sqrt0;
    x=maxx-minx;y=maxy-miny;sqrt=(x-y)*(x-y);
    x0=*omaxx-*ominx;y0=*omaxy-*ominy;sqrt0=(x0-y0)*(x0-y0);
    if (sum-x/3-y/3-sqrt<=*osum-x0/3-y0/3-sqrt0) return;
    for (i=minx;i<=maxx;i++)
    {
        for (j=miny;j<=maxy;j++)
        {
            oa[i*1000+j] = a[i][j];
        }
    }
    *ominx=minx;
    *ominy=miny;
    *omaxx=maxx;
    *omaxy=maxy;
    *osum =sum;
    for (i=0;i<60;i++) {ovisited[i]=visited[i];}
}

