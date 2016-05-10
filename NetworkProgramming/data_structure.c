struct addrinfo 
{
    int ai_flags; // AI_PASSIVE, AI_CANONNAME 等。
	int ai_family; // AF_INET, AF_INET6, AF_UNSPEC
	int ai_socktype; // SOCK_STREAM, SOCK_DGRAM
	int ai_protocol; // 用 0 当作 "any"
	size_t ai_addrlen; // ai_addr 的大小，单位是 byte
	struct sockaddr *ai_addr; // struct sockaddr_in 或 _in6
	char *ai_canonname; // 典型的 hostname
	struct addrinfo *ai_next; // 链表丶下个节点
};

struct sockaddr 
{
    unsigned short sa_family; // address family, AF_xxx
	char sa_data[14]; // 14 bytes of protocol address
};

// (IPv4 only--see struct sockaddr_in6 for IPv6)
struct sockaddr_in 
{
    short int sin_family; // Address family, AF_INET
	unsigned short int sin_port; // Port number
	struct in_addr sin_addr; // Internet address
	unsigned char sin_zero[8]; // 与 struct sockaddr 相同的大小
};

// (仅限 IPv4 — Ipv6 请参考 struct in6_addr)
// Internet address (a structure for historical reasons)
struct in_addr 
{
    uint32_t s_addr; // that's a 32-bit int (4 bytes)
};

// (IPv6 only--see struct sockaddr_in and struct in_addr for IPv4)
struct sockaddr_in6 {
    u_int16_t sin6_family; // address family, AF_INET6
	u_int16_t sin6_port; // port number, Network Byte Order
	u_int32_t sin6_flowinfo; // IPv6 flow information
	struct in6_addr sin6_addr; // IPv6 address
	u_int32_t sin6_scope_id; // Scope ID
};

struct in6_addr 
{
	unsigned char s6_addr[16]; // IPv6 address
};

struct sockaddr_storage 
{
    sa_family_t ss_family; // address family
	// all this is padding, implementation specific, ignore it:
	char __ss_pad1[_SS_PAD1SIZE];
	int64_t __ss_align;
	char __ss_pad2[_SS_PAD2SIZE];
};
