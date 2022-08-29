/*
Hash Class

***
Defines the hashing function

Value cannot be changed once object is defined.
*/
#include <iostream>
#include <string>
#include "block.h"
#include "cryptlib.h"
#include "sha.h"
#include "hex.h"
#include "files.h"
#include "filters.h"
#include <unistd.h>

class Hashing_func {

    public:
        //constructor
        Hashing_func()=default;
        Hashing_func(double difficulty){
            this->difficulty = difficulty;
        }


        //destructor
        ~Hashing_func()=default;


        //hashing_func
        std::string hash_func(std::string raw_input, double nonce){
            using namespace CryptoPP;
            std::string output_str {};
            HexEncoder encoder(new StringSink(output_str));

            std::string msg = raw_input + (std::to_string(nonce));
            std::string digest;

            SHA256 hash;
            hash.Update((const byte*)msg.data(), msg.size());
            digest.resize(hash.DigestSize());
            hash.Final((byte*)&digest[0]);

            StringSource(digest, true, new Redirector(encoder));

            return output_str;
        }


        //generate zero string
        std::string gen_zero_str(){
            std::string zero_str {""};

            for(size_t i = 0; i < difficulty; ++i){
                zero_str.append("0");
            }

            return zero_str;
        }


        //check hash
        int check_hash(std::string hashed_input, std::string zero_str){
            std::string hashed = hashed_input;
            std::string hash_check = hashed.substr(0, difficulty);

            if(hash_check == zero_str){
                return 1;
            }else{
                return 0;
            }
        }


        //mining_loop
        double mine_hash(std::string raw_input){
            int i = 0;
            std::string msg = raw_input;
            double nonce = 0;
            double golden_nonce {0};

            std::cout << "mining\n";

            std::string zero_str = gen_zero_str();

            std::cout << zero_str << "\n";

            while(i == 0){
                std::string hashed = hash_func(msg, nonce);
                std::cout << hashed << "\n";
                i = check_hash(hashed, zero_str);
                golden_hash = hashed;
                ++nonce;
                golden_nonce = nonce;
            }
            return golden_nonce;
        }


        //getter
        std::string get_golden_hash(){
            std::string hash = golden_hash;
            return hash;
        }

    private:

        int difficulty = 0;
        std::string golden_hash {};

};
