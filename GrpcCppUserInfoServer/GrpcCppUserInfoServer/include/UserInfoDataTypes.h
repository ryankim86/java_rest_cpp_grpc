#ifndef USER_INFO_DATA_TYPES_H
#define USER_INFO_DATA_TYPES_H

#include <iostream>
#include <cstdint>

namespace UserInfoData {
	// represents time seconds + nanoseconds since UTC epoch
	struct Timestamp
	{
		int64_t seconds;
		int32_t nanoseconds;

		friend std::ostream& operator<<(std::ostream& os, const Timestamp& timestamp)
		{
			os << timestamp.seconds << ", " << timestamp.nanoseconds;
			return os;
		}
	};
}

#endif // USER_INFO_DATA_TYPES_H
