#ifndef USER_INFO_SERVICE_H
#define USER_INFO_SERVICE_H

#include <memory>

#include "user_info.grpc.pb.h"
#include <grpcpp/grpcpp.h>

#include "UserInfoRepository.h"

class UserInfoService final : public UserInfo::Service
{
public:
	UserInfoService(std::unique_ptr<UserInfoRepository> userInfoRepository) : m_userRepository(std::move(userInfoRepository)) {}
	UserInfoService() = delete;

	grpc::Status SetUserInfo(grpc::ServerContext* context, const SetUserInfoRequest* request, SetUserInfoResponse* response) override;

private:
	std::unique_ptr<UserInfoRepository> m_userRepository;
};

#endif // USER_INFO_SERVICE_H