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
   int transactionData;
   int transactionID;
   double transactionAmount;

public:
   Transaction();
   Transaction(int transDate, int transID, double transAmount);
   virtual ~Transaction();

   bool  operator== (const Transaction & right) const;

   virtual void display() = 0;
   virtual void earmPoints()= 0;

   void setTransData(int data);
   void setTransID(int id);
   void setTransAmount(double amount);

   int getTransData();
   int getTransID();
   double getTransAmount();
};


class DepartmentStoreTransaction : public Transaction
{
private:
   string departmentName;
   string returnPolicy;
public:
   DepartmentStoreTransaction();
   DepartmentStoreTransaction(int t_d, int t_I, double t_A, string d_N, string r_P);
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
   double feeCharge;
public:
   BankingTransaction();
   BankingTransaction(int t_d, int t_I, double t_A, string tp, double f_C);
   ~BankingTransaction();

   void setType(string type);
   void setFreeCharge(double f_C);

   string getType();
   double getFreecharge();

   virtual void display();
   virtual void earmPoints();
};


class GroceryTransaction : public Transaction
{
private:
   string storeName;
public:
   GroceryTransaction();
   GroceryTransaction(int t_d, int t_I, double t_A, string s_N);
   ~GroceryTransaction();

   void setStoreName(string s_N);

   string getStoreName();

   virtual void display();
   virtual void earmPoints();
};





class Customer
{
private:
   string customerName;
   string creditCardNumber;
   double transactionBalance;
   int rewardPointsTotal;
   Transaction *customerTran[];

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
rewardPointsTotal(1000){}

Customer::Customer(string c_name, string c_CN, double trans_B):customerName(c_name),
creditCardNumber(c_CN){}

Customer::~Customer()
{

}



//---------------------class Transaction definition----------------------
Transaction::Transaction():transactionData(0),transactionID(0), transactionAmount(0.0){}

Transaction::Transaction(int t_d, int t_I, double t_A):transactionData(t_d),
transactionID(t_I), transactionAmount(t_A){}

Transaction::~Transaction()
{

}


bool Transaction::operator==(const Transaction &) const
{
   return true;
}


void Transaction::setTransData(int data)
{

}


void Transaction::setTransID(int id)
{

}


void Transaction::setTransAmount(double amount)
{

}


int Transaction::getTransData()
{
   return transactionData;
}


int Transaction::getTransID()
{
   return transactionID;
}


double Transaction::getTransAmount()
{
   return transactionAmount;
}


//-----------------------class DepartmentStoreTransaction definition-----------------
DepartmentStoreTransaction::DepartmentStoreTransaction():Transaction(), departmentName(""),
returnPolicy(""){}

DepartmentStoreTransaction::DepartmentStoreTransaction(int t_d, int t_I, double t_A, string d_N, string r_P):
Transaction(t_d, t_I, t_A), departmentName(d_N), returnPolicy(r_P){}

void DepartmentStoreTransaction::setDepartmentName(string d_N)
{
   departmentName = d_N;
}

void DepartmentStoreTransaction::setReturnPolicy(string r_P)
{
   returnPolicy = r_P;
}






//-----------------------class BankingTransaction definition-----------------
BankingTransaction::BankingTransaction():Transaction(), type(""), feeCharge(0.0){}

BankingTransaction::BankingTransaction(int t_d, int t_I, double t_A, string tP, double f_C):
Transaction(t_d, t_I, t_A), type(tP), feeCharge(f_C){}







//-----------------------class GroceryTransaction definition-----------------
GroceryTransaction::GroceryTransaction():Transaction(), storeName(""){}

GroceryTransaction::GroceryTransaction(int t_d, int t_I, double t_A, string s_N):
Transaction(t_d, t_I, t_A), storeName(s_N){}
