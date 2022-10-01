#include "UserInfoItem.h"

using namespace UserInfoData;

bool UserInfoItem::isValid() const
{
	/* 
	TODO: determine whether construction was valid
		1. Names do not contain special characters or numbers except for - and '			
		2. 1900 <= year <= 2022
		3. 1 <= month <= 12
		4. 1 <= day <= # of days in month (28-31). Also check for leap-year
		5. email is of format [a-zA-Z0-9+_\.-]+@[a-zA-Z0-9+_.-]+ (roughly)
		6. phone number is a string of 10-11 numbers (depends on if we include country code)
	*/

	return true;
}

const std::string UserInfoItem::firstName() const
{
	return m_firstName;
}

const std::string UserInfoItem::lastName() const
{
	return m_lastName;
}

int32_t UserInfoItem::yearOfBirth() const
{
	return m_yearOfBirth;
}

int32_t UserInfoItem::monthOfBirth() const
{
	return m_monthOfBirth;
}

int32_t UserInfoItem::dayOfBirth() const
{
	return m_dayOfBirth;
}

const std::string UserInfoItem::email() const
{
	return m_email;
}

const std::string UserInfoItem::phoneNumber() const
{
	return m_phoneNumber;
}

const Timestamp UserInfoItem::timestamp() const
{
	return m_timestamp;
}

std::ostream& operator<<(std::ostream& os, const UserInfoItem& userInfoItem)
{
	std::stringstream ss;
	ss << "Name: " << userInfoItem.firstName() << " " << userInfoItem.lastName() << std::endl;
	ss << "DOB (MM-DD-YYYY): " << std::setw(2) << std::setfill('0') << userInfoItem.monthOfBirth() << "-"
		<< std::setw(2) << std::setfill('0') << userInfoItem.dayOfBirth() << "-" << userInfoItem.yearOfBirth() << std::endl;
	ss << "Email: " << userInfoItem.email() << std::endl;
	ss << "Phone Number: " << userInfoItem.phoneNumber() << std::endl;
	ss << "Timestamp (s, ns since UTC epoch): " << userInfoItem.timestamp() << std::endl;
	os << ss.str();
	return os;
}