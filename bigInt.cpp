#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <iostream>

using namespace std;
void reverseNum(char*);
//Precondition: input is a char type array.
//Postcondition: return reverse input array.

class BigInt
{
public:
    BigInt();
    //Constructor default nothing.
    ~BigInt();
    //destructor delete *charValue.
    BigInt(int intValueTmp);
    //Constructor default intValue.
    BigInt(string charValueTmp);
    //Constructor default charValue.
    BigInt(const BigInt& copyObj);
    //Constructor let copy copyObj's charValue to calling object's charValue.
    BigInt& operator=(const BigInt& number);
    //Constructor let number's charValue's array's value assign to calling object's charValue.
    friend ostream& operator <<(ostream& outputStream,const BigInt& amount);
    //Precondition: outputStream is the output. amount is the BigInt's object.
    //Postcondition: return the amount's value.(intValue or charValue)
    friend const BigInt operator +(const BigInt& amount1,const BigInt& amount2);
    //Precondition: amount1 and amount2 is the BigInt's object.
    //Postcondition: return amount1 add amount2 's result.
    friend const BigInt operator -(const BigInt& amount1,const BigInt& amount2);
    //Precondition: amount1 and amount2 is the BigInt's object.
    //Postcondition: return amount1 subtract amount2 's result.

private:
    int intValue=0;
    char *charValue;
    int capacity;
    int length;
};

int main()
{
    BigInt a("314159265358979323846264338327950288419716939937510"), c(a);
BigInt *b = new BigInt(1123581321);
c = a + *b;
BigInt d("314159265358979323846264338327950288419718063518831");
BigInt f(30);
f = c - d;

cout << "c - d = " << f << endl;

c = a - *b;
BigInt e("314159265358979323846264338327950288419715816356189");
BigInt g(30);
g = c - e;
cout << "c - e = " << g << endl;

}

void reverseNum(char* str)
{
    int i,j;
    char c[3];
    for(i=0,j=strlen(str)-1; i<j; ++i,--j)
        c[0]=str[i],str[i]=str[j],str[j]=c[0];
}

BigInt::BigInt() {}
BigInt::BigInt(int intValueTmp):intValue(intValueTmp) {}
BigInt::~BigInt()
{
    delete []charValue;
}

BigInt::BigInt(const BigInt& copyObj):capacity(copyObj.capacity)
{
    charValue = new char [capacity+5];
    for(int i=0; i<capacity; i++)
        charValue[i]=copyObj.charValue[i];
}

BigInt::BigInt(string charValueTmp)
{
    int len;
    len=strlen(charValueTmp.c_str());
    capacity=charValueTmp.size();
    length=charValueTmp.length();
    charValue=new char[len+5];
    strcpy(charValue,charValueTmp.c_str());
}

ostream& operator <<(ostream& outputStream,const BigInt& amount)
{
    if(amount.intValue==30)
        outputStream << amount.charValue;
    else if(amount.intValue!=0)
        outputStream << amount.intValue;
    else
        outputStream << amount.charValue;
    return outputStream;
}

BigInt& BigInt::operator=(const BigInt& number)
{
    if(intValue==30)
    {
        capacity=number.capacity;
        length=number.length;
        delete []charValue;
        charValue = new char[capacity+5];
        strcpy(charValue,number.charValue);
        return *this;
    }

    if(this==&number)
        return *this;
    else
    {
        capacity=number.capacity;
        length=number.length;
        delete []charValue;
        charValue = new char[capacity+5];
        strcpy(charValue,number.charValue);
        return *this;
    }
}

const BigInt operator +(const BigInt& amount1,const BigInt& amount2)
{
    char *second,*total,*first;
    int len;
    if(amount1.intValue!=0)
    {
        stringstream ss;
        ss<<amount1.intValue;
        string str;
        ss>>str;
        ss.clear();
        first=new char[str.length()+5];
        sprintf(first,"%d",amount1.intValue);
    }
    else
    {
        len=strlen(amount1.charValue);
        first=new char[len+5];
        strcpy(first,amount1.charValue);
    }
    if(amount2.intValue!=0)
    {
        stringstream ss;
        ss<<amount2.intValue;
        string str;
        ss>>str;
        ss.clear();
        second=new char[str.length()+5];
        sprintf(second,"%d",amount2.intValue);
    }
    else
    {
        len=strlen(amount2.charValue);
        second=new char[len+5];
        strcpy(second,amount2.charValue);
    }
    reverseNum(first);
    reverseNum(second);
    len=max(strlen(first),strlen(second))-1;
    int firstLen=strlen(first)-1;
    int secLen=strlen(second)-1;
    if(len==firstLen)
    {
        total=new char[len+5];
        strcpy(total,first);
    }
    else
    {
        total=new char[len+5];
        strcpy(total,second);
    }
    len=min(strlen(first),strlen(second));
    for (int i=0; i<len; i++)
    {
        total[i]=first[i]+second[i]-'0';
    }
    len=strlen(total);
    total[len]='0';
    total[len+1]='\0';
    for (int i=0; i<len; i++)
    {
        total[i+1]+=(total[i]-'0')/10;
        total[i]=((total[i]-'0')%10)+'0';
    }
    len=strlen(total)-1;
    if(total[len]=='0')
        total[len]='\0';
    reverseNum(total);
    string temp;
    temp=total;
    return BigInt(temp);
}

const BigInt operator -(const BigInt& amount1,const BigInt& amount2)
{
    char *second,*total,*first;
    int len,big=0,small=0;
    if(amount1.intValue!=0)
    {
        stringstream ss;
        ss<<amount1.intValue;
        string str;
        ss>>str;
        ss.clear();
        first=new char[str.length()+5];
        sprintf(first,"%d",amount1.intValue);
    }
    else
    {
        len=strlen(amount1.charValue);
        first=new char[len+5];
        strcpy(first,amount1.charValue);
    }
    if(amount2.intValue!=0)
    {
        stringstream ss;
        ss<<amount2.intValue;
        string str;
        ss>>str;
        ss.clear();
        second=new char[str.length()+5];
        sprintf(second,"%d",amount2.intValue);
    }
    else
    {
        len=strlen(amount2.charValue);
        second=new char[len+5];
        strcpy(second,amount2.charValue);
    }
    len=max(strlen(first),strlen(second))-1;
    int firstLen=strlen(first)-1;
    int secLen=strlen(second)-1;
    if(firstLen<secLen)
        small=1;
    else if(firstLen>secLen)
        big=1;
    else
    {
        if(strcmp(first,second)>=0)
            big=1;
        else
            small=1;
    }
    if(small==1)
    {
        char *Temp;
        Temp = first;
        first = second;
        second = Temp;
        Temp = NULL;
    }
    reverseNum(first);
    reverseNum(second);
    firstLen=strlen(first)-1;
    secLen=strlen(second)-1;
    if(len==firstLen)
    {
        total=new char[len+5];
        strcpy(total,first);
    }
    else
    {
        total=new char[len+5];
        strcpy(total,second);
    }
    len=max(strlen(first),strlen(second));
    for (int i=0; total[i]!='\0'; i++)
    {
        if(total[i]<0)total[i]+='0';
        else total[i]-='0';
    }
    int totalLong=len;
    len=strlen(second);
    for (int i=0; second[i]!='\0'; i++)
    {
        if(second[i]<0)second[i]+='0';
        else second[i]-='0';
    }
    for (int i=0; i<len; i++)
        total[i]=total[i]-second[i];
    total[totalLong]='\0';
    for (int i=0; i<totalLong; i++)
        if(total[i]<0)
        {
            total[i+1]=total[i+1]-1;
            total[i]=total[i]+10;
        }
    for (int i=0; i<totalLong; i++)
        total[i]+='0';

    if(total[totalLong-1]-'0'==0)
    {
        total[totalLong-1]='\0';
        totalLong=totalLong-1;
    }

    if(small==1)
    {
        total[totalLong]='-';
        total[totalLong+1]='\0';
    }

    if(total[0]=='\0')
    {
        total[0]='0';
        total[1]='\0';
    }
    reverseNum(total);
    if(total[0]=='0')
    {
        total[1]='\0';
    }
    string temp;
    temp=total;
    return BigInt(temp);
}
