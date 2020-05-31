#include<iostream>
#include<string>
#include <math.h>
#include<sstream>
#include <algorithm>
#include<vector>
#include<fstream>
using namespace std;
void Trim0(string& a)
{
    int i=0;
    for(;a[i]=='0';i++);
    a=a.substr(i,a.length()-i);
}
class Sint
{
    public:
    string number;
    bool isNegative;
    public:
    Sint(){isNegative=false;};
    Sint(string a)
    {
        if(a[0]=='-')
        {
            isNegative=true;
            number=a.substr(1,a.length()-1);
        }
        else
        {
            number=a;
        }

    }
    friend ostream& operator<<(ostream& out, Sint a)
    {
        if(!a.isNegative)
            out<<a.number;
        else out<<'-'<<a.number;
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
        if(a.number=="0" && b.number=="0") return true;
        return (a.number==b.number) && (a.isNegative==b.isNegative);
    }
    friend bool operator != (Sint a,Sint b)
    {
        if(a.number=="0" && b.number=="0") return false;
        return (a.number!=b.number) || (a.isNegative==b.isNegative);
    }

};
class Qint
{
    private:
    int  arrBits[4];
    public:
    Qint()
    {
        for(int i=0;i<4;i++)
            arrBits[i]=0;
    }
    void Setbit(int pos,int value)
    {
        int temp=pos/32;
        if(value)
        {
            arrBits[temp]=(1 << (31-pos-(temp*32))) | arrBits[temp];
        }
        else
        {
            arrBits[temp]=~(1<<(31-pos-(32*temp))) & arrBits[temp];
        }
    }
    bool BitValue(int pos)
    {
        int temp = pos/32;
        return (arrBits[temp]>>(31-pos-(32*temp))) &1;
    }
    void ReverseBit(int pos)
    {
        int temp=pos/32;
        arrBits[temp]=(1<<(31-pos-(32*temp)))^arrBits[temp];
    }
	void Input(string input, int base)
	{
		if (base == 2)
			this->Input2(input);
		if (base == 10)
			this->Input10(input);
		if (base == 16)
			this->Input16(input);
	}
	string Output(int base)
	{
		if (base == 2)
			return this->Output2();
		if (base == 10)
			return this->OutPut10();
		if (base == 16)
			return this->Output16();
	}
    void Input2(string input)
    {
        for(int i=0;i<input.length();i++)
            this->Setbit(128-input.length()+i,input[i]-'0');
    }
    string Output2()
    {
        stringstream result;
        int i=0;
        while(!this->BitValue(i)) i++;
        for(;i<128;i++)
            result<<this->BitValue(i);
        return result.str();
    }
    void Input10(string input)
    {
        Sint Dec(input);
        Sint zero("0");
        Sint one("1");
        int i=0;
        if(!Dec.isNegative)
        {
            while(Dec!=zero)
            {
                this->Setbit(127-i,(Dec.number[Dec.number.length()-1]-'0') % 2);
                Dec.Div2();
                i++;
            }
        }
        else
        {
            Dec=Dec-one;
            while(Dec!=zero)
            {
                this->Setbit(127-i,(Dec.number[Dec.number.length()-1]-'0') % 2);
                Dec.Div2();
                i++;
            }
            for(int i=0;i<128;i++)
                this->ReverseBit(i);
        }
    }
    string OutPut10()
    {
        Sint dec("0");
        Sint base2("1");
        for(int i=127;i>0;i--)
        {
            if(this->BitValue(i))
                dec = dec+base2;
            base2=base2+base2;
        }
        if(!this->BitValue(0))
        {
            return dec.number;
        }
        else
        {
            string result;
            dec=base2-dec;
            result +='-';
            int i=0;
            for(;dec.number[i]=='0';i++);
            result += dec.number.substr(i,dec.number.length()-i);
            return result;
        }
    }
    void Input16(string input)
    {
        int i=124;
        for(int j=input.length()-1;j>=0;j--)
        {
            switch (input[j])
            {
            case '0':
                this->Setbit(i,0);
                this->Setbit(i+1,0);
                this->Setbit(i+2,0);
                this->Setbit(i+3,0);
                break;
            case '1':
                this->Setbit(i,0);
                this->Setbit(i+1,0);
                this->Setbit(i+2,0);
                this->Setbit(i+3,1);
                break;
            case '2':
                this->Setbit(i,0);
                this->Setbit(i+1,0);
                this->Setbit(i+2,1);
                this->Setbit(i+3,0);
                break;
            case '3':
                this->Setbit(i,0);
                this->Setbit(i+1,0);
                this->Setbit(i+2,1);
                this->Setbit(i+3,1);
                break;
            case '4':
                this->Setbit(i,0);
                this->Setbit(i+1,1);
                this->Setbit(i+2,0);
                this->Setbit(i+3,0);
                break;
            case '5':
                this->Setbit(i,0);
                this->Setbit(i+1,1);
                this->Setbit(i+2,0);
                this->Setbit(i+3,1);
                break;
            case '6':
                this->Setbit(i,0);
                this->Setbit(i+1,1);
                this->Setbit(i+2,1);
                this->Setbit(i+3,0);
                break;
            case '7':
                this->Setbit(i,0);
                this->Setbit(i+1,1);
                this->Setbit(i+2,1);
                this->Setbit(i+3,1);
                break;
            case '8':
                this->Setbit(i,1);
                this->Setbit(i+1,0);
                this->Setbit(i+2,0);
                this->Setbit(i+3,0);
                break;
            case '9':
                this->Setbit(i,1);
                this->Setbit(i+1,0);
                this->Setbit(i+2,0);
                this->Setbit(i+3,1);
                break;
            case 'A':
                this->Setbit(i,1);
                this->Setbit(i+1,0);
                this->Setbit(i+2,1);
                this->Setbit(i+3,0);
                break;
            case 'B':
                this->Setbit(i,1);
                this->Setbit(i+1,0);
                this->Setbit(i+2,1);
                this->Setbit(i+3,1);
                break;
            case 'C':
                this->Setbit(i,1);
                this->Setbit(i+1,1);
                this->Setbit(i+2,0);
                this->Setbit(i+3,0);
                break;
            case 'D':
                this->Setbit(i,1);
                this->Setbit(i+1,1);
                this->Setbit(i+2,0);
                this->Setbit(i+3,1);
                break;
            case 'E':
                this->Setbit(i,1);
                this->Setbit(i+1,1);
                this->Setbit(i+2,1);
                this->Setbit(i+3,0);
                break;
            case 'F':
                this->Setbit(i,1);
                this->Setbit(i+1,1);
                this->Setbit(i+2,1);
                this->Setbit(i+3,1);
                break;
            }
            i-=4;
        }
    }
    string Output16()
    {
        stringstream hex;
        for(int i=127;i>=0;i=i-4)
        {
            int sum=0;
            for(int j=i;j>i-4;j--)
            {
                if(this->BitValue(j))
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
        Trim0(result);
        return result;
    }
    friend Qint operator <<(Qint a,int bit)
    {
        for(int i=0;i<128-bit;i++)
            a.Setbit(i,a.BitValue(i+bit));
        for(int i=128-bit;i<128;i++)
            a.Setbit(i,0);
            return a;
    }
    friend Qint operator >>(Qint a,int bit)
    {
        Qint result;
        for(int i=bit;i<128;i++)
            result.Setbit(i,a.BitValue(i-bit));
        for(int i=0;i<bit;i++)
            result.Setbit(i,a.BitValue(0));
        return result;
    }
    friend Qint operator ^ (Qint a,Qint b)
    {
        Qint result;
        for(int i=0;i<128;i++)
        {
            if(a.BitValue(i)!=b.BitValue(i))
                result.Setbit(i,1);
            else
                result.Setbit(i,0);

        }
        return result;
    }
	friend Qint operator & (Qint a, Qint b)
	{
		Qint result;
		for (int i = 0; i < 128; i++)
		{
			if (a.BitValue(i) && b.BitValue(i))
				result.Setbit(i, 1);
			else
				result.Setbit(i, 0);

		}
		return result;
	}
	friend Qint operator | (Qint a, Qint b)
	{
		Qint result;
		for (int i = 0; i < 128; i++)
		{
			if (!a.BitValue(i) && !b.BitValue(i))
				result.Setbit(i, 0);
			else
				result.Setbit(i, 1);

		}
		return result;
	}
    friend Qint operator ~(Qint a)
    {
        for(int i=0;i<128;i++)
            a.ReverseBit(i);
        return a;
    }
    friend Qint operator + (Qint a,Qint b)
    {
        int nho=0;
        Qint sum;
        for(int i=127;i>=0;i--)
        {
            if(a.BitValue(i)+b.BitValue(i)+nho>=2)
            {
                sum.Setbit(i,a.BitValue(i)+b.BitValue(i)+nho-2);
                nho=1;
            }
            else
            {
                sum.Setbit(i,a.BitValue(i)+b.BitValue(i)+nho);
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
        Qint one;
        one.Input2("1");
        bool isPositive;
        if(a.BitValue(0)==b.BitValue(0)) isPositive=1;else isPositive=0;
        if(a.BitValue(0))
            a = ~a +one;
        if(b.BitValue(0))
            b= ~b +one;
        for(;b.BitValue(pivot);pivot++);
        for(int i=127;i>=pivot;i--)
        {
            if(b.BitValue(i))
                {
                    int temp=127-i;
                    result=result + (a<<temp);
                }
        }
        if(isPositive)
        return result;
        else
        return ~result +one;
    }
    friend Qint operator / (Qint a,Qint b)
    {
        Qint one;
        Qint result;
        int pivota=0;
        int pivotb=0;
        one.Input2("1");
        bool isPositive;
        if(a.BitValue(0)==b.BitValue(0)) isPositive=1;else isPositive=0;
        if(a.BitValue(0))
            a = ~a +one;
        if(b.BitValue(0))
            b= ~b +one;
        for(;!a.BitValue(pivota);pivota++);
        for(;!b.BitValue(pivotb);pivotb++);
        if(pivota>pivotb) return result;
        int distance=pivotb-pivota;
        for(int i=distance;i>=0;i--)
        {
            Qint sub=a-(b<<i);
            if(!sub.BitValue(0))
            {
                result =result + (one<<i);
                a =sub;
            }

        }
        if(isPositive) return result;else return ~result +one;
    }
    friend Qint rol(Qint a)
    {
        Qint result;
        for(int i=0;i<127;i++)
            result.Setbit(i,a.BitValue(i+1));
        result.Setbit(127,a.BitValue(0));
        return result;
    }
    friend Qint ror(Qint a)
    {
        Qint result;
        for(int i=1;i<128;i++)
            result.Setbit(i,a.BitValue(i-1));
        result.Setbit(0,a.BitValue(127));
        return result;
    }

};
vector<string> tokenizer(string line)
{
    vector <string> tokens;
    stringstream check1(line);
    string temp;
    while(getline(check1, temp,' '))
    {
        tokens.push_back(temp);
    }
    return tokens;
}
string EveryLine(string line)
{
	vector<string> tonken = tokenizer(line);
	int base = stoi(tonken[0]);

	int n = tonken.size();
	if (n == 4)
	{
		Qint temp1;
		temp1.Input(tonken[1], base);

		if (tonken[2] == ">>")
		{
			int bit = stoi(tonken[3]);
			temp1=temp1 >> bit;
			return temp1.Output(base);
		}
		if (tonken[2] == "<<")
		{
			int bit = stoi(tonken[3]);
			temp1=temp1 << bit;
			return temp1.Output(base);
		}
		Qint temp2;
		temp2.Input(tonken[3], base);
		if (tonken[2] == "|")
		{
			Qint result = temp1 | temp2;
			return result.Output(base);
		}
		if (tonken[2] == "&")
		{
			Qint result = temp1 & temp2;
			return result.Output(base);
		}
		if (tonken[2] == "^")
		{

			Qint result = temp1 ^ temp2;
			return result.Output(base);
		}
		if (tonken[2] == "+")
		{

			Qint result = temp1 + temp2;
			return result.Output(base);
		}
		if (tonken[2] == "-")
		{

			Qint result = temp1 - temp2;
			return result.Output(base);
		}
		if (tonken[2] == "*")
		{

			Qint result = temp1 * temp2;
			return result.Output(base);
		}
		if (tonken[2] == "/")
		{

			Qint result= temp1/temp2;
            return result.Output(base);
		}

	}
	if (n == 3)
	{
		Qint temp1;
		temp1.Input(tonken[2], base);
		if (tonken[1] == "~")
		{
			temp1=~temp1;
			return temp1.Output(base);
		}
		if (tonken[1] == "rol")
		{
			temp1=rol(temp1);
			return temp1.Output(base);
		}
		if (tonken[1] == "ror")
		{
			temp1=ror(temp1);
			return temp1.Output(base);
		}
		if (stoi(tonken[1]) == base)
			return temp1.Output(base);
		else
		{
			int base1 = stoi(tonken[1]);
			return temp1.Output(base1);
		}

	}
}
void process(string inputF, string outputF)
{
	fstream input;
	input.open(inputF, ios::in);
	if (!input)
	{
		cout << "File " << inputF << " is not exist!" << endl;
		return;
	}

	fstream output;
	output.open(outputF, ios::out);
	string line;
	while (!input.eof())
	{
		getline(input, line);
		output << EveryLine(line) << endl;
	}

	input.close();
	output.close();
}



int main(int agrc,char* argv[])
{
	string inputF =argv[1];
	string outputF = argv[2];
	cout << "Is running......" << endl;
	process(inputF, outputF);

	return 0;
}
