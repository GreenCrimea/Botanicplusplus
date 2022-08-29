#include <iostream>
#include <string>
#include <string_view>
#include "hash.h"
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>
#include <cryptopp/eccrypto.h>
#include <cryptopp/oids.h>


void Save(const std::string& filename, const CryptoPP::BufferedTransformation& bt)
{
    CryptoPP::FileSink file(filename.c_str());

    bt.CopyTo(file);
    file.MessageEnd();
}


void Load(const std::string& filename, CryptoPP::BufferedTransformation& bt)
{
    CryptoPP::FileSource file(filename.c_str(), true);

    file.TransferTo(bt);
    bt.MessageEnd();
}


void SavePrivateKey(const std::string& filename, const CryptoPP::RSA::PrivateKey& key)
{
    CryptoPP::ByteQueue queue;
    key.Save(queue);

    Save(filename, queue);
}


void LoadPrivateKey(const std::string& filename, CryptoPP::RSA::PrivateKey& key)
{
    CryptoPP::ByteQueue queue;
    Load(filename, queue);

    key.Load(queue);    
}


void save_keys (CryptoPP::RSA::PrivateKey rsaPrivate, std::string wallet){
    std::string dir_str = "keys/" + wallet + ".key";
    SavePrivateKey(dir_str, rsaPrivate);
}



std::string sign_message(CryptoPP::RSA::PrivateKey privateKey, std::string passphrase){
    using namespace CryptoPP;

    AutoSeededRandomPool rng;

    RSASSA_PKCS1v15_SHA_Signer signer(privateKey);

    size_t length = signer.MaxSignatureLength();
    SecByteBlock signature(length);

    length = signer.SignMessage(rng, (const byte*) passphrase.c_str(), passphrase.length(), signature);

    signature.resize(length);

    std::string userAccess;

    std::string token(reinterpret_cast<const char*>(signature.data()), signature.size());

    token += userAccess;

    return token;
}


bool verify_wallet(std::string check_wallet, std::string wallet){
    bool result = false;

    if (check_wallet == wallet){
        result = true;
    }else{
        result = false;
    }

    if( !result ) {
        std::cout << "Failed to verify signature on message" << std::endl;
    } else {
        std::cout << "All good!" << std::endl;
    }  

    return result;
}


std::string generate_wallet (std::string signature){
    using namespace CryptoPP;

    std::string sig_hex;
    HexEncoder hex(new StringSink(sig_hex));

    StringSource(signature, true, new Redirector(hex));

    std::string wallet = sig_hex.substr(0,24);

    return wallet;
}


CryptoPP::RSA::PrivateKey load_keys(std::string wallet){
    using namespace CryptoPP;

    std::string filename = "keys/" + wallet + ".key";
    RSA::PrivateKey privateKey;

    LoadPrivateKey(filename, privateKey);

    return privateKey;
}


bool verify_wallet_owner(std::string wallet, std::string passphrase){
    using namespace CryptoPP;

    RSA::PrivateKey privateKey = load_keys(wallet);

    std::string signature = sign_message(privateKey, passphrase);

    std::string check_wallet = generate_wallet(signature);

    bool result = verify_wallet(check_wallet, wallet);

    return result;
}


std::string generate_keypair(std::string passphrase){
    using namespace CryptoPP;
    
    AutoSeededRandomPool rng;

    InvertibleRSAFunction parameters;
    parameters.GenerateRandomWithKeySize(rng, 3072);

    RSA::PrivateKey privateKey(parameters);
    RSA::PublicKey publicKey(parameters);
    
    std::string signature = sign_message(privateKey, passphrase);

    std::string wallet = generate_wallet(signature);

    save_keys(privateKey, wallet);

    return wallet;
}

std::string generate_transaction_ID(){
    using namespace CryptoPP;

    SecByteBlock rand_bytes(AES::BLOCKSIZE);
    std::string rand_hex;

    OS_GenerateRandomBlock(false, rand_bytes, rand_bytes.size());

    HexEncoder hex (new StringSink(rand_hex));
    hex.Put(rand_bytes, rand_bytes.size());
    hex.MessageEnd();

    return rand_hex.substr(0,24);
}



