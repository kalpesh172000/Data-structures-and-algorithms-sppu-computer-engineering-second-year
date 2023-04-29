/*
data stucture and alogorithm lab asignment No. 8 :
There are flight paths between cities .
If there is a flight between city A and city B then there is an edge between the cities.
The cost of the edge can be the time that flight takes to reach city B from A,
or the amount of fuel used for the journey.
Represent this as a graph.
The node can be represented by the airport name or by the name of the city.
Use representation of the graph. Check whether the graph is connected or not.
Justify the storage representation used.
*/


//this program takes input form txt files 
//check if declared txt files are present in the same directory as this program 

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

const int maxsize=20;
const string cityfile="Exp8FlightManagement_city_data.txt";
const string pathfile="Exp8FlightManagement_path_data.txt";

class node
{
	public:
	int vertex;
	string city;
	int fuel;
	node *next;
};


class flightmanagement
{
	node *head[maxsize];
	int total_cities,total_edges;
	string locations[maxsize];
	bool visited[maxsize];
	void getcityfile();     //this function takes input from city.txt file 
	void getpathfile();     //this function takes input from path.txt file
	void reset_graph();     //this function deletes all adjecent nodes and NULL the head nodes 
	void getvertex(string ,string ,int &,int &);    //this function finds vertex of 2 cities at a time;

	void connected_flight();	//this function checks weather graph is connected or not 
	void connected_search(int); //this function aids connected flight funcion
	void direct_flight(string ,string);     //this function checks if direct flight exits between 2 cities
	void indirect_flight(string ,string);    //this function check does an indirect path exist between 2 cities 
	void display_all();		//display entire adjecency list
	void dfs(int);			//display's nodes in dfs manner
	void path_check(int,int,int &); //this function aids indirect_flight funcion
	

	public:
	void menu();
	flightmanagement()
	{
		total_cities=total_edges=0;
		for(int i=0;i<maxsize;i++)
			head[i]=NULL;
	}
};


void flightmanagement::connected_flight()
{
	int flag=0;
	fill_n (visited, maxsize, 0); //fills the array with zeros
	for(int i=0;i<total_cities;i++)
		if(visited[i]==0)
		{
			flag++;
			if(flag==2)
			{
				cout<<"\ngraph is not connected";
				return;
			}
			cout<<"\n";
			connected_search(i);
		}
	cout<<"\ngraph is connected";
}


// this is just dfs but it's purpose is to change the visited array for function connected_search()
void flightmanagement::connected_search(int vertex) 
{
	node *temp;
	while(true)
	{
		if(visited[vertex])
			return;
		visited[vertex]=1;
		temp=head[vertex]->next;
		while (temp!=NULL)
		{
			connected_search(temp->vertex);
			temp=temp->next;
		}
	}
	return;
}


//this is dfs search and it display's the node in dfs manner
void flightmanagement::dfs(int vertex)
{
	node *temp;
	while(true)
	{
		if(visited[vertex])
			return;
		visited[vertex]=1;
		cout<<"->"<<head[vertex]->city;
		temp=head[vertex]->next;
		while (temp!=NULL)
		{
			dfs(temp->vertex);
			temp=temp->next;
		}
	}
	return;
}


void flightmanagement::indirect_flight(string city1,string city2)
{
	int vertex1,vertex2,flag;
	vertex1=-1;
	vertex2=-1;
	flag=0;
	getvertex(city1,city2,vertex1,vertex2);
	if(vertex1==-1||vertex2==-1)
	{
		cout<<"\nyou have entered wrong city name";
		return;
	}
	path_check(vertex1,vertex2,flag);
	if(flag)
	{
		cout<<"\n"<<city2<<" is reachable from "<<city1;
		return;
	}    
	cout<<"\n"<<city2<<" is not reachable from "<<city1;
}


// this is just dfs but instead of displaying node it checks whether traget appears in path 
void flightmanagement::path_check(int vertex,int target,int &flag)
{
	node *temp;
	while(true)
	{
		if(visited[vertex])
			return;
		visited[vertex]=1;
		temp=head[vertex]->next;
		while (temp!=NULL)
		{
			if(temp->vertex==target)
			{
				flag=1;
				return;
			}
			path_check(temp->vertex,target,flag);
			temp=temp->next;
		}
	}
	return;
}


void flightmanagement::getvertex(string city1,string city2,int &vertex1,int &vertex2)
{
	for(int i=0;i<total_cities;i++)
	{
		if(city1==locations[i])
			vertex1=i;
		if(city2==locations[i])
			vertex2=i;
	}
	return;
}


void flightmanagement::reset_graph()
{
	node* temp,*current;
	for(int i=0;i<maxsize;i++)
	{
		if(head[i]!=NULL)
		{
			current=head[i]->next;
			head[i]=NULL;
			while(current!=NULL)
			{
				temp=current;
				current=current->next;
				delete temp;
			}
		}
	}
	total_cities=0;
	total_edges=0;
}


void flightmanagement::getcityfile()
{
	try
	{
	ifstream fin;
	node *temp;
	fin.open(cityfile,ios::in);
	char choice;
	string cityname;

		do
		{
			fin>>cityname;
			temp=new node;
			temp->city=cityname;
			temp->vertex=total_cities;
			temp->fuel=0;
			temp->next=NULL;
			head[total_cities]=temp;
			locations[total_cities]=cityname;

			total_cities++;
			fin>>choice;

		}while(choice=='y' && total_cities<=maxsize);
	fin.close();
	}
	catch(const exception& e)
	{
		cerr <<'\n'<<e.what();
	}
}


void flightmanagement::getpathfile()
{
	try
	{
	ifstream fin;
	node *temp,*current;

	fin.open(pathfile,ios::in);
	char choice;
	string cityname1,cityname2;
	int fuel,vertex1,vertex2;

		do
		{

			fin>>cityname1>>cityname2>>fuel;
			getvertex(cityname1,cityname2,vertex1,vertex2);


			// add city 1 -> city 2

			current=head[vertex1];
			while (current->next!=NULL)
				current=current->next;

			temp=new node;
			temp->vertex=vertex2;
			temp->city=cityname2;
			temp->fuel=fuel;
			temp->next=NULL;
			current->next=temp;

			// add city 2 -> city 1

			current=head[vertex2];
			while (current->next!=NULL)
				current=current->next;

			temp=new node;
			temp->vertex=vertex1;
			temp->city=cityname1;
			temp->fuel=fuel;
			temp->next=NULL;
			current->next=temp;
			total_edges++;
			fin>>choice;

		}while(choice=='y' && total_edges<40);
	fin.close();
	}
	catch(const exception& e)
	{
		cerr <<'\n'<<e.what();
	}
	return;
}


void flightmanagement::direct_flight(string city1,string city2)
{
	int vertex1,vertex2;
	vertex1=-1;
	vertex2=-1;
	getvertex(city1,city2,vertex1,vertex2); //vertex1 and vertex2 is passed by reference
	if(vertex1==-1||vertex2==-1)
	{
		cout<<"\nyou have entered wrong city name";
		return;
	}

	node *temp;
	temp=head[vertex1]->next;
	while (temp!=NULL)
	{
		if(temp->city==city2)
		{
			cout<<"\nflight exits between "<<city1<<" and "<<city2;
			return;
		}
		temp=temp->next;
	}
	cout<<"\nflight doesn't exits between "<<city1<<" and "<<city2;
	return;
}


void flightmanagement::display_all()
{
	node *temp;
	cout<<"\n\ncity\t\t\tconnected cities";
	cout<<"\n-------------------------------------------------";
	for(int i=0;i<total_cities;i++)
	{
		cout<<"\n"<<locations[i]<<"\t\t\t";
		if(head[i]->next==NULL)
		{
			cout<<"NULL";
			return;
		}
		temp=head[i]->next;
		
		while(temp!=NULL)
		{
			cout<<"->"<<temp->city;
			temp=temp->next;
		}
	}
}


void flightmanagement::menu()
{
	int ch;
	string city1,city2;
	while(true)
	{
		cout<<"\n\n\n------------------------------------\nMENU";
		cout<<"\n1. Enter a new graph";
		cout<<"\n2. check if direct flight exits between cities";
		cout<<"\n3. check if indirect flight exits between two cities";
		cout<<"\n4. check if graph is connected or not";
		cout<<"\n5. dislplay dfs";
		cout<<"\n6. disply adjacency list";
		cout<<"\n7. Exit";
		cout<<"\n\nEnter the choice: ";
		cin>>ch;

		switch(ch)
		{
			case 1:
				reset_graph();
				fill_n (locations,maxsize,NULL);  //reset list to defalt to insert new edges
				getcityfile();
				getpathfile();
				break;
			case 2:
				cout<<"\nEnter the cities that you want to check the path: ";
				cin>>city1>>city2;
				direct_flight(city1,city2);
				break;
			case 3:
				fill_n (visited, maxsize, 0);	//fills the array with zeros
				cout<<"\nEnter the cities that you want to check the indirect path: ";
				cin>>city1>>city2;
				indirect_flight(city1,city2);
				break;
			case 4:
				connected_flight();
				break;
			case 5:
				fill_n (visited, maxsize, 0); //fills the array with zeros
				for(int i=0;i<total_cities;i++)
					if(visited[i]==0)
					{
						cout<<"\n";
						dfs(i);
					}
				break;
			case 6:
				display_all();
				break;
			case 7:
				return;
			default:
				cout<<"\nenter the correct choice";
		}
	}
}


int main()
{
	flightmanagement f;
	f.menu();
}
