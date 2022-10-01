package com.userinfo.UserInfoSetterService;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import io.grpc.*;

@SpringBootApplication
public class UserInfoSetterServiceApplication {
	public static void main(String[] args) {
		SpringApplication.run(UserInfoSetterServiceApplication.class, args);
	}

	@Bean
	public UserInfoClientInterface userInfoClient() {
		// construct channel and inject into client
		ManagedChannel channel = ManagedChannelBuilder.forTarget("localhost:50051").usePlaintext().build();
		return new UserInfoGrpcClient(channel);
	}
}
