#include <iostream>
#include <string>
#include <string_view>
#include "hash.h"
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>


void Save(const std::string& filename, const CryptoPP::BufferedTransformation& bt)
{
    CryptoPP::FileSink file(filename.c_str());

    bt.CopyTo(file);
    file.MessageEnd();
}


void SavePrivateKey(const std::string& filename, const CryptoPP::RSA::PrivateKey& key)
{
    CryptoPP::ByteQueue queue;
    key.Save(queue);

    Save(filename, queue);
}



void save_keys (CryptoPP::RSA::PrivateKey rsaPrivate){
    SavePrivateKey("keys/rsa-private.key", rsaPrivate);
}


auto generate_rsa_keypair (){
    CryptoPP::AutoSeededRandomPool prng;

    CryptoPP::RSA::PrivateKey rsaPrivate;
    rsaPrivate.GenerateRandomWithKeySize(prng, 3072);

    CryptoPP::RSA::PublicKey rsaPublic(rsaPrivate);

    save_keys(rsaPrivate);
    
    return rsaPrivate, rsaPublic;
}



//std::string get_wallet_address (CryptoPP::RSA::PrivateKey rsaPrivate){
//    
//}