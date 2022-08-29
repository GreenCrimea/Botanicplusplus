#include <iostream>
#include <string>
#include <string_view>
#include "cryptography.h"
#include <ctime>

class Blockchain {

    public:

        //constructors
        Blockchain()=default;

        //destructor
        ~Blockchain()=default;

        //create genesis block
        Block create_genesis_block(std::string reciever_wallet){
            if(chain_index == 0){
            std::string previous_proof {"0"};
            Block block = create_block(reciever_wallet, previous_proof);
            return block;
            }
        }

        //create next block
        Block create_next_block(std::string reciever_wallet){
        
            Hashing_func hasher;
            std::string previous_proof = hasher.hash_func(previous_block_string, previous_nonce);
            Block block = create_block(reciever_wallet, previous_proof);
            return block;
        }

        //create mining reward contract
        Contracts create_mining_reward(std::string reciever_wallet){
            
            std::string transaction_ID = generate_transaction_ID();
            std::string sender_wallet {"MINING PROTOCOL"};
            std::string sender_signature {"000000000000000000000000"};
            double data {1000};
            double reward {0};

            Contracts contract(transaction_ID, reciever_wallet, sender_wallet, sender_signature, data, reward);

            return contract;
        }

        //create block
        Block create_block(std::string reciever_wallet, std::string previous_proof){
            
            double index = chain_index;

            Hashing_func hasher(difficulty);
            double proof = hasher.mine_hash(previous_proof);

            time_t now = time(0);
            char* dt = ctime(&now);

            std::string timestamp = dt;

            Block block(index, timestamp, proof, previous_proof);

            Contracts mining_reward = create_mining_reward(reciever_wallet);

            int contract_index {0};
            block.initialise_array(contract_index, mining_reward);
            ++contract_index;

            previous_nonce = proof;

            previous_block_string = block.add_block();

            ++chain_index;

            return block;
        }

    private:

        double chain_index {0};
        double difficulty {3};
        double previous_nonce {};
        std::string previous_block_string {};

};
