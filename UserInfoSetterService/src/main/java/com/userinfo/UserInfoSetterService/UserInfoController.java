package com.userinfo.UserInfoSetterService;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.BindingResult;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import javax.validation.Valid;


@RestController
public class UserInfoController {
    private final UserInfoClientInterface userInfoClient;

    @Autowired
    public UserInfoController(UserInfoClientInterface userInfoClient) {
        this.userInfoClient = userInfoClient;
    }

    @PostMapping("/setuser")
    ResponseEntity setUserInfo(@RequestBody @Valid UserInfo userInfo, BindingResult bindingResult) {
        if (bindingResult.hasErrors()) {
            return new ResponseEntity(HttpStatus.BAD_REQUEST);
        }

        UserInfoClientCommandStatus status = userInfoClient.setUserInfo(userInfo);
        switch (status)
        {
            case OK:
                return new ResponseEntity(HttpStatus.NO_CONTENT);
            case INVALID_ARGUMENT:
                return new ResponseEntity(HttpStatus.BAD_REQUEST);
            default:
                return new ResponseEntity(HttpStatus.INTERNAL_SERVER_ERROR);
        }
    }
}
