#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/time.hpp>
#include <eosiolib/print.hpp>
// using namespace std;
using namespace eosio;

class [[eosio::contract("tdrecord")]] tdrecord :  public eosio::contract {
  public:
      // using contract::contract;
      tdrecord(eosio::name receiver, eosio::name code, eosio::datastream<const char*> ds):eosio::contract(receiver, code, ds), data_np(receiver, code.value), data_noja(receiver, code.value), data_nbd(receiver, code.value), data_nplog(receiver, code.value){}
      //user - read only
      [[eosio::action]] void nptotal();
      [[eosio::action]] void nphistory();
      [[eosio::action]] void nbdtotal();
      [[eosio::action]] void nojatotal();
      //traveldnation only
      [[eosio::action]] void upsertnp(eosio::name s, std::string newval, std::string d);
      [[eosio::action]] void upsertnplog(eosio::name s, uint32_t cdate, std::string userid, std::string newval);
      [[eosio::action]] void upsertnoja(eosio::name s, std::string newval, std::string d);
      [[eosio::action]] void upsertnbd(eosio::name s, std::string newval, std::string d);
  private: 
    struct  [[eosio::table]] np{
      name key;
      std::string c_nbd;
       std::string c_date;
      uint64_t primary_key() const { return key.value;}        
    };
    struct  [[eosio::table]] noja{
      name key;
      std::string c_nbd;
      std::string c_date;
      uint64_t primary_key() const { return key.value;}        
    };
    struct  [[eosio::table]] nbd{
      name key;
      std::string c_nbd;
      std::string c_date;
      uint64_t primary_key() const { return key.value;}        
    };
    struct  [[eosio::table]] nplog{
      uint64_t key;
      uint32_t cdate;  //20190409
      // time_point c_date;
      std::string user_id;
      std::string np_value;
      
      uint64_t primary_key() const { return key; }
      uint64_t by_cdate() const {return cdate; }
    };
    typedef eosio::multi_index<"np"_n, np> np_datastore;
    typedef eosio::multi_index<"noja"_n, noja> noja_datastore;
    typedef eosio::multi_index<"nbd"_n, nbd> nbd_datastore;
    typedef eosio::multi_index<"nplog"_n, nplog, eosio::indexed_by<"cdate"_n, eosio::const_mem_fun<nplog, uint64_t, &nplog::by_cdate>>> nplog_datastore;

    np_datastore data_np;
    noja_datastore data_noja;
    nbd_datastore data_nbd;
    nplog_datastore data_nplog;
};  


