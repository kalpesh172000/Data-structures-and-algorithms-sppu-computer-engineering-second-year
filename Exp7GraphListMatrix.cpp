/*
data structures and algorithm lab assignment No. 7 :
Represent a given graph using adjacency matrix / list to perform DFS and using adjacency list to perform BFS.
Use the map of the area around the college as the graph.
Identify the prominent landmarks as nodes and perform DFS and BFS on that .
*/

//note; in this the location data is predefined and isn't set up to accept from user 
//check exp8 for taking location input from user

#include<iostream>

using namespace std;

const int maxsize=9;

class node
{   public:
    int vertex;
    node* next;
};

//---queue implementation start-------------

const int size=20;

class queue
{
    public:
    int qu[size];
    int front,rear;
    void enque(int);
    int dequeue();
    int getfront();
    bool empty();
    queue()
    {
        for(int i=0;i<size;i++)
            qu[i]=0;
        front=rear=-1;
    }
};


void queue::enque(int current)
{
    if((front==0 && rear==size-1)||(rear==front-1))
    {
        cout<<"\nqueue overflow terminating the programm";
        exit(1);
    }
    if(front==-1)
    {
        front=rear=0;
        qu[rear]=current;
    }
    else if(rear==size-1)
    {
        rear=0;
        qu[rear]=current;
    }
    else
        qu[++rear]=current;
    
}


bool queue::empty()
{
    if(front==-1)
        return 1;
    return 0;
}


int queue::dequeue()
{
    if(front==rear && front!=-1)
    {
        int temp=qu[front];
        front=rear=-1;
        return temp;
    }
    if(front==size-1)
    {
        int temp=qu[front];
        front=0;
        return temp;
    }
    return qu[front++];
}


int queue::getfront()
{
    return qu[front];
}

//---queue implementation stop--------------

class graph
{
    node *head[maxsize];
    int matrix[maxsize][maxsize];
    string locations[maxsize];
    bool visited[maxsize];
    void insert_edges();
    void reset_graph();
    void displaymatrix();
    void displaylist();

    void dfs_adj_matrix(int);
    void dfs_adj_list(int);
    void bfs_adj_list(int);

    public:
    void menu();

    graph()
    {
        locations[0]="gate";
        locations[1]="canteen";
        locations[2]="gym";
        locations[3]="boys h";
        locations[4]="diploma";
        locations[5]="pharma";
        locations[6]="girls h";
        locations[7]="degree";
        locations[8]="ground";
        for(int i=0;i<maxsize;i++)
            head[i]=NULL;
    }
};


void graph::reset_graph()
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

    for(int i=0;i<maxsize;i++)
        for(int j=0;j<maxsize;j++)
            matrix[i][j]=0;
}


void graph::insert_edges()
{
    int edges,vertex1,vertex2;
    node *current,*temp,*temp2;
    cout<<"\nenter the number of edges: ";
    cin>>edges;
    cout<<"\navailable locations: ";
    for(int i=0;i<maxsize;i++)
    {
      cout<<"\n"<<i+1<<" : "<<locations[i];
    }

    for(int i=0;i<edges;i++)
    {
        cout<<"\nenter pair of vertcies to indicate edge: ";
        cin>>vertex1>>vertex2;
        if(vertex1>maxsize || vertex2>maxsize)
        {
            i--;
            cout<<"\nvertex out of range\nenter only between 1-"<<maxsize;
            continue;
        }
        vertex1--;
        vertex2--;

        //input for adjecency matrix
        matrix[vertex1][vertex2]=1;
        matrix[vertex2][vertex1]=1;

        //input for adjecency list
        temp=new node;
        temp->vertex=vertex1;
        temp->next=NULL;
        if(head[vertex2]==NULL)
        {
            head[vertex2]=temp;
        }
        else
        {
            current=head[vertex2];
            while (current->next!=NULL)
                current=current->next;
            current->next=temp;
        }


        temp2=new node;
        temp2->vertex=vertex2;
        temp2->next=NULL;
        if(head[vertex1]==NULL)
        {
            head[vertex1]=temp2;
        }
        else
        {
            current=head[vertex1];
            while (current->next!=NULL)
                current=current->next;
            current->next=temp2;
        }

    }
}


void graph::dfs_adj_matrix(int vertex)
{
    cout<<"\n"<<locations[vertex];
    visited[vertex]=1;
    for(int i=0;i<maxsize;i++)
    {
        if(matrix[vertex][i]==1 && visited[i]==0)
            dfs_adj_matrix(i);
    }
}


void graph::dfs_adj_list(int vertex)
{
    node *temp;

    while(true)
    {
        if(visited[vertex]==1)
            return;
        visited[vertex]=1;
        cout<<"\n"<<locations[vertex];
        temp=head[vertex];
        while(temp!=NULL)
        {
            dfs_adj_list(temp->vertex);
            temp=temp->next;
        }
    }
}


void graph::bfs_adj_list(int vertex)
{
    queue q;
    node *temp;
    visited[vertex]=1;
    q.enque(vertex);
    while(!q.empty())
    {

        vertex=q.dequeue();
        cout<<"\n"<<locations[vertex];
        temp=head[vertex];
        while(temp!=NULL)
        {
            if(visited[temp->vertex]==0)
            {
                q.enque(temp->vertex);
                visited[temp->vertex]=1;
            }
            temp=temp->next;
        }
    }
}


void graph::displaymatrix()
{
  cout<<"\n\t";
  for(int i=0;i<maxsize;i++)
    cout<<locations[i]<<"\t";
  for(int i=0;i<maxsize;i++)
  {
    cout<<"\n"<<locations[i]<<"\t";
    for(int j=0;j<maxsize;j++)
      cout<<matrix[i][j]<<"\t";
  }
}


void graph::displaylist()
{
    node *temp;
    cout<<"\n\nnode\t\tadjecent nodes ";
    cout<<"\n------------------------------------";
    for(int i=0;i<maxsize;i++)
    {

        cout<<"\n"<<locations[i]<<"\t\t";
        if(head[i]==NULL)
        {
            cout<<"NULL";
            continue;
        }
        temp=head[i];
        while(temp!=NULL)
        {
            cout<<locations[temp->vertex]<<"\t\t";
            temp=temp->next;
        }
    }
}


void graph::menu()
{
    int ch;
    while(true)
    {
		cout<<"\n\n\n------------------------------------\nMENU";
		cout<<"\n1. Enter a new graph";
		cout<<"\n2. display graph in dfs for adjency matrix";
        cout<<"\n3. display graph in dfs for adjency list";
		cout<<"\n4. display graph in bfs for adjency list";
        cout<<"\n5. disply adjacency matrix";
        cout<<"\n6. disply adjacency list";
		cout<<"\n7. Exit";
		cout<<"\n\nEnter the choice: ";
		cin>>ch;

        switch(ch)
        {
            case 1:
                reset_graph();  //reset matrix and list to defalt to insert new edges
            	insert_edges();
                break;
            case 2:
                fill_n (visited, maxsize, 0); //fills the array with zeros
                for(int i=0;i<maxsize;i++)
				    if(visited[i]==0)
                    {
                        cout<<"\n";
                        dfs_adj_matrix(i);
                    }
                break;
            case 3:
                fill_n (visited, maxsize, 0);
                for(int i=0;i<maxsize;i++)
				    if(visited[i]==0)
                    {
                        cout<<"\n";
                        dfs_adj_list(i);
                    }
                break;
            case 4:
                fill_n (visited, maxsize, 0);
                for(int i=0;i<maxsize;i++)
				    if(visited[i]==0)
                    {
                        cout<<"\n";
                        bfs_adj_list(i);
                    }
                break;
            case 5:
                displaymatrix();
                break;
            case 6:
                displaylist();
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
    graph g;
    g.menu();
}
