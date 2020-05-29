#include<iostream>
#include<string>
#include <math.h>
#include<sstream>
#include <algorithm>
using namespace std;
class Sint
{
    public:
    string number;
    public:
    Sint(){};
    Sint(string a)
    {
        number=a;
    }
    friend ostream& operator<<(ostream& out, Sint a)
    {
        out<<a.number;
        return out;
    }
    friend Sint operator +(Sint a,Sint b)
    {
        Sint result;
        stringstream sum;
        int m=a.number.length();
        int n=b.number.length();
        int nho=0;
        reverse(a.number.begin(),a.number.end());
        reverse(b.number.begin(),b.number.end());
        if (m>n)
    {
        for(int i=0;i<m-n;i++)
            b.number+='0';
    }
    else
    {
        for(int i=0;i<n-m;i++)
            a.number+='0';
    }
    for(int i=0;i<a.number.length();i++)
    {
        if(a.number[i]-'0'+b.number[i]-'0'+nho >=10 )
        {
            sum<<a.number[i]-'0'+b.number[i]-'0'+nho-10;
            nho=1;
        }
        else
        {
            sum<<a.number[i]-'0'+b.number[i]-'0'+nho;
            nho=0;
        }
    }
    if(nho==1)
        sum<<"1";
    result.number=sum.str();
    reverse(result.number.begin(),result.number.end());
    return result;

    }
    friend Sint operator - (Sint a,Sint b)
    {
    stringstream sub;
    int m = a.number.length(),n=b.number.length();
    int nho =0;
    reverse(a.number.begin(),a.number.end());
    reverse(b.number.begin(),b.number.end());
    if (m>n)
    {
        for(int i=0;i<m-n;i++)
            b.number+='0';
    }
    else
    {
        for(int i=0;i<n-m;i++)
            a.number+='0';
    }
    for(int i=0;i<a.number.length();i++)
    {
        if(a.number[i]-b.number[i]-nho <0 )
        {
            sub<<a.number[i]-b.number[i]-nho+10;
            nho=1;
        }
        else
        {
            sub<<a.number[i]-b.number[i]-nho;
            nho=0;
        }
    }
    Sint result=sub.str();
    reverse(result.number.begin(),result.number.end());
    return result;
    }
    void Div2()
    {
        if(number=="1")
            {number="0";return;}
        stringstream result;
        int i=0;
        int du=0;
        if(number[0]=='1')
            {du=1;i++;}
        while (i<number.length())
        {
            int kq=(number[i]-'0'+du*10)/2;
            result<<kq;
            du=(number[i]-'0'+du*10)%2;

            i++;

        }
        number= result.str();
    }
    friend bool operator ==(Sint a,Sint b)
    {
        return a.number==b.number;
    }
    friend bool operator != (Sint a,Sint b)
    {
        return a.number!=b.number;
    }

};


class Qint
{
    private:
    char arrBits[128];
    public:
    Qint()
    {
        for(int i=0;i<128;i++)
            arrBits[i]=0;
    }
    // Binary
    void Input2(string input)
    {
        for(int i=0;i<input.length();i++)
            if(input[i]=='0')
                arrBits[128-input.length()+i]=0;
            else
                arrBits[128-input.length()+i]=1;
    }
    string Output2()
    {
        stringstream result;
        int i=0;
        while (!arrBits[i])
        {
            i++;
        }
        for(;i<128;i++)
            result<<(int)arrBits[i];
        return result.str();


    }
    Sint BinToDec()
    {
        Sint Dec;
        Sint base2("1");
        for(int i=127;i>=1;i--)
        {
            if(arrBits[i])
                Dec =Dec +base2;
            base2=base2+base2;
        }
        if(arrBits[0])
        {
            Sint temp=base2-Dec;
            string result;
            result +='-';
            int i=0;
            while(temp.number[i]=='0') i++;
            result += temp.number.substr(i,temp.number.length()-i);
            return result;
        }
        else
            return Dec;
    }
    string BintoHex()
    {
        stringstream hex;
        for(int i=127;i>=0;i=i-4)
        {
            int sum=0;
            for(int j=i;j>i-4;j--)
            {
                if(arrBits[j])
                    sum +=pow(2,i-j);
            }
            if(sum<10)
                    hex<<sum;
                else
                {
                    switch (sum)
                    {
                    case 10:
                        hex<<"A";
                        break;
                    case 11:
                        hex<<"B";
                        break;
                    case 12:
                        hex<<"C";
                        break;
                    case 13:
                        hex<<"D";
                        break;
                    case 14:
                        hex<<"E";
                        break;
                    case 15:
                        hex<<"F";
                        break;
                    default:
                        break;
                    }
                }
        }
        string result= hex.str();
        reverse(result.begin(),result.end());
        return result;
    }
    void Input16(string input)
    {
        int i=124;
        for(int j=input.length()-1;j>=0;j--)
        {
            switch (input[j])
            {
            case '0':
                arrBits[i]=0;
                arrBits[i+1]=0;
                arrBits[i+2]=0;
                arrBits[i+3]=0;
                break;
            case '1':
                arrBits[i]=0;
                arrBits[i+1]=0;
                arrBits[i+2]=0;
                arrBits[i+3]=1;
                break;
            case '2':
                arrBits[i]=0;
                arrBits[i+1]=0;
                arrBits[i+2]=1;
                arrBits[i+3]=0;
                break;
            case '3':
                arrBits[i]=0;
                arrBits[i+1]=0;
                arrBits[i+2]=1;
                arrBits[i+3]=1;
                break;
            case '4':
                arrBits[i]=0;
                arrBits[i+1]=1;
                arrBits[i+2]=0;
                arrBits[i+3]=0;
                break;
            case '5':
                arrBits[i]=0;
                arrBits[i+1]=1;
                arrBits[i+2]=0;
                arrBits[i+3]=1;
                break;
            case '6':
                arrBits[i]=0;
                arrBits[i+1]=1;
                arrBits[i+2]=1;
                arrBits[i+3]=0;
                break;
            case '7':
                arrBits[i]=0;
                arrBits[i+1]=1;
                arrBits[i+2]=1;
                arrBits[i+3]=1;
                break;
            case '8':
                arrBits[i]=1;
                arrBits[i+1]=0;
                arrBits[i+2]=0;
                arrBits[i+3]=0;
                break;
            case '9':
                arrBits[i]=1;
                arrBits[i+1]=0;
                arrBits[i+2]=0;
                arrBits[i+3]=1;
                break;
            case 'A':
                arrBits[i]=1;
                arrBits[i+1]=0;
                arrBits[i+2]=1;
                arrBits[i+3]=0;
                break;
            case 'B':
                arrBits[i]=1;
                arrBits[i+1]=0;
                arrBits[i+2]=1;
                arrBits[i+3]=1;
                break;
            case 'C':
                arrBits[i]=1;
                arrBits[i+1]=1;
                arrBits[i+2]=0;
                arrBits[i+3]=0;
                break;
            case 'D':
                arrBits[i]=1;
                arrBits[i+1]=1;
                arrBits[i+2]=0;
                arrBits[i+3]=1;
                break;
            case 'E':
                arrBits[i]=1;
                arrBits[i+1]=1;
                arrBits[i+2]=1;
                arrBits[i+3]=0;
                break;
            case 'F':
                arrBits[i]=1;
                arrBits[i+1]=1;
                arrBits[i+2]=1;
                arrBits[i+3]=1;
                break;
            }
            i-=4;
        }
    }
    string Output16()
    {
        string out=this->BintoHex();
        int i=0;
        while (out[i]=='0') i++;
        return out.substr(i,out.length()-i);
    }
    void Input10(string input)
    {
        Sint Dec(input);
        Sint zero("0");
        Sint base2("1");
        int i=127;
        while (Dec!=zero)
        {
            if((Dec.number[Dec.number.length()-1]-'0')%2)
            {
                arrBits[i]=1;
            }
            else arrBits[i]=0;
            Dec.Div2();
            i--;
        }


    }
    string Output10()
    {
        Sint result=this->BinToDec();
        return result.number;

    }
    friend Qint operator <<(Qint a,int bit)
    {
        for(int i=0;i<128-bit;i++)
            a.arrBits[i]=a.arrBits[i+bit];
        for(int i=128-bit;i<128;i++)
            a.arrBits[i]=0;
            return a;
    }
    friend Qint operator >>(Qint a,int bit)
    {
        for(int i=127;i>bit;i--)
            a.arrBits[i]=a.arrBits[i-bit];
        for(int i=0;i<bit;i++)
            a.arrBits[i]=a.arrBits[bit];
        return a;
    }
    friend Qint operator & (Qint a,Qint b)
    {
        Qint result;
        for(int i=0;i<128;i++)
        {
            if(a.arrBits[i]==1 && b.arrBits[i]==1)
                result.arrBits[i]=1;
            else
                result.arrBits[i]=0;

        }
        return result;
    }
    friend Qint operator | (Qint a,Qint b)
    {
        Qint result;
        for(int i=0;i<128;i++)
        {
            if(a.arrBits[i]==0 && b.arrBits[i]==0)
                result.arrBits[i]=0;
            else
                result.arrBits[i]=1;

        }
        return result;
    }
    friend Qint operator ^ (Qint a,Qint b)
    {
        Qint result;
        for(int i=0;i<128;i++)
        {
            if(a.arrBits[i]!=b.arrBits[i])
                result.arrBits[i]=1;
            else
                result.arrBits[i]=0;

        }
        return result;
    }
    friend Qint operator ~(Qint a)
    {
        Qint result;
        for(int i=0;i<128;i++)
            result.arrBits[i]=1-a.arrBits[i];
        return result;
    }


    friend Qint operator+ (Qint a,Qint b)
    {
        int nho=0;
        Qint sum;
        for(int i=127;i>=0;i--)
        {
            if(a.arrBits[i]+b.arrBits[i]+nho>=2)
            {
                sum.arrBits[i]=a.arrBits[i]+b.arrBits[i]+nho-2;
                nho=1;
            }
            else
            {
                sum.arrBits[i]=a.arrBits[i]+b.arrBits[i]+nho;
                nho=0;
            }

        }
        return sum;
    }

    friend Qint operator -(Qint a,Qint b)
    {
        Qint temp;
        temp.Input10("1");
        return a+~b+temp;
    }


    friend Qint operator*(Qint a,Qint b)
    {
        Qint result;
        int pivot=0;
        for(;b.arrBits[pivot]==0;pivot++);
        cout<<pivot<<endl;
        for(int i=127;i>=pivot;i--)
        {
            if(b.arrBits[i])
                {
                    int temp=127-i;
                    result=result + (a<<temp);
                }
        }
        return result;
    }
    friend Qint operator/(Qint a,Qint b)
    {
    }
    friend Qint rol(Qint a)
    {
        Qint result;
        for(int i=0;i<127;i++)
            result.arrBits[i]=a.arrBits[i+1];
        result.arrBits[127]=a.arrBits[0];
        return result;
    }
    friend Qint ror(Qint a)
    {
        Qint result;
        for(int i=1;i<128;i++)
            result.arrBits[i]=a.arrBits[i-1];
        result.arrBits[0]=a.arrBits[127];
        return result;
    }
};
int main()
{
    string s="111111111111";
    Qint a,a2;
    a.Input2(s);
    a2.Input10("9999999999");
    cout<<a.Output2()<<endl<<a.Output10()<<endl<<a.Output16()<<endl;
    cout<<a2.Output2()<<endl<<a2.Output10()<<endl<<a2.Output16()<<endl;
    Qint c=rol(a);
    cout<<c.Output2()<<endl<<c.Output10()<<endl<<c.Output16()<<endl;







    return 0;
}