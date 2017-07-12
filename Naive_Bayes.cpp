#include<iostream>
#include<string>
#include<sstream>
#include <fstream>
#include<math.h>
using namespace std;

int main()
{
    double imgf[70][60]={0.0};//Arrays to store pixel probabilitu of face
    double imgnf[70][60]={0.0};//Arrays to store pixel probabilitu of non-face
    int i,j;
    int n = 451;//Total number of images
    int ct=0;
    int k=0;
    int a[n];
    //File paths for testing and training data
    string f1name = "C:\\cygwin\\home\\Nishanth\\ml3\\facedatatrain";
    string f2name = "C:\\cygwin\\home\\Nishanth\\ml3\\facedatatrainlabels";
    string f3name = "C:\\cygwin\\home\\Nishanth\\ml3\\facedatatest";
    string f4name = "C:\\cygwin\\home\\Nishanth\\ml3\\facedatatestlabels";
    ifstream data1;
    ifstream data2;
    ifstream data3;
    ifstream data4;

    //Error Handling
    string line;
    data2.open(f2name.c_str());
    if(data2==NULL)
    {
       cout<<"error in opening"<<endl;
    }

    for(i=0;i<n;i++)
       a[i]=0;
    i=0;
    while(!data2.eof())//Store labels of training data
    {
        if(data2.eof() == 1)
        break;
        getline(data2,line);
        if(line=="0")
        a[i]=0;
        else if(line=="1")
        a[i]=1;
        i++;
    }
    int face=0;
    int non_face=0;
    for(i=0;i<n;i++)//Calculate number of faces and non-face
     if(a[i]==1)
      face++;
     else
      non_face++;
    double f = (double)face/n;//Probability of face and non-face
    double nf = (double)non_face/n;
    data2.close();
    data1.open(f1name.c_str());
    if(data1==NULL)//Error handling
     {
       cout<<"error in opening"<<endl;
     }
     k=0;
     while (! data1.eof() )//Read input training data and change the probability matrix accordingly
     {
        if(a[k]==1)
        {
            for(i=0;i<70;i++)
            {
               getline(data1,line);
               for(j=0;j<60;j++)
               {
                  if(line[j] == ' ')
                    imgf[i][j]+=0;
                  else if(line[j] == '#')
                    imgf[i][j]+=1;
               }
            }
        }
        else if(a[k]==0)
        {
            for(i=0;i<70;i++)
            {
               getline(data1,line);
               for(j=0;j<60;j++)
               {
                  if(line[j] == ' ')
                    imgnf[i][j]+=0;
                  else if(line[j] == '#')
                    imgnf[i][j]+=1;
               }
            }

        }
        k++;
     }
     data1.close();
     for(i=0;i<70;i++)//Divide by total number of faces/non-faces to get pixel probability
        {for(j=0;j<60;j++)
            {imgf[i][j]/=face;
             imgnf[i][j]/=non_face;
            }
        }
     data4.open(f4name.c_str());
     int actual[150]={0};
     i=0;
     while(!data4.eof())//Read test data labels
     {
        getline(data4,line);
        if(line=="0")
        actual[i] = 0;
        else if(line=="1")
        actual[i] = 1;
        i++;
     }
     data4.close();
     int tp=0,tn=0,fp=0,fn=0;
     data3.open(f3name.c_str());
    if(data3==NULL)
     {
       cout<<"error in opening"<<endl;
     }
     k=0;
     int x=0;
     double accuracy = 0.0;
     while (! data3.eof() )//Read test data input values
     {
         x=0;
         //Calculate probability of test image being a face or a non face
         double it_face=0,it_nonface=0;
            for(i=0;i<70;i++)
            {
               getline(data3,line);
               for(j=0;j<60;j++)
               {
                  if(line[j] == '#')
                    {
                        it_face+=log(imgf[i][j]);
                        it_nonface+=log(imgnf[i][j]);
                    }
                    else if(line[j] == ' ')
                    {
                        it_face+=log(1-imgf[i][j]);
                        it_nonface+=log(1-imgnf[i][j]);
                    }
               }
               ct++;
            }
            cout<<k<<" ";
            if((it_face+log(f) )>=(it_nonface + log(nf)))//Output actual and predicted results
                {x=1;
                cout<<"Actual = "<<actual[k]<<" Predicted = "<<x<<endl;}
            else
                {x=0;
                cout<<"Actual = "<<actual[k]<<" Predicted = "<<x<<endl;}
            if(x&&actual[k])//Calculate confusion matrix
              tp++;
            else if(!x&&!actual[k])
              tn++;
            else if(!x&&actual[k])
              fn++;
            else
              fp++;
        k++;
     }
     accuracy = (double)(tp + tn)/(tp+tn+fn+fp);//Print accuracy and confusion matrix
     cout<<"accuracy = "<<accuracy *(100)<<" %"<<endl;
     cout<<"            "<<"Predicted(Yes)"<<"      "<<"Predicted(No)"<<endl;
     cout<<"Actual(Yes) "<<"    "<<tp<<"     "<<"           "<<fn<<"          "<<endl;
     cout<<"Actual(No)  "<<"     "<<fp<<"     "<<"          "<<tn<<"          "<<endl;
}
