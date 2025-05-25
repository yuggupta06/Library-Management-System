# include <iostream>
# include "admin.h"

# include <unordered_map>
# include <vector>
#include <limits> // Required for numeric_limits'

//For file handling
#include <fstream>
#include <cstdio> // For remove()
using namespace std;


void putData(unordered_map<int ,pair<Book *,string>> &book_ids,unordered_map<string,Book*>&book_name){
    ifstream file("books.txt");
    if (!file) {
        cout << "Error in opening the file!\n";
        return;
    }
    string line;
    while(getline(file,line)){
        int id_start=line.find("id:")+4;
        int id_end=line.find(',',id_start);
        int id=stoi(line.substr(id_start,id_end-id_start));

        int name_start=line.find("name:")+6;
        int name_end=line.find(',',name_start);
        string name=line.substr(name_start,name_end-name_start);

        int author_start=line.find("author:")+8;
        int author_end=line.find(',',author_start);
        string author=line.substr(author_start,author_end-author_start);

        int issued_start=line.find("isIssued:")+10;
        int issued_end=line.find('}',issued_start);
        bool issue=line.substr(issued_start,issued_end-issued_start)=="false"?false:true;

        string issuedDate="";
        int x =line.find("issuedDate");
        if(x==string::npos)issuedDate="-1";
        else{
            int start_point=x+12;
            int end_point=line.find(",",start_point);
            issuedDate=line.substr(start_point,end_point-start_point);
        }
        // Make book objects here..
        Book * b= new Book(id,name,author,issue,issuedDate);
        book_ids[id].first=b;
        book_ids[id].second="";
        book_name[name]=b;
    }
    file.close();
}


// Used for putting the users data from the users.txt file into the hash map
void putUser(unordered_map<int,pair<Book*,string>>&book_ids,unordered_map<string,User*>&Users){
    ifstream file("users.txt");
    if (!file) {
        cout << "Error in opening the file!\n";
        return ;
    }
    string line="";
    // Node * head=new Node("start"),*fake=head;
    while(getline(file,line)){

        int name_start=line.find("name:");
        if (name_start == string::npos) continue;
        name_start+=6;
        int name_end=line.find(',',name_start);
        string username=line.substr(name_start,name_end-name_start);
        book_ids[1].second=username;

        int pass_start=line.find("id:")+3;
        int pass_end=line.find(',',pass_start);
        string id=line.substr(pass_start,pass_end-pass_start);

        User *u=new User(username,id);
        Users[username]=u;
        int book_start=line.find("[");
        if (book_start == string::npos) continue; 
        book_start++;

        while(book_start < line.length() && line[book_start - 1] != ']'){
            int book_end=line.find(',',book_start);
            if(book_end==std::string::npos){
                book_end = line.find(']', book_start);
            }
            if (book_end == string::npos) break;
   
           string book_id_str = line.substr(book_start, book_end - book_start);
            if (!book_id_str.empty()) {
                    int id = stoi(book_id_str);
                    if (book_ids.find(id) != book_ids.end()) {
                        u->putBook(id, book_ids[id].first);
                    }
            }
            book_start=book_end+1;
        }
    }
    return;
}
#include <cctype> // Required for isalpha()

bool namechecker(string username){
    for(int i=0;i<username.length();i++){
        if(( !isalpha(username[i])  && !isdigit(username[i]) )&& (username[i]!='_' && !isspace(username[i]))){
         return false;
        }
    }
    return true;
}
string trim(string username) {
    size_t first = username.find_first_not_of(" \t\n\r");
    size_t last = username.find_last_not_of(" \t\n\r");
    return username.substr(first,last-first+1);
}

// For taking input as username and id
string accountdetails(string key){
    size_t first=string::npos;
    while(first==string::npos){
    string s;
    cout<<"\nEnter Your "+key+" for your new account: ";
    getline(cin,s);
    first = s.find_first_not_of(" \t\n\r");
    if(key=="id"&& s.find(' ',0)!=string::npos){
        cout<<"This field does not contain spaces enter a valid id.\n";
        first=string::npos;
    }
     if(first==string::npos){
        cout<<"The field should not be empty .\n";
    }
    else return trim(s);
    }
}

User *newUser(unordered_map<string,User*>&Users){
    ofstream file("users.txt", ios::app); // Open file in append mode
    cin.ignore();
    string username=accountdetails("username");

    while(!namechecker(username)){
        cout<<"\n-----------Warning !! Only alpha characters ,numbers or underscore are allowed in username.Please change your username.\n";
        username=accountdetails("username");
    }
    while(Users.find(username)!=Users.end()){
        cout<<"\n-----------Warning !!This username is already taken. Please enter another username.\n\n";
        username=accountdetails("username");
    }

    string id=accountdetails("id");
    User *u=new User(username,id);
    Users[username]=u;
    string newuser="{name: "+username+",id:"+id+", issuedBooks: []}";
    if(file.is_open()){
        file<<newuser<<endl;
        file.close();
    }
    cout<<"You are successfully entered in your account.\n";
    return u;
}



User *UserExistance(unordered_map<string,User*>&Users,string &username,string &id){
    if(Users.find(username)!=Users.end()){
        if(Users[username]->id_check(id)){
            cout << "Wait for few seconds.....\n";
            timer(2);
            cout<<"You are successfully entered in your account.\n";
            User *u=Users[username];
            u->expireBooks();
            return u;
        }
        else{
            cout<<"Your id is incorrect.Please try again!!\n";
            return NULL;
        }
    }
    cout<<"This username or password does not belong to any account.Check u already signed in or not\n";
    return NULL;

}

void UserTasks(User *u,unordered_map<int,pair<Book *,string>>&book_ids){
    while(true){
    timer(1);
    cout<<"\nThis is the list of the task you will be performed:\n";
    cout<<"1. Issue a book\n";
    cout<<"2. Return a book\n";
    cout<<"3. To show your all the books you issued.\n";
    cout<<"4. Details of a particular book.\n";
    cout<<"5. Exit\n";
    string choice;
    cout<<"\nEnter your task number: ";
    cin>>choice;
    int book_id;
        if(choice =="1"){
            cout<<"Enter the id of the book you want to issue: ";
            cin>>book_id;
            if(book_ids.find(book_id)==book_ids.end()){
                cout<<"Sorry, This book is not available in the library.\n";
            }
            else if(u->getBook(book_id)){
                cout<<"You already issued this book.\n";
            }
            else{
                if(book_ids[book_id].first->isIssued){
                    cout<<"Sorry, This book is already issued to someone else.\n";
                }
                else{
                    u->Addbook(book_id,book_ids[book_id].first);
                    cout << "Wait for few seconds.....\n";
                    timer(2);
                    cout<<"You have successfully issued the book \""+book_ids[book_id].first->name+"\"\n";
                }
            }
           timer(1);
        }
        else if(choice=="2"){
            cout<<"Enter the id of the book you want to return: ";
            cin>>book_id;
            if(u->getBook(book_id)){
                u->Removebook(book_id);
                cout<<"You have successfully returned the book \""+book_ids[book_id].first->name+"\"\n";
            }
            else{
                cout<<"Sorry, This book is not issued to you.\n";
            }
        }
        else if(choice=="3"){
        cout<<"\nThese are the list of all the books you issued:-\n";
            u->showBooks();
        }
        else if(choice=="4"){
            cout<<"Enter the id of the book:";
            cin>>book_id;
            if(book_ids.find(book_id)==book_ids.end()){
                cout<<"Invalid Book id.";
                continue;
            }
            cout<<"Name: "<<book_ids[book_id].first->name<<" , "<<"Author: "<<book_ids[book_id].first->author<<"\n";
            timer(1);
        }
        else if(choice=="5"){
            cout<<"Thank you for using our services.\n";
            return;
        }
        else  cout<<"Invalid choice.\n";
    }
}

int main(){
    //List of unordered maps
    unordered_map<int,pair<Book *,string>>book_ids;
    unordered_map<string,Book*>book_name;
    unordered_map<string,User*>Users;

    //putting data into the hash map
    putData(book_ids,book_name);
    putUser(book_ids,Users);


    cout<<"Hello Sir ,Welcome to the library management system.\n";
    User *Current_User=NULL;
    Admin *admin=NULL;
    string username,id;
    while(!Current_User && !admin){
        timer(2);
        int choice;
        cout<<"1. Signed up\n"<<"2. Already have an account\n"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        if(choice==1){
            Current_User=newUser(Users);
        }
        else if( choice ==2){
            string username,id;
            cout<<"Enter your username: ";
            cin.ignore();
            getline(cin,username);
            cout<<"Enter your id: ";
            getline(cin,id);
            if(username=="Yug" && id=="7017"){    // This is the admin password.
                admin=new Admin(username,id);
            }else
            Current_User=UserExistance(Users,username,id);
        }
    }
    if(admin) admin->AdminPowers(book_ids,Users);
    else UserTasks(Current_User,book_ids);
    
}