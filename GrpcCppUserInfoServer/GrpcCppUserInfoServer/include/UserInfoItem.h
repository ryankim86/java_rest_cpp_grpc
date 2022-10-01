#ifndef USER_INFO_ITEM_H
#define USER_INFO_ITEM_H

#include <string>
#include <sstream>
#include <iomanip>

#include "UserInfoDataTypes.h"

class UserInfoItem
{
public:
	UserInfoItem(const std::string& firstName, const std::string& lastName, 
		int32_t year_of_birth, int32_t month_of_birth, int32_t day_of_birth, 
		const std::string& email, const std::string& phoneNumber, const UserInfoData::Timestamp& timestamp):
		m_firstName(firstName),
		m_lastName(lastName),
		m_yearOfBirth(year_of_birth),
		m_monthOfBirth(month_of_birth),
		m_dayOfBirth(day_of_birth),
		m_email(email),
		m_phoneNumber(phoneNumber),
		m_timestamp(timestamp)
		{ }

	UserInfoItem() = delete;

	bool isValid() const;

	// accessors
	const std::string firstName() const;
	const std::string lastName() const;
	int32_t yearOfBirth() const;
	int32_t monthOfBirth() const;
	int32_t dayOfBirth() const;
	const std::string email() const;
	const std::string phoneNumber() const;
	const UserInfoData::Timestamp timestamp() const;

	friend std::ostream& operator<<(std::ostream& os, const UserInfoItem& userInfoItem);

private:
	std::string m_firstName;
	std::string m_lastName;
	int32_t m_yearOfBirth;
	int32_t m_monthOfBirth;
	int32_t m_dayOfBirth;
	std::string m_email;
	std::string m_phoneNumber;
	UserInfoData::Timestamp m_timestamp;
};

#endif // USER_INFO_ITEM_H