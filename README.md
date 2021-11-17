# -CS6530-Assignment-3-RSA-Algorithm
Assignment - 3 :  RSA Algorithm using Mod Exponentiation and Chinese Remainder Theorem

Assignments for IIT CS6530 Cryptography Basics

Name : Gobinath Periyasamy

Roll Number : CS21M501

Registered Mail id : janu.gobi@gmail.com

Steps to Execute the Program:

1. To open the rsa.exe file.
2. To input the message Eg : 3456, 8986, 9876, 67895

It will automatically choose random p, q values.

Cipher text will be created.

Then Original text would be created using the Normal Mod Exponentiation Algorithm and Chinese Remainder Theorem
And the approx time to calculate them will be displayed.

Sample Ouput:

E:\IIT Sem\Cryptography Basics\Assignment 3>rsa.exe

Enter the message :9876

Cipher message : 33001235

p : 9833

q : 9437

N : 92794021

phi_N : 92774752

e : 29633

d : 47146593

Original message by Normal Mod Exp Method: 9876

The total time taken by Normal Mod Exp method is : 4.000000 s

Original message by Chinese Remainder Theorem: 9876

The total time taken by Chinese Remainder Theorem method is : 1.000000 s


Sample Output 2:


E:\IIT Sem\Cryptography Basics\Assignment 3>gcc -o rsa.exe RSA.c

E:\IIT Sem\Cryptography Basics\Assignment 3>rsa.exe


Enter the Numerical message :6354728

Cipher message : 27537680

p : 18313

q : 10631

N : 194685503

phi_N : 194656560

e : 12889

d : 87428569

Original message by Normal Mod Exp Method: 6354728

The total time taken by Normal Mod Exp method is : 3.000000 s

Original message by Chinese Remainder Theorem: 6354728

The total time taken by Chinese Remainder Theorem method is : 1.000000 s

