#include <iostream>
#include <string>
#include <string_view>
#include "hash.h"

class Cryptography {

    public:
        //constructor
        Cryptography()=default;


        //destructor
        ~Cryptography()=default;


        //CRYPTO FUNCS
        //generate wallet
        auto generate_wallet(std::string passphrase){
            generate_private_key();
            generate_public_key();


        }


        //generate private key
        void generate_private_key(){
            AutoSeededRandomPool prng;

            RSA::PrivateKey rsa_private;
            rsa_private.GenerateRandomWithKeySize(prng, 3072);
            current_working_prikey = rsa_private;           
        }


        //generate public key
        void generate_public_key(){
            RSA::PublicKey rsa_public(current_working_prikey);
            current_working_pubkey = rsa_public;
        }


        //get wallet address



    private:

        auto current_working_pubkey;
        auto current_working_prikey;
}