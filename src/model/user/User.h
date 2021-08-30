/*
 * User.h
 *
 */

#ifndef SRC_MODEL_USER_USER_H_
#define SRC_MODEL_USER_USER_H_

#include <unordered_map>
#include <string>

#include "observer/Observable.h"
#include "events/Event.h"


#include "freezer/Freezer.h"

#include "User_types.h"
#include "User_callbacks.h"

namespace freezer {


class User: public ocutils::Observable<EUserEvents,ocutils::Event*> {
public:
	User();
	virtual ~User();

	void registerItemAdded(int obs_key, const AddedItem_callback_t& callback) noexcept;
	void registerItemRemoved(int obs_key, const RemovedItem_callback_t& callback) noexcept;
	void registerItemUpdated(int obs_key, const UpdatedItem_callback_t& callback) noexcept;

	int addItem(const std::string& freezer_name,
	        int drawer,
	        const std::string& name,
	        const std::string& description);

	bool removeItem(const std::string& freezer_name,
	            int id);

	bool editItem(const std::string& freezer_name,
	                int id,
	                int drawer,
	                const std::string& name,
	                const std::string& description);

	int getNextId(const std::string& freezer_name);
    int getNumDrawers(const std::string& freezer_name);

	std::vector<SItem> getAllItem();
	std::vector<std::string> getFreezers();

protected:


private:

	bool doFreezer(const std::string freezer_name,
	        std::function<bool(freezer::Freezer& freezer)> call);

	std::string name;


	std::unordered_map<std::string,freezer::Freezer> freezers;


};

}

#endif /* SRC_MODEL_USER_USER_H_ */
