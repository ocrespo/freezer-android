/*
 * User_callbacks.h
 *
 *  Created on: 30 Aug 2021
 *      Author: Oscar Crespo
 */

#ifndef SRC_MODEL_USER_USER_CALLBACKS_H_
#define SRC_MODEL_USER_USER_CALLBACKS_H_

#include <string>
#include <functional>
#include <chrono>

using AddedItem_callback_t = std::function<void(const std::string&,
                                                int,
                                                int,
                                                const std::string&,
                                                const std::string&,
                                                const std::chrono::time_point<std::chrono::system_clock>&)>;
using RemovedItem_callback_t = std::function<void(const std::string&,int)>;
using UpdatedItem_callback_t = std::function<void(const std::string&,int,int,const std::string&, const std::string&)>;



#endif /* SRC_MODEL_USER_USER_CALLBACKS_H_ */
