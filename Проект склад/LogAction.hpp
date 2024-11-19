/** @file LogAction.hpp
 *  @brief An enum class for the product's log actions
 *  
 *  @author Georgi Paleykov, 0MI0800195, Computer Science, Group 4
 */
#include <iostream>

/**
 * @class LogAction
 */
enum Action
{
    ADDED = 1,   //!< If the product is added
    REMOVED = 2, //!< If the product is removed
    CLEARED = 3  //!< If the product is cleared because it has expired
};