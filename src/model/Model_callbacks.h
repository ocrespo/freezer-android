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
#include <vector>


#include "user/freezer/Item.h"

using Void_callback_t = std::function<void()>;
using Int_callback_t = std::function<void(const std::string&,int)>;
using AllItems_callback_t = std::function<void(std::vector<freezer::SItem>&&)>;


#endif /* SRC_MODEL_MODEL_CALLBACKS_H_ */
