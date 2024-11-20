# 351-echo server
Using TCP, create a server that echoes all messages it receives, line by line.

If you send "abcd"(newline), you should get back "abcd"(newline). Then type another line, the same thing. As long as the connection stays alive. 

Implement a "-p" argument that specifies the port it listens to.

It only needs to accept one connection at a time, but it must accept new connections after one is terminated.

Test this with telnet; you'll probably need to install it.

# Example Usage
There are two ways to start the server side socket:

1. use the default port 46645: ./echoserver
2. use the specific port: ./echoserver -p <port number>

To test the server side socket, run "telnet" in the another terminal. "telnet 127.0.0.1 <port number>"

e.g.) telnet 127.0.0.1 46645
