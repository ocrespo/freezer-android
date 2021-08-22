/*
 * Model_callbacks.h
 *
 *  Created on: 2 Dec 2018
 *      Author: Oscar Crespo
 */

#ifndef SRC_MODEL_MODEL_CALLBACKS_H_
#define SRC_MODEL_MODEL_CALLBACKS_H_

#include <string>
#include <functional>

using Void_callback_t = std::function<void()>;
using Int_callback_t = std::function<void(int)>;
using AddedItem_callback_t = std::function<void(int,int,const std::string&, const std::string&, const std::string&)>;
using UpdatedItem_callback_t = std::function<void(int,int,const std::string&, const std::string&)>;


#endif /* SRC_MODEL_MODEL_CALLBACKS_H_ */
