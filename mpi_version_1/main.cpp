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
    double isSkin;

    public:
    Instance(double R, double G, double B, int isSkin){
        this->R = R;
        this->G = G;
        this->B = B;
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
     double getR(){
        return R;
    }

     double getG(){
        return G;
    }

     double getB(){
        return B;
    }

     int skin(){
        return isSkin;
    }

    double calculateDistance(double otherR, double otherG, double otherB){
        return sqrt((R - otherR) * (R - otherR) + (G - otherG) * (G - otherG) + (B - otherB) * (B - otherB));

    }

};

class TestInstance{
  private:
    double R;
    double G;
    double B;
    

    public:
    TestInstance(double R, double G, double B){
        this->R = R;
        this->G = G;
        this->B = B;

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
     double getR(){
        return R;
    }

     double getG(){
        return G;
    }

     double getB(){
        return B;
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

//returns the class value
int returnClassForObject(double r, double g, double b, set<double> distances, map<double, int> distanceToClass){

	for(int i = 0; i < instances.size(); i++){
		double distance = instances[i].calculateDistance(r, g, b);
		distances.insert(distance);
		distanceToClass.insert(std::pair<double, int>(distance, instances[i].skin()));
	}
	
	int countFirstClass = 0;
	int countSecondClass = 0;
	
	set<double>::iterator it = distances.begin();
	
	while(countFirstClass != k && countSecondClass != k){
		if(distanceToClass.find(*it) -> second == 1){
			countFirstClass++;
		}
		else if(distanceToClass.find(*it) -> second == 2){
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
	
}



int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);


    int world_size;
    int rank;

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	MPI_Request requests[(world_size - 1) * 3];
    MPI_Status statuses[(world_size - 1) * 3];

    string line;
    ifstream myfile("training.txt");
 
	
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

     
    }
	
	k = sqrt(instances.size());

    
    ifstream new_file("test.txt");
    string new_line;

    vector<TestInstance>test_instances;

	
	
	double start, end;

  if(rank == 0){
     if (new_file.is_open())
    {
        while (getline(new_file,new_line))
        {

            vector<string> parts = split(new_line, ' ');

            double r = std::stod(parts[0]);
            double g = std::stod(parts[1]);
            double b = std::stod(parts[2]);

            r = (r - minR) / (maxR - minR);
            g = (g - minG) / (maxG - minG);
            b = (b - minB) / (maxB - minB);

            TestInstance new_instance(r, g, b);
            test_instances.push_back(new_instance);

        }

    }
	
	start = MPI_Wtime();
	
	int index = 1;
    for(int i = 1; i < test_instances.size(); i++){
		double r = test_instances[i].getR();
        MPI_Isend(&r, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, requests + index);
        index ++;
		double g = test_instances[i].getG();
        MPI_Isend(&g, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, requests + index);
        index ++;
		double b = test_instances[i].getB();
        MPI_Isend(&b, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, requests + index);
		index ++;
    }

	
	double r = test_instances[0].getR();
	double g = test_instances[0].getG();
	double b = test_instances[0].getB();
	map<double, int> distanceToClass;
	set<double> distances;
	int class_predicted = returnClassForObject(r, g, b, distances, distanceToClass);
	printf("Class for %d object is: %d\n", rank + 1, class_predicted);
	}
	else{
		double r;
      double g;
      double b;
      MPI_Irecv(&r, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, requests + rank + 1);
      MPI_Irecv(&g, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, requests + rank + 2);
      MPI_Irecv(&b, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, requests + rank + 3);

      MPI_Wait(requests + rank + 1, statuses + rank + 1);
      MPI_Wait(requests + rank + 2, statuses + rank + 2);
      MPI_Wait(requests + rank + 3, statuses + rank + 3);
	  
	  map<double, int> distanceToClass;
	  set<double> distances;
	  int class_predicted = returnClassForObject(r, g, b, distances, distanceToClass);
	  printf("Class for %d object is: %d\n", rank + 1, class_predicted);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank == 0){
		end = MPI_Wtime();
		printf("Elapsed time: %.2f seconds.\n", (end - start));
	}
	MPI_Finalize();

}

