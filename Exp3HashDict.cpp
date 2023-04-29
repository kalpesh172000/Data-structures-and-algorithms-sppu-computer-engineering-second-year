/*
data stucture and alogorithm lab asignment No. 3 :
Implement all the functions of a dictinary (ADT) using hashing 
and handle collisions using chaining with / without replacement.
Data: Set of (key,value) pairs, Keys are mapped to values, 
Keys must be comparable, Keys must be unique,
Standard Operations: Insert(key,value), Find(key), Delete(key)
*/

/*
NOTE : there's confusion between chaining and seperate chaining 
this code is for seperate chaining and not chaining 
1) seperate chaining uses linked nodes 
2) chaining uses the array with extra slot that tells where the next synonym is stored in array.
*/

#include<iostream>
#include<string.h>

using namespace std;

#define max 26

class entry
{
    public:
    char word[30]; 
    char meaning[60];
    entry* next;

};

class dictionary
{
    entry *head[max];

    public:
    dictionary()
    {
        for(int i=0;i<max;i++)
        {
            head[i]=NULL;
        }
    }

    void insert();
    void del_entry();
    void search();
    void display();
    int hashFun(char);
};


int dictionary::hashFun(char word)
{
	return word-97;
}


void dictionary::insert()
{
    char word[30];
    char meaning[50];

    entry *temp,*current;

    cout<<"\nenter the word: ";
    cin.ignore();
	cin.getline(word,30);
	cout<<"\nenter the meaning of the word: ";
	cin.getline(meaning,50);
	
	
	/*
	if(search(word))
    {
        cout<<"\nword is already present in the dictionary";
        return;
    }
	*/
    
    
	int position;
	position=hashFun(word[0]);

    temp=new entry;
    if(temp==NULL)
    {
        cout<<"memory not allocated"<<endl;
        return;
    }
    strcpy(temp->word,word);
    strcpy(temp->meaning,meaning);
    temp->next=NULL;
    
    
    current=head[position];
    if(current==NULL)
    {
    	head[position]=temp;
    }
    else
    {
    	while(current->next==NULL)
    	{
    		if(strcmp(current->word,word)==0) //benifit of adding entry at the end of chain is that you can search for copy while traversing to end 
    		{
    			cout<<"\nword is already present in the dictionary";
    			return;
    		}
    		current=current->next;
    	}
    	current->next=temp;
    }
    cout<<"\nword is inserted in dictionary at index "<<position;
    return;
}


void dictionary::search()
{
    entry *temp;
    char word[30];
    int position;
    
    cout<<"\nenter the word you want to search: ";
    cin.ignore();
	cin.getline(word,30);
    
	position=hashFun(word[0]);

    temp=head[position];
    while(temp!=NULL)
    {
        if(strcmp(temp->word,word)==0)
        {
        	cout<<"\nmeaning: "<<temp->meaning;
	        return;
        }
        temp=temp->next;
    }
    cout<<"\nword is not present in the dictionary";
}


void dictionary::del_entry()
{
    char word[30];
    entry *temp,*current;

    cout<<"\nenter the word you want to delete: ";
	cin.ignore();
	cin.getline(word,30);

	int position;
	position=hashFun(word[0]);

    if(head[position]==NULL)
    {
        cout<<"\nword is not present in the dictionary";
        return;
    }

    if(strcmp(head[position]->word,word)==0)
    {
        temp=head[position];
        head[position]=head[position]->next;
        delete temp;
        cout<<"\nword was deleted from the dictionary";
        return;
    }

    current=head[position];
    temp=head[position]->next;

    while(temp!=NULL)
    {
        {
            current->next=temp->next;
            delete temp;
            cout<<"\nword was deleted from the dictionary";
	        return;
        }
        current=temp;
        temp=temp->next;
    }

    cout<<"\nword is not present in the dictionary";

}


void dictionary::display()
{
    entry *temp;
    bool flag=true;
    cout<<"\n\nword\t\t\t\tmeaning";
    for(int i=0;i<max;i++)
    {
        temp=head[i];
        while(temp!=NULL)
        {
            flag=false;
            cout<<"\n"<<temp->word<<"\t\t\t\t"<<temp->meaning;
            temp=temp->next;
        }
    }
    if(flag)
        cout<<"\n\n\ndictionary is empty";
}



int main()
{
    dictionary d;
    int ch;
    
    while(true)
    {
		cout<<"\n\n\n------------------------------------\nMENU";
		cout<<"\n1. insert";
		cout<<"\n2. search";
		cout<<"\n3. delete";
		cout<<"\n4. display";
		cout<<"\n5. exit";
		cout<<"\n\nEnter the choice: ";
		cin>>ch;
		
        switch(ch)
        {
            case 1:
            	d.insert();
                break;
            case 2:
                d.search();
                break;
            case 3:
            	d.del_entry();
                break;
            case 4:
            	d.display();
                break;
            case 5:
                return 0;
            default:
                cout<<"\nenter the correct choice";
        }
    }  
}

