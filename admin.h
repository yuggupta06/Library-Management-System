# include <iostream>
# include "book_class.h"
# include "user_class.h"
# include <unordered_map>
# include <vector>


//For file handling
#include <fstream>
#include <cstdio> // For remove()
using namespace std;

class Admin:public Person{
    public:
        Admin(string a,string pass):Person(a,pass){};
        void showBooks(unordered_map<int,pair<Book *,string>>&book_ids){
            string a=" issued to ",b="not issued to anyone.";
            for(int i=1;i<book_ids.size()+1;i++){
                string name=book_ids[i].second;
                cout<<i<<":  \""+book_ids[i].first->name+"\" ";
                cout<<(name.length()?a+name:b)<<"\n";
            }
        }
        void AdminPowers(unordered_map<int,pair<Book *,string>>&book_ids,unordered_map<string,User*>Users){
            cout<<"\nWelcome Admin Yug.. !!"<<endl<<endl;
            timer(2);
            while(true){
            cout<<"What can i do for you Sir??\n";
            cout<<"1. Show all the books.\n";
            cout<<"2. Add a new book in the library.\n";
            cout<<"3.Exit\n";
            int choice;
            cout<<"\nEnter your choice: ";
            cin>>choice;
            switch(choice){
                case 1:
                    cout<<"These are the list of all the books with their users:-\n";
                    showBooks(book_ids);
                    cout<<"\n";
                    timer(2);
                    break;
                case 2:
                {
                    string n,a;
                    int new_book_id=book_ids.size()+1;
                    cout<<"Enter the book name: ";
                    cin.ignore();
                    getline(cin,n);
                    cout<<"Enter the author name: ";
                    getline(cin, a);
                    ofstream file("books.txt", ios::app);
                    if(file.is_open()){
                        file<<"{id: "+to_string(new_book_id)+", name: "+n+", author: "+a+", isIssued: false}";
                        file.close();
                    }else {
                        cout<<"Error in file opening.";
                    }
                    Book * b1=new Book(new_book_id,n,a,true,"-1");
                    book_ids[new_book_id].first=b1;
                    book_ids[new_book_id].second="";
                    cout<<"Loading...";
                    timer(2);
                    cout<<"The book is succesfully added in library.\n";
                    timer(1);
                    break;
                }
                case 3:
                    cout<<"\nThanks for coming Sir and check about the details of the library.\n";
                    return;
                        
                default:
                    cout<<"Invalid Choice!!";
                    timer(1);   
            }
        }

        }
};