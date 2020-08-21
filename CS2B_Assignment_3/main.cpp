//
//  main.cpp
//  CS2B_Assignment_3
//
//  Created by yuteng Wu on 8/20/20.
//  Copyright © 2020 Yuteng Wu. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;


class Transaction
{
protected:
   string transactiondate;
   string transactionID;
   string transactionAmount;

public:
   Transaction();
   Transaction(string transDate, string transID, string transAmount);
   virtual ~Transaction();

   bool  operator== (const Transaction & right) const;

   virtual void display() = 0;
   virtual void earmPoints()= 0;

   void setTransdate(int date);
   void setTransID(int id);
   void setTransAmount(double amount);

   string getTransdate();
   string getTransID();
   string getTransAmount();
};


class DepartmentStoreTransaction : public Transaction
{
private:
   string departmentName;
   string returnPolicy;
public:
   DepartmentStoreTransaction();
   DepartmentStoreTransaction(string t_d, string t_I, string t_A, string d_N, string r_P);
   ~DepartmentStoreTransaction();

   void setDepartmentName(string d_N);
   void setReturnPolicy(string r_P);

   string getDepartmentName();
   string getReturnPolicy();

   virtual void display();
   virtual void earmPoints();
};


class BankingTransaction : public Transaction
{
private:
   string type;
   string feeCharge;
public:
   BankingTransaction();
   BankingTransaction(string t_d, string t_I, string t_A, string tp, string f_C);
   ~BankingTransaction();

   void setType(string type);
   void setFreeCharge(double f_C);

   string getType();
   string getFreecharge();

   virtual void display();
   virtual void earmPoints();
};


class GroceryTransaction : public Transaction
{
private:
   string storeName;
public:
   GroceryTransaction();
   GroceryTransaction(string t_d, string t_I, string t_A, string s_N);
   ~GroceryTransaction();

   void setStoreName(string s_N);

   string getStoreName();

   virtual void display();
   virtual void earmPoints();
};



const int array_size = 16;

class Customer
{
private:
   string customerName;
   string creditCardNumber;
   double transactionBalance;
   int rewardPointsTotal;
   Transaction *customerTran[array_size];
   int tran_count;
   //int tran_count = 0;

public:
   Customer();
   Customer(string c_name, string c_CN, double trans_B);
   ~Customer();

   void readTransactions();
   void reportAllTransactions();
   void reportRewardSummary();








};






int main()
{


}



//---------------------------class Customer definition---------------

Customer::Customer():customerName(""),creditCardNumber(""),transactionBalance(0.0),
rewardPointsTotal(1000), tran_count(0){}

Customer::Customer(string c_name, string c_CN, double trans_B):customerName(c_name),
creditCardNumber(c_CN), tran_count(0){}

Customer::~Customer()
{
   for(int i = 0; i < array_size; i++)
   {
      delete customerTran[i];
   }
}


void Customer::readTransactions()
{
   string buffer;
   char transactionType;
   string transactionDate;
   string transactionId;
   string transactionAmount;

   string departmentName;
   string returnPolicy;

   string type;
   string feeCharge;

   string storeName;


   ifstream fin("transactionReport");

   if(!fin)
   {
      cout << "ERROR: Failed to open input file\n";

      exit(-1);
   }

   while(getline(fin, buffer, '~' ))
   {
      transactionType = buffer[0];

      getline(fin, buffer, '~');
      transactionDate = buffer;

      getline(fin, buffer, '~');
      transactionId = buffer;

      getline(fin, buffer, '~');
      transactionAmount = buffer;


      switch (buffer[0])
        {
           case 'D':
              getline(fin, buffer, '~');
              departmentName = buffer;

              getline(fin, buffer, '~');
              returnPolicy = buffer;

              customerTran[tran_count] = new DepartmentStoreTransaction
              (transactionDate, transactionId, transactionAmount, departmentName, returnPolicy);

              tran_count++;
              break;

           case 'B':
              getline(fin, buffer, '~');
              type = buffer;
              getline(fin, buffer, '~');
              feeCharge = buffer;

              customerTran[tran_count] = new BankingTransaction
              (transactionDate, transactionId, transactionAmount, type, feeCharge);
              break;

           case 'G':
              getline(fin, buffer, '~');
              storeName = buffer;

              customerTran[tran_count] = new GroceryTransaction
              (transactionDate, transactionId, transactionAmount, storeName);
              break;

           default:
              break;
        }




   }





}



//---------------------class Transaction definition----------------------
Transaction::Transaction():transactiondate(""),transactionID(""), transactionAmount(""){}

Transaction::Transaction(string t_d, string t_I, string t_A):transactiondate(t_d),
transactionID(t_I), transactionAmount(t_A){}

Transaction::~Transaction()
{

}


bool Transaction::operator==(const Transaction &) const
{
   return true;
}


void Transaction::setTransdate(int date)
{
   transactiondate = date;
}


void Transaction::setTransID(int id)
{
   transactionID = id;
}


void Transaction::setTransAmount(double amount)
{
   transactionAmount = amount;
}


string Transaction::getTransdate()
{
   return transactiondate;
}


string Transaction::getTransID()
{
   return transactionID;
}


string Transaction::getTransAmount()
{
   return transactionAmount;
}


//-----------------------class DepartmentStoreTransaction definition-----------------
DepartmentStoreTransaction::DepartmentStoreTransaction():Transaction(), departmentName(""),
returnPolicy(""){}

DepartmentStoreTransaction::DepartmentStoreTransaction(string t_d, string t_I, string t_A, string d_N, string r_P):
Transaction(t_d, t_I, t_A), departmentName(d_N), returnPolicy(r_P){}

void DepartmentStoreTransaction::setDepartmentName(string d_N)
{
   departmentName = d_N;
}

void DepartmentStoreTransaction::setReturnPolicy(string r_P)
{
   returnPolicy = r_P;
}

string DepartmentStoreTransaction::getDepartmentName()
{
   return departmentName;
}

string DepartmentStoreTransaction::getReturnPolicy()
{
   return returnPolicy;
}




//-----------------------class BankingTransaction definition-----------------
BankingTransaction::BankingTransaction():Transaction(), type(""), feeCharge(""){}

BankingTransaction::BankingTransaction(string t_d, string t_I, string t_A, string tP, string f_C):
Transaction(t_d, t_I, t_A), type(tP), feeCharge(f_C){}

void BankingTransaction::setType(string type)
{
   this->type = type;
}

void BankingTransaction::setFreeCharge(double f_C)
{
   this->feeCharge = f_C;
}

string BankingTransaction::getType()
{
   return type;
}

string BankingTransaction::getFreecharge()
{
   return feeCharge;
}



//-----------------------class GroceryTransaction definition-----------------
GroceryTransaction::GroceryTransaction():Transaction(), storeName(""){}

GroceryTransaction::GroceryTransaction(string t_d, string t_I, string t_A, string s_N):
Transaction(t_d, t_I, t_A), storeName(s_N){}

void GroceryTransaction::setStoreName(string s_N)
{
   this->storeName = s_N;
}

string GroceryTransaction::getStoreName()
{
   return storeName;
}
