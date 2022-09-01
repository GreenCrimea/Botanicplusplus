#include <iostream>
#include <string>
#include <string_view>
#include "transactions.h"
#include <ctime>
const long unsigned int CHAINSIZE {10000};
const long unsigned int MEMPOOL_SIZE {4};

class Blockchain: public Transactions{

    public:

        //constructors
        Blockchain()=default;

        //destructor
        ~Blockchain()=default;

        //create genesis block
        void create_genesis_block(std::string reciever_wallet){
            if(chain_index == 0){
            std::string previous_proof {"0"};
            create_block(reciever_wallet, previous_proof);
            }
        }

        //create next block
        void create_next_block(std::string reciever_wallet){
        
            Hashing_func hasher;
            std::string previous_proof = hasher.hash_func(previous_block_string, previous_nonce);
            create_block(reciever_wallet, previous_proof);
        }

        //create mining reward contract
        Contracts create_mining_reward(std::string reciever_wallet, double reward){
            
            std::string transaction_ID = generate_transaction_ID();
            std::string sender_wallet {"MINING PROTOCOL"};
            std::string sender_signature {"000000000000000000000000"};
            double data {1000};

            change_balance(reciever_wallet, 1000 + reward);

            Contracts contract(transaction_ID, reciever_wallet, sender_wallet, sender_signature, data, reward);

            return contract;
        }

        //create block
        void create_block(std::string reciever_wallet, std::string previous_proof){
            
            double index = chain_index;

            Hashing_func hasher(difficulty);
            double proof = hasher.mine_hash(previous_proof);

            time_t now = time(0);
            char* dt = ctime(&now);

            std::string timestamp = dt;

            Block block(index, timestamp, proof, previous_proof);

            for(int i = 0; i < block_mempool_size; ++i){
                Contracts empty_contract;
                block.initialise_array((i + 1), block_mempool[i]);
                block_mempool[i] = empty_contract;
            }

            double reward = calculate_reward_for_miner();

            Contracts mining_reward = create_mining_reward(reciever_wallet, reward);

            block.initialise_array(0, mining_reward);

            block_mempool_size = 0;

            add_to_chain(block);

            previous_nonce = proof;

            previous_block_string = block.add_block();

            reset_mempool_state();

            calculate_mempool_state();

            test_print_mempools();

            ++chain_index;
        }


        double calculate_reward_for_miner(){
            double value {0};
            for(int i = 0; i < block_mempool_size; ++i){
                double num = block_mempool[i].get_reward_value();
                value = value + num;
            }
            return value;
        }


        //add to chain array
        void add_to_chain(Block block){
            the_chain[chain_index] = block;
        }

        //see chain
        void see_chain(){
            for(int i = 0; i < chain_index; ++i){
                the_chain[i].print_block();
                std::cout << "\n\n" << std::endl;
            }
        }

        //see block
        void see_block(long unsigned int index){
            the_chain[index].print_block();
        }

        //is block valid
        bool is_block_valid(long unsigned int index){
            std::string block_str = the_chain[index-1].add_block();
            Hashing_func hasher;

            double previous_nonce = the_chain[index-1].get_proof();

            std::string previous_block_proof = hasher.hash_func(block_str, previous_nonce);
            std::string previous_proof_next = the_chain[index].get_previous_proof();
            
            if(previous_block_proof == previous_proof_next){
                return true;
            }else{
                return false;
            }
        }

        //is chain valid
        bool is_chain_valid(){
            int valid = 1;
            while(valid == 1){
                for(int i = 1; i < chain_index; ++i){
                    std::string block_str = the_chain[i-1].add_block();
                    Hashing_func hasher;

                    double previous_nonce = the_chain[i-1].get_proof();

                    std::string previous_block_proof = hasher.hash_func(block_str, previous_nonce);
                    std::string previous_proof_next = the_chain[i].get_previous_proof();

                    if(previous_block_proof == previous_proof_next){
                        valid = 1;
                    }else{
                        valid = 0;
                    }
                }
            }
            if(valid == 0){
                return false;
            }else if (valid == 1){
                return true;
            }
        }


        //create transaction
        void create_transaction(std::string sender_wallet, std::string passphrase, std::string reciever_wallet, double data, double reward){
            if(is_wallet_in_index(reciever_wallet)){
                if(is_wallet_in_index(sender_wallet)){
                    if(verify_wallet_owner(sender_wallet, passphrase)){
                        if(is_transaction_valid(sender_wallet, data)){
                            Contracts contract = send_coins(sender_wallet, passphrase, reciever_wallet, data, reward);
                            total_mempool[total_mempool_size] = contract;
                            ++total_mempool_size;
                            calculate_mempool_state();
                            test_print_mempools();
                        }
                    }
                }
            }
        }


        void calculate_mempool_state(){
            int mempool_remaining = MEMPOOL_SIZE - block_mempool_size;
            Contracts empty_contract;
            if(mempool_remaining > 0){

                if(mempool_remaining >= total_mempool_size){

                    for(int i = 0; i < total_mempool_size; ++i){

                        block_mempool[block_mempool_size + i] = total_mempool[i];
                        total_mempool[i] = total_mempool[total_mempool_size];
                        total_mempool[total_mempool_size] = empty_contract;
                        ++block_mempool_size;
                        --total_mempool_size;
                    }

                }else if (total_mempool_size > mempool_remaining){

                    for(int i = 0; i < mempool_remaining; ++i){
                        block_mempool[block_mempool_size + i] = total_mempool[i];
                        total_mempool[i] = total_mempool[total_mempool_size];
                        total_mempool[total_mempool_size] = empty_contract;
                        ++block_mempool_size;
                        --total_mempool_size;
                    }
                }
            }


            if((mempool_remaining == 0) && (total_mempool_size > 0)){

                for(int a = 0; a < (total_mempool_size + MEMPOOL_SIZE); ++a){

                    for(int i = 0; i < total_mempool_size; ++i){

                        int lowest_block_index = find_lowest_block_index();
                        double lowest_block_value = block_mempool[lowest_block_index].get_reward_value();
                        int highest_mempool_index = find_highest_mempool_index();
                        double highest_mempool_value = total_mempool[highest_mempool_index].get_reward_value();

                        if(lowest_block_value < highest_mempool_value){
                            Contracts block_contract = block_mempool[lowest_block_index];
                            Contracts total_contract = total_mempool[highest_mempool_index];
                            block_mempool[lowest_block_index] = total_contract;
                            total_mempool[highest_mempool_index] = block_contract;
                        }
                    }
                }
            }
        }


        void reset_mempool_state(){
            Contracts empty_contract;
            if(total_mempool_size <= MEMPOOL_SIZE){   
                std::cout << "test" << std::endl; 
                for(int i = 0; i < total_mempool_size; ++i){
                    block_mempool[i] = total_mempool[i];
                    total_mempool[i] = empty_contract;
                    ++block_mempool_size;
                    
                }
                total_mempool_size = 0;
            }else if(total_mempool_size > MEMPOOL_SIZE){
                std::cout << "test2" << std::endl; 
                for(int i = 0; i < MEMPOOL_SIZE; ++i){
                    block_mempool[i] = total_mempool[i];
                    total_mempool[i] = total_mempool[total_mempool_size - MEMPOOL_SIZE];
                    total_mempool[total_mempool_size - MEMPOOL_SIZE] = empty_contract;
                    ++block_mempool_size;
                    test_print_mempools();
                }
                total_mempool_size = total_mempool_size - MEMPOOL_SIZE;
            }
        }

        
        int find_lowest_block_index(){
            double lowest_block_value = block_mempool[0].get_reward_value();
            int lowest_block_index = 0;
            for(int y = 1; y < MEMPOOL_SIZE ; ++y){
                    double value = block_mempool[y].get_reward_value();
                    if(value < lowest_block_value){
                        lowest_block_value = value;
                        lowest_block_index = y;
                    }
                }
            return lowest_block_index;
        }


        double find_highest_mempool_index(){
            double highest_mempool_value = total_mempool[0].get_reward_value();
            int highest_mempool_index = 0;
            for(int y = 1; y < total_mempool_size; ++y){
                double value = total_mempool[y].get_reward_value();
                if(value > highest_mempool_value){
                    highest_mempool_value = value;
                    highest_mempool_index = y;
                }
            }
            return highest_mempool_index;
        }


        void test_print_mempools(){
            std::cout << "BLOCK MEMPOOL size:" << block_mempool_size << std::endl;
            std::cout << "0; " << block_mempool[0].get_reward_value() << std::endl;
            std::cout << "1; " << block_mempool[1].get_reward_value() << std::endl;
            std::cout << "2; " << block_mempool[2].get_reward_value() << std::endl;
            std::cout << "3; " << block_mempool[3].get_reward_value() << std::endl;
            std::cout << "4; " << block_mempool[4].get_reward_value() << std::endl;
            std::cout << "TOTAL MEMPOOL size:" << total_mempool_size << std::endl;
            std::cout << "0; " << total_mempool[0].get_reward_value() << std::endl;
            std::cout << "1; " << total_mempool[1].get_reward_value() << std::endl;
            std::cout << "2; " << total_mempool[2].get_reward_value() << std::endl;
            std::cout << "3; " << total_mempool[3].get_reward_value() << std::endl;
            std::cout << "4; " << total_mempool[4].get_reward_value() << std::endl;
            std::cout << "5; " << total_mempool[5].get_reward_value() << std::endl;
            std::cout << "6; " << total_mempool[6].get_reward_value() << std::endl;
            std::cout << "7; " << total_mempool[7].get_reward_value() << std::endl;
 

        }


    private:

        long unsigned int chain_index {0};
        double difficulty {5};
        double previous_nonce {};
        std::string previous_block_string {};

        Block the_chain[CHAINSIZE];

        Contracts block_mempool[MEMPOOL_SIZE];
        int block_mempool_size {0};

        Contracts total_mempool[1000];
        int total_mempool_size {0};



};
