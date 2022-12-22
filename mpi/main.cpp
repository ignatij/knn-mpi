/*
 * How to Run
 * mpicxx -o main main.cpp -std=c++11; mpirun -np 2 main; ; rm .\main.exe;
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
#include<mpi.h>
#include<set>

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

    double calculateDistance(double otherR, double otherG, double otherB){
        return sqrt(
            (R - otherR) * (R - otherR) + 
            (G - otherG) * (G - otherG) + 
            (B - otherB) * (B - otherB)
            );

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

class TestInstance{
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
    

    public:

    TestInstance(double R, double G, double B){
        this->R = R;
        this->G = G;
        this->B = B;
    }

    TestInstance(double R, double G, double B, double one, double two, double three, double four, double five, double six, double seven){
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

	vector<Instance> instances;
	int k;


	vector<map<double, int> > distanceToClass;
	vector<set<double> > distances;

int returnClassForObject(int index){
	
	int countFirstClass = 0;
	int countSecondClass = 0;
	
	set<double>::iterator it = distances[index].begin();
	
	while(countFirstClass != k && countSecondClass != k){
		if(distanceToClass[index].find(*it) -> second == 1){
			countFirstClass++;
		}
		else if(distanceToClass[index].find(*it) -> second == 2){
			countSecondClass++;
		}
		it++;
	}
	if(countFirstClass == k){
		return 1;
	}
	else if(countSecondClass == k){
		return 2;
	}
    return 0;
}
//adapt to the number of processors
int getStartRange(int id){
	switch(id){
		case 1: return 0;
		case 2: return 150000;
		default: return -1;
	}
}

int getEndRange(int id){
		switch(id){
		case 1: return 150000;
		case 2: return instances.size();
		default: return -1;
	}
}





int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);


    int world_size;
    int rank;

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		
    string line;
    ifstream myfile("training.txt");
 
	
	//init
    if (myfile.is_open())
    {
        while (getline(myfile,line))
        {
            vector<string> parts = split(line, ' ');
            Instance instance(
                std::stod(parts[0]),
                std::stod(parts[1]),
                std::stod(parts[2]),
                std::stod(parts[3])
            );
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

        // R
        if(instances[i].getR() > maxR){
            maxR = instances[i].getR();
        }
        else if(instances[i].getR() < minR){
            minR = instances[i].getR();
        }

        // G
        if(instances[i].getG() > maxG){
            maxG = instances[i].getG();
        }
        else if(instances[i].getG() < minG){
            minG = instances[i].getG();
        }




        // One
        if(instances[i].getOne() > maxOne){
            maxOne = instances[i].getOne();
        }
        else if(instances[i].getOne() < minOne){
            minOne = instances[i].getOne();
        }

        // Two
        if(instances[i].getTwo() > maxTwo){
            maxTwo = instances[i].getTwo();
        }
        else if(instances[i].getTwo() < minTwo){
            minTwo = instances[i].getTwo();
        }

        // Three
        if(instances[i].getThree() > maxThree){
            maxThree = instances[i].getThree();
        }
        else if(instances[i].getThree() < minThree){
            minThree = instances[i].getThree();
        }

        // Four
        if(instances[i].getFour() > maxFour){
            maxFour = instances[i].getFour();
        }
        else if(instances[i].getB() < minB){
            minB = instances[i].getB();
        }

        // Five
        if(instances[i].getFive() > maxFive){
            maxFive = instances[i].getFive();
        }
        else if(instances[i].getFive() < minFive){
            minFive = instances[i].getFive();
        }

        // Six
        if(instances[i].getSix() > maxSix){
            maxSix = instances[i].getSix();
        }
        else if(instances[i].getSix() < minSix){
            minSix = instances[i].getSix();
        }

        // Seven
        if(instances[i].getSeven() > maxSeven){
            maxSeven = instances[i].getSeven();
        }
        else if(instances[i].getSeven() < minSeven){
            minSeven = instances[i].getSeven();
        }

    }


    //standardization
    for(int i = 0; i < instances.size(); i++){


        // R
        double curr = instances[i].getR();
        double res = (curr - minR) / (maxR - minR);
        instances[i].setR(res);

        // G
        curr = instances[i].getG();
        res = (curr - minG) / (maxG - minG);
        instances[i].setG(res);

        // B
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
	
	//setting k = sqrt(number of training instances)
	k = sqrt(instances.size());

    
    ifstream new_file("test.txt");
    string new_line;

    vector<TestInstance>test_instances;

	
	
	double start, end;
	
	
	
	for(int i = 0; i < instances.size(); i++){
		distanceToClass.push_back(map<double, int>());
		distances.push_back(set<double>());
	}
	

	//reading test instances from test.txt


     if (new_file.is_open())
    {
        while (getline(new_file,new_line))
        {

            vector<string> parts = split(new_line, ' ');

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

            // TestInstance new_instance(r, g, b);
            TestInstance new_instance(r, g, b, one, two, three, four, five, six, seven);
            test_instances.push_back(new_instance);

        }

    }
	
	for(int i = 0; i < test_instances.size(); i++){
		distances.push_back(set<double>());
		distanceToClass.push_back(map<double, int>());	
	}
	

	
	start = MPI_Wtime();
	MPI_Status status;
	

	for(int i = 0; i < test_instances.size(); i++){
		
		  double r = test_instances[i].getR();
		  double g = test_instances[i].getG();
		  double b = test_instances[i].getB();
          double one = test_instances[i].getOne();
          double two = test_instances[i].getTwo();
          double three = test_instances[i].getThree();
          double four = test_instances[i].getFour();
          double five = test_instances[i].getFive();
          double six = test_instances[i].getSix();
          double seven = test_instances[i].getSeven();


		  int startRange = getStartRange(rank);
		  int endRange = getEndRange(rank);	
		
		if(rank > 0){
			int length = endRange - startRange;
			
			double arrayToSend1[length];
			int arrayToSend2[length];
			
			int l = 0;
			int q = 0;
			for(int j = startRange; j < endRange; j++){
				double distance = instances[j].calculateDistance(r, g, b
                , one, two, three, four, five, six, seven
                );
				arrayToSend1[l++] = distance;
				arrayToSend2[q++] = instances[j].skin();
			}
			 

			MPI_Send(&length, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);
			MPI_Send(arrayToSend1, length, MPI_DOUBLE, 0, rank * 10, MPI_COMM_WORLD);
			MPI_Send(arrayToSend2, length, MPI_INT, 0, rank * 100, MPI_COMM_WORLD);
		}
		 else{
			for(int j = 1; j < world_size; j++){
			 int length;
			 MPI_Recv(&length, 1, MPI_INT, j, j, MPI_COMM_WORLD, &status);
	
			 
		 	double arrayToRecv[length];
			int classValues[length];
			 
			MPI_Recv(arrayToRecv, length, MPI_DOUBLE, j, j * 10, MPI_COMM_WORLD, &status);
			MPI_Recv(classValues, length, MPI_INT, j, j * 100, MPI_COMM_WORLD, &status);
			
			for(int j = 0; j < length; j++){
				distances[i].insert(arrayToRecv[j]);
				distanceToClass[i].insert(std::pair<double, int>(arrayToRecv[j], classValues[j]));
				
			 }
			}
			
		 } 
		 
	}		
	
	if(rank == 0){
		
		for(int i = 0; i < test_instances.size(); i++){
		
			int classForObject = returnClassForObject(i);
			printf("Class for %d object: %d\n", i + 1, classForObject);
		}	
		end = MPI_Wtime();
		printf("Elapsed time: %.2f seconds.\n", (end - start));
	}
	MPI_Finalize();

}