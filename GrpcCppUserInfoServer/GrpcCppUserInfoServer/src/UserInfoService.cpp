#include "UserInfoDataTypes.h"
#include "UserInfoItem.h"
#include "UserInfoService.h"

using namespace grpc;

Status UserInfoService::SetUserInfo(ServerContext* context, const SetUserInfoRequest* request, SetUserInfoResponse* response)
{
	UserInfoData::Timestamp timestamp { request->timestamp().seconds(), request->timestamp().nanos() };

	std::shared_ptr<UserInfoItem> userInfoItem = std::make_shared<UserInfoItem>(request->first_name(), 
																				request->last_name(), 
																				request->date_of_birth().year(),
																				request->date_of_birth().month(),
																				request->date_of_birth().day(),
																				request->email(),
																				request->phone_number(),
																				timestamp);
	if (!userInfoItem->isValid())
	{
		return Status(StatusCode::INVALID_ARGUMENT, "Invalid User Information was provided");
	}
		
	return m_userRepository->addUser(userInfoItem) ? Status::OK : Status(StatusCode::ABORTED, "Failed to add User");
}