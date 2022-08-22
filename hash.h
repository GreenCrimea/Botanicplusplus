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

            std::string msg = raw_input;
            msg.append(std::to_string(nonce));
            std::string digest;

            SHA256 hash;
            hash.Update((const byte*)msg.data(), msg.size());
            digest.resize(hash.DigestSize());
            hash.Final((byte*)&digest[0]);

            std::cout << "Message: " << msg << "\n";
            StringSource(digest, true, new Redirector(encoder));
            std::cout << output_str << std::endl;

            return output_str;
        }

        //check hash
        int check_hash(std::string hashed_input){
            std::string hashed = hashed_input;
            std::string hash_check = hashed.substr(0,3);
            std::string zero_str {"000"};

            std::cout << "zero_str: " << zero_str << "\n";
            std::cout << "hash_check: " << hash_check << "\n";

            if(hash_check == zero_str){
                return 1;
            }else{
                return 0;
            }
        }

        //mining_loop
        std::string mine_hash(std::string raw_input){
            int i = 0;
            std::string msg = raw_input;
            int nonce = 0;
            std::string golden_hash {};

            while(i == 0){
                std::string hashed = hash_func(msg, nonce);
                i = check_hash(hashed);
                golden_hash = hashed;
                ++nonce;
                std::cout << "nonce: " << nonce << "\n";
                //sleep(3);
                
            }

            return golden_hash;
        }

    private:

        int difficulty = 5;

};
