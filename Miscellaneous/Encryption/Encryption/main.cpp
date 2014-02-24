//
//  main.cpp
//  Encryption
//
//  Created by Daniel Eisterhold on 1/19/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#include <iostream>
using namespace std;

int encrypt(int publicKey, int maxValue, int const numberToEncrypt)
{
    int encryptedNumber = numberToEncrypt;
    
    for (int counter = 1; counter < publicKey; counter++)
    {
        encryptedNumber = ((encryptedNumber * numberToEncrypt) % maxValue);
    }
    
    return encryptedNumber;
}

int decrypt(int privateKey, int maxValue, int const numberToDecrypt)
{
    int decryptedNumber = numberToDecrypt;
    
    for (int counter = 1; counter < privateKey; counter++)
    {
        decryptedNumber = ((decryptedNumber * numberToDecrypt) % maxValue);
    }
    
    return decryptedNumber;
}

int main(int argc, const char * argv[])
{
    int maxValue = 91;//rand()*rand();
    int publicKey = 5;
    int privateKey = 29;
    
    int numberToEncrypt;
    int numberAfterEncryption;
    int numberAfterDecryption;
    
    cout<<"Please enter a number that you would wish to encrypt: ";
    cin>>numberToEncrypt;
    cout<<"Encrypting the number: "<<numberToEncrypt<<endl;
    
    numberAfterEncryption = encrypt(publicKey, maxValue, numberToEncrypt);
    
    cout<<"The encrypted number is: "<<numberAfterEncryption<<endl;
    
    cout<<"Now decrypting the number: "<<numberAfterEncryption<<endl;
    
    numberAfterDecryption = decrypt(privateKey, maxValue, numberAfterEncryption);
    
    cout<<"The decrypted number is: "<<numberAfterDecryption<<endl;
    if (numberToEncrypt == numberAfterDecryption)
    {
        cout<<"The encryption was successful"<<endl;
    }
    else
    {
        cout<<"The encryption was unsuccessful"<<endl;
    }
    
    return 0;
}

