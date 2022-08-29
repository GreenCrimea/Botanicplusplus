#include <iostream>
#include <string>
#include "cryptography.h"
#include <string_view>
#include <cryptopp/rsa.h>
const long unsigned int ARRAYSIZE {10000};

class Wallet_ID {
        public:
        //constructor
        Wallet_ID()=default;
        Wallet_ID(std::string_view wallet){
            this->wallet = wallet;
        }

        //destructor
        ~Wallet_ID()=default;

        //getter
        std::string get_wallet_ID(){
            return wallet;
        }

        //setter
        void set_wallet_ID(std::string wallet){
            this->wallet = wallet;
        }

    private:

        //value
        std::string wallet{"null"};
};


class Wallet_Balance {
        public:
        //constructor
        Wallet_Balance()=default;
        Wallet_Balance(double balance){
            this->balance = balance;
        }

        //destructor
        ~Wallet_Balance()=default;

        //getter
        double get_wallet_balance(){
            return balance;
        }

        //setter
        void set_wallet_balance(double balance){
            this->balance = balance;
        }

    private:

        //value
        double balance{0};
};


class Balance_Tracker :     public Wallet_ID,
                            public Wallet_Balance {
    
    public:
        //constructor
        Balance_Tracker()=default;
        Balance_Tracker(std::string_view wallet_ID, double balance):
                                Wallet_ID(wallet_ID),
                                Wallet_Balance(balance){}

        //destructor
        ~Balance_Tracker()=default;
};


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


        long unsigned int find_wallet_index (std::string wallet){
            for(long unsigned int i = 0; i < total_wallets; ++i){
                std::string check_wallet = balance_array[i].get_wallet_ID();
                if(wallet == check_wallet){
                    return i;
                }
            }
        }


        double get_balance (long unsigned int index){
            double balance = balance_array[index].get_wallet_balance();
            return balance;
        }


        void change_balance(std::string wallet, double data){
            if(is_transaction_valid(wallet, data)){
                long unsigned int index = find_wallet_index(wallet);
                double balance = get_balance(index);
                double new_balance = balance + data;
                balance_array[index].set_wallet_balance(new_balance);
            }
        }


        bool is_transaction_valid(std::string wallet, double data){
            long unsigned int index = find_wallet_index(wallet);
            double balance = get_balance(index);
            if((balance + data) >= 0){
                return true;
            }else{
                return false;
            }
        }


        bool is_wallet_in_index(std::string wallet){
            for(long unsigned int i = 0; i < total_wallets; ++i){
                std::string check_wallet = balance_array[i].get_wallet_ID();
                if(wallet == check_wallet){
                    return true;
                }
            }
            return false;
        }
        


    private:

        Balance_Tracker balance_array[ARRAYSIZE];
        long unsigned int total_wallets {0};

};



