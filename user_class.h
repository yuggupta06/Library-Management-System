# include <iostream>
# include <unordered_map>
# include <vector>

//For file handling
#include <fstream>
#include <cstdio> // For remove()

//For timings
#include <ctime>
#include <cctype> // Required for isalpha()

using namespace std;

void timer(int seconds) {
    time_t startTime = time(0);  // Get current time
    while (difftime(time(0), startTime) < seconds) {
        // Just wait until the time passes
    }
}
class Person{
    protected:
        string name;
        string id;
        Person(string a,string pass):name(a),id(pass){};
};

class User:public Person{
    private:
        unordered_map<int,Book*>issuedBooks;

    public:
        User(string a,string pass):Person(a,pass){};
        void putBook(int id,Book *b){
            issuedBooks[b->id]=b;
        }
        void showBooks(){
            for(auto x:issuedBooks){
                cout<<x.first<<":\""+x.second->name+"\"  \n";
            }
            cout<<"\n";
        } 
        bool getBook(int id){
            if(issuedBooks.find(id)!=issuedBooks.end()){
                return true;
            }
            return false;
        }
        bool id_check(string id_number){
            return id==id_number;
        }
        void expireBooks(){
            time_t now = time(0);  // Get current time
            tm *ltm = localtime(&now); 
            string year_ = to_string(1900 + ltm->tm_year);  // Year starts from 1900
            string month_ = to_string(1 + ltm->tm_mon); 
            string date_=to_string(ltm->tm_mday);
            for(auto x:issuedBooks){
                string temp=x.second->issuedDate;
                if(temp!="-1"){
                    int year=stoi(temp.substr(temp.find_last_not_of("\t\n\r")-3,4));
                    int month=stoi(temp.substr(temp.find("-")+1,temp.find("-",temp.find("-")+1)-temp.find("-")+1));
                    int date=stoi(temp.substr(0,temp.find("-")));
                    if(stoi(year_)-year<=1){
                        int totaldays=30-date+stoi(date_);
                        if(stoi(month_)-month==1 && totaldays>5){
                            cout<<"\n Notification!!!!"<<endl;
                            timer(1);
                            if(totaldays>5 && totaldays<10) cout<<"A fine is is imposed on you if you not return your book  "<<x.second->name<<", book_id:"<<x.second->id;
                            if(totaldays>10)cout<<"You have been fined for not returning your book "<<x.second->name<<", book_id:"<<x.second->id;
                        }
                        else if(stoi(month_)-month>=2){
                            cout<<"\n Notification!!!!"<<endl;
                            cout<<"You have been fined for not returning your book "<<x.second->name<<", book_id:"<<x.second->id;
                        }
                    }
                }
                else  cout<<"You have been fined for not returning your book "<<x.second->name;
            }
        }
        void Addbook(int id,Book *b){
            b->issuing(true);
            string line;
            ifstream inputFile("users.txt");
            ofstream tempFile("temp.txt");
            while(getline(inputFile,line)){
                int a=line.find("name:")+6;
                int b=line.find(',',a);
                if(line.substr(a,b-a)==name){
                    int n=line.find(']');
                    if(!issuedBooks.empty()) line.insert(n,","+to_string(id));
                    else line.insert(n,to_string(id));
                }
                tempFile<<line<<endl;
            }
            inputFile.close();
            tempFile.close();
            remove("users.txt");         // Delete original file
            rename("temp.txt", "users.txt");  // Rename new file to original name
            issuedBooks[id]=b;
        }
        void Removebook(int id){
            issuedBooks[id]->issuing(false);
            issuedBooks.erase(id);
            string line;
            ifstream inputFile("users.txt");
            ofstream tempFile("temp.txt"); 
            while(getline(inputFile,line)){
                int a=line.find("name:")+6;                 //For extracting the name of the user
                int b=line.find(',',a);
                if(line.substr(a,b-a)==name){
                    int n=line.find('[')+1;
                    while(line[n]!='}'){
                        int m=line.find(',',n);
                        if(m==string::npos){
                            m=line.find(']',n);
                        }
                        if(line.substr(n,m-n)==to_string(id)){
                            if(m==line.find(']',n)) line.erase(n,m-n);
                            else line.erase(n,m-n+1);
                            break;
                        }
                        n=m+1;
                    }
                }
                tempFile<<line<<endl;
            }
            inputFile.close();
            tempFile.close();
            remove("users.txt");         // Delete original file
            rename("temp.txt", "users.txt");
        }
};
