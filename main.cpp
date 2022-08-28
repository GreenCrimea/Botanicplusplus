#include <iostream>
#include <string>
#include "cryptography.h"
#define CROW_MAIN
#include "crow.h"


int main() {

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

