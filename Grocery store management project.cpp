#include <iostream>
#include<fstream>
using namespace std;

//shopping class;
class Shopping {
private:
    int pcode;
    float price;
    float disc;
    string pname;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

//menu function implementation
void Shopping::menu() { //:: scope resolution operator

    begin: //goto statements jumps to this label here.
    
    int choice;
    string email;
    string password;

    cout << "\n\t\t\t\t..............................\n";
    cout << "\t\t\t\t                              \n";
    cout << "\t\t\t\t       Store main menu        \n";
    cout << "\t\t\t\t                              \n";
    cout << "\t\t\t\t..............................\n";
    cout << "\t\t\t\t                              \n";
    cout << "\t\t\t\t|  1) Administrator          |\n";
    cout << "\t\t\t\t                              \n";
    cout << "\t\t\t\t|  2) Buyer                  |\n";
    cout << "\t\t\t\t                              \n";
    cout << "\t\t\t\t|  3) Exit                   |\n";
    cout << "\t\t\t\t                              \n";
    cout << "\n\t\t\t\t Please select: ";
    cin >> choice;

    switch (choice) 
    {
    case 1:
        cout << "\t\t\t Please login to access the Administrator menu! \n";
        cout << "\t\t\t Enter Email: ";
        cin >> email;
        cout << "\t\t\t Enter Password: ";
        cin >> password;

        if (email == "ibrahim@gmail.com" && password == "ibrahim1234")
            administrator();
       
        else
            cout << "Invalid Email/Password !";
        break;

    case 2:
        buyer();
        break;

    case 3:
        exit(0);

    default:
        cout << "Please enter a valid options !";
    } //end of switch case

    goto begin; //goto is a jump statement. and word begin is a label which label is found at the begining of the menu function. 

} //end of menu function


//administrator function implementation
void Shopping::administrator() {

admin: //admin label

    int choice;
    cout << "\n\n\n\t\t\t Administrator menu";
    cout << "\n\t\t\t|......1) Add product......|";
    cout << "\n\t\t\t|                          |";
    cout << "\n\t\t\t|......2) Modify product...|";
    cout << "\n\t\t\t|                          |";
    cout << "\n\t\t\t|......3) Delete product...|";
    cout << "\n\t\t\t|                          |";
    cout << "\n\t\t\t|......4) Back to main menu|";

    cout << "\n\n\t Please enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        add();
        break;
        
    case 2:
        edit();
        break;

    case 3:
        rem();
        break;

    case 4:
        menu();
        break;

    default:
        cout << "Please enter a valid choice!";

    }

    goto admin;

} //end of administrator function



//buyer function implementation
void Shopping::buyer() {

buyer: //buyer label

    int choice;
    cout << "\n\n\t\t\t Buyer \n";
    cout << "\t\t\t..................\n";
    cout << "                        \n";
    cout << "\t\t\t 1) Buy product   \n";
    cout << "                        \n";
    cout << "\t\t\t 2) Main menu     \n";

    cout << "\n\n\t\t\t Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        receipt();
        break;

    case 2:
        menu();

    default:
        cout << "Invalid entry !";
    }

    goto buyer;
}


//add function implementation
void Shopping::add() {

m:

    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\n\n\t\t\t Add new product";
    cout << "\n\n\t Please enter Product code: ";
    cin >> pcode;
    cout << "\n\n\tPlease enter product name: ";
    cin >> pname;
    cout << "\n\n\tPlease enter product price: ";
    cin >> price;
    cout << "\n\n\tPlease enter discount percentage: ";
    cin >> disc;

    data.open("database.txt", ios::in);

    if (!data) {
        data.open("database.txt", ios::app | ios::out);
        data << " " << pcode << " " << pname << " " << price << " " << disc << "\n";
        data.close();
    }
    else
    {
        data >> c >> n >> p >> d;
        while (!data.eof()) {
            if (c == pcode) {
                token++;
            }
            data >> c >> n >> p >> d;
        }
        data.close();
    

    if (token == 1)
        goto m;
    else
    {
        data.open("database.txt", ios::app | ios::out);
        data << " " << pcode << " " << pname << " " << price << " " << disc << "\n";
        data.close();
    }
}
    cout<<"\n\n\t\t Record saved.!";
} // end of add function


//edit function implementation
void Shopping::edit() {
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << "\n\t\t\t Modify the record";
    cout << "\n\t\t\t Please enter Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n File does not exist !";
    }
    else {
        data1.open("database1.txt", ios::app | ios::out);

        data >> pcode >> pname >> price >> disc;
        while (!data.eof()) {
            if (pkey == pcode) {
                cout<<"\n\t\t\t Please enter product new code: ";
                cin >> c;
                cout << "\n\t\t\t Please enter product name: ";
                cin >> n;
                cout << "\n\t\t\t Please enter product Price: ";
                cin >> p;
                cout << "\n\t\t\t Please enter product discount: ";
                cin >> d;
                data1<<" "<<c<<" "<<n<<" "<<p<<" "<<d<<"\n";
                cout << "\n\n\t\t Record edited !";
                token++;
            }
            else
            {
                data1 << " " << pcode << " " << pname << " " << price << " " << disc << "\n";
            }
            data >> pcode >> pname >> price >> disc;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");
        if (token == 0) {
            cout << "Record was not found !";
        }
    }
} //end of edit function



//remove function implementation
void Shopping::rem() {
    fstream data, data1;
    int pkey;
    int token = 0;
    cout << "\n\t\t Delete product\n";
    cout << "\n\n\tPlease enter product code: ";
    cin >> pkey;
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "File does not found !";
    }
    else {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> disc;
        while (!data.eof()) {
            if (pcode == pkey) {
                cout << "\n\n\t Product deleted successfully !";
                token++;
            }
            else {
                data1 << pcode << " " << pname << " " << price << " " << disc<<"\n";
            }
            data >> pcode >> pname >> price >> disc;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\n\t Record not found !";
        }
    }

} //end of delete function



//list function implementation
void Shopping::list() {
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n\t\t|.........................................\n";
    cout << "\t\tproduct no\tproduct name\tprice\n";
    cout << "\n\t\t|.........................................\n";
    data >> pcode >> pname >> price >> disc;

    while (!data.eof()) {
        cout <<"\t\t"<< pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> disc;
    }
    data.close();
} //end of list function



//receipt function implementation
void Shopping::receipt() {

//m:

    fstream data;

    int arrc[100]{};
    int arrq[100]{};
    char choice;
    int c = 0;
    float amount = 0;
    float disc = 0;
    float total = 0;

    cout << "\n\n\t\t\t\t Receipt";
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n Database is empty !";
    }
    else {
        data.close();

        list();
        cout << "\n\n\n\t\t.............................\n";
        cout << "\n\t\t|                           |\n";
        cout << "\n\t\t   Please place your order    \n";
        cout << "\n\t\t|                           |\n";
        cout << "\t\t.............................\n";

        do {
        m:

            cout << "\n\n\t\tPlease enter the product code: ";
            cin >> arrc[c];
            cout << "\n\n\t\tPlease enter the product quantity: ";
            cin >> arrq[c];
            for (int i = 0; i < c; i++) {
                if (arrc[c] == arrc[i]) {
                    cout << "\n\n\t\tDuplicate product code ! please try again";
                    goto m;
                }
            }
            c++; //if the product key is not duplicate, c will increment, it is called controval increment
            cout << "\n\n\t\tDo you want to buy another product? Press y for Yes, n for No: ";
            cin >> choice;
        } while (choice != 'n');

        cout << "\n\n\.......................................Receipt..................................................\n";
        cout << "\nprodtct no.\tproduct name\tproduct quantity\tprice\tamount\tamount with discount\n";

        
        for (int i = 0; i <= c; i++) {
            data.open("database.txt", ios::in);
            data >> pcode >> pname >> price >> disc;
            while (!data.eof()) {
                if (pcode == arrc[i]) {
                    amount = price * arrq[i];
                    disc = amount - (amount * disc / 100);
                    total =total+ disc;
                    cout << "\n"<<pcode<<"\t\t"<<pname<<"\t\t"<<arrq[i]<<"\t\t\t"<<price<<"\t"<<amount<<"\t\t"<<disc;
                }
                data >> pcode >> pname >> price >> disc;
            }
            data.close();
        }
        //data.close();
    }
    cout << "\n\n.................................................................................................";
    cout << "\n Total amount: $" << total;
} //end of receipt function


int main()
{
    Shopping shop;
    shop.menu();

}

