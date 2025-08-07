#include<iostream>
#include<limits>
#include<iomanip>
using namespace std;
class Calculator
{
public:
    float add(float a,float b)
    {
        return a+b;
    }
    float subtract(float a,float b)
    {
        return a-b;
    }
    float multiply(float a,float b)
    {
        return a*b;
    }
    float divide(float a,float b)
    {
        if(b==0)
        {
            return 0;
        }
        return a/b;
    }
};
void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}
int main()
{
    Calculator calc;
    float num1,num2;
    char op;
    char choice;
    cout<<"===== C++ OOP Calculator ====="<<endl;
    do
    {
        cout<<"\nEnter first number: ";
        while(!(cin>>num1))
        {
            cout<<"Invalid input! Please enter a valid number: ";
            clearInput();
        }
        cout<<"Enter operator (+, -, *, /): ";
        cin>>op;
        if(op!='+'&&op!='-'&&op!='*'&&op!='/')
        {
            cout<<"Invalid operator! Please use only +, -, *, or /."<<endl;
            clearInput();
            continue;
        }
        cout<<"Enter second number: ";
        while(!(cin>>num2))
        {
            cout<<"Invalid input! Please enter a valid number: ";
            clearInput();
        }
        if(op=='/'&&num2==0)
        {
            cout<<"Error: Cannot divide by zero!"<<endl;
            continue;
        }
        float result=0.0;
        switch(op)
        {
            case '+':
                result=calc.add(num1,num2);
                break;
            case '-':
                result=calc.subtract(num1,num2);
                break;
            case '*':
                result=calc.multiply(num1,num2);
                break;
            case '/':
                result=calc.divide(num1,num2);
                break;
            default:
                cout<<"Invalid, Check your Input..!"<<endl;
                return 1;
        }
        cout<<fixed<<setprecision(4);
        cout<<"\nResult: "<<num1<<" "<<op<<" "<<num2<<" = "<<result<<endl;
        cout<<"\nDo you want to perform another calculation? (y/n): ";
        cin>>choice;
        clearInput();
    }
    while(choice=='y'||choice=='Y');
    cout<<"Thank you for using the calculator. Goodbye!"<<endl;
    return 0;
}