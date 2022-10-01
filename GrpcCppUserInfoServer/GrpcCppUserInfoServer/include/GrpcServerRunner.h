#include <memory>
#include <future>
#include <thread>

#include <grpcpp/grpcpp.h>

template <typename GrpcService>
class GrpcServerRunner
{
public:
	GrpcServerRunner(std::unique_ptr<GrpcService> service) : m_service(std::move(service)) {};
	GrpcServerRunner() = delete;

	bool start()
	{
		if (m_serverThread.joinable())
		{
			std::cout << "gRPC Server already running" << std::endl;
			return false;
		}

		try
		{
			m_serverThread = std::thread(&GrpcServerRunner::runImpl, this);
			return true;
		}
		catch (const std::system_error& se)
		{
			std::cout << "failed to start gRPC server" << std::endl;
			return false;
		}
	}

	bool stop()
	{
		try
		{
			m_shutdownPromise.set_value();
		}
		catch (std::future_error& fe)
		{
			std::cout << "failed to stop gRPC server" << std::endl;
			return false;
		}

		try
		{
			m_serverThread.join();
		}
		catch (const std::system_error& se)
		{
			std::cout << "Unable to cleanup gRPC server thread" << std::endl;
			return false;
		}

		return true;
	}

private:
	void runImpl()
	{
		grpc::ServerBuilder builder;
		builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
		builder.RegisterService(m_service.get());

		std::unique_ptr<grpc::Server> server = builder.BuildAndStart();

		std::future<void> shutdownFuture = m_shutdownPromise.get_future();
		shutdownFuture.wait();

		server->Shutdown();
	}

	std::promise<void> m_shutdownPromise;
	std::unique_ptr<GrpcService> m_service;
	std::thread m_serverThread;
};
