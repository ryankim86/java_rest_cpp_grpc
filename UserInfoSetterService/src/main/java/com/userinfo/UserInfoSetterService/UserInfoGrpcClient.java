package com.userinfo.UserInfoSetterService;

import io.grpc.*;
import com.userinfoservice.grpc.UserInfoGrpc;
import com.userinfoservice.grpc.UserInfoOuterClass.Date;
import com.userinfoservice.grpc.UserInfoOuterClass.SetUserInfoRequest;
import com.google.protobuf.Timestamp;

import java.time.LocalDate;

public class UserInfoGrpcClient implements UserInfoClientInterface {
    private final UserInfoGrpc.UserInfoBlockingStub blockingStub;

    public UserInfoGrpcClient(ManagedChannel channel) {
        blockingStub = UserInfoGrpc.newBlockingStub(channel);
    }

    public UserInfoClientCommandStatus setUserInfo(UserInfo userInfo) {
        SetUserInfoRequest.Builder requestBuilder = SetUserInfoRequest.newBuilder();
        requestBuilder.setFirstName(userInfo.getFirstName());
        requestBuilder.setLastName(userInfo.getLastName());

        LocalDate localDate = userInfo.getDateOfBirth();
        if (localDate != null) {
            Date.Builder dateBuilder = Date.newBuilder();
            dateBuilder.setYear(userInfo.getDateOfBirth().getYear());
            dateBuilder.setMonth(userInfo.getDateOfBirth().getMonthValue());
            dateBuilder.setDay(userInfo.getDateOfBirth().getDayOfMonth());
            requestBuilder.setDateOfBirth(dateBuilder.build());
        }

        requestBuilder.setEmail(userInfo.getEmail());
        requestBuilder.setPhoneNumber(userInfo.getPhoneNumber());

        // calculate and add timestamp
        long msSinceUTCEpoch = System.currentTimeMillis();
        Timestamp timestamp = Timestamp.newBuilder().setSeconds(msSinceUTCEpoch / 1000)
                .setNanos((int) ((msSinceUTCEpoch % 1000) * 1000000)).build();
        requestBuilder.setTimestamp(timestamp);

        SetUserInfoRequest request = requestBuilder.build();
        try {
            blockingStub.setUserInfo(request); // response is empty body
        }
        catch (StatusRuntimeException sre) {
            Status callStatus = sre.getStatus();
            return UserInfoClientCommandStatus.values()[callStatus.getCode().value()];
        }

        return UserInfoClientCommandStatus.OK;
    }
}
