#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
#include <unistd.h>
#include <stack>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

using namespace std;

struct node{
	string flight;
	string remarks;
	string country;
	string time;
	
};

node arr[10];
stack<int> dep;
stack<int> land;
//srand (time(NULL));


string Remarks[] = {"Landing","Boarding","On Schedule","Departed","Delayed"};


string remarks() { //Generate Remarks (Sequencial)

//	string Remarks[] = {"Landing","Delayed","Boarding","On Schedule","Departed"};
	string remarks;
	int random;
	
	random = rand() % (sizeof(Remarks)/sizeof(*Remarks));
	remarks = Remarks[random];
	
	return remarks;
}

string flight() { //Generate Random Flight Number
	
	char letter;
	int random;
	string number;
	
	string flightcode;
	
	for (int i=0; i<2; i++) {
		random = rand() % 26;
		letter = 'A' + random;
		flightcode += letter;
	}
	
	for (int i=0; i<4; i++) {
		random = rand() % 10;
		number = to_string(random);
		flightcode += number;
	}
		
	return flightcode;
}

string country() { //Generate Random Country
	
	string arr[] = {"London","Alaska","Boston","Roma"} ;
	string country;
	int random;
	
	random = rand() % (sizeof(arr)/sizeof(*arr));
	country = arr[random];
	return country;
}

string time() { //Generate Random Time
	
	string clock;
	
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);
	
	int hour = aTime->tm_hour;
	int min = aTime->tm_min;
	clock += to_string(hour);
	clock += ":";
	if (min%10==min){
		clock += to_string(0);
		clock += to_string(min);
	}else {
		clock += to_string(min);
	}
	
	return clock;
}

void newData(stack<int> dep){
	int y;
	while(!dep.empty()){
		y=dep.top();
		dep.pop();
		
		node obj;
		obj.country=country();
		obj.flight=flight();
		obj.time=time();
		obj.remarks=remarks();

		
		arr[y].country=obj.country;
		arr[y].flight=obj.flight;
		arr[y].remarks=obj.remarks;
		arr[y].time=obj.time;
		
	}
}

void announcement(stack<int> dep, stack<int> lan, node arr[]){
	int x;
	while(!dep.empty()){
		x = dep.top();
		dep.pop();
		cout<<arr[x].time<<setw(9)<<" flight No."<<arr[x].flight<<" has departed"<<endl;
	}
	while(!lan.empty()){
		x=lan.top();
		lan.pop();
		cout<<arr[x].time<<setw(9)<<" flight No."<<arr[x].flight<<" has landed"<<endl;
	}
	cout<<endl<<"notice"<<endl;
	cout<<"press spacebar to search for your flight number.";
}

int checknum(string input){
	
	for (int i=0;i<10;i++){
		if(arr[i].flight==input){
			cout<<arr[i].flight<<setw(9);
			cout<<arr[i].country<<setw(9);
			cout<<arr[i].time<<setw(15);
			cout<<arr[i].remarks;
			cout<<endl;		
			return 0;
		}
	}
	
	cout<< "Flight Number " << input <<" Not Found"<<endl;
	return 1;
}

void checkData(){
	int random;
	for (int i=0;i<10;i++){
		if(arr[i].remarks=="Departed"){
			dep.push(i);		
		}
		
		else if(arr[i].remarks=="Landing"){
			land.push(i);
			arr[i].remarks="On Schedule";
		}
		
		else if(arr[i].remarks=="On Schedule"){
			random =  rand() % 100;
			if(random<30){
				arr[i].remarks="Delayed";
			}else{
			arr[i].remarks="Boarding";
			}
		}
		
		else if(arr[i].remarks=="Boarding"){
			random =  rand() % 100;
			if(random<30){
				arr[i].remarks="Delayed";
			}else{
			arr[i].remarks="Departed";
			}
		}
		
		else if(arr[i].remarks=="Delayed"){
			arr[i].remarks="Boarding";
		}			
	}
}

void clearStack(stack<int>& dep, stack<int>& lan){
	while(!lan.empty()){
		lan.pop();
	}
	while(!dep.empty()){
		dep.pop();
	}
}

	
void declaredata(){
	for (int i=0;i<10;i++){
	node obj;
	obj.flight=flight();
	obj.time=time();
	obj.country=country();
	obj.remarks=remarks();
	
	arr[i].flight=obj.flight;
	arr[i].country=obj.country;
	arr[i].remarks=obj.remarks;
	arr[i].time=obj.time;
	}
}

void printdata(){
	cout<<"=============================================================================="<<endl;
	cout<<"Flight No."<<setw(6)<<"||"<<setw(10);
		cout<<"Country"<<setw(10)<<"||"<<setw(10);
		cout<<"Time"<<setw(10)<<"||"<<setw(12);
		cout<<"Remarks"<<setw(10)<<"||";
		cout<<endl;	
	cout<<"=============================================================================="<<endl;

	for (int i=0;i<10;i++){
		cout<<arr[i].flight<<setw(10)<<"||"<<setw(10);
		cout<<arr[i].country<<setw(10)<<"||"<<setw(10);
		cout<<arr[i].time<<setw(10)<<"||"<<setw(12);
		cout<<arr[i].remarks<<setw(10)<<"||";
		cout<<endl;	
	}
	cout<<"=============================================================================="<<endl;

}

int main(){
	
	declaredata();
	bool pause = false;	
	string Numbers;

		
	while(true){
		printdata();
		checkData();
		
		cout<<endl;
		cout<<"============"<<endl;
		cout<<"ANNOUNCEMENT"<<endl;
		cout<<"============"<<endl;
		
		announcement(dep , land, arr);
	
		
		cout<<endl;
		sleep(5);

		
		if (kbhit()){
			switch (_getch()){
				case 32:
					sleep(2);
					pause = true;
			}	
		}
		
		while(pause){
			cout<<"Flight Number : ";
			cin>>Numbers;
			checknum(Numbers);
				cout<<"press Spacebar to exit search"<<endl;
			sleep(3);
		
			if (kbhit()){
				switch (_getch()){
					case 32:
						sleep(2);
						pause = false;
						
				}	
			}
		}
		

		system("cls");
		sleep(0.8);
		newData(dep);
		clearStack(dep,land);	
	}
}