#define _GNU_SOURCE // sendmmsg

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>

#include "common.h"


struct state {
	struct net_addr *target_addr;
	int packets_in_buf;
	const char *payload;
	int payload_sz;
	int src_port;
};

void thread_loop(void *userdata) {
	struct state *state = userdata;

	struct mmsghdr *messages = calloc(state->packets_in_buf, sizeof(struct mmsghdr));
	struct iovec *iovecs = calloc(state->packets_in_buf, sizeof(struct iovec));

	int fd = net_connect_udp(state->target_addr, state->src_port);

	int i;
	for (i = 0; i < state->packets_in_buf; i++) {
		struct iovec *iovec = &iovecs[i];
		struct mmsghdr *msg = &messages[i];

		msg->msg_hdr.msg_iov = iovec;
		msg->msg_hdr.msg_iovlen = 1;

		iovec->iov_base = (void*)state->payload;
		iovec->iov_len = state->payload_sz;
	}
	
	while (1) {
		int r = sendmmsg(fd, messages, state->packets_in_buf, 0);
		if (r <= 0) {
			if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
				continue;
			}

			if (errno == ECONNREFUSED) {
				continue;
			}
			PFATAL("sendmmsg()");
		}
		int i, bytes = 0;
		for (i = 0; i < r; i++) {
			struct mmsghdr *msg = &messages[i];
			/* char *buf = msg->msg_hdr.msg_iov->iov_base; */
			int len = msg->msg_len;
			msg->msg_hdr.msg_flags = 0;
			msg->msg_len = 0;
			bytes += len;
		}
	}
}
int gloal_sockfd;
int main(int argc, const char *argv[])
{
	int packets_in_buf = 1024;
	const char *payload = (const char[32]){0};
	int payload_sz = 32;

	if (argc == 1) {
		FATAL("Usage: %s [target ip:port] [target ...]", argv[0]);
	}

	struct net_addr *target_addrs = calloc(argc-1, sizeof(struct net_addr));
	int thread_num = argc - 1;

	int t;
	for (t = 0; t < thread_num; t++) {
		const char *target_addr_str = argv[t+1];
		parse_addr(&target_addrs[t], target_addr_str);

		fprintf(stderr, "[*] Sending to %s, send buffer %i packets\n",
			addr_to_str(&target_addrs[t]), packets_in_buf);
	}

	 		global_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
           if (sockfd == -1) {
               perror("socket()");
               exit(EXIT_FAILURE);
           }

           addr.sin_family = AF_INET;
           addr.sin_addr.s_addr = htonl(inet_addr("172.17.0.4");
           addr.sin_port = htons(9000);

           memset(msg1, 0, sizeof(msg1));
           msg1[0].iov_base = "one";
           msg1[0].iov_len = 3;
           msg1[1].iov_base = "two";
           msg1[1].iov_len = 3;

           memset(&msg2, 0, sizeof(msg2));
           msg2.iov_base = "three";
           msg2.iov_len = 5;

           memset(msg, 0, sizeof(msg));
           msg[0].msg_hdr.msg_iov = msg1;
           msg[0].msg_hdr.msg_iovlen = 2;

           msg[1].msg_hdr.msg_iov = &msg2;
           msg[1].msg_hdr.msg_iovlen = 1;

           //retval = sendmmsg(sockfd, msg, 2, 0);
           if (retval == -1)
               perror("sendmmsg()");
           else
               printf("%d messages sent\n", retval);



	struct net_addr *target_addrs = calloc(argc-1, sizeof(struct net_addr));
	int thread_num = argc - 1;

	int t;
	for (t = 0; t < thread_num; t++) {
		const char *target_addr_str = argv[t+1];
		parse_addr(&target_addrs[t], target_addr_str);

		fprintf(stderr, "[*] Sending to %s, send buffer %i packets\n",
			addr_to_str(&target_addrs[t]), packets_in_buf);

	struct state *array_of_states = calloc(thread_num, sizeof(struct state));

	for (t = 0; t < thread_num; t++) {
		struct state *state = &array_of_states[t];
		state->target_addr = &target_addrs[t];
		state->packets_in_buf = packets_in_buf;
		state->payload = payload;
		state->payload_sz = payload_sz;
		state->src_port = 11404;
		thread_spawn(thread_loop, state);
	}

	while (1) {
		struct timeval timeout =
			NSEC_TIMEVAL(MSEC_NSEC(1000UL));
		while (1) {
			int r = select(0, NULL, NULL, NULL, &timeout);
			if (r != 0) {
				continue;
			}
			if (TIMEVAL_NSEC(&timeout) == 0) {
				break;
			}
		}
		// pass
	}
	return 0;
}
