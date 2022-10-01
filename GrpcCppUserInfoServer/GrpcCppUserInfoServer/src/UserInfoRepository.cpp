#include <iostream>

#include "UserInfoRepository.h"

// returns true if operation successful
// TODO: Update a user that already exists
bool UserInfoRepository::addUser(std::shared_ptr<UserInfoItem> userInfoItem)
{
	std::lock_guard<std::mutex> lock(m_user_info_mutex);

	if (!userInfoItem->isValid())
	{
		return false;
	}

	auto insertResult = m_userInfo.insert(std::move(userInfoItem));

	if (insertResult.second)
	{
		std::cout << "Succesfully Added User Information--" << std::endl;
		std::cout << *(*(insertResult.first));
		std::cout << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}