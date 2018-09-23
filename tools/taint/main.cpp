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
    auto root = blocksci::Transaction("ce354852eb449f07ee5c2ff8c781a8ad76ec0cae9adf804fb7ae089d3faffed6",chain.getAccess());
    auto block = chain[root.blockHeight];
    std::cout << "block5:  "<< block.at(5) << std::endl;
    //std::cout << "block6:  "<< block.at(6).outputs() << std::endl;
    //std::cout << "block7:  "<< block.at(7).outputs() << std::endl;
    //std::cout << "block8:  "<< block.at(8).outputs() << std::endl;
    /*auto tx = block[0];
    auto output = tx.outputs()[0];
    auto value = output.getValue();
    std::cout << "Transaction:    "<< output << std::endl;
    std::cout << "Transaction:    "<< value<< std::endl;

    auto tainted = blocksci::heuristics::getPoisonTainted(output,value);
    //std::cout << "Transaction:    "<< tainted << std::endl;
    std::cout << "first out:    "<<std::get<0>(tainted[0]) << ",  second :   " << std::get<1>(tainted[0]);
    //std::co

*/



}