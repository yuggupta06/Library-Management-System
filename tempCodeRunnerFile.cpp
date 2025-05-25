void UserTasks(User *u,unordered_map<int,pair<Book *,string>>&book_ids){
    while(true){
    timer(1);
    cout<<"\nThis is the list of the task you will be performed:\n";
    cout<<"1. Issue a book\n";
    cout<<"2. Return a book\n";
    cout<<"3. To show your all the books you issued.\n";
    cout<<"4. Details of a particular book.\n";
    cout<<"5. Exit\n";
    int choice ;
    cout<<"\nEnter your task number: ";
    cin>>choice;
    int book_id;
    switch(choice){
        case 1:
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
            break;
        case 2:
            cout<<"Enter the id of the book you want to return: ";
            cin>>book_id;
            if(u->getBook(book_id)){
                u->Removebook(book_id);
                cout<<"You have successfully returned the book \""+book_ids[book_id].first->name+"\"\n";
            }
            else{
                cout<<"Sorry, This book is not issued to you.\n";
            }
            break;
        case 3:
        cout<<"\nThese are the list of all the books you issued:-\n";
            u->showBooks();
                break;
        case 4:
            cout<<"Enter the id of the book:";
            cin>>book_id;
            if(book_ids.find(book_id)==book_ids.end()){
                cout<<"Invalid Book id.";
                break;
            }
            cout<<"Name: "<<book_ids[book_id].first->name<<" , "<<"Author: "<<book_ids[book_id].first->author<<"\n";
            timer(1);
            break;
        case 5:
            cout<<"Thank you for using our services.\n";
            return;
            break;
        default:
            cout<<"Invalid choice.\n";
            break;
    }
    }
}
