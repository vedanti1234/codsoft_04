#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct todolist
{
    int id;
    string task;
};

int ID;
void banner();
void addTask();
void ShowTask();
int SearchTask();
void DeleteTask();

int main(){
    system("cls");
    while (true)
    {
        banner();
        cout<<"\n\t1. Add task";
        cout<<"\n\t2. Show task";
        cout<<"\n\t3. Search task";
        cout<<"\n\t4. Delete task";

        int choice;
        cout<<"\n\t Enter choice: ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            addTask();
            break;
        case 2:
            ShowTask();
            break;
        case 3:
            SearchTask();
            break;
        case 4:
            DeleteTask();
            break;
        default:
            break;
        }
    }
    return 0;
}

void banner(){
    cout<<"______________________________________"<<endl;
    cout<<"\t           my todo     "<<endl;
    cout<<"______________________________________"<<endl;
}

void addTask(){
    system("cls");
    banner();
    todolist todo;
    cout<<" Enter new task: "<<endl;
    cin.get();
    getline(cin,todo.task);
    char save;
    cout<<"Save? (y/n): ";
    cin>>save;
    if(save=='y'){
        ID++;
        ofstream fout;
        fout.open("todo.txt", ios::app);
        fout<<"\n"<<ID;
        fout<<"\n"<<todo.task;
        fout.close();

        char more;
        cout<<"Add more task ? (y/n): ";
        cin>>more;

        if(more=='y'){
            addTask();
        }
        else{
            system("cls");
            cout<<"Added Successfully!"<<endl;
            return;
        }
    }
    system("cls");
}

void ShowTask()
{
    system("cls");
    banner();
    todolist todo;
    ifstream fin;
    fin.open("todo.txt");
    cout<<"Task:"<<endl;

    while (!fin.eof())
    {
        fin>>todo.id;
        fin.ignore();
        getline(fin, todo.task);
        if(todo.task !=""){
            cout<<"\t"<<todo.id<<":"<<todo.task<<endl;
        }
        else{
            cout<<"\tEmpty"<<endl;
        }
    }
    fin.close();
    char exit;
    cout<<"Exit? (y/n): ";
    cin>>exit;
    if(exit != 'y'){
        ShowTask();
    }
    system("cls");
}

int SearchTask(){
    system("cls");
    banner();
    int id;
    cout<<"Enter task id: ";
    cin>>id;
    todolist todo;
    ifstream fin("todo.txt");
    while (!fin.eof())
    {
        fin>>todo.id;
        fin.ignore();
        getline(fin, todo.task);
        if (todo.id==id){
            system("cls");
            cout<<"\t"<<todo.id<<":"<<todo.task<<endl;
            return id;
        }
    }
    system("cls");
    cout<<"not found!"<<endl;
    return 0; 
}

void DeleteTask(){
    system("cls");
    int id = SearchTask();
    if(id !=0){
        char del;
        cout<<"\n\tDelete? (y/n): ";
        cin>>del;
        if(del=='y'){
            todolist todo;
            ofstream tempfile;
            tempfile.open("temp.txt");
            ifstream fin;
            fin.open("todo.txt");
            int index=1;
            while(!fin.eof()){
                fin>>todo.id;
                fin.ignore();
                getline(fin,todo.task);
                if(todo.id != id){
                    tempfile<<"\n"<<index;
                    tempfile<<"\n"<<todo.task;
                    index++;
                    ID--;
                }
            }
            fin.close();
            tempfile.close();
            remove("todo.txt");
            rename("temp.txt","todo.txt");
            system("cls");
            cout<<"\n\tDeleted Successfully"<<endl;
        }
        else{
            system("cls");
            cout<<"Not Deleted!"<<endl;
        }
    }
}