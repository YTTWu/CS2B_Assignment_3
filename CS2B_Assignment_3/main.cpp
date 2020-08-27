//
//  main.cpp
//  CS2B_Assignment_3
//
//  Created by yuteng Wu on 8/20/20.
//  Copyright © 2020 Yuteng Wu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>     /* atof */

using namespace std;


class Transaction
{
protected:
   string transactiondate;
   string transactionID;
   double transactionAmount;

public:
   Transaction();
   Transaction(string transDate, string transID, double transAmount);
   virtual ~Transaction();

   bool  operator== (const Transaction & right) const;

   virtual void display() = 0;
   virtual double earmPoints()= 0;

   void setTransdate(int date);
   void setTransID(int id);
   void setTransAmount(double amount);

   string getTransdate();
   string getTransID();
   double getTransAmount();
};


class DepartmentStoreTransaction : public Transaction
{
private:
   string departmentName;
   string returnPolicy;
public:
   DepartmentStoreTransaction();
   DepartmentStoreTransaction(string t_d, string t_I, double t_A, string d_N, string r_P);
   ~DepartmentStoreTransaction();

   void setDepartmentName(string d_N);
   void setReturnPolicy(string r_P);

   string getDepartmentName();
   string getReturnPolicy();

   void display();
   double earmPoints();
};


class BankingTransaction : public Transaction
{
private:
   string type;
   double feeCharge;
public:
   BankingTransaction();
   BankingTransaction(string t_d, string t_I, double t_A, string tp, double f_C);
   ~BankingTransaction();

   void setType(string type);
   void setFreeCharge(double f_C);

   string getType();
   double getFreecharge();

   void display();
   double earmPoints();
};


class GroceryTransaction : public Transaction
{
private:
   string storeName;
public:
   GroceryTransaction();
   GroceryTransaction(string t_d, string t_I, double t_A, string s_N);
   ~GroceryTransaction();

   void setStoreName(string s_N);

   string getStoreName();

   void display();
   double earmPoints();
};



const int array_size = 16;

class Customer
{
private:
   string customerName;
   string creditCardNumber;
   double transactionBalance;
   double rewardPointsTotal;
   Transaction *customerTran[array_size];
   int tran_count;
   //int tran_count = 0;

public:
   Customer();
   Customer(string c_name, string c_CN, double trans_B, double r_P);
   ~Customer();

   void readTransactions();
   void reportAllTransactions();
   void reportRewardSummary();

   string getCustomerName();
   string getCustomerCN();
   double getTransBalance();
   double getRewardP();









};






int main()
{
   Customer* p_customer = new Customer("Yuteng Wu", "1234567890123456", 10000, 998);
     p_customer->readTransactions();
     p_customer->reportAllTransactions();
     p_customer->reportRewardSummary();
     //p_customer->DuplicatedTransactionReport();
     delete p_customer;

}



//---------------------------class Customer definition---------------

Customer::Customer():customerName(""),creditCardNumber(""),transactionBalance(0.0),
rewardPointsTotal(1000), tran_count(0){}

Customer::Customer(string c_name, string c_CN, double trans_B, double r_P):customerName(c_name),
creditCardNumber(c_CN), tran_count(0), rewardPointsTotal(r_P){}

Customer::~Customer()
{
   for(int i = 0; i < tran_count; i++)
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
   double transactionAmount;

   string departmentName;
   string returnPolicy;

   string type;
   double feeCharge;

   string storeName;


   ifstream fin("transactionReport.txt");

   if(!fin)
   {
      cout << "ERROR: Failed to open input file\n";

      exit(-1);
   }

   while(getline(fin, buffer, '~' ))
   {
      buffer.erase(remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
      transactionType = buffer[0];

      getline(fin, buffer, '~');
      transactionDate = buffer;

      getline(fin, buffer, '~');
      transactionId = buffer;

      getline(fin, buffer, '~');
      transactionAmount = atof(buffer.c_str());


      switch (transactionType)
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
              feeCharge = stod(buffer);

              customerTran[tran_count] = new BankingTransaction
              (transactionDate, transactionId, transactionAmount, type, feeCharge);

              tran_count++;
              break;

           case 'G':
              getline(fin, buffer, '~');
              storeName = buffer;

              customerTran[tran_count] = new GroceryTransaction
              (transactionDate, transactionId, transactionAmount, storeName);

              tran_count++;
              break;

           default:
              break;
        }
   }
}


void Customer::reportAllTransactions()
{
   double totalFeeCharged = 0;
   double totalBalance = 0;
   double transAmount = 0;;

   double departmentPurchase = 0;
   double BankinngPurchase = 0;
   double groceryPurchase = 0;

   DepartmentStoreTransaction *p_D;
   BankingTransaction *p_B;
   GroceryTransaction *p_G;

   int d_C = 0, b_C = 0, g_C = 0;

   cout << "-----------------Transactions Listings-------------------" << endl;

   for(int i = 0; i < tran_count; i++)
   {
      customerTran[i]->display();

      transAmount += customerTran[i]->getTransAmount();

      if((p_D = dynamic_cast<DepartmentStoreTransaction*>(customerTran[i])))
      {
         d_C++;
         departmentPurchase += p_D->getTransAmount();

      }

      if((p_B = dynamic_cast<BankingTransaction*>(customerTran[i])))
      {
         b_C++;
         totalFeeCharged += p_B->getFreecharge();
         BankinngPurchase += p_B->getTransAmount();
      }

      if((p_G = dynamic_cast<GroceryTransaction*>(customerTran[i])))
      {
         g_C++;
         groceryPurchase += p_G->getTransAmount();
      }
      cout << endl;
   }

   totalBalance = departmentPurchase + BankinngPurchase + groceryPurchase + totalFeeCharged;

   cout << "Total fee charge: $" << totalFeeCharged << endl;
   cout << "Total balance: $" << totalBalance << endl << endl;

   cout << "Total Purchase " << "  Transaction type " << "    Transaction count " << endl;
   cout << departmentPurchase << "          " << " Department Store         " << d_C << endl;
   cout << BankinngPurchase << "          " << "    Banking                  " << b_C << endl;
   cout << groceryPurchase << "          " << "  Grocery Store            " << g_C << endl;
   cout << "Total: " << totalBalance << endl << endl;

}


void Customer::reportRewardSummary()
{
   DepartmentStoreTransaction *p_D;
   GroceryTransaction *p_G;

   double d_TotoalPoints = 0;
   double g_TotalPoints = 0;
   double totalPoints = 0;

   for(int i = 0; i < tran_count; i++)
   {
      if((p_D = dynamic_cast<DepartmentStoreTransaction*>(customerTran[i])))
      {
         d_TotoalPoints += p_D->earmPoints();
      }

      else if((p_G = dynamic_cast<GroceryTransaction*>(customerTran[i])))
      {
         g_TotalPoints += p_G->earmPoints();
      }
   }


   cout << "Rewards Summary for " << getCustomerName() << " " << getCustomerCN() << endl;
   cout << "Previous points balance: " << getRewardP() << endl;
   cout << "+ Department store purchase:   " << d_TotoalPoints << endl;
   cout << "+ Grocery purchase:   " << g_TotalPoints << endl << endl;

   totalPoints = getRewardP() + d_TotoalPoints + g_TotalPoints;

   cout << "Total points available for redemption: " << totalPoints << endl;




}


string Customer::getCustomerName()
{
   return customerName;
}


string Customer::getCustomerCN()
{
   return creditCardNumber;
}


double Customer::getTransBalance()
{
   return transactionBalance;
}


double Customer::getRewardP()
{
   return rewardPointsTotal;
}

//---------------------class Transaction definition----------------------
Transaction::Transaction():transactiondate(""),transactionID(""), transactionAmount(0.0){}

Transaction::Transaction(string t_d, string t_I, double t_A):transactiondate(t_d),
transactionID(t_I), transactionAmount(t_A){}

Transaction::~Transaction()
{
   cout << "Transaction: " << transactionID << " destroyed" << endl;
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


double Transaction::getTransAmount()
{
   return transactionAmount;
}


//-----------------------class DepartmentStoreTransaction definition-----------------
DepartmentStoreTransaction::DepartmentStoreTransaction():Transaction(), departmentName(""),
returnPolicy(""){}

DepartmentStoreTransaction::DepartmentStoreTransaction(string t_d, string t_I, double t_A, string d_N, string r_P):
Transaction(t_d, t_I, t_A), departmentName(d_N), returnPolicy(r_P){}

DepartmentStoreTransaction::~DepartmentStoreTransaction()
{
   cout << "Transaction " << departmentName << " destroyed..." << endl;
}

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

void DepartmentStoreTransaction::display()
{
   cout << transactiondate << " Department Store: " << departmentName << " return in "
   << returnPolicy << " $" << transactionAmount << endl;
}

double DepartmentStoreTransaction::earmPoints()
{
   double points;

   points = getTransAmount() * 1.5;

   return points;
}




//-----------------------class BankingTransaction definition-----------------
BankingTransaction::BankingTransaction():Transaction(), type(""), feeCharge(0.0){}

BankingTransaction::BankingTransaction(string t_d, string t_I, double t_A, string tP, double f_C):
Transaction(t_d, t_I, t_A), type(tP), feeCharge(f_C){}

BankingTransaction::~BankingTransaction()
{
   cout << "Transaction " << type << " destroyed..." << endl;
}

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

double BankingTransaction::getFreecharge()
{
   return feeCharge;
}

void BankingTransaction::display()
{
   cout << transactiondate << " Banking: " << type << " " << transactionAmount
   << " fee charged: " <<feeCharge << endl;
}

double BankingTransaction::earmPoints()
{
   return 0;
}



//-----------------------class GroceryTransaction definition-----------------
GroceryTransaction::GroceryTransaction():Transaction(), storeName(""){}

GroceryTransaction::GroceryTransaction(string t_d, string t_I, double t_A, string s_N):
Transaction(t_d, t_I, t_A), storeName(s_N){}

GroceryTransaction::~GroceryTransaction()
{
   cout << "Transaction " << storeName << " destroyed..." << endl;
}

void GroceryTransaction::setStoreName(string s_N)
{
   this->storeName = s_N;
}

string GroceryTransaction::getStoreName()
{
   return storeName;
}

void GroceryTransaction::display()
{
   cout << transactiondate << " Grocery " << transactionAmount << " " << storeName << endl;
}

double GroceryTransaction::earmPoints()
{
   double points;

   points = getTransAmount() * 2.5;

   return points;
}
