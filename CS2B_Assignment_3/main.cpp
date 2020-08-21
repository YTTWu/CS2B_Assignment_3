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
   double transactionAmount;

public:
   Transaction();
   Transaction(string transDate, string transID, double transAmount);
   virtual ~Transaction();

   bool  operator== (const Transaction & right) const;

   virtual void display() = 0;
   virtual void earmPoints()= 0;

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
   BankingTransaction(string t_d, string t_I, double t_A, string tp, double f_C);
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
   GroceryTransaction(string t_d, string t_I, double t_A, string s_N);
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
   double transactionAmount;

   string departmentName;
   string returnPolicy;

   string type;
   double feeCharge;

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
      transactionAmount = stod(buffer);


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
              feeCharge = stod(buffer);

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


void Customer::reportAllTransactions()
{
   double totalFeeCharged = 0;
   double transAmount = 0;;

   DepartmentStoreTransaction *p_D;
   BankingTransaction *p_B;
   GroceryTransaction *p_G;

   int d_C = 0, b_C = 0, g_C = 0;

   for(int i = 0; i < tran_count; i++)
   {
      customerTran[i]->display();

      transAmount += customerTran[i]->getTransAmount();

      if((p_D = dynamic_cast<DepartmentStoreTransaction*>(customerTran[i])))
      {
         d_C++;
      }

      if((p_B = dynamic_cast<BankingTransaction*>(customerTran[i])))
      {
         b_C++;
         totalFeeCharged += p_B->getFreecharge();
      }

      if((p_G = dynamic_cast<GroceryTransaction*>(customerTran[i])))
      {
         g_C++;
      }
      cout << endl;
   }

   cout << "Total Purchase " << " Transaction type " << " Transaction count " << " Total " << endl;


}



//---------------------class Transaction definition----------------------
Transaction::Transaction():transactiondate(""),transactionID(""), transactionAmount(0.0){}

Transaction::Transaction(string t_d, string t_I, double t_A):transactiondate(t_d),
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


double Transaction::getTransAmount()
{
   return transactionAmount;
}


//-----------------------class DepartmentStoreTransaction definition-----------------
DepartmentStoreTransaction::DepartmentStoreTransaction():Transaction(), departmentName(""),
returnPolicy(""){}

DepartmentStoreTransaction::DepartmentStoreTransaction(string t_d, string t_I, double t_A, string d_N, string r_P):
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

void DepartmentStoreTransaction::display()
{
   cout << transactiondate << " Department Store: " << departmentName << " return in "
   << returnPolicy << " $" << transactionAmount << endl;
}




//-----------------------class BankingTransaction definition-----------------
BankingTransaction::BankingTransaction():Transaction(), type(""), feeCharge(0.0){}

BankingTransaction::BankingTransaction(string t_d, string t_I, double t_A, string tP, double f_C):
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

double BankingTransaction::getFreecharge()
{
   return feeCharge;
}

void BankingTransaction::display()
{
   cout << transactiondate << " Banking: " << type << " " << transactionAmount
   << " fee charged: " <<feeCharge << endl;
}



//-----------------------class GroceryTransaction definition-----------------
GroceryTransaction::GroceryTransaction():Transaction(), storeName(""){}

GroceryTransaction::GroceryTransaction(string t_d, string t_I, double t_A, string s_N):
Transaction(t_d, t_I, t_A), storeName(s_N){}

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
