#include <iostream>
#include <string>
#include "blockchain.h"
#include <cryptopp/rsa.h>

class Transactions {

    public:
        //constructor
        Transactions()=default;

        //destructor
        ~Transactions()=default;

        //send coins
        Contracts send_coins(std::string sender_wallet, std::string passphrase, std::string reciever_wallet, double data, double reward){
            
            std::string transaction_ID = generate_transaction_ID();

            std::string sender_signature {};

            std::string string_to_sign = transaction_ID + reciever_wallet + sender_wallet + std::to_string(data) + std::to_string(reward);

            if(verify_wallet_owner(sender_wallet, passphrase)){
                CryptoPP::RSA::PrivateKey privateKey = load_keys(sender_wallet);

                std::string signature = sign_message(privateKey, string_to_sign);

                sender_signature = generate_wallet(signature);
            }

            Contracts contract(transaction_ID, reciever_wallet, sender_wallet, sender_signature, data, reward);

            return contract;
        }

};