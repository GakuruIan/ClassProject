#include <iostream>
#include <fstream>
#include<conio.h>
#include <cerrno>
#include <cstring>
#include <iomanip>
#include <vector>

using namespace std;



// product class
class Product{
private:
  fstream productfile;

public:
  vector<Product> products;
  char product_name[20];
  int id;
  int price;
  int quantity;

  void AddProduct();
  void GetProductDetails();
  void FetchAllProducts();
  void DisplayProduct();
  void ListProducts();
  void SearchProduct();
  void UpdateProduct();
  void DeleteProduct();
}product;


// getting product details
void Product::GetProductDetails(){
  fflush(stdin);
  std::cout << "ENTER PRODUCT NAME " << '\n';
  cin.getline(product_name,20);
  std::cout << "ENTER PRODUCT ID" << '\n';
  std::cin >> id;
  std::cout << "ENTER PRODUCT PRICE " << '\n';
  std::cin >> price;
  std::cout << "ENTER PRODUCT QUANTITY " << '\n';
  std::cin >> quantity;
}

// create product
void Product::AddProduct(){
  productfile.open("products.bin",ios::out|ios::binary);

  if(!productfile.is_open()){
    std::cerr << "ERROR IN OPENNING FILE" << '\n';
  }
    system("cls");
    std::cout << "CREATE PRODUCT " << '\n';
    product.GetProductDetails();

    productfile.write((char *)&product,sizeof(product));

    productfile.close();
    std::cout << "PRODUCT ADDED SUCCESSFULLY" << '\n';
}

// display all products
void Product::DisplayProduct(){
  std::cout << "Id: "<<id << '\n';
  std::cout << "Name: "<<product_name << '\n';
  std::cout << "Price: "<<price << '\n';
  std::cout << "Quantity: "<< quantity << '\n';
}

// list all products
void Product::ListProducts(){
  productfile.open("products.bin",ios::in|ios::binary);

  if(!productfile.is_open()){
    std::cerr << "ERROR IN OPENNING FILE" << '\n';
  }
  system("cls");
  std::cout << "---------------PRODUCT LIST---------------" << '\n';
  while (productfile.read((char *)&product,sizeof(product))) {
    product.DisplayProduct();
    std::cout << "-----------------------------------------------------" << '\n';
  }

  productfile.close();
}

// search for a product
void Product::SearchProduct(){
  Product p;
   productfile.open("products.bin",ios::in|ios::binary);
   int id;

   if(!productfile.is_open()){
     std::cerr << "ERROR IN OPENNING FILE " << '\n';
   }
   std::cout << "ENTER PRODUCT ID TO SEARCH " << '\n';
   std::cin >> id;

   while (productfile.read((char *)&p,sizeof(p))) {
     if(p.id == id){
       p.DisplayProduct();
     }

   }
  productfile.close();
}


// Delete product
void Product::DeleteProduct(){
  int id;
  fstream temp;
  bool flag = false;
  int delete_result;
  Product p;
  //open product file
  productfile.open("products.bin",ios::in|ios::binary);

  // open trash FILE
  temp.open("trash.bin",ios::out|ios::binary|ios::app);

  if(!productfile.is_open() || !temp.is_open()){
    std::cerr << "ERROR IN OPENNING FIlE" << '\n';
  }

  std::cout << "ENTER PRODUCT ID TO DELETE " << '\n';
  std::cin >> id;

  while (productfile.read((char *)&p,sizeof(p))) {
    if(p.id != id){
      temp.write((char *)&p,sizeof(p));
    }
    else{
      flag = true;
    }
  }

  productfile.close();
  temp.close();

  if(!flag){
    std::cout << "NO RECORD FOUND " << '\n';
  }
 else{
   try{
       // delete the product file
     delete_result = remove("products.bin");

        if(delete_result != 0){
          throw runtime_error(strerror(errno));
        }
   }
   catch(exception &ex){
     std::cerr << "Error in deleting file "<<ex.what() << '\n';
   }

   if(delete_result == 0){
     // renaming the trash FIlE
      rename("trash.bin","products.bin");
      std::cout << "PRODUCT DELETED SUCCESSFULLY" << '\n';
   }
 }


}


// staff CLASS
class Staff{
   private:
     fstream input;
     fstream output;

   protected:
     char name[20];
     char role[29];
     int id;
     int pass;
   public:
     void CreateAccount();
     string LoginAccount(int empID,int pass);
     void GetUserInfo();
     void DisplayUserDetails();
     void ListEmployees();
     void SearchEmployee();
     void DeleteEmployee();
     void UpdateEmployee();
     int GetUserId();
     int GetUserPassword();

}staff;

// collecting employees information
void Staff::GetUserInfo(){
  fflush(stdin);
  std::cout << "ENTER EMPLOYEE FULLNAME " << '\n';
  cin.getline(name,20);
  std::cout << "ENTER EMPLOYEE ROLE" << '\n';
  cin.getline(role,20);
  std::cout << "ENTER EMPLOYEE ID " << '\n';
  std::cin >> id;
  std::cout << "CREATE PASSWORD " << '\n';
  std::cin >> pass;
}

// creating employee account
void Staff::CreateAccount(){
  output.open("staff.bin",ios::out|ios::app|ios::binary);

  if(!output.is_open()){
    std::cerr << "ERROR IN OPENNING FILE!!" << '\n';
    exit(1);
  }
  std::cout << "\t\t\t\tCREATE EMPLOYEE" << '\n';
  //staff.GetUserInfo();
  fflush(stdin);
  std::cout << "ENTER EMPLOYEE FULLNAME " << '\n';
  cin.getline(name,20);
  std::cout << "ENTER EMPLOYEE ROLE" << '\n';
  cin.getline(role,20);
  std::cout << "ENTER EMPLOYEE ID " << '\n';
  std::cin >> id;
  std::cout << "CREATE PASSWORD " << '\n';
  std::cin >> pass;

  output.write(reinterpret_cast<char *>(&staff),sizeof(staff));

  output.close();
  std::cout << "USER ADDED SUCCESSFULLY "<< '\n';
}

void Staff::ListEmployees(){
  Staff s;
  output.open("staff.bin",ios::in|ios::binary);

  if(!output.is_open()){
      std::cerr << "ERROR IN OPENNING FILE" << '\n';
  }

  std::cout << "Id " <<"\t Name " << "\t\t Role " << '\n';
  while (output.read(reinterpret_cast<char *>(&s),sizeof(s))) {
        std::cout <<s.id <<"\t" << s.name <<"\t" << s.role << '\n';
  }

  output.close();
}

// searching for an EMPLOYEE
void Staff::SearchEmployee(){
   bool flag =false;
   int empID;

   Staff s;

   std::cout << "ENTER EMPLOYEE ID TO SEARCH" << '\n';
   std::cin >> empID;

   output.open("staff.bin",ios::in|ios::binary);

   if (!output.is_open()) {
     std::cerr << "ERROR IN OPENNING FILE" << '\n';
   }

// traversing the file
   while (output.read((char *)&s,sizeof(s))) {
      if(s.GetUserId() == empID){
          flag=true;
          s.DisplayUserDetails();
      }
   }
   output.close();

   // checking if a employee exists
   if(!flag){
     std::cout << "EMPLOYEE NOT FOUND" << '\n';
   }

}

// displaying employee details
void Staff::DisplayUserDetails(){
         std::cout << "EMPLOYEE ID "<<id << endl;
         std::cout << "EMPLOYEE NAME: " << name<<endl;
         std::cout << "ROLE " << role<<endl;
}

// updating employee information

void Staff::UpdateEmployee(){

  int pos;
  int id =1;
  bool flag = false;
  Staff s;

  output.open("staff.bin",ios::in|ios::binary|ios::out);

  if(!output.is_open()){
    std::cerr << "ERROR IN OPENNING FILE" << '\n';
  }

  // getting the possition of the cursor
  pos=output.tellg();

  // traversing the file
  while(output.read((char *)&s,sizeof(s))){
    if(s.GetUserId() == id){
        std::cout << "CURRENT USER DETAILS " << '\n';
        s.DisplayUserDetails();
        std::cout << "-------------------------------------------" << '\n';
        flag = true;
    }
  }


  if(flag){
     std::cout << "ENTER NEW DETAILS " << '\n';
     s.GetUserInfo();

     // editting the FILE
     output.seekp(pos);
     output.write((char *)&s,sizeof(s));
     std::cout << "RECORD UPDATED SUCCESSFULLY !!!" << '\n';
  }
  else{
    std::cout << "NO RECORD FOUND" << '\n';
  }
  output.close();
}

// deleting an employee ACCOUNT
void Staff::DeleteEmployee(){
  int id;
  bool flag = false;
  fstream temp;
  Staff s;
  int delete_result;

  std::cout << "ENTER EMPLOYEE ID TO DELETE" << '\n';
  std::cin >> id;

  output.open("staff.bin",ios::in|ios::binary);
  temp.open("trash.bin",ios::out|ios::app|ios::binary);

  if (!output.is_open() && !temp.is_open()) {
    std::cerr << "ERROR IN OPENNING FILE" << '\n';
  }

 // traversing the file
  while (output.read((char *)&s,sizeof(s))) {
     if(s.GetUserId() != id){
         temp.write((char *)&s,sizeof(s));
     }
     else{
       flag = true;
     }
  }
  // close files
  output.close();
  temp.close();

// if no record is found
  if(!flag){
      std::cout << "NO RECORD FOUND" << '\n';
    }

 else{
   //deleting the staff FILE
   delete_result = remove("staff.bin");
   try{
        if(delete_result != 0){
          throw runtime_error(strerror(errno));
        }
   }
   catch(exception &ex){
     std::cerr << "Error in deleting file "<<ex.what() << '\n';
   }

   //renaming trash file to staff
   if(delete_result == 0){
      rename("trash.bin","staff.bin");
      std::cout << "DELETION SUCCESSFUL" << '\n';
   }

 }

}

string Staff::LoginAccount(const int empID,const int pass){
   output.open("staff.bin",ios::in|ios::binary);
   bool flag = false;

   if(!output.is_open()){
     std::cerr << "ERROR IN OPENNING FILE" << '\n';
   }

   while(output.read((char *)&staff,sizeof(staff))){
        if(staff.id == id){
           flag = true;
            if(staff.pass == pass){
               return staff.role;
            }
            else{
              std::cout << "INVALID CREDENTIALS " << '\n';
            }
        }
   }

   if(!flag){
     std::cout << "NO RECORD FOUND" << '\n';
   }

   return NULL;

}


// getting user id
int Staff::GetUserId(){
  return id;
}

// getting user PASSWORD
int Staff::GetUserPassword(){
  return pass;
}



//sell function
void sell(){

  int total = 0;
  int option;
  int id,price,quantity;

  do{
     std::cout << "ENTER PRODUCT ID: " << '\n';
     std::cin >> id;
     std::cout << "ENTER PRICE: " << '\n';
     std::cin >> price;
     std::cout << "ENTER QUANTITY: " << '\n';
     std::cin >> quantity;

     price = price * quantity;

     total = total + price;

     std::cout << "PRESS 1 TO CONTINUE 0 TO EXIT: " << '\n';
     std::cin >> option;

  }while(option != 0);

  std::cout << "TOTAL PRICE: "<<total << '\n';

}

// Employee MENU
void EmployeeMenu(){
  fflush(stdin);
  system("cls");

  int option;
  std::cout << "1. SELL PRODUCT " << '\n';
  std::cout << "2. PRODUCTS QUERY " << '\n';
  std::cin >> option;

  switch(option){
    case 1:
      sell();
    break;

    default:
    std::cout << "INVALID CHOICE " << '\n';
  }
}

// Admin menu
void Adminmenu(){

    int option;

    system("cls");
    std::cout << "1. CREATE AN EMPLOYEE ACCOUNT " << '\n';
    std::cout << "2. LIST ALL EMPLOYEES " << '\n';
    std::cout << "3. SEARCH EMPLOYEE " << '\n';
    std::cout << "4. EDIT EMPLOYEE ACCOUNT " << '\n';
    std::cout << "5. DELETE EMPLOYEE ACCOUNT " << '\n';
    std::cout << "6. CREATE PRODUCT " << '\n';
    std::cout << "7. LIST ALL PRODUCTS " << '\n';
    std::cout << "8. SEARCH PRODUCT " << '\n';
    std::cout << "9. EDIT PRODUCT " << '\n';
    std::cout << "10. DELETE PRODUCT " << '\n';
    std::cout << "0. EXIT " << '\n';

    std::cout << "ENTER YOUR OPTION" << '\n';
    std::cin >> option;

    switch (option) {
      case 0:
      std::cout << "GOODBYE...." << '\n';
      break;
      case 1:
        staff.CreateAccount();
        break;
        case 2:
        staff.ListEmployees();
        break;
      case 3:
        staff.SearchEmployee();
        break;
      case 4:
       staff.UpdateEmployee();
       break;
      case 5:
      staff.DeleteEmployee();
      break;
      case 6:
       product.AddProduct();
      break;
      case 7:
       product.ListProducts();
      break;
      case 8:
      product.SearchProduct();
      break;
      case 10:
      product.DeleteProduct();
      break;
      default:
       std::cout << "INVALID INPUT " << '\n';
     }
}

void LoginMenu(){
  int pass;
  int id;
string role;

  std::cout << "--------------------WELCOME TO POS LOGIN TO ACCOUNT--------------------" << '\n';
  std::cout << "ENTER YOUR EMPLOYEE ID: " << '\n';
  std::cin >> id;
  std::cout << "ENTER YOUR PASSWORD: " << '\n';
  std::cin >> pass;

  role = staff.LoginAccount(id,pass);

  if(!role.empty()){
      if((role.compare("admin"))== 0){
          Adminmenu();
      }
      else{
         EmployeeMenu();
      }
  }

}

int main(int argc, char const *argv[]) {
  // Adminmenu();
  LoginMenu();
  return 0;
}
