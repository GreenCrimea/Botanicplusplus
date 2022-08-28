#include <iostream>
#include <string>
#include "hash.h"
#define CROW_MAIN
#include "crow.h"

Contracts test_1();

Contracts test_2();

void test_3(Contracts a, Contracts b);


int main() {
/*
    //Contracts contract_1 = test_1();
    //Contracts contract_2 = test_2();

    //test_3(contract_1, contract_2);
    double difficulty = 6;
    Hashing_func hasher(difficulty);
    
    std::string golden_hash {};
    std::string DATA {"testdata23"};
    
    golden_hash = hasher.mine_hash(DATA);
    std::cout << "golden hash: " << golden_hash << "\n";
    std::cout << "golden nonce: " << hasher.get_golden_nonce() << "\n";
*/
    crow::SimpleApp app;


    CROW_ROUTE(app, "/")([](){
        return "hello world";
    });

    app.port(18080).multithreaded().run();

    return 0;
} 

Contracts test_1(){

    std::string transaction_ID{"87f897f987e7"};
    std::string reciever_wallet{"689fe6a897f"};
    std::string sender_wallet{"a75ba789c"};
    std::string sender_signature{"ab7894576532cbe9f"};
    double data{100};
    double reward{10};

    Contracts contract_1(   transaction_ID, reciever_wallet, 
                            sender_wallet, sender_signature, data, 
                            reward);

    return contract_1; 
}

Contracts test_2(){

    std::string transaction_ID{"87f8a00f0c987e7"};
    std::string reciever_wallet{"689a00f0ca897f"};
    std::string sender_wallet{"a75baa00f0cc"};
    std::string sender_signature{"aba00f0c4576532cbe9f"};
    double data{500};
    double reward{50};

    Contracts contract_2(   transaction_ID, reciever_wallet, 
                            sender_wallet, sender_signature, data, 
                            reward);

    return contract_2; 
}

void test_3(Contracts a, Contracts b){

    double index {1};
    std::string timestamp {"1/1/1970"};
    std::string proof {"786978b7abfe9687f"};
    std::string previous_proof {"698a9869b869876f767e"};

    Block block_1(index, timestamp, proof, previous_proof);

    block_1.initialise_array(0,a);
    block_1.initialise_array(1,b);

    block_1.print_block();
}