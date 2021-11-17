#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>


clock_t start,end;
double cpu_time_used;
// Generate random numbers in range of lower and upper

uint64_t randoms(uint64_t upper, uint64_t lower)

{
    uint64_t num = ( rand()%
                (upper - lower +1)) + lower;
    return num;

}

//Find whether given number is prime or not

uint64_t prime(uint64_t n)
{
    uint64_t i, flag = 0;
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
uint64_t prime_ran(uint64_t upper,uint64_t lower)
{
    uint64_t p;
    uint64_t flag = 1;
    while(flag)
    {
        p = randoms(upper, lower);
        flag = prime(p);
    }
    return p;
}

uint64_t Euc_gcd(uint64_t a, uint64_t b)
{
    if (a == 0)
        return b;
    return Euc_gcd(b % a, a);
}


//Finding Inverse
uint64_t modInverse(uint64_t e, uint64_t phi)
{
    uint64_t i,Temp;
    //printf("%d",phi);
    for(i = 0; i<phi; i++)
    {
        uint64_t  mul = e*i;
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
uint64_t power(uint64_t  x, uint64_t y, uint64_t p)
{
    uint64_t res = 1;     // Initialize result

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



uint64_t chineseremaindertheorem (uint64_t d, uint64_t n, uint64_t p, uint64_t q, uint64_t c)

{
    uint64_t decrypt;
	uint64_t cp, cq, dpvalue, dqvalue;
	cp = c % p;
	cq = c % q;
	dpvalue = d % (p-1);
	dqvalue = d % (q-1);

	uint64_t vp, vq;
	vp = power(cp, dpvalue, p);
	vq = power(cq, dqvalue, q);

	uint64_t x_pvalue, x_qvalue, vpq;

	x_pvalue = q * modInverse(q,p);
	x_qvalue = p * modInverse(p,q);

    decrypt = (x_pvalue*vp + x_qvalue*vq) % n;

    return decrypt;



}



//Driver code

uint64_t main()

{

    printf("Please wait while selecting p and q values from Random Prime...\n");

    uint64_t p,q;


    uint64_t upper = 100000;
    uint64_t lower = (upper/10);

    srand (time(0));

    p = prime_ran(upper,lower);
    q = prime_ran(upper,lower);

//Randomly selecting p and q;



//Calculating N from p and q, N = p*q

    uint64_t N = p*q;


//Calculating phi_N from p-1 and q-1, phi_N = p*q
    uint64_t phi_N = (p-1)*(q-1);


//Selecting e randomly such that 1 < e < phi_n
    uint64_t flag = 1;
    uint64_t e;
    while(flag)
    {
        e = prime_ran(phi_N,1);
        if (Euc_gcd(e,phi_N) == 1)
            flag = 0;

    }
    

    uint64_t d = modInverse(e,phi_N);
    

    //uint64_t message = 12345;

    uint64_t message;
    printf("Thanks for waiting. \nPlease Enter the Numerical message :");
    scanf("%ld",&message);

            // Chinese Remainder Theorem set :
            // uint64_t m1_inv = modInverse(q, p);
            // uint64_t m2_inv = modInverse(p, q);

            // uint64_t c1 = q * (modInverse(q, p)%p);
            // uint64_t c2 = p * (modInverse(p, q)%q);

            // uint64_t dp = d % (p-1);
            // uint64_t dq = d % (q-1);
            // uint64_t q_inv = q % (q-1);

            // uint64_t fin_qinv = q_inv % p;

            // uint64_t x_qvalue = p * (p_inv % q);


            
            uint64_t dq = power(d, 1, (q-1));
            uint64_t dp = power(d, 1, (p-1));
            
            uint64_t qinv = modInverse(q, p);


    // Encrypt using the Modular Arithmetic:
    uint64_t c = power(message, e, N );
    printf("Cipher message : %d \n",c);

    start = clock();

    // Decrypt using Modular Arithmetic:
    message = power(c,d,N);
    printf("p : %d \n", p);
    printf("q : %d \n", q);
    printf("N : %d \n", N);
    printf("phi_N : %d \n", phi_N);
    printf("e : %d \n", e);
    printf("d : %d \n",d);
    printf("Original message by Normal Mod Exp Method: %d \n",message);

	end = clock();
	cpu_time_used = ((double) (end-start));
	printf("The total time taken by Normal Mod Exp method is : %lf s\n",cpu_time_used);


    start = clock();
            // Decrypt using Chinese Remainder Theorem:


            uint64_t m1 = power(c, dp, p);
            
            //Message part 2
            uint64_t m2 = power(c, dq, q);


            uint64_t h = (qinv * (m1 - m2)) % p;

            //printf("q value : %d \n",q);
            uint64_t m = m2 + h * q;

            uint64_t cp, cq, dpvalue, dqvalue;
            // Finding cp using cipher mod p
            cp = c % p;
            // Finding cq using cipher mod q
            cq = c % q;
            // Finding the dpvalue using d mod p-1
            dpvalue = d % (p-1);
            // Finding the dqvalue using d mod q-1
            dqvalue = d % (q-1);

            // Find Vert p value:
            uint64_t vp = power(cp, dpvalue, p);
            // Find Vert q value:
            uint64_t vq = power(cq, dqvalue, q);

            uint64_t x_pvalue, x_qvalue, vpq;

            // Find x_pvalue and x_qvalue using q and p
            x_pvalue = q * modInverse(q,p);
            x_qvalue = p * modInverse(p,q);

            // Getting Original message using CRT method
            message = (x_pvalue*vp + x_qvalue*vq) % N;

            // message = chineseremaindertheorem(dq, dp, p, q, c); 
            //message = m;

            printf("Original message by Chinese Remainder Theorem: %d \n",message);
            //uint64_t d = inv_e % phi_N;
	end = clock();
	cpu_time_used = ((double) (end-start)) ;
	printf("The total time taken by Chinese Remainder Theorem method is : %lf s\n",cpu_time_used);
    return 0;
}
