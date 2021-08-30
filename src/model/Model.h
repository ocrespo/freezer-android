/*
 * Model.h
 *
 *  Created on: 10 Dec 2017
 *      Author: Oscar Crespo
 */

#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <memory>

#include "observer/Observer.h"
#include "observer/Observable.h"
#include "events/Event.h"

#include "Model_types.h"
#include "Model_callbacks.h"

#include "user/User_callbacks.h"


namespace freezer{
	class User;
}

class Model : public ocutils::Observable<EModelEvents,ocutils::Event*>,
              public ocutils::Observer{
public:
	Model();
	virtual ~Model();

	void registerItemAdded(const AddedItem_callback_t& callback);
	void registerItemRemoved(const RemovedItem_callback_t& callback);
    void registerItemUpdated(const UpdatedItem_callback_t& callback);
	void registerNextId(const Int_callback_t& callback);
	void registerNumDrawers(const Int_callback_t& callback);
    void registerAllItem(const AllItems_callback_t& callback);
    void registerInitFinished(const Void_callback_t& callback);


	void requestInitialInfo();
	void addItem(const std::string& freezer,
	        int drawer,
	        const std::string& name,
	        const std::string& description);
    void modifyItem(const std::string& freezer,
            int id,
            int drawer,
            const std::string& name,
            const std::string& description);
	void removeItem(const std::string& freezer,
	        int id);

protected:


private:

	void notifyNextId(const std::string& freezer);
	void notifyNumDrawers(const std::string& freezer);

	std::unique_ptr<freezer::User> user;

};

#endif /* SRC_MODEL_MODEL_H_ */
