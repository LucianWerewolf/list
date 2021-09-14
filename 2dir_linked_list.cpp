//dwukierunkowa lista cykliczna
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <ctime>
using namespace std; 

struct node
{
    int value;
    double dual;
    char sign;
    node*next;
    node *prev;
};

bool isUnique(node* head, int vta)
{
    bool flag=true;
     if(NULL != head)
     {
        node* current=head;
        do
        {
            if (current->value==vta)
            {
                flag=false;
                break;
            }
            current=current->next;
        }while (current!=head);

    }
    return flag;
}

double losowanieWartosci()
{
    double los=rand();
    return los;
}

node* createNode(int vta)
{
    node* ptr=new node;
    ptr->dual = losowanieWartosci();
    ptr->sign='T';
    ptr->value=vta;
    ptr->next=ptr->prev=ptr;
    return ptr;         
};

void add(node*& head, int vta)
{
    if (head==NULL)
    {
        head=createNode(vta);
    }
    else
    {
            node* current=head;
            node* newNode=createNode(vta);
            if(vta < head->value)
            {
                newNode->prev=head->prev;
                newNode->next=head;
                head->prev->next=newNode;
                head->prev=newNode;
                head=newNode;
            }
            else if (vta > head->prev->value)
            {
                //za ogon
                newNode->next=head;
                newNode->prev=head->prev;
                head->prev->next = newNode;
                head->prev=newNode;
            }
            else
            {
                //w srodek
                do
                {
                    if (newNode->value<current->value)
                    {
                        newNode->next=current;
                        newNode->prev=current->prev;
                        current->prev->next=newNode;
                        current->prev=newNode;
                        break;
                    }
                   current=current->next;
                }while (current!=head);
            }
    }
}

void losowanieWezlow(node*& head, int x)
{
    int los;

    for (int i=0; i<x;)
    {
        los= (rand() << 2) % 99901 + (rand() % 4) + 95;
        if(isUnique(head, los))
        {
            add(head, los);
            i++;
        }
    }
}

void seek(node* head, int vta)
{
    bool flag=false;
    if (head==NULL)
    {
        cout<<"Lista jest pusta!"<<endl;
    }
    else
    {
    node* current=head;
    do
    {
        if (current->value==vta)
        {
            flag=true;
            break;
        }
        else current=current->next;
    }while (current!=head);
    if (flag==true) {cout<<"jest"<<endl;}
    else if(flag==false){cout<<"nie ma"<<endl;}
    }
}

void pokapokaIle(node* head)//pokazuje ilosc wezlow
{
    node* current=head;
    int flaga=0;
   if (head!=NULL)
   {
        do
        {
            flaga++;
            current=current->next;
        }while (current!=head);
    }
    cout<<"Lista ma "<<flaga<<" elementow."<<endl;
}

void pokapokaHead(node* head)//pokazuje wszystkie od glowy
{
    node* current=head;
   if (head!=NULL)
   {
        do
        {
            cout<<" ["<<current->value<<"] ";
            current=current->next;
        }while (current!=head);
        cout<<endl<<endl;
    }
    else{cout<<"Lista jest pusta!"<<endl;}
}

void pokapokaHead(node* head, int ilosc)//pokazuje ilosc od glowy
{
    node* current=head;
   if (head!=NULL)
   {

        for (int i=0; i<ilosc; i++)
        {
            cout<<" ["<<current->value<<"] ";
            current=current->next;
            if (current==head){break;}//ta linia zapobiega wyswietlaniu pozostalej ilosci elementow od nowa gdyby ilosc byla wieksza od liczby wezlow
        }
        cout<<endl<<endl;
    }
    else if (head==NULL){cout<<"Lista jest pusta!"<<endl;}
}

void pokapokaTail(node* head)//pokazuje wszystkie od ogona
{
   if (head!=NULL)
   {
       node* current=head->prev;
        do
        {
            cout<<" ["<<current->value<<"] ";
            current=current->prev;
        }while (current!=head->prev);
        cout<<endl<<endl;
    }
    else if (head==NULL){cout<<"Lista jest pusta!"<<endl;}
}

void pokapokaTail(node* head, int ilosc)//pokazuje ilosc od ogona
{
   if (head!=NULL)
    {
        node* current=head->prev;
        for (int i=0; i<ilosc; i++)
        {
            cout<<" ["<<current->value<<"] ";
            current=current->prev;
            if (current==head->prev){break;}
        }
        cout<<endl<<endl;
    }
    else if (head==NULL){cout<<"Lista jest pusta!"<<endl;}
}

void del(node*& head, int vta)
{
    bool flag=false;
    if(head==NULL)
    {
        cout<<"Lista jest pusta!"<<endl;
        return;
    }
    else//cos jest w liscie
    {
        if (head->value==vta)//jesli pierwszy element jest wyszukanym do usuniecia
        {
            node* temphead=head;
            head->prev->next=head->next;
            head->next->prev=head->prev;
            head=head->next;
            if (head==temphead)
            {
                head=NULL;
            }
            delete temphead;flag=true;
            return;
        }
        else
        {
            node* current=head;
            do
            {
                if (current->value==vta)
                {
                    current->prev->next=current->next;
                    current->next->prev=current->prev;
                    delete current;flag=true;
                    break;
                }
                current=current->next;
            }while (current!=head);
        }
    }
    if (flag==true){cout<<"usunieto element"<<endl;}
    else cout<<"nie znaleziono elementu, ktory chcesz usunac"<<endl;
}

void delAll(node*& head)
{
    do
    {
        del(head, head->value);
    }while (NULL != head); //const value always on the left side
}

int main()
{
    int x, k1, k2, k3, k4, k5;
    fstream plik;
    plik.open("inlab02.txt");
    if (plik.good())
    {
        plik>>x>>k1>>k2>>k3>>k4>>k5;
    }
	else
    {
        cout << "Blad pliku" <<endl;
        exit (0);
    }
    double ileczasu;
    srand(time(NULL));
    clock_t start, stop;
    start=clock();
    node* head=NULL;
    seek(head, k1);
    losowanieWezlow(head, x);
    pokapokaIle(head);
    pokapokaHead(head, 20);
    add(head, k2);
    pokapokaHead(head, 20);
    add(head, k3);
    pokapokaHead(head, 20);
    add(head, k4);
    pokapokaHead(head, 20);
    add(head, k5);
    pokapokaTail(head, 11);
    del(head, k3);
    pokapokaHead(head, 20);
    del(head, k2);
    pokapokaHead(head, 20);
    del(head, k5);
    pokapokaTail(head, 11);
    pokapokaIle(head);
    seek(head, k5);
    pokapokaTail(head, 11);
    delAll(head);
    pokapokaTail(head, 11);
    pokapokaIle(head);
    stop=clock();
    ileczasu=(double)(stop - start)/CLOCKS_PER_SEC;
    cout<<"Program wykonal sie w czsie: "<<ileczasu<<" sekund(y)."<<endl;
    plik.close();

return 0;
}
/* */
