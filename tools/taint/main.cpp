//
// Created by uthpala on 9/20/18.
//

#include <blocksci/blocksci.hpp>
#include <blocksci/address/address.hpp>
#include <blocksci/cluster/cluster_manager.hpp>
#include <blocksci/chain/transaction.hpp>
#include <blocksci/heuristics/taint.hpp>
#include <blocksci/chain/blockchain.hpp>

//using namespace blocksci::heuristics;

int main(int argc, const char * argv[]) {
    blocksci::Blockchain chain("/root/bitcoin-data");
    //std::cout<<"test";

    //auto root = chain.tx_with_hash('e12670b7efc7b6076df4fec69c7ff13f4c49531304b5fa909f3097be4a4ff3f1');
    auto root = blocksci::Transaction("e12670b7efc7b6076df4fec69c7ff13f4c49531304b5fa909f3097be4a4ff3f1",chain.getAccess());
    auto block = chain[root.blockHeight];
  ///  for (&tx: block.getTransact)
    //auto tx = block[1];
    //auto output = tx.outputs()[0];
    //auto val = tx.outputs()[0].getValue();
    //std::cout << "Output: " << output << std::endl;
    //std::cout << "Output: " << val << std::endl;
    //auto tainted = blocksci::heuristics::getPoisonTainted(output,val);
    //std::cout << "first out:    "<<std::get<0>(tainted[0]) << ",  second :   " << std::get<1>(tainted[0]);
    //std::cout << "Taints: " << tainted << std::endl;
    //for(int i=0;i< tainted.size();i++){
      //std::cout << "Taints: " << tainted[0]<< std::endl;

    //}





    //RANGES_FOR (auto &taints, tainted){
      //  std::cout << "Taints: " << taints << std::endl;


    //}
    //std::cout << "Taints: " << taints << std::endl;
    //auto test2 = blocksci::outputs(chain[test]);
   // auto c = root.outputs()[0].getAddress();
    //std::cout << "Output: " << root.outputs()[0] << std::endl;

    //auto test = root.blocksci::Transaction.getTransactions();
    //for (auto &tx : test2.numTxes){
      //std::cout<<root.outputs()[0];
    //}





}