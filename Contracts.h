/*
Contracts Class

***
Defines a single contract.

Value cannot be changed once object is defined.

Inherited by Block.

Inherits types, Transaction_ID, Reciever_Wallet, Sender_Wallet,
Sender_Signature, Data, Reward
*/
#include <string_view>
#include <string>


class Data {

    public:
        //constructor
        Data()=default;
        Data(double data_value){
            this->data_value = data_value;
        }

        //destructor
        ~Data()=default;

        //getter
        double get_data_value(){
            return data_value;
        }

    private:

        //value
        double data_value{0};
};


class Reciever_Wallet{

    public:
        //constructor
        Reciever_Wallet()=default;
        Reciever_Wallet(std::string_view wallet){
            this->wallet = wallet;
        }

        //destructor
        ~Reciever_Wallet()=default;

        //getter
        std::string get_reciever_wallet(){
            return wallet;
        }

    private:

        //value
        std::string wallet{"null"};
};


class Reward {

    public:
        //constructor
        Reward()=default;
        Reward(double reward_value){
            this->reward_value = reward_value;
        }

        //destructor
        ~Reward()=default;

        //getter
        double get_reward_value(){
            return reward_value;
        }

    private:

        //value
        double reward_value{0};
};


class Sender_Signature{

    public:
        //constructor
        Sender_Signature()=default;
        Sender_Signature(std::string_view signature){
            this->signature = signature;
        }

        //destructor
        ~Sender_Signature()=default;

        //getter
        std::string get_sender_signature(){
            return signature;
        }

    private:

        //value
        std::string signature{"null"};
};


class Sender_Wallet{

    public:
        //constructor
        Sender_Wallet()=default;
        Sender_Wallet(std::string_view wallet){
            this->wallet = wallet;
        }

        //destructor
        ~Sender_Wallet()=default;

        //getter
        std::string get_sender_wallet(){
            return wallet;
        }

    private:

        //value
        std::string wallet{"null"};
};


class Transaction_ID{

    public:
        //constructor
        Transaction_ID()=default;
        Transaction_ID(std::string_view transaction_ID){
            this->transaction_ID = transaction_ID;
        }

        //destructor
        ~Transaction_ID()=default;

        //getter
        std::string get_transaction_ID(){
            return transaction_ID;
        }

    private:

        //value
        std::string transaction_ID{"null"};
};



class Contracts :   public Transaction_ID,
                    public Reciever_Wallet,
                    public Sender_Wallet,
                    public Sender_Signature,
                    public Data,
                    public Reward {

    public:
        //constructors
        Contracts()=default;
        Contracts(  std::string_view transaction_ID,
                    std::string_view reciever_wallet,
                    std::string_view sender_wallet,
                    std::string_view sender_signature,
                    double data,
                    double reward):
            Transaction_ID(transaction_ID),
            Reciever_Wallet(reciever_wallet),
            Sender_Wallet(sender_wallet),
            Sender_Signature(sender_signature),
            Data(data),
            Reward(reward){}
 
        //destructor
        ~Contracts()=default;

        //printer
        void print_contract(){
            std::cout << "transaction ID: " << get_transaction_ID() << "\n";
            std::cout << "reciever wallet: " << get_reciever_wallet() << "\n";
            std::cout << "sender wallet: " << get_sender_wallet() << "\n";
            std::cout << "sender signature: " << get_sender_signature() << "\n";
            std::cout << "data: " << get_data_value() << "\n";
            std::cout << "reward: " << get_reward_value() << "\n";
        }
};