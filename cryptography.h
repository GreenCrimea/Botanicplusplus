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


std::string sign_message(auto privateKey, std::string passphrase){
    using namespace CryptoPP;

    AutoSeededRandomPool prng;

    ECDSA<ECP, SHA256>::Signer signer(privateKey);

    size_t siglen = signer.MaxSignatureLength();
    std::string signature(siglen, 0x00);

    siglen = signer.SignMessage( prng, (const byte*)&passphrase[0], passphrase.size(), (byte*)&signature[0] );
    signature.resize(siglen);

    return signature;
}


bool verify_signature(auto publicKey, std::string passphrase, std::string signature){
    using namespace CryptoPP;

    ECDSA<ECP, SHA256>::Verifier verifier(publicKey);

    bool result = verifier.VerifyMessage( (const byte*)&passphrase[0], passphrase.size(), (const byte*)&signature[0], signature.size() );

    // Verification failure?
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


void generate_keypair(std::string passphrase){
    using namespace CryptoPP;
    
    AutoSeededRandomPool prng;

    ECDSA<ECP, SHA256>::PrivateKey privateKey;
    privateKey.Initialize( prng, ASN1::secp256r1() );

    ECDSA<ECP, SHA256>::PublicKey publicKey;
    privateKey.MakePublicKey(publicKey);
    
    std::string signature = sign_message(privateKey, passphrase);

    //bool result = verify_signature(publicKey, passphrase, signature); 
    std::string wallet = generate_wallet(signature);

    std::cout << wallet << std::endl;
}



/*
void Save(const std::string& filename, const CryptoPP::BufferedTransformation& bt)
{
    CryptoPP::FileSink file(filename.c_str());

    bt.CopyTo(file);
    file.MessageEnd();
}


void Load(const std::string& filename, std::BufferedTransformation& bt)
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
    SavePrivateKey("keys/rsa-private.key", rsaPrivate);
}


std::string generate_wallet_address (){
    const unsigned int BLOCKSIZE = 16 * 8;
    CryptoPP::SecByteBlock scratch(BLOCKSIZE);

    CryptoPP::AutoSeededRandomPool rng;

    rng.GenerateBlock(scratch, scratch.size());

    std::string s;
    CryptoPP::HexEncoder hex(new CryptoPP::StringSink(s));

    hex.Put(scratch, scratch.size());
    hex.messageEnd();

    return s;
}


auto generate_rsa_keypair (){
    CryptoPP::AutoSeededRandomPool prng;

    CryptoPP::RSA::PrivateKey rsaPrivate;
    rsaPrivate.GenerateRandomWithKeySize(prng, 3072);

    CryptoPP::RSA::PublicKey rsaPublic(rsaPrivate);

    std::string wallet = generate_wallet_address();

    save_keys(rsaPrivate, wallet);
    
    return rsaPrivate, rsaPublic;
}
*/

