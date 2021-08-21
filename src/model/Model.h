/*
 * Model.h
 *
 *  Created on: 10 Dec 2017
 *      Author: Oscar Crespo
 */

#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include "observer/Observable.h"
#include "events/Event.h"

#include "Model_types.h"
#include "Model_callbacks.h"

namespace freezer{
	class Freezer;
}

class Model : public ocutils::Observable<EModelEvents,ocutils::Event*> {
public:
	Model();
	virtual ~Model();

	void registerItemAdded(const AddedItem_callback_t& callback);
	void registerItemRemoved(const Int_callback_t& callback);
	void registerNextId(const Int_callback_t& callback);
	void registerNumDrawers(const Int_callback_t& callback);
    void registerItemInfo(const AddedItem_callback_t& callback);
    void registerItemUpdated(const UpdatedItem_callback_t& callback);
    void registerInitFinished(const Void_callback_t& callback);


	void requestInitialInfo();
	void addItem(int drawer,const std::string& name, const std::string& description);
    void modifyItem(int id, int drawer,const std::string& name, const std::string& description);
	void removeItem(int id);
	void requestItemInfo(int id);

protected:


private:

	void save(const std::string& path);
	void load(const std::string& path);

	freezer::Freezer *freezer;

};

#endif /* SRC_MODEL_MODEL_H_ */
