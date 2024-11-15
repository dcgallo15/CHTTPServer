# HTTP Server in C

## Goals

- Have a client program that can send a HTML file to the server when given a path to it.\
- Implement a server program that stores a database of HTML files and can serve them on demand.\
- The server must be able to accept HTTP requests from the browser and server specific HTML files.\
  - The server has to run on multiple ports.\
  - The server will give the correct file or 404 response depending on the address of the request.
    - e.g: localhost:80/index.html -> index.html on the server

 ## Usage

```
client.exe portno FILE_PATH
```

```
server.exe portno
```
