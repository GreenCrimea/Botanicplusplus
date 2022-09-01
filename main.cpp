#include <iostream>
#include <string>
#include "blockchain.h"
#define CROW_MAIN
#include "crow.h"


int main() {

    Blockchain main_chain;

    std::string passphrase {"password"};
    std::string passphrase2 {"example"};
    std::string passphrase3 {"test"};
    std::string wallet = generate_keypair(passphrase);
    std::string wallet2 = generate_keypair(passphrase2);
    std::string wallet3 = generate_keypair(passphrase3);

    main_chain.add_new_wallet(wallet, 0);
    main_chain.add_new_wallet(wallet2, 0);
    main_chain.add_new_wallet(wallet3, 0);

    main_chain.create_genesis_block(wallet);

    main_chain.create_transaction(wallet, passphrase, wallet2, 50, 5);

    main_chain.create_next_block(wallet);

    main_chain.create_transaction(wallet, passphrase, wallet2, 5, 75);
    main_chain.create_transaction(wallet, passphrase, wallet2, 5, 35);
    main_chain.create_transaction(wallet, passphrase, wallet2, 5, 12);
    main_chain.create_transaction(wallet, passphrase, wallet2, 5, 1);
    main_chain.create_transaction(wallet, passphrase, wallet2, 5, 99);
    main_chain.create_transaction(wallet, passphrase, wallet2, 5, 4);
    main_chain.create_transaction(wallet, passphrase, wallet2, 5, 3);
    main_chain.create_transaction(wallet, passphrase, wallet2, 5, 67);
    main_chain.create_transaction(wallet, passphrase, wallet2, 5, 9);
    main_chain.create_transaction(wallet, passphrase, wallet2, 5, 43);
    main_chain.create_transaction(wallet, passphrase, wallet2, 5, 32);
    main_chain.create_transaction(wallet, passphrase, wallet2, 5, 67);

    main_chain.create_next_block(wallet3);
    main_chain.create_next_block(wallet3);
    main_chain.create_next_block(wallet3);

    double bal = main_chain.get_wallet_balance(wallet);
    double bal2 = main_chain.get_wallet_balance(wallet2);
    double bal3 = main_chain.get_wallet_balance(wallet3);

    std::cout << "bal: " << bal << std::endl;
    std::cout << "bal2: " << bal2 << std::endl;
    std::cout << "bal3: " << bal3 << std::endl;

    main_chain.see_chain();

    if(main_chain.is_chain_valid()){
        std::cout << "VALID" << std::endl;
    }else{
        std::cout << "NOT VALID" << std::endl;
    }


    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        auto page = crow::mustache::load_text("index.html");
        return page;
    });

    
    CROW_ROUTE(app, "/test.html")([](){
        auto page = crow::mustache::load_text("test.html");
        return page;
    });


    CROW_ROUTE(app, "/mine_block.html")([](){
        auto page = crow::mustache::load_text("mine_block.html");
        return page;
    });


    CROW_ROUTE(app, "/get_chain.html")([](){
        auto page = crow::mustache::load_text("get_chain.html");
        return page;
    });


    CROW_ROUTE(app, "/join.html")([](){
        auto page = crow::mustache::load_text("join.html");
        return page;
    });


    CROW_ROUTE(app, "/see_nodes.html")([](){
        auto page = crow::mustache::load_text("see_nodes.html");
        return page;
    });


    CROW_ROUTE(app, "/generate_wallet.html")([](){
        auto page = crow::mustache::load_text("generate_wallet.html");
        return page;
    });


    CROW_ROUTE(app, "/send_coins.html")([](){
        auto page = crow::mustache::load_text("send_coins.html");
        return page;
    });


    CROW_ROUTE(app, "/balance.html")([](){
        auto page = crow::mustache::load_text("balance.html");
        return page;
    });


    app.port(18080).multithreaded().run();

    return 0;
} 

