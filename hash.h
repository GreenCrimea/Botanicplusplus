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
std::string TEST{"TEST"};

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
        std::string hash_block(){
            using namespace CryptoPP;
            HexEncoder encoder(new FileSink(std::cout));

            std::string msg = TEST;
            std::string digest;

            SHA256 hash;
            hash.Update((const byte*)msg.data(), msg.size());
            digest.resize(hash.DigestSize());
            hash.Final((byte*)&digest[0]);

            std::cout << "Message: " << msg << "\n";
            StringSource(digest, true, new Redirector(encoder));
            std::cout << std::endl;

            std::string hash_outcome{"hi"};
            return hash_outcome;
        }

    private:

        double difficulty{5};

};
