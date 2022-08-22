/*
Block Class

***
Defines a single block.

Value cannot be changed once object is defined.

Inherits Index, Timestamp, Proof, Previous_proof, Contracts_Array
*/
#include <string_view>
#include <string>
#include "Contracts.h"
const int BLOCKSIZE {2};

class Index {

    public:
        //constructor
        Index()=default;
        Index(double index_value){
            this->index_value = index_value;
        }

        //destructor
        ~Index()=default;

        //getter
        double get_index_value(){
            return index_value;
        }
    
    private:

        //value
        double index_value{0};
};


class Timestamp {

    public:
        //constructor
        Timestamp()=default;
        Timestamp(std::string_view timestamp){
            this->timestamp = timestamp;
        }

        //destructor
        ~Timestamp()=default;

        //getter
        std::string get_timestamp(){
            return timestamp;
        }

    private:

        //value
        std::string timestamp{"null"};
};


class Proof {

    public:
        //constructor
        Proof()=default;
        Proof(std::string_view proof){
            this->proof = proof;
        }

        //destructor
        ~Proof()=default;

        //getter
        std::string get_proof(){
            return proof;
        }

    private:

        //value
        std::string proof{"null"};
};


class Previous_Proof {

    public:
        //constructor
        Previous_Proof()=default;
        Previous_Proof(std::string_view previous_proof){
            this->previous_proof = previous_proof;
        }

        //destructor
        ~Previous_Proof()=default;

        //getter
        std::string get_previous_proof(){
            return previous_proof;
        }

    private:

        //value
        std::string previous_proof{"null"};
};


class Contracts_Array{

    public:
        //constructors
        Contracts_Array()=default;

        void initialise_array(int index, Contracts contract){
            contracts_array[index] = contract;
        }

        //getter
        Contracts get_contracts_array(int index){
            return contracts_array[index];
        }

    private:
        Contracts contracts_array[BLOCKSIZE];
};


class Block :   public Index, 
                public Timestamp,
                public Proof,
                public Previous_Proof,
                public Contracts_Array {
    
    public:
        //constructors
        Block()=default;
        Block(  double index,
                std::string_view timestamp,
                std::string_view proof,
                std::string_view previous_proof):
            Index(index),
            Timestamp(timestamp),
            Proof(proof),
            Previous_Proof(previous_proof),
            Contracts_Array(){}

        //destructor
        ~Block()=default;

        //printer
        void print_block(){
            std::cout << "BLOCK" << "\n";
            std::cout << "=============" << "\n";
            std::cout << "index: " << get_index_value() << "\n";
            std::cout << "timestamp: " << get_timestamp() << "\n";
            std::cout << "proof: " << get_proof() << "\n";
            std::cout << "Previous proof: " << get_previous_proof() << "\n";
            std::cout << "Contracts: \n";
            std::cout << "---------------\n";
            for(int i = 0; i < BLOCKSIZE; ++i){
                std::cout << "contract " << i << "\n";
                std::cout << "===============\n";
                get_contracts_array(i).print_contract();
                std::cout << "---------------\n";
            }
        }

};