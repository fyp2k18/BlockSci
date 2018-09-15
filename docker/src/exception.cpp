//
//  exception.cpp
//  bitcoinapi
//
//  Created by Harry Kalodner on 4/15/18.
//

#include <blocksci/exception.hpp>

namespace blocksci {
    ReorgException::~ReorgException() = default;
    InvalidAddressException::~InvalidAddressException() = default;
    
} // namespace blocksci
