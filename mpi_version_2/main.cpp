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
}
//adapt to the number of processors
int getStartRange(int id){
	switch(id){
		case 1: return 0;
		case 2: return 150000;
		//case 3: return 80000;
		//case 4: return 120000;
		//case 5: return 160000;
		//case 6: return 200000;
		default: return -1;
	}
}

int getEndRange(int id){
		switch(id){
		case 1: return 150000;
		case 2: return instances.size();
		//case 3: return 120000;
		//case 4: return 160000;
		//case 5: return 200000;
		//case 6: return instances.size();
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

            r = (r - minR) / (maxR - minR);
            g = (g - minG) / (maxG - minG);
            b = (b - minB) / (maxB - minB);

            TestInstance new_instance(r, g, b);
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


		  int startRange = getStartRange(rank);
		  int endRange = getEndRange(rank);	
		
		if(rank > 0){
			int length = endRange - startRange;
			
			double arrayToSend1[length];
			int arrayToSend2[length];
			
			int l = 0;
			int q = 0;
			for(int j = startRange; j < endRange; j++){
				double distance = instances[j].calculateDistance(r, g, b);
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

