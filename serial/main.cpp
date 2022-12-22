/*
 * How to Run
 * g++ -o main.exe main.cpp; ./main.exe; rm ./main.exe;
 */




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
    private:
    double R;
    double G;
    double B;
    double one;
    double two;
    double three;
    double four;
    double five;
    double six;
    double seven;
    double isSkin;

    public:

    Instance(double R, double G, double B, int isSkin){
        this->R = R;
        this->G = G;
        this->B = B;
        this->isSkin = isSkin;
    }

    Instance(double R, double G, double B, double one, double two, double three, double four, double five, double six, double seven, int isSkin){
        this->R = R;
        this->G = G;
        this->B = B;

        this->one = one;
        this->two = two;
        this->three = three;
        this->four = four;
        this->five = five;
        this->six = six;
        this->seven = seven;
        this->isSkin = isSkin;
    }

    void setR(double R){
        this->R = R;
    }

    void setG(double G){
        this->G = G;
    }

    void setB(double B){
        this->B = B;
    }


    void setOne(double one){
        this->one = one;
    }

    void setTwo(double two){
        this->two = two;
    }

    void setThree(double three){
        this->three = three;
    }
    
    void setFour(double four){
        this->four = four;
    }

    void setFive(double five){
        this->five = five;
    }

    void setSix(double six){
        this->six = six;
    }

    void setSeven(double seven){
        this->seven = seven;
    }

     double getR(){
        return R;
    }

     double getG(){
        return G;
    }

     double getB(){
        return B;
    }

    double getOne(){
        return one;
    }

    double getTwo(){
        return two;
    }

    double getThree(){
        return three;
    }

    double getFour(){
        return four;
    }

    double getFive(){
        return five;
    }

    double getSix(){
        return six;
    }

    double getSeven(){
        return seven;
    }

     int skin(){
        return isSkin;
    }

    double calculateDistance(double otherR, double otherG, double otherB, double otherOne, double otherTwo, double otherThree, double otherFour, double otherFive, double otherSix, double otherSeven){
        return sqrt(
            (R - otherR) * (R - otherR) + 
            (G - otherG) * (G - otherG) + 
            (B - otherB) * (B - otherB) +
            (one - otherOne) * (one - otherOne) +
            (two - otherTwo) * (two - otherTwo) +
            (three - otherThree) * (three - otherThree) +
            (four - otherFour) * (four - otherFour) +
            (five - otherFive) * (five - otherFive) +
            (six - otherSix) * (six - otherSix) +
            (seven - otherSeven) * (seven - otherSeven)
            );

    }

};

vector<string> split(string a,char e){
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
            Instance instance(std::stod(parts[0]), std::stod(parts[1]), std::stod(parts[2]), std::stod(parts[3]));
            instances.push_back(instance);
        }
        myfile.close();
    }

    //find min and max
    double minR = instances[0].getR();
    double maxR = instances[0].getR();

    double minG = instances[0].getG();
    double maxG = instances[0].getG();

    double minB = instances[0].getB();
    double maxB = instances[0].getB();

    double minOne = instances[0].getOne();
    double maxOne = instances[0].getOne();

    double minTwo = instances[0].getTwo();
    double maxTwo = instances[0].getTwo();

    double minThree = instances[0].getThree();
    double maxThree = instances[0].getThree();

    double minFour = instances[0].getFour();
    double maxFour = instances[0].getFour();

    double minFive = instances[0].getFive();
    double maxFive = instances[0].getFive();

    double minSix = instances[0].getSix();
    double maxSix = instances[0].getSix();

    double minSeven = instances[0].getSeven();
    double maxSeven = instances[0].getSeven();

    for(int i = 0; i < instances.size(); i++){
        if(instances[i].getR() > maxR){
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
        }
    }


    //standardization
    for(int i = 0; i < instances.size(); i++){

        double curr = instances[i].getR();
        double res = (curr - minR) / (maxR - minR);
        instances[i].setR(res);

        curr = instances[i].getG();
        res = (curr - minG) / (maxG - minG);
        instances[i].setG(res);

        curr = instances[i].getB();
        res = (curr - minB) / (maxB - minB);
        instances[i].setB(res);

        // One
        curr = instances[i].getOne();
        res = (curr - minOne) / (maxOne - minOne);
        instances[i].setOne(res);

        // Two
        curr = instances[i].getTwo();
        res = (curr - minTwo) / (maxTwo - minTwo);
        instances[i].setTwo(res);

        // Three
        curr = instances[i].getThree();
        res = (curr - minThree) / (maxThree - minThree);
        instances[i].setThree(res);

        // Four
        curr = instances[i].getFour();
        res = (curr - minFour) / (maxFour - minFour);
        instances[i].setFour(res);

        // Five
        curr = instances[i].getFive();
        res = (curr - minFive) / (maxFive - minFive);
        instances[i].setFive(res);

        // Six
        curr = instances[i].getSix();
        res = (curr - minSix) / (maxSix - minSix);
        instances[i].setSix(res);

        // Seven
        curr = instances[i].getSeven();
        res = (curr - minSeven) / (maxSeven - minSeven);
        instances[i].setSeven(res);

    }

    int k = sqrt(instances.size());
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


            double r = std::stod(parts[0]);
            double g = std::stod(parts[1]);
            double b = std::stod(parts[2]);
            double one = std::stod(parts[3]);
            double two = std::stod(parts[4]);
            double three = std::stod(parts[5]);
            double four = std::stod(parts[6]);
            double five = std::stod(parts[7]);
            double six = std::stod(parts[8]);
            double seven = std::stod(parts[9]);

            r = (r - minR) / (maxR - minR);
            g = (g - minG) / (maxG - minG);
            b = (b - minB) / (maxB - minB);
            one = (one - minOne) / (maxOne - minOne);
            two = (two - minTwo) / (maxTwo - minTwo);
            three = (three - minThree) / (maxThree - minThree);
            four = (four - minFour) / (maxFour - minFour);
            five = (five - minFive) / (maxFive - minFive);
            six = (six - minSix) / (maxSix - minSix);
            seven = (seven - minSeven) / (maxSeven - minSeven);


            double minimum_distance = 500;
            for(int i = 0; i < instances.size(); i++){
                double d = instances[i].calculateDistance(r, g, b
                , one, two, three, four, five, six, seven
                );
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