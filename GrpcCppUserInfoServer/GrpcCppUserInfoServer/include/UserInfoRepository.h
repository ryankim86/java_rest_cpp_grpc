#ifndef USER_INFO_REPOSITORY_H
#define USER_INFO_REPOSITORY_H

#include <memory>
#include <unordered_set>
#include <mutex>

#include "UserInfoItem.h"

class UserInfoRepository
{
public:
	bool addUser(std::shared_ptr<UserInfoItem> userInfoItem);

private:
	std::mutex m_user_info_mutex;

	// for simplicity, assume that each added user will be unique, hence a set
	std::unordered_set<std::shared_ptr<UserInfoItem>> m_userInfo;
};

#endif // USER_INFO_REPOSITORY_H

