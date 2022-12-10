#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <set>
#include <map>
#include <ctime>

using namespace std;

class Instance{
    //private:

    /*double R;
    double G;
    double B;*/

    public:
      double letters[];// = new double[10];
      double isSkin;
    /*Instance(double R, double G, double B, int isSkin){
        this->R = R;
        this->G = G;
        this->B = B;
        this->isSkin = isSkin;
    }*/
      Instance(double letters2[], int isSkin) {
      double[] letters = new double[10];
      this->letters = letters2;
      this->isSkin = isSkin;
    }
    /*
    void setR(double R){
        this->R = R;
    }

    void setG(double G){
        this->G = G;
    }

    void setB(double B){
        this->B = B;
    }*/
    void setVal(double value, int index) {
      letters[index] = value;
    }
    double getVal(int index) {
      return letters[index];
    }/*
     double getR(){
        return R;
    }

     double getG(){
        return G;
    }

     double getB(){
        return B;
    }*/

     int skin(){
        return isSkin;
    }

    /*double calculateDistance(double otherR, double otherG, double otherB){
        return sqrt((R - otherR) * (R - otherR) + (G - otherG) * (G - otherG) + (B - otherB) * (B - otherB));

    }*/
    double calculateDistance(double otherLetters[]) {
      double sum = 0;
      for(int i = 0; i < letters.length; i++) {
        sum += (letters[i] - otherLetters[i]) * (letters[i] - otherLetters[i]);
      }
      return sqrt(sum);
    }

};

vector<string> split(string a,char e){//WHAT IS THIS
    vector<string> rez;
    string cur;
    for(int ctr1=0;ctr1<a.size();ctr1++){
        if(a[ctr1]!=e)
            cur.push_back(a[ctr1]);
        else
            rez.push_back(cur),cur.clear();
    }
    if(cur!="")
        rez.push_back(cur);
    return rez;
}


int main()
{
    string line;
    ifstream myfile("training.txt");
    vector<Instance> instances;

    //init
    if (myfile.is_open())
    {
        while (getline(myfile,line))
        {
            vector<string> parts = split(line, ' ');
            Instance instance(std::stod(parts[0]), std::stod(parts[1]), std::stod(parts[2]), std::stod(parts[3]), std::stod(parts[4]), std::stod(parts[5]), std::stod(parts[6]), std::stod(parts[7]), std::stod(parts[8]), std::stod(parts[9]));
            instances.push_back(instance);
        }
        myfile.close();
    }

    //find min and max
    /*double minR = instances[0].getR();
    double maxR = instances[0].getR();

    double minG = instances[0].getG();
    double maxG = instances[0].getG();

    double minB = instances[0].getB();
    double maxB = instances[0].getB();*/
    double min[] = new double[10];
    double max[] = new double[10];
    for(int i = 0; i < min.length; i++) {
      min[i] = instances[0].getVal(i);
    }

    for(int i = 0; i < instances.size(); i++){
      if(instances[i].getVal(i) > max[i]){
          max[i] = instances[i].getVal(i);
      }
      else if(instances[i].getVal() < min[i]){
          min[i] = instances[i].getVal(i);
      }
        /*if(instances[i].getR() > maxR){
            maxR = instances[i].getR();
        }
        else if(instances[i].getR() < minR){
            minR = instances[i].getR();
        }

        if(instances[i].getG() > maxG){
            maxG = instances[i].getG();
        }
        else if(instances[i].getG() < minG){
            minG = instances[i].getG();
        }

        if(instances[i].getB() > maxB){
            maxB = instances[i].getB();
        }
        else if(instances[i].getB() < minB){
            minB = instances[i].getB();
        }*/
    }


    //standardization
    for(int i = 0; i < instances.size(); i++){
        /*double curr = instances[i].getR();
        double res = (curr - minR) / (maxR - minR);
        instances[i].setR(res);

        curr = instances[i].getG();
        res = (curr - minG) / (maxG - minG);
        instances[i].setG(res);

        curr = instances[i].getB();
        res = (curr - minB) / (maxB - minB);
        instances[i].setB(res);
*/
      for(int j = 0; j < 10; j++) {
        double curr = instances[i].getVal(j);
        double res = (curr - min[j]) / (max[j] - minR[j]);
        instances[i].setVal(res, j);
      }
       // cout<<instances[i].getR()<<" "<<instances[i].getG()<<" "<<instances[i].getB()<<endl;
    }

    //setting k = sqrt(number of training instances)
    int k = sqrt(instances.size());

    //finding k-nn on input from test.txt
    ifstream new_file("test.txt");
    string new_line;

    //start time
    clock_t start_time = clock();

    int test_instance = 0;

     if (new_file.is_open())
    {
        while (getline(new_file,new_line))
        {

            test_instance++;

            vector<string> parts = split(new_line, ' ');

            set<double> distances;

            map<double, int> distanceToClass;

            double lets[] = new double[10];
            for(int i = 0; i < lets.length; i++) {
              lets[i] = std::stod(parts[i]);
              lets[i] = (lets[i] - min[i]) / (max[i] - min[i]);
            }

            /*double r = std::stod(parts[0]);
            double g = std::stod(parts[1]);
            double b = std::stod(parts[2]);

            r = (r - minR) / (maxR - minR);
            g = (g - minG) / (maxG - minG);
            b = (b - minB) / (maxB - minB);*/

            double minimum_distance = 500;
            for(int i = 0; i < instances.size(); i++){
                double d = instances[i].calculateDistance(lets[0], lets[1], lets[2], lets[3], lets[4], lets[5], lets[6], lets[7], lets[8], lets[9]);
                distances.insert(d);
                distanceToClass.insert(std::pair<double, int> (d, instances[i].skin()));
            }

            int firstClassCounter = 0;
            int secondClassCounter = 0;

            set<double>::iterator it = distances.begin();

            while(firstClassCounter != k && secondClassCounter != k){
                if(distanceToClass.find(*it)->second == 1){
                    firstClassCounter++;
                }
                else if(distanceToClass.find(*it)->second == 2){
                    secondClassCounter++;
                }
                it++;
            }

            if(firstClassCounter == k){
                printf("Class for %d object is: 1\n", test_instance);
            }
            else if(secondClassCounter == k){
                printf("Class for %d object is: 2\n", test_instance);
            }

        }

    }

     new_file.close();
     clock_t end_time = clock();
     double elapsed_secs = double(end_time - start_time) / CLOCKS_PER_SEC;

     cout<<"Elapsed time: "<<elapsed_secs<<" seconds."<<endl;
}
