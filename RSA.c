#include <stdio.h>
#include <stdlib.h>
#include <time.h>


clock_t start,end;
double cpu_time_used;
// Generate random numbers in range of lower and upper

int randoms(int upper, int lower)

{
    int num = ( rand()%
                (upper - lower +1)) + lower;
    return num;

}

//Find whether given number is prime or not

int prime(int n)
{
    int i, flag = 0;
    for (i=2;i<n/2; ++i)
    {
        //condition for non-prime
        if (n % i == 0)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

// get random and prime
int prime_ran(int upper,int lower)
{
    int p;
    int flag = 1;
    while(flag)
    {
        p = randoms(upper, lower);
        flag = prime(p);
    }
    return p;
}

long int Euc_gcd(long int a, long int b)
{
    if (a == 0)
        return b;
    return Euc_gcd(b % a, a);
}


//Finding Inverse
long int modInverse(long int e, long int phi)
{
    unsigned long long int i,Temp;
    //printf("%d",phi);
    for(i = 0; i<phi; i++)
    {
        long long mul = e*i;
        Temp = mul%phi;
        //printf("e : %d \t i: %d \t phi = %d \t Temp : %d \n", e, i, phi, Temp);
        if(Temp == 1)
        {
            //printf("%d",i);
            return i;
        }
    }
}

//Modular Exponentiation
int power(long long x, unsigned int y, int p)
{
    int res = 1;     // Initialize result

    x = x % p; // Update x if it is more than or
                // equal to p

    if (x == 0) return 0; // In case x is divisible by p;

    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;

        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}



int chineseremaindertheorem (unsigned long long int dq, unsigned long long int dp, unsigned long long int p, unsigned long long int q, unsigned long long int c)

{
    unsigned long long int m1 = power(c, dp, p);
      
    //Message part 2
    unsigned long long int m2 = power(c, dq, q);

    unsigned long long int qinv = modInverse(q, p);
    unsigned long long int h = (qinv * (m1 - m2)) % p;
    unsigned long long int m = m2 + h * q;
    return m;



}



//Driver code

int main()

{


    int p,q;


    unsigned long long int upper = 10000;
    int lower = (upper-1000);

    srand (time(0));

    p = prime_ran(upper,lower);
    q = prime_ran(upper,lower);

//Randomly selecting p and q;



//Calculating N from p and q, N = p*q

    unsigned long long int N = p*q;
    printf("N : %d \n", N);

//Calculating phi_N from p-1 and q-1, phi_N = p*q
    unsigned long long int phi_N = (p-1)*(q-1);
    printf("phi_N : %d \n", phi_N);

//Selecting e randomly such that 1 < e < phi_n
    int flag = 1;
    unsigned long long int e;
    while(flag)
    {
        e = prime_ran(phi_N,1);
        if (Euc_gcd(e,phi_N) == 1)
            flag = 0;

    }
    printf("e : %d \n", e);

    unsigned long long int d = modInverse(e,phi_N);
    printf("d : %d \n",d);

    //unsigned long long int message = 12345;

    unsigned long long int message;
    printf("Enter the message :");
    scanf("%ld",&message);

            // Chinese Remainder Theorem set :
            // unsigned long long int m1_inv = modInverse(q, p);
            // unsigned long long int m2_inv = modInverse(p, q);

            // unsigned long long int c1 = q * (modInverse(q, p)%p);
            // unsigned long long int c2 = p * (modInverse(p, q)%q);

            // unsigned long long int dp = d % (p-1);
            // unsigned long long int dq = d % (q-1);
            // unsigned long long int q_inv = q % (q-1);

            // unsigned long long int fin_qinv = q_inv % p;

            // unsigned long long int xq = p * (p_inv % q);


            
            unsigned long long int dq = power(d, 1, (q-1));
            unsigned long long int dp = power(d, 1, (p-1));
            
            unsigned long long int qinv = modInverse(q, p);


    // Encrypt using the Modular Arithmetic:
    int c = power(message, e, N );
    printf("Cipher message : %d \n",c);

    start = clock();

    // Decrypt using Modular Arithmetic:
    message = power(c,d,N);
        printf("p : %d \n", p);
    printf("q : %d \n", q);
    printf("Original message by Normal Method: %d \n",message);

	end = clock();
	cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
	printf("The total time taken by Normal method is : %lf s\n",cpu_time_used);



            // Decrypt using Chinese Remainder Theorem:
            // unsigned long long int vp = power(c,d,p);
            // printf("vp : %d \n",vp);
            // unsigned long long int vq = power(c,d,q);
            // printf("vq : %d \n",vp);

            // unsigned long long int m1 = power(c,d,p);
            // printf("m1 : %d \n",m1);
            // unsigned long long int m2 = power(c,d,q);
            // printf("m2 : %d \n",m2);


    start = clock();

            //message = ((vp * xp) + (vq * xq)) % N;

            // unsigned long long int h = (fin_qinv*(m1-m2) ) %p;
            // message = (m2 + (h*q)) % N ;

            // unsigned long long int dq = power(d, 1, (q-1));
            // unsigned long long int dp = power(d, 1, (p-1));

            unsigned long long int m1 = power(c, dp, p);
            
            //Message part 2
            unsigned long long int m2 = power(c, dq, q);


            unsigned long long int h = (qinv * (m1 - m2)) % p;

            //printf("q value : %d \n",q);
            unsigned long long int m = m2 + h * q;



            // message = chineseremaindertheorem(dq, dp, p, q, c); 
            message = m;

            printf("CRT Original message : %d \n",message);
            //int d = inv_e % phi_N;
	end = clock();
	cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
	printf("The total time taken by CRT method is : %lf s\n",cpu_time_used);
    return 0;
}
