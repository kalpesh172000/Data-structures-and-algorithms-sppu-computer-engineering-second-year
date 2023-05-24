/*
data structures and algorithm lab assignment No. 2:
Consider the telephone book database of N clients.
Make use of a hash table implementation to quickly look up a client's telephone number.
Make use of two collision handeling techniques 
and compare them using number of comparisons required to find a set of telephone numbers.
*/
#include<iostream>
#include<string.h>

using namespace std;

#define max 10

struct phonebook
{
    long phone;
    char name[30];
};

class hashTable
{
    phonebook ht_linear[max]; //both collision handeling techniques use different array
    phonebook ht_quadratic[max];
    public:
    hashTable()
    {
    	for(int i=0;i<max;i++)
    	{
    		ht_linear[i].phone=0;
    		strcpy(ht_linear[i].name,"------");
    	}
        for(int i=0;i<max;i++)
    	{
    		ht_quadratic[i].phone=0;
    		strcpy(ht_quadratic[i].name,"------");
    	}
        
    }

    // these 3 functions are for linear probing 
    void insert_linear_probe();
    void del_entry_linear_probe();
    void search_linear_probe();
    void menu_linear_probe();
    void display_linear_probe();

    // these 3 functions are for quadratic probing 
    void insert_quadratic_probe();
    void del_entry_quadratic_probe();
    void search_quadratic_probe();
    void menu_quadratic_probe();
    void display_quadratic_probe();


    int hashFun(long phone);
};


int hashTable::hashFun(long phone)
{
	return phone%10;
}


void hashTable::insert_linear_probe()
{
	long phone;
	char name[30];
	cout<<"\nenter the phone number: ";
	cin>>phone;
	cout<<"\nenter the name: ";
	cin.ignore();
	cin>>name;
	
	int pos;
	pos=hashFun(phone);
	if(ht_linear[pos].phone==0)
	{
		ht_linear[pos].phone=phone;
		strcpy(ht_linear[pos].name,name);
    	cout<<"\ncontact inserted in phonebook at index "<<pos;
		return;
	}
	
	
	for(int i=(pos+1)%max;(i%max)!=pos;i=(i+1)%max)
	{
		if(ht_linear[i].phone==0)
		{
			ht_linear[i].phone=phone;
			strcpy(ht_linear[i].name,name);
			cout<<"\ncontact inserted in phonebook at index "<<i;
			return;
		}
	}
	
	cout<<"\nphonebook full cant insert new contact";
	return;
	
}


void hashTable::search_linear_probe()
{
	long phone;
	char name[30];
	cout<<"\nenter the phone number for search: ";
	cin>>phone;
	
	int pos;
	pos=hashFun(phone);
	
	
	if(ht_linear[pos].phone==0)
	{
		cout<<"\ncontact is not present in the phonebook";
		return;
	}
	
	
	if(ht_linear[pos].phone==phone)
	{
    	cout<<"\ncontact found in phonebook at index "<<pos;
		return;
	}
	
	
	for(int i=(pos+1)%max;((i%max)!=pos && ht_linear[i%max].phone!=0);i=(i+1)%max)
	{
		if(ht_linear[i].phone==phone)
		{
			cout<<"\ncontact found in phonebook at index "<<i;
			return;
		}
	}
	
	cout<<"\ncontact is not present in the phonebook";
	return;
	
}


void hashTable::del_entry_linear_probe()
{
	long phone;
	char name[30];
	cout<<"\nenter the phone number for for delete purpose: ";
	cin>>phone;
	
	int pos;
	pos=hashFun(phone);
	
	
	if(ht_linear[pos].phone==0)
	{
		cout<<"\ncontact is not present in the phonebook";
		return;
	}
	
	
	if(ht_linear[pos].phone==phone)
	{
		ht_linear[pos].phone=0;
    	strcpy(ht_linear[pos].name,"------");
    	cout<<"\ncontact was deleted from phonebook at index "<<pos;
		return;
	}
	
	
	for(int i=(pos+1)%max;((i%max)!=pos && ht_linear[i%max].phone!=0);i=(i+1)%max)
	{
		if(ht_linear[i].phone==phone)
		{
			ht_linear[i].phone=0;
    		strcpy(ht_linear[i].name,"------");
			cout<<"\ncontact was deleted from phonebook at index "<<i;
			return;
		}
	}
	
	cout<<"\ncontact is not present in the phonebook";
	return;
	
}


void hashTable::insert_quadratic_probe()
{
	long phone;
	char name[30];
	cout<<"\nenter the phone number: ";
	cin>>phone;
	cout<<"\nenter the name: ";
	cin.ignore();
	cin>>name;
	
	int pos,i,j;
	pos=hashFun(phone);
	
	for(i=0;i<max;i++)
	{
		cout<<"\nheloow";
		j=(pos+(i*i))%max;
		if(ht_quadratic[j].phone==0)
		{
			ht_quadratic[j].phone=phone;
			strcpy(ht_quadratic[j].name,name);
			cout<<"\ncontact inserted in phonebook at index "<<j;
			return;
		}
	}
	cout<<"\nphonebook full cant insert new contact";
	return;
	
}


void hashTable::search_quadratic_probe()
{
	long phone;
	char name[30];
	cout<<"\nenter the phone number for search: ";
	cin>>phone;
	
	int pos,i,j;
	pos=hashFun(phone);
	
	for(i=0;i<max;i++)
	{
		j=(pos+(i*i))%max;
		if(ht_quadratic[j].phone==0)
			break;
		if(ht_quadratic[j].phone==phone)
		{
			cout<<"\ncontact found in phonebook at index "<<j;
			return;
		}
	}
	
	cout<<"\ncontact is not present in the phonebook";
	return;
	
}


void hashTable::del_entry_quadratic_probe()
{
	long phone;
	char name[30];
	cout<<"\nenter the phone number for for delete purpose: ";
	cin>>phone;
	
	int pos,i,j;
	pos=hashFun(phone);
	
	for(i=0;i<max;i++)
	{
		j=(pos+(i*i))%max;
		if(ht_quadratic[j].phone==0)
			break;
		if(ht_quadratic[j].phone==phone)
		{
			ht_quadratic[j].phone=0;
    		strcpy(ht_quadratic[j].name,"------");
			cout<<"\ncontact is deleted from the phonebook";
			return;
		}
	}
	
	cout<<"\ncontact is not present in the phonebook";
	return;
	
}


void hashTable::display_linear_probe()
{
	cout<<"\n\nphone\t\t\t\tname";
	for(int i=0;i<max;i++)
	{
		cout<<"\n"<<ht_linear[i].phone<<"\t\t\t\t"<<ht_linear[i].name;
	}
	return;
}


void hashTable::display_quadratic_probe()
{
	cout<<"\n\nphone\t\t\t\tname";
	for(int i=0;i<max;i++)
	{
		cout<<"\n"<<ht_quadratic[i].phone<<"\t\t\t\t"<<ht_quadratic[i].name;
	}
	return;
}


void hashTable::menu_linear_probe()
{
    int ch;

    while(true)
    {
		cout<<"\n\n\n------------------------------------";
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
            	insert_linear_probe();
                break;
            case 2:
            	search_linear_probe();
                break;
            case 3:
            	del_entry_linear_probe();
                break;
            case 4:
            	display_linear_probe();
                break;
            case 5:
                return;
            default:
                cout<<"\nenter the correct choice";
        }
    } 
}


void hashTable::menu_quadratic_probe()
{
    int ch;

    while(true)
    {
		cout<<"\n\n\n------------------------------------";
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
            	insert_quadratic_probe();
                break;
            case 2:
            	search_quadratic_probe();
                break;
            case 3:
            	del_entry_quadratic_probe();
                break;
            case 4:
            	display_quadratic_probe();
                break;
            case 5:
                return;
            default:
                cout<<"\nenter the correct choice";
        }
    } 
}


int main()
{
    hashTable linear,quadratic;
    int ch;
    
    while(true)
    {
		cout<<"\n\n\n------------------------------------";
		cout<<"\n1. linear probing";
		cout<<"\n2. quadratic probing";
		cout<<"\n3. exit";
		cout<<"\n\nEnter the choice: ";
		cin>>ch;
		
        switch(ch)
        {
            case 1:
            	linear.menu_linear_probe();
                break;
            case 2:
            	quadratic.menu_quadratic_probe();
                break;
            case 3:
                return 0;
            default:
                cout<<"\nenter the correct choice";
        }
    }

}