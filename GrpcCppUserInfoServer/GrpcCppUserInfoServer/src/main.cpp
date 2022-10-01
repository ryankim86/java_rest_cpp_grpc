#include <memory>
#include <future>
#include <signal.h>

#include "UserInfoRepository.h"
#include "UserInfoService.h"
#include "GrpcServerRunner.h"

std::promise<void> shutdownSignalPromise;

void signalHandler(int param)
{
	shutdownSignalPromise.set_value();
}

int runUserInfoService()
{
	std::unique_ptr<UserInfoRepository> userInfoRepository = std::make_unique<UserInfoRepository>();
	std::unique_ptr<UserInfoService> service = std::make_unique<UserInfoService>(std::move(userInfoRepository));

	std::unique_ptr<GrpcServerRunner<UserInfo::Service>> serverRunner = std::make_unique<GrpcServerRunner<UserInfo::Service>>(std::move(service));
	
	if (!serverRunner->start())
	{
		return 1;
	}

	std::future<void> shutdownFuture = shutdownSignalPromise.get_future();
	shutdownFuture.wait();

	if (!serverRunner->stop())
	{
		return 1;
	}
	
	return 0;
}

int main()
{
	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);

	return runUserInfoService();
}
