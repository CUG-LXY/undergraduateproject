#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<string>
#include<fstream>
using namespace std;

#define LL long long

LL cm(LL x,LL n,LL m)//��x��n�η�ģm
{//ģ�ظ�ƽ���㷨
	x = x % m;
	vector<int>a;
	LL num=1;
	//��n�Ķ����Ʊ�ʾ
	while (n!=0)
	{
		a.push_back(n % 2);
		n /= 2;
	}
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i])
			num = (num%m)*(x%m)%m;
		x = (x%m)*(x%m)%m;
		//��ֹ�˵�ʱ�����������ģ����
	}
	return num;
}



bool Prime(LL num)  //�ж�����
{
	for (int i = 2; i <= sqrt(num); i++)
	{
		if (num%i == 0)
		{
			//cout << i << endl; //����õ��ĵ�һ������
			return false;
		}
	}
	return true;
}




LL gcd(LL a, LL b)   //��a,b�������
{
	if (a == 0 && b == 0)exit(0);
	if (a == 0) return b;
	if (b == 0) return a;
	int temp = a;
	while (a%b != 0)
	{
		a = b;
		b = temp % b;
		temp = a;
	}
	return b;
}
int LCM(int a, int b)    //��С������
{
	return a / gcd(a, b)*b;
}


int Caesar(string a)      //�����������
{
	string b = a;
	for (int i = 0; i < a.size(); i++)
	{
		b[i] = (a[i] - 'a' + 26 - 11) % 26 + 'a';  //11Ϊ�����������Կ
	}
	cout << "Our plaintext:" << endl << b << endl;
	
	return 0;
}



LL Euler(LL n)   //ŷ����ʽ
{
	LL num=1; int i = 2;
	do {
		int count = 0;
		while (n%i == 0)
		{
			count++;
			n /= i;
		}
		if (count > 1)
		{
			LL a=pow(i, count) - pow(i, count - 1);
			num *= a;
		}
		if (count == 1)num=num*(i-1);
		i++;
	} while (!Prime(n));
	return num*(n-1);
}

LL Euler1(LL n) //����ʱ����
{
	LL num = n; LL i=2;
	while (!Prime(n))
	{
		if (n%i == 0)
		{
			num = num - num / i;
			n /= i;
		}
		while (n%i == 0)n /= i;
		i++;
	}
	num = num - num / n;
	return num;
}


LL Euler2(LL p, LL q)
{
	return (p - 1)*(q - 1);
}

LL euler(LL a, LL p)   //ŷ���б��ж�ƽ��ʣ��
{
	LL num = cm(a,(p-1)/2,p);  //����ģ�ظ�ƽ���㷨
	if (num == 1)
	{
		//cout << "aΪƽ��ʣ��" << endl;
		return 1;
	}
	else
	{
		//cout << "aΪƽ����ʣ��" << endl;
		return -1;
	}
}


LL Lengendre(LL a, LL p) //�����жϷ���,a������012-1��a,pһ��Ҫ������
{
	if (a == 0)return 0;
	if (a == 1)return 1;
	LL num=0;
	if (a == -1)
	{
		num = (p - 1) / 2;
		if (num % 2 == 0)return 1;
		if (num % 2 == 1)return -1;
	}
	if (a == 2)
	{
		num = (p*p - 1) / 8;
		if (num % 2 == 0)return 1;
		if (num % 2 == 1)return -1;
	}
	num = (a - 1)*(p - 1) / 4;
	num = pow(-1, num);
	LL temp = a;
	a = p;
	p = temp;
	a %= p;
	temp = euler(a, p);
	return num * temp;
}

void ext_gcd(LL a, LL b, LL& x, LL& y)  //��չŷ���������Ԫ
{
	if (!b) { x = 1; y = 0; }  //�ݹ��˳���������b==0,��ʱx*a+b*y=1;��x*aͬ��1��
	else { ext_gcd(b, a%b,y, x); y -= x * (a / b); }  //���ͨ��x����,x*a(mod b)ͬ��1
}

void ext_gcd(int a, int b, int& x, int& y)  //��չŷ���������Ԫ
{
	if (!b) { x = 1; y = 0; }
	else
	{
		ext_gcd(b, a%b, y, x);
		y -= x * (a / b);
	}
}

LL crt(LL c, LL d, LL p, LL q,LL n)//p,q��Ϊ����,�˴������й�ʣ�ඨ����ʹ����Կ����
{
	LL d11, d22,x, y;
	LL d1 = d % (p - 1);
	LL c1 = cm(c, d1, p);//ʹ�÷���С�����ģ�ظ�ƽ�����㷨��ͬʱ�ܹ���ֹ���
	ext_gcd(q, p,x, y);  //����Ԫ
	d11 = x;
	LL d2 = d % (q - 1);
	LL c2 = cm(c, d2, q);
	ext_gcd(p, q, x, y);
	d22 = x;
	LL o=(q*c1)%n*(d11%n)%n + (p*c2)%n*(d22%n)%n;
	if (o < 0)o += n;
	return o % n;
}

void myRSA()
{
	LL p = 187963, q = 163841, n = 30796045883;  //n=p*q
	LL e = 48611, x, y;  //e�ǹ�Կ
	LL cipher[15] = { 5272281348, 21089283929, 3117723025, 26844144908, 22890519533, 26945939925, 27395704341, 2253724391, 1481682985, 2163791130, 13583590307, 5838404872, 12165330281, 501772358, 7536755222 };
	LL message[15];//�洢��õ�����
	cout << "PUBLIC KEY e:" << e;
	cout << "��n=" << n << endl;
	LL faim = Euler2(p, q); //�õ�faim
	cout << endl << "First we use Euler's formula,get the faim:" << faim << endl << endl;
	ext_gcd(e, faim, x, y);
	if (x < 0)x += faim;
	LL d = x;
	cout << "Then we use Extended Euclidean Algorithm,get our PRIVATE KEY:" << d << endl << endl;
	cout << "Decrypting..." << endl;
	for (int i = 0; i < 15; i++)
	{
		message[i] = crt(cipher[i], d, p, q, n);
		cout << "  #" << i + 1 << "	 " << message[i] << endl;
	}
	string a;//������Ķ�Ӧ���ַ���
	for (int i = 0; i < 15; i++)
	{
		char ch[5];  //һ�����Ķ�Ӧ������ַ�����ch[]�ַ�������
		for (int j = 0; j < 5; j++)
		{
			ch[j] = message[i] % 100 % 26 + 97;
			message[i] /= 100;
		}
		for (int j = 4; j >= 0; j--)//���ַ����鷴���㵹�����������ַ���a��
			a.push_back(ch[j]);
	}

	cout << endl << "We get the string as Ceasar Cipher:" << endl << a << endl;
	cout << endl;
	Caesar(a);  //ʹ�ÿ���������н���
	cout << endl << "At last we get:" << endl << "mathematics is the queen of science and number theory is the queen of mathematics----CF Gauss." << endl;

}






int CRT()  //�ҵ������й�ʣ�ඨ��CRT
{
	//����x[]�д洢ͬ����������p[]�д洢ģ��p
	cout << endl << endl << "�����й�ʣ�ඨ�������ѧ���⣺" << endl << "�����ﲻ֪���� ������֮ʣ�� ������֮ʣ�� ������֮ʣ�� ���Ｘ�Σ�" << endl;
	int x1[3] = { 2,3,4 }, p1[3] = {3,5,7};
	int m = 1,num=0;
	int a, b;
	for (int i = 0; i < 3; i++)//��ģ��ѭ�����
	{
		m *= p1[i];
	}
	for (int i = 0; i < 3; i++)
	{
		int m1 = m / p1[i];
		ext_gcd(m1, p1[i], a, b);
		if (a < 0)a += p1[i]; //��֤��Ԫ������
		x1[i] = a * m1*x1[i];
		num += x1[i];
	}
	cout << "ʹ���й�������õĽ��Ϊ��" << num << endl << endl;
	cout << "ĳ����ģ 10 �� 4��ģ 13 �� 6��ģ 7 �� 4��ģ 11 �� 2�������������������С������?" << endl;
	int x2[4] = { 4,6,4,2 }, p2[4] = { 10,13,7,11 };
	m = 1; num = 0;
	for (int i = 0; i < 4; i++)
	{
		m *= p2[i];
	}
	for (int i = 0; i < 4; i++)
	{
		int m1 = m / p2[i];
		ext_gcd(m1, p2[i], a, b);
		if (a < 0)a += p2[i];
		x2[i] = a * m1*x2[i];
		num += x2[i];
	}
	cout << "ʹ���й�������õĽ��Ϊ��" << num << endl;
	int lcm1 = LCM(p2[0], p2[1]);
	int lcm2 = LCM(lcm1, p2[2]);
	int lcm3 = LCM(lcm2, p2[3]);
	num %= lcm3;
	cout << "�����ģ��10��13��7��11����С������֮��õ�������������С��������" << num << endl;
	return 0;
}


void inverse(LL a, LL b)
{
	LL inverse_a, x, y;
	if (gcd(a, b) != 1) cout << "û����Ԫ���������Ϊ" << gcd(a, b) << endl;
	else {
		ext_gcd(a, b, x, y);
		if (x < 0)x += b;
		inverse_a = x;
		cout << "a����ԪΪ��" << inverse_a << endl << endl;
	}
}

void Inverse()
{
	LL a, b;
	a = 19789, b = 23548;
	cout <<  "��1�����a=19789,b=23548ʱaģb����Ԫ��" << endl;
	inverse(a, b);
	a = 31875, b = 8387;
	cout << endl << "��2�����a=31875,b=8387ʱaģb����Ԫ��"<< endl;
	inverse(a, b);
}





vector<int> mul_division(vector<int>&a, vector<int>&b)//����ʽ����������
{
	while (a.size()>=b.size())
	{
		if (a[0] == 1)
		{
			for (int i = 0; i < b.size(); i++)
				a[i] = a[i]^b[i];
		}
		else 
		{
			for (int i = 0; i < b.size(); i++)
				a[i] = a[i] ^ 0;

		}
		a.erase(a.begin());
	}
	vector<int>tmp(a.size(), 0);
	if (tmp != a)                  //�ж��Ƿ�Ϊȫ0
		while (a[0] == 0)
		{
			a.erase(a.begin());
		}
	return a;
}

vector<int> mul_division1(vector<int>&a, vector<int>&b)//����ʽ��������
{
	vector<int>c(a.size() - b.size()+1, 0);
	int count = 0;
	while (a.size() >= b.size())
	{
		if (a[0] == 1)
		{
			for (int i = 0; i < b.size(); i++)
				a[i] = a[i] ^ b[i];
			c[count] = 1;
		}
		else
		{
			for (int i = 0; i < b.size(); i++)
				a[i] = a[i] ^ 0;

		}
		a.erase(a.begin());
		count++;
	}
	vector<int>tmp(a.size(), 0);
	if (tmp != a)                  //�ж��Ƿ�Ϊȫ0
		while (a[0] == 0)
		{
			a.erase(a.begin());
		}
	return c;
}

vector<int> mul(vector<int>a, vector<int>b)//����ʽ�˷�
{

	vector<int>c(a);
	c.push_back(0);
	for (int i = 1; i < b.size(); i++)
	{
		if (b[i])
		{
			int k = c.size()-1;
			for (int j = a.size() - 1; j >= 0; j--)
			{
				c[k] = c[k] + a[j];
				if (c[k] >= 2) c[k]%=2;
				k--;
			}
			for (k; k > 0; k--)
			{
				if (c[k] >= 2) c[k] %= 2;
			}
			if (c[0] >= 2) c[0] %= 2;
			if(i!=b.size()-1)c.push_back(0);
		}
		else {
			if(i!=b.size()-1)c.push_back(0);
		}
	}
	return c;
}
void swap(vector<int>&a, vector<int>&b)//����
{
	vector<int>temp(a);
	a.swap(b);
	b.swap(temp);
}


void print(vector<int>a)//�����������ʽ
{
	if (a.size() == 2)cout << "x";
	else if (a.size() == 1)
		cout << "1";
	else {
		cout << "x^" << a.size() - 1;
	}
	for (int i = 1; i < a.size(); i++)
	{
		if (a[i])
		{
			if (a.size() - 1 - i == 0)
				cout << " +1";
			else if (a.size() - 1 - i == 1)
				cout << " +x";
			else
				cout << " +x^" << a.size() - 1 - i;
		}
	}
}


void ext_gcd1(vector<int>a, vector<int>b)  //����Ԫ
{
	vector<int>q;
	vector<int>ans = { 1 };
	int count = 0;
	while (b.size()!=1)
	{
		q = mul_division1(a, b);
		ans = mul(ans, q);
		swap(a, b);
		if (count == 1)ans[ans.size() - 1] ^= 1;
		if (count == 2)ans[ans.size() - 2] ^= 1;
		count++;
	}
	print(ans);
}




void my_mul_division()
{
	vector<int>a = { 1,0,0,0,1,1,0,1,1 };
	vector<int>b = {1,0,0,0,0,0,1,1};
	print(a); cout << "   "; print(b);
	cout << "����GF(2)�ϵ������ʽΪ��";
	while (1)
	{
		mul_division(a, b);
		swap(a, b);
		vector<int>tmp(b.size(), 0);
		if (tmp == b)break;
	}
	//cout << "ok" << endl;
	print(a);
	cout << endl << endl;
	vector<int>c = { 1,1,1,1,1,1,1 };
	vector<int>d = { 1,0,1,1,1 };
	print(c); cout << "   "; print(d);
	cout << "����GF(2)�ϵ������ʽΪ��";
	while (1)
	{
		mul_division(c, d);
		swap(c, d);
		vector<int>tmp(d.size(), 0);
		if (tmp == d)break;
	}
	print(c);
	cout << endl << endl;
	vector<int>e = { 1,0,0,0,1,1,0,1,1 };
	vector<int>f = { 1,0,0,0,0,0,1,1 };
	print(e); cout << " ģ "; print(f);
	cout << "�ĳ˷���Ԫ�ǣ�";
	ext_gcd1(e, f);
	cout << endl << endl;
	//print(x);
}


   
LL Quick_mul(LL a, LL b, LL p)  //���ٻ�ȡģ
{
	LL ans = 0, res = a;
	while (b)
	{
		if (b & 1)
			ans = (ans + res) % p;
		res = (res + res) % p;
		b >>= 1;
	}
	return ans;
}
LL Quick_pow(LL a, LL b, LL c)     //������ȡģ
{
	int ans = 1, res = a;
	while (b)
	{
		if (b & 1)
			ans = Quick_mul(ans, res, c);
		res = Quick_mul(res, res, c);
		b >>= 1;
	}
	return ans;
}



bool RabinMiller(LL x)
{
	//ȡ200���ڵ��������в���
	int prime[46] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199};
	LL i, j, k;
	LL s = 0, t = x - 1;//����С�������漰��x-1,����t=x-1
	if (x == 2)  return true;    
	if (x < 2 || !(x & 1))  return false;     //���x��ż��������0,1���ǲ������� 
	while (!(t & 1))  //��(x-1)�ֽ��(2^s)*t������ 
	{
		s++;
		t >>= 1;
	}
	for (i = 0; i < 46 && prime[i] < x; i++)      //�������е�������������һ���в��� 
	{
		int a = prime[i];
		int b = Quick_pow(a, t, x);      
		for (j = 0; j < s; j++)    
		{
			k = Quick_mul(b, b, x); 
			if (k == 1 && b != 1 && b != x - 1)     //�ö���̽���ж� 
			{
				return false;
			}
			b = k;
		}
		if (k != 1)   return false;   //�÷���С�����ж� 
	}
	return true;   
}



void RabinMillerTest()
{
	LL x[4] = {211,561,1105,294409};
	for (int i = 0; i < 4; i++)
	{
		if (RabinMiller(x[i]))
			cout << x[i] << "��������" << endl;
		else
			cout << x[i] << "����������" << endl;
	}
}

int main()
{
	cout << endl;
	cout << "****************** ʵ���� ******************" << endl;
	Inverse();
	cout << endl << endl << endl;
	cout << "************************* ʵ���� *************************"<< endl;
	CRT();
	cout << endl << endl << endl;
	cout << "************************* ʵ���� *************************" << endl;
	myRSA();
	cout << endl << endl << endl;
	cout << "************************ ʵ���� ************************" << endl;
	my_mul_division();
	cout << endl << endl << endl;
	cout << "****************** ʵ��� ******************"<< endl;
	RabinMillerTest();
	cout << endl << endl << endl;
	cout << "****************** ʵ��� ******************" << endl;
	cout << "ʹ��ŷ����ʽ��Lengendre�����ж�ƽ��ʣ�ࣺ" << endl;
	LL num=Lengendre(211,641);
	if (num == 1)cout << "211��641��ƽ��ʣ��" << endl;
	else cout << "211��641��ƽ����ʣ��" << endl;
	num = Lengendre(641, 1291);
	if (num == 1)cout << "641��1291��ƽ��ʣ��" << endl;
	else cout << "641��1291��ƽ����ʣ��" << endl;
	getchar();
	getchar();
	return 0;
}