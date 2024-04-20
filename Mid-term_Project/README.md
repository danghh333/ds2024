# Load balancer to RPC based service

## _Group 6 - Distributed System Course - Data Science_

## Team members:

- Phạm Hải Nam (BI12-307)
- Lê Mậu Minh Phúc (BI12-351)
- Đoàn Hữu Thành (BI12-418)
- Hoàng Hà Đăng (BI12-077)
- Nguyễn Đức Thành (BI12-420)

## Overview:

This project focuses on implementing a server-side load balancing to a simple gRPC deployment, using NGINX as the load balancer.

## Definition:

*- Load Balancer:* a device or software that distributes network or application traffic across multiple servers. Its primary goal is to increase the capacity and reliability of applications by distributing the load among multiple servers, thereby ensuring no single server becomes overwhelmed.

\- *RPC (Remote Procedure Call)*: a protocol or a technique that enables a program on one computer (called the client) to execute code on another computer (the server), allowing developers to call functions on remote servers as if they were local to the client machine.

## Tools and framework:

*- Go (Programming language)*: Known for its simplicity and efficiency. It\'s often chosen for load balancing gRPC services with NGINX due to its lightweight concurrency model.

*- NGINX (Load balancer)*: Often used as a reverse proxy and load balancer, NGINX is lightweight and can efficiently handle a large number of concurrent connections. It's configurable for different load
balancing methods.

*- gRPC (RPC framework)*: Supported by Google, gRPC is a modern open source high performance Remote Procedure Call (RPC) framework that can run in any environment. gRPC uses HTTP/2, enabling bidirectional streaming and making it more efficient than traditional HTTP.

## Architecture (design explanation)
**Flow  gRPC client to a gRPC server**

![alt text](https://i.postimg.cc/J44nfGps/2.jpg)

By making a call to the server, the gRPC client invokes the client code generated by gRPC tooling at build time through encoding and decoding, which results in a generated client code called "client stub". gRPC encodes the data passed to the client stub into Protocol Buffers and send the data into the low-level transport layer. Afterward, the data are sent over the network as a stream of HTTP/2 data frames. In the gRPC server, the transport layer receives the packets, decodes and invokes the server application. Next, the result returns from the server application, gets encoded into Protocol Buffers and gets sent to the transport layer. The client side is then receives the packets, decodes and sends the result to the client application.

**Overall architecture**

![alt text](https://i.postimg.cc/xdFq5YvX/1.jpg)

This project deploys the gRPC framework to create a identical backend servers and a number of clients. The load balancer distributes the RPC call to one of the available backend servers. In distributing gRPC clients and servers equally through load balancing, the goal is to ensure that client requests are evenly spread across all available servers. This helps in optimizing performance and reliability. NGINX load balance directs incoming requests to the most suitable server based on various factors like server health or proximity. This setup is good for scaling as servers can be added or removed without impacting the client operations and requests, thus improving resource utilization and maintaining high availability in distributed systems.
## Installation
1. Install Git: If you haven\'t already installed Git on your Ubuntu system, you can do so by opening a terminal and running the following command:

```sh
sudo apt update
sudo apt install git
```
2.  *Clone the Repository:* Once Git is installed, you can clone the repository using the git clone command. Navigate to the directory where you want to download the repository and run:

```sh
git clone https://github.com/danghh333/FinalDS
```

3.  Install Go:

```sh
sudo apt install golang
#Check for go version
go version
```
Set up the Go workspace by defining the GOPATH environment variable:

```sh
export GOPATH=\$HOME/go

source \~/.bashrc #apply the changes to your current session
```
4.  Install NGINX:
```sh
sudo apt install nginx
```
(Optional) If you want NGINX to start automatically whenever your system boots up, enable with:
```sh
sudo systemctl enable nginx
```
Check NGINX status:

```sh
sudo systemctl status nginx
```
Adjust Firewall Settings (if necessary): If you have a firewall enabled on your server, you may need to allow traffic on port 80 (HTTP) and/or port 443 (HTTPS) to access NGINX:

```sh
sudo ufw allow \'NGINX Full\'
```
Verify NGINX installation by going to [ttp://localhost/](ttp://localhost/).


5.  Manage NGINX

To stop NGINX:

```sh
sudo systemctl stop nginx
```
To start NGINX when it is stopped:
```sh
sudo systemctl start nginx
```
To restart NGINX (when changing configuration files):
```sh
sudo systemctl restart nginx
```
To reload NGINX without dropping connections (also after configuration changes):
```sh
sudo systemctl reload nginx
```
To enable NGINX to start at boot:
```sh
sudo systemctl enable nginx
```
To disable NGINX from starting at boot:
```sh
sudo systemctl disable nginx
```
## Config NGINX for gRPC

Navigate to the directory "/etc/nginx/" and open up the nginx.conf file

Paste the following configs into the file:
```sh
worker_processes  1;

error_log  /var/log/nginx/error.log;

events {
    worker_connections  10;
}

http {
    access_log  /var/log/nginx/access.log;

    upstream grpc_servers {
        server 0.0.0.0:50051;
        server 0.0.0.0:50052;
    }

    server {
        listen       8080 http2;

        location / {
            grpc_pass grpc://grpc_servers;
        }
    }
}
```
Save the file and reload NGINX in the terminal:
```sh
sudo systemctl enable nginx
```
## Setting up

To setup the first gRPC server: Open up the terminal, navigate to FinalDS Github repository:
```sh
make server1
```
To setup the second gRPC server: Open up a new terminal, navigate to FinalDS Github repository:
```sh
make server2
```
To setup the client: Open up a new terminal, navigate to FinalDS Github repository:
```sh
make client
```
By running the make client more than 2 times, the requests should appear equally on both server1 and server 2 terminals. Thus the output should be:
```sh
go run client.go -port 8080
2024/04/20 08:51:30 The response: Hello world (server port: 50051)
```
or
```sh
go run client.go -port 8080
2024/04/20 08:51:30 The response: Hello world (server port: 50052)
```
## *Acknowledgements*

[gRPC Framework](https://grpc.io/)
[NGINX Load balancer](https://www.nginx.com/)
[Load balancing gRPC service with NGINX](https://dev.to/techschoolguru/load-balancing-grpc-service-with-nginx-3fio#install-nginx)
