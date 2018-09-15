//
//  cluster.cpp
//  blocksci
//
//  Created by Harry Kalodner on 7/6/17.
//
//

#include <blocksci/cluster/cluster.hpp>
#include <blocksci/cluster/cluster_manager.hpp>

#include <blocksci/address/dedup_address.hpp>
#include <blocksci/address/equiv_address.hpp>
#include <blocksci/chain/output.hpp>
#include <blocksci/chain/inout_pointer.hpp>
#include <blocksci/chain/transaction.hpp>
#include <blocksci/chain/algorithms.hpp>
#include <blocksci/core/address_info.hpp>
#include <blocksci/index/address_index.hpp>

namespace blocksci {
    
    ranges::any_view<Address> Cluster::getAddresses() const {
        auto &addressIndex = clusterAccess.access.getAddressIndex();
        return getPossibleAddresses() | ranges::view::filter([&addressIndex](const Address &address) {
            return addressIndex.checkIfTopLevel(address);
        });
    }

    ranges::optional<TaggedCluster> Cluster::getTagged(const std::unordered_map<Address, std::string> &tags) const {
        bool isEmpty = [&]() {
            auto addresses = taggedAddresses(tags);
            RANGES_FOR(auto tagged, addresses) {
                return true;
            }
            return false;
        }();
        if (isEmpty) {
            return TaggedCluster{*this, taggedAddresses(tags)};
        } else {
            return ranges::nullopt;
        }
    }
    
    ranges::optional<TaggedCluster> Cluster::getTaggedUnsafe(const std::unordered_map<blocksci::Address, std::string> &tags) const {
        bool isEmpty = [&]() {
            auto addresses = taggedAddressesUnsafe(tags);
            RANGES_FOR(auto tagged, addresses) {
                return true;
            }
            return false;
        }();
        if (isEmpty) {
            return TaggedCluster{*this, taggedAddresses(tags)};
        } else {
            return ranges::nullopt;
        }
    }
    
    uint32_t Cluster::countOfType(AddressType::Enum type) const {
        auto dedupSearchType = dedupType(type);
        uint32_t count = 0;
        for (auto &address : clusterAccess.getClusterScripts(clusterNum)) {
            if (address.type == dedupSearchType) {
                auto searchAddress = Address{address.scriptNum, type, clusterAccess.access};
                if (clusterAccess.access.getAddressIndex().checkIfTopLevel(searchAddress)) {
                    ++count;
                }
            }
        }
        return count;
    }

    ranges::any_view<Output> Cluster::getOutputs() const {
        return blocksci::outputs(getOutputPointers(), clusterAccess.access);
    }
    
    std::vector<blocksci::Input> Cluster::getInputs() const {
        auto pointers = getOutputPointers() | ranges::to_vector;
        return blocksci::getInputs(pointers, clusterAccess.access);
    }
    
    std::vector<blocksci::Transaction> Cluster::getTransactions() const {
        auto pointers = getOutputPointers() | ranges::to_vector;
        return blocksci::getTransactions(pointers, clusterAccess.access);
    }
    
    std::vector<blocksci::Transaction> Cluster::getOutputTransactions() const {
        auto pointers = getOutputPointers() | ranges::to_vector;
        return blocksci::getOutputTransactions(pointers, clusterAccess.access);
    }
    
    std::vector<blocksci::Transaction> Cluster::getInputTransactions() const {
        auto pointers = getOutputPointers() | ranges::to_vector;
        return blocksci::getInputTransactions(pointers, clusterAccess.access);
    }
}


