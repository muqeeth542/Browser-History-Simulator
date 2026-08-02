#include<iostream>
#include<string>
using namespace std;

struct node {
    string url;
    node *next,*prev;

    node(string u) {
        url = u;
        next = NULL;
        prev = NULL;
    }
};

class BrowserHistory {
private:
    node *CurrentPage;
public:
    BrowserHistory(string homepage) {
        CurrentPage = new node(homepage);
        cout<<"\nBrowser Started at : "<<CurrentPage->url<<endl;
    }
    void visit(string url) {
        node *temp = CurrentPage->next;
        
        // Deleting Forward history when we are backward.
        while (temp!=NULL) {
            node *nextnode = temp->next;
            delete temp;
            temp = nextnode;
        }

        node *newnode = new node(url);
        CurrentPage->next = newnode;
        newnode->prev = CurrentPage;
        CurrentPage = newnode;
        cout<<"Visited : "<<CurrentPage->url<<endl;
    }
    void back() {
        if (CurrentPage->prev!=NULL) {
            CurrentPage = CurrentPage->prev;
            cout<<"Back at the page : "<<CurrentPage->url<<endl;
        }else
            cout<<"No previous Page Found"<<endl;
    }
    void forward() {
        if (CurrentPage->next!=NULL) {
            CurrentPage = CurrentPage->next;
            cout<<"Forwarded to next Page : "<<CurrentPage->url<<endl;
        }else
            cout<<"No Page found"<<endl;
    }
    void viewpages() {
        node *ptr = CurrentPage;
        while (ptr->prev!=NULL)
            ptr = ptr->prev;
        while (ptr!=NULL) {
            if (ptr==CurrentPage)
                cout<<" --> "<<ptr->url<<endl;
            else {
                cout<<"     "<<ptr->url<<endl;
            }
            ptr=ptr->next;
        }
    }
};
int main() {
    string home = "Google.com";
    BrowserHistory browser(home);
    string url;
    int choice;
    do {
        cout<<"------------------------------------\n0.Exit\n1.Visit Site.\n2.Previous Tab.\n3.Next Tab.\n4.View Pages.\n------------------------------------\nChoice: ";
        cin>>choice;
        switch (choice) {
            case 0:
                cout<<"\nexited sucessfully\n";
                break;
            case 1:
                cout<<"\nEnter Url: ";
                cin>>url;
                browser.visit(url);
                break;
            case 2:
                browser.back();
                break;
            case 3:
                browser.forward();
                break;
            case 4:
                browser.viewpages();
                break;
            default:
                cout<<"\nInvalid Choice\n"<<endl;
                break;
        }
    }while (choice!=0);
    return 0;
}