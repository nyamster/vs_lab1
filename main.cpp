#include "myneuro.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

float* inputs_list(const vector<string> &strList)
{
    float* inputs = (float*) malloc((784)*sizeof(float));
    string str;
//    bool ok=true;
    for (int i = 1; i<strList.size();i++)
    {
        str = strList.at(i);
        inputs[i-1]= ( (stof(str) / 255.0 *0.99)+0.01);
    }
    return inputs;
}

float* targets_list(const int &j)
{
     float* targets = (float*) malloc((10)*sizeof(float));
    for (int i = 0; i<10;i++)
    {
        if(i==j)
        targets[i]=(0.99);
        else
        targets[i]=(0.01);
    }

    return targets;
}


int main(int argc, char *argv[])
{
    myNeuro *nW = new myNeuro();
    vector<string> wordList;
    bool ok=true;
        ifstream f;
        f.open("/home/michail/labs/vs_lab1/mnist_train.csv");
        if (f.is_open())
        {
            int qq=0;
//            while(!f.atEnd())
           while(qq<3000)
            {
                qq++;
                if(qq%100==0)
                    cout << "Num: " << qq << "\n";
                string data;
                getline(f, data);
                stringstream ss(data);
                wordList.clear();
                while (!ss.eof())
                {
                    string word;
                        getline(ss, word, ',');
                        wordList.push_back(word);
                }
                string str = wordList.at(0);
                int ans = 0;
                if (str != "label")
                    ans = stoi(str);
                float * tmpIN = inputs_list(wordList);
                float * tmpTAR = targets_list(ans);
                nW->train(tmpIN,tmpTAR);
                delete tmpIN;
                delete tmpTAR;
            }

            f.close();
        }

        int sum = 0, correct = 0;
        ifstream f2("/home/michail/labs/vs_lab1/mnist_test.csv");
        if (f2.is_open())
        {
            while(!f2.eof())
            {
                string data;
                getline(f2, data);
                stringstream ss(data);
                wordList.clear();
                while (!ss.eof())
                {
                    string word;
                        getline(ss, word, ',');
                        wordList.push_back(word);
                }
                string str = wordList.at(0);
                int ans = 0;
                if (str != "label" && str != "")
                {
                    ans = stoi(str);
                    cout<<"__________________\n";
                    cout<<"For number "<<str << "\n";
                    float * tmpIN = inputs_list(wordList);
                    int guess = nW->query(tmpIN);
                    if (ans == guess)
                        correct++;
                    sum++;
                    delete tmpIN;
                    tmpIN = nullptr;
                }
            }

            f2.close();
        }
         delete nW;
        nW = nullptr;
        cout<<"_______________THE____END_______________\n";

        cout << "Guessed: " << correct << ", out of: " << sum << endl;



    return 0;
}
