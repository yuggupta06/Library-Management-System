# include <iostream>
# include <unordered_map>
# include <vector>
# include <ctime>
//For file handling
#include <fstream>
#include <cstdio> // For remove()
using namespace std;

class Book{
    public:
        int id;
        string name;
        string author;
        bool isIssued;
        string issuedDate;
        Book(int a,string b,string c,bool d,string date):id(a),name(b),author(c),isIssued(d),issuedDate(date){};

        void issuing(bool flag){
            isIssued=flag;
            string line;
            ifstream inputFile("books.txt");
            ofstream tempFile("temp.txt");
            while(getline(inputFile,line)){
                if(line.find(name)!= string::npos){
                    int n=line.find(flag?"false":"true");
                    if(flag){
                        time_t now = time(0);  // Get current time
                        tm *ltm = localtime(&now); 
                        string year = to_string(1900 + ltm->tm_year);  // Year starts from 1900
                        string month = to_string(1 + ltm->tm_mon); 
                        string date=to_string(ltm->tm_mday);
                        line.replace(n,5,"true");
                        issuedDate=date+"-"+month+"-"+year;
                        line.insert(line.find("isIssued")-1," issuedDate: "+issuedDate+",");

                    }
                    else{
                        issuedDate="-1";
                        line.replace(n,4,"false");
                        int m=line.find("issuedDate:");
                        int n=line.find(',',m);
                        line.erase(m,n-m+2);
                    }
                }
                tempFile<<line<<endl;
            }
            inputFile.close();
            tempFile.close();
            remove("books.txt");         // Delete original file
            rename("temp.txt", "books.txt");  // Rename new file to original name 
        }
};