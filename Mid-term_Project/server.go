package main

import (
	"context"
	"flag"
	"fmt"
	"log"
	"net"
	"strconv"

	"google.golang.org/grpc"
	pb "google.golang.org/grpc/examples/helloworld/helloworld"
)

type server struct {
	pb.UnimplementedGreeterServer
	port int
}

func (s *server) SayHello(ctx context.Context, in *pb.HelloRequest) (*pb.HelloReply, error) {
	log.Printf("Received request with name: %s", in.Name)
	reply := &pb.HelloReply{Message: fmt.Sprintf("Hello %s (server port: %d)", in.Name, s.port)}
	log.Printf("Sending response: %s", reply.Message)
	return reply, nil
}

func getPortFromListener(lis net.Listener) int {
	address := lis.Addr().String()
	_, portStr, _ := net.SplitHostPort(address)
	port, _ := strconv.Atoi(portStr)
	return port
}

func main() {
	port := flag.Int("port", 0, "port number")
	flag.Parse()
	log.Printf("start server on port %d", *port)
	lis, err := net.Listen("tcp", fmt.Sprintf(":%d", *port))
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}
	s := grpc.NewServer()
	server := &server{port: *port}
	pb.RegisterGreeterServer(s, server)
	log.Printf("Server is running on port %d...", *port)
	if err := s.Serve(lis); err != nil {
		log.Fatalf("failed to serve: %v", err)
	}
}
