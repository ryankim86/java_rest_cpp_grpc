# Java Spring App Interfacing with C++ gRPC Server
### For Job application--October 2022

## Overall Repo Structure
- UserInfoSetterService is the Java application that exposes the REST API
- GrpcCppUserInfoServer is the C++ application that stores request from the Java application into memory

## Building Applications
- Java application uses maven
- C++ application was built using Visual Studios 2022, and admittedly, portability is probably poor

## Building C++ Application
1. Use `vcpkg` to install gRPC for Windows
2. Create environment variable `VCPKG_DIR` that stores the path to your local vcpkg directory
3. Build in `Release 64-bit` Using VS Compiler
4. Resolve any missing DLLs, should be in `vcpkg` directory. (manual process, sorry!)

## Using the applications
- Launch C++ gRPC Server
- Launch Java application
- The Java application exposes a single route, `/setuser` on `localhost:8080`. To add a user, do a HTTP `POST` with the following JSON payload:
```
{
    "firstName":"Abalone", // 1 to 50 characters
    "lastName":"Shell", // 1 to 50 characters
    "dateOfBirth":"2012-04-23", // javascript date string format 
    "email":"abalone.shell@aoshell.org", // most be properly formatted
    "phoneNumber":"4087778888" // numeric characters only; only USA numbers supported
}
```
Upon success, a HTTP 204 code will be returned. Invalid parameters in the payload will result in a HTTP 400, and all other errors HTTP 500.
- Printout on the console should be visible

## Other Notes
- Java application listens on port `8080` on `localhost`
- C++ gRPC server listens on port `50051` on `localhost`
