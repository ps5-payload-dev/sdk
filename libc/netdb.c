/* Copyright (C) 2024 John Törnblom

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING. If not, see
<http://www.gnu.org/licenses/>.  */

#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <net/if_types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/param.h>
#include <sys/socket.h>
#include <sys/queue.h>
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <sys/ioctl.h>
#include <sys/errno.h>


int sceNetPoolCreate(const char*, int, int);
int sceNetPoolDestroy(int);

int sceNetResolverCreate(const char*, int, int);
int sceNetResolverDestroy(int);

int sceNetResolverStartNtoa(int, const char*, in_addr_t*, int, int, int);
int sceNetResolverStartAton(int, const in_addr_t*, char *, int, int, int, int);

int *sceNetErrnoLoc(void);


static const char *g_errlist[] = {
  "Success",
  "Address family for hostname not supported",
  "Temporary failure in name resolution",
  "Invalid value for ai_flags",
  "Non-recoverable failure in name resolution",
  "ai_family not supported",
  "Memory allocation failure",
  "No address associated with hostname",
  "hostname nor servname provided, or not known",
  "servname not supported for ai_socktype",
  "ai_socktype not supported",
  "System error returned in errno",
  "Invalid value for hints",
  "Resolved protocol is unknown",
  "Argument buffer overflow"
};


static struct protoent g_protent[] = {
  {"ip", (char*[]){"IP", 0}, IPPROTO_IP},
  {"icmp", (char*[]){"ICMP", 0}, IPPROTO_ICMP},
  {"tcp", (char*[]){"TCP", 0}, IPPROTO_TCP},
  {"udp", (char*[]){"UDP", 0}, IPPROTO_UDP},
  {"ipv6", (char*[]){"IPV6", 0}, IPPROTO_IPV6},
  {0, 0, 0}
};


const char*
gai_strerror(int err) {
  static char buf[50];

  if(0 <= err && err < EAI_MAX) {
    return g_errlist[err];
  }

  sprintf(buf, "Unknown network error code 0x%08x", err);

  return buf;
}


const char*
hstrerror(int herr) {
  static char buf[50];

  sprintf(buf, "Unknown network error code 0x%08x", herr);

  return buf;
}


int*
__h_errno(void) {
  return sceNetErrnoLoc();
}


static int
resolve_ntoa(const char *hostname, in_addr_t *addr) {
  int pool_handle = -1;
  int res_handle = -1;
  int err = 0;

  if((pool_handle=sceNetPoolCreate("", 0x4000, 0)) < 0) {
    err = h_errno;

  } else if((res_handle=sceNetResolverCreate("", pool_handle, 0)) < 0) {
    err = h_errno;

  } else if((sceNetResolverStartNtoa(res_handle, hostname, addr, 0, 0, 0)) < 0) {
    err = h_errno;
  }

  if(res_handle >= 0) {
    if(sceNetResolverDestroy(res_handle) < 0) {
      if(!err) {
	err = h_errno;
      }
    }
  }

  if(pool_handle >= 0) {
    if(sceNetPoolDestroy(pool_handle)) {
      if(!err) {
	err = h_errno;
      }
    }
  }

  return err;
}


static int
resolve_aton(const in_addr_t *addr, char *hostname, size_t size) {
  int pool_handle = -1;
  int res_handle = -1;
  int err = 0;

  if((pool_handle=sceNetPoolCreate("", 0x4000, 0)) < 0) {
    err = h_errno;

  } else if((res_handle=sceNetResolverCreate("", pool_handle, 0)) < 0) {
    err = h_errno;

  } else if((sceNetResolverStartAton(res_handle, addr, hostname, size,
				     0, 0, 0)) < 0) {
    err = h_errno;
  }

  if(res_handle >= 0) {
    if(sceNetResolverDestroy(res_handle) < 0) {
      if(!err) {
	err = h_errno;
      }
    }
  }

  if(pool_handle >= 0) {
    if(sceNetPoolDestroy(pool_handle)) {
      if(!err) {
	err = h_errno;
      }
    }
  }

  return err;
}


static int
is_ifdisabled(char *name) {
  struct in6_ndireq nd;
  int fd;

  if((fd=socket(AF_INET6, SOCK_DGRAM | SOCK_CLOEXEC, 0)) < 0) {
    return -1;
  }
  memset(&nd, 0, sizeof(nd));
  strlcpy(nd.ifname, name, sizeof(nd.ifname));
  if(ioctl(fd, SIOCGIFINFO_IN6, &nd) < 0) {
    close(fd);
    return -1;
  }
  close(fd);

  return ((nd.ndi.flags & ND6_IFF_IFDISABLED) != 0);
}


static int
addrconfig(int family) {
  struct ifaddrs *ifaddrs, *ifa;
  struct sockaddr_in6 *sin6;
  struct sockaddr_in *sin;
  int seen_inet6 = 0;
  int seen_inet = 0;

  if(getifaddrs(&ifaddrs)) {
    return 0;
  }

  for(ifa=ifaddrs; ifa; ifa=ifa->ifa_next) {
    if(ifa->ifa_addr == NULL || (ifa->ifa_flags & IFF_UP) == 0) {
      continue;
    }

    switch (ifa->ifa_addr->sa_family) {
    case AF_INET:
      if(seen_inet) {
	continue;
      }
      sin = (struct sockaddr_in *)(ifa->ifa_addr);
      if(htonl(sin->sin_addr.s_addr) == INADDR_LOOPBACK) {
	continue;
      }
      seen_inet = 1;
      break;

    case AF_INET6:
      if(seen_inet6) {
	continue;
      }
      sin6 = (struct sockaddr_in6 *)(ifa->ifa_addr);
      if(IN6_IS_ADDR_LOOPBACK(&sin6->sin6_addr)) {
	continue;
      }
      if((ifa->ifa_flags & IFT_LOOP) != 0 &&
	 IN6_IS_ADDR_LINKLOCAL(&sin6->sin6_addr)) {
	continue;
      }
      if(is_ifdisabled(ifa->ifa_name)) {
	continue;
      }
      seen_inet6 = 1;
      break;
    }
  }
  freeifaddrs(ifaddrs);

  switch(family) {
  case AF_INET6:
    return seen_inet6;

  case AF_INET:
    return seen_inet;

  case AF_UNSPEC:
    if(seen_inet == seen_inet6) {
      return seen_inet;
    }
    return 1;
  }
  return 1;
}


struct hostent*
gethostbyaddr(const void* addr, socklen_t len, int type) {
  static struct in_addr inaddr;
  static char host[NI_MAXHOST];
  static char* addr_list[] = {(char*)&inaddr, 0};
  static char* aliases[] = {0};
  static struct hostent h;

  if(type != AF_INET || len != 4) {
    return 0;
  }

  h.h_name = host;
  h.h_addr_list = addr_list;
  h.h_aliases = aliases;
  h.h_addrtype = type;
  h.h_length = len;

  memcpy(&inaddr, addr, sizeof(inaddr));

  if(!resolve_aton(addr, host, sizeof(host))) {
    return &h;
  }

  return 0;
}


int
gethostbyname_r(const char *name, struct hostent *ret, char *buf, size_t buflen,
                struct hostent **result, int *h_errnop) {
  struct in_addr inaddr;
  int needed = 0;
  int err;

  needed += strlen(name)+1;  // h_name
  needed += sizeof(char*)*2; // h_addr_list
  needed += sizeof(inaddr);  // h_addr_list[0]
  needed += sizeof(char*);   // h_aliases

  if(needed > buflen) {
    return ERANGE;
  }

  if((err=resolve_ntoa(name, &inaddr.s_addr))) {
    return err;
  }

  ret->h_name = buf;
  strcpy(ret->h_name, name);
  buf += strlen(name)+1;

  ret->h_addr_list = (void*)buf;
  buf += sizeof(char*)*2;

  ret->h_addr_list[0] = buf;
  memcpy(ret->h_addr_list[0], &inaddr, sizeof(inaddr));
  buf += sizeof(inaddr);
  ret->h_addr_list[1] = 0;

  ret->h_aliases = (void*)buf;
  ret->h_aliases[0] = 0;
  buf += sizeof(char*);

  ret->h_addrtype = AF_INET;
  ret->h_length = sizeof(inaddr);

  *result = ret;

  return 0;
}


struct hostent*
gethostbyname(const char *name) {
  static struct in_addr inaddr;
  static char host[NI_MAXHOST];
  static char* addr_list[] = {(char*)&inaddr, 0};
  static char* aliases[] = {0};
  static struct hostent h;

  h.h_name = host;
  h.h_addr_list = addr_list;
  h.h_aliases = aliases;
  h.h_addrtype = AF_INET;
  h.h_length = sizeof(inaddr);

  if(!resolve_ntoa(name, &inaddr.s_addr)) {
    strncpy(host, name, sizeof(host));
    return &h;
  }

  return 0;
}


int
getnameinfo(const struct sockaddr *sa, socklen_t salen, char *hostname,
	    size_t hostlen, char *servname, size_t servlen, int flags) {
  struct sockaddr_in *addr_in = (struct sockaddr_in *)sa;
  int port;

  if(!hostname && !servname) {
    return EAI_NONAME;
  }

  if(sa->sa_family != AF_INET) {
    return EAI_FAMILY;
  }

  if(hostname) {
    if(flags & NI_NUMERICHOST) {
      if(!inet_ntop(AF_INET, &addr_in->sin_addr, hostname, hostlen)) {
	return EAI_SYSTEM;
      }
    }
    else if(resolve_aton(&addr_in->sin_addr.s_addr, hostname, hostlen)) {
      return EAI_FAIL;
    }
  }

  if(servname) {
    switch((port=ntohs(addr_in->sin_port))) {
    case 21:
      strncpy(servname, "ftp", servlen);
      break;

    case 22:
      strncpy(servname, "ssh", servlen);
      break;

    case 23:
      strncpy(servname, "telnet", servlen);
      break;

    case 80:
      strncpy(servname, "http", servlen);
      break;

    case 443:
      strncpy(servname, "https", servlen);
      break;

    default:
      snprintf(servname, servlen, "%d", port);
      break;
    }
  }

  return 0;
}


int
getaddrinfo(const char *hostname, const char *servname,
	    const struct addrinfo *hints, struct addrinfo **res) {
  struct addrinfo info_tmpl = {0};
  struct sockaddr_in *sock_addr;
  struct addrinfo *info;
  in_addr_t ip_addr = 0;
  int port = 0;

  if(!hostname && !servname) {
    return EAI_NONAME;
  }

  info_tmpl.ai_family = PF_INET;
  info_tmpl.ai_protocol = IPPROTO_TCP;
  info_tmpl.ai_socktype = SOCK_STREAM;
  info_tmpl.ai_addrlen = sizeof(struct sockaddr_in);
  info_tmpl.ai_flags = AI_DEFAULT;
  info_tmpl.ai_canonname = 0;
  info_tmpl.ai_addr = 0;
  info_tmpl.ai_next = 0;

  if(hints) {
    if(hints->ai_addrlen || hints->ai_canonname || hints->ai_addr ||
       hints->ai_next) {
      return EAI_BADHINTS;
    }

    if(hints->ai_flags & ~AI_MASK) {
      return EAI_BADFLAGS;
    }
    info_tmpl.ai_flags = hints->ai_flags;

    switch(hints->ai_family) {
    case PF_UNSPEC:
      info_tmpl.ai_family = PF_INET;
    case PF_INET:
      break;
    case PF_INET6:
    default:
      return EAI_FAMILY;
    }

    switch(hints->ai_socktype) {
    case 0:
    case SOCK_STREAM:
    case SOCK_DGRAM:
    case SOCK_RAW:
      break;
    default:
      return EAI_SOCKTYPE;
    }

    switch(hints->ai_protocol) {
    case 0:
    case IPPROTO_TCP:
    case IPPROTO_UDP:
    case IPPROTO_ICMP:
      break;
    default:
      return EAI_PROTOCOL;
    }

    if(!hints->ai_protocol && !hints->ai_socktype) {
      info_tmpl.ai_protocol = IPPROTO_TCP;
      info_tmpl.ai_socktype = SOCK_STREAM;

    } else if((hints->ai_protocol == IPPROTO_TCP && !hints->ai_socktype) ||
	      (!hints->ai_protocol && hints->ai_socktype == SOCK_STREAM)) {
      info_tmpl.ai_protocol = IPPROTO_TCP;
      info_tmpl.ai_socktype = SOCK_STREAM;

    } else if((hints->ai_protocol == IPPROTO_UDP && !hints->ai_socktype) ||
	      (!hints->ai_protocol && hints->ai_socktype == SOCK_DGRAM)) {
      info_tmpl.ai_protocol = IPPROTO_UDP;
      info_tmpl.ai_socktype = SOCK_DGRAM;

    } else if((hints->ai_protocol == IPPROTO_ICMP && !hints->ai_socktype) ||
	      (!hints->ai_protocol && hints->ai_socktype == SOCK_RAW)) {
      info_tmpl.ai_protocol = IPPROTO_ICMP;
      info_tmpl.ai_socktype = SOCK_RAW;
    }
  }

  if(servname) {
    port = atoi(servname);
    if(port <= 0 || port > 65535) {
      return EAI_SERVICE;
    }
  }

  if(hostname) {
    struct in_addr tmp;

    if(info_tmpl.ai_flags & AI_ADDRCONFIG && !addrconfig(info_tmpl.ai_family)) {
      return EAI_FAIL;
    }

    if(info_tmpl.ai_flags & AI_NUMERICHOST) {
      if(inet_aton(hostname, &tmp)) {
	ip_addr = tmp.s_addr;
      } else {
	return EAI_FAIL;
      }
    }
    else if(resolve_ntoa(hostname, &ip_addr)) {
      return EAI_FAIL;
    }
  }

  if(!(sock_addr=malloc(sizeof(struct sockaddr_in)))) {
    return EAI_MEMORY;
  }

  sock_addr->sin_family = AF_INET;
  sock_addr->sin_port = htons(port);
  sock_addr->sin_addr.s_addr = ip_addr;

  if(!(info=malloc(sizeof(struct addrinfo)))) {
    free(sock_addr);
    return EAI_MEMORY;
  }

  info->ai_addr = (struct sockaddr *)sock_addr;
  info->ai_family = sock_addr->sin_family;
  info->ai_addrlen = sizeof(struct sockaddr_in);
  info->ai_socktype = info_tmpl.ai_socktype;
  info->ai_protocol = info_tmpl.ai_protocol;
  info->ai_canonname = NULL;
  info->ai_next = NULL;

  if(info_tmpl.ai_flags & AI_CANONNAME) {
    info->ai_canonname = strdup(hostname); //TODO: CNAMEs
  }

  *res = info;

  return 0;
}


void
freeaddrinfo(struct addrinfo *res) {
  struct addrinfo *next;

  while(res) {
    next = res->ai_next;
    if(res->ai_canonname) {
      free(res->ai_canonname);
    }
    if(res->ai_addr) {
      free(res->ai_addr);
    }
    free(res);
    res = next;
  }
}


int
getservbyname_r(const char *name, const char *prots, struct servent *se,
                char *buf, size_t buflen, struct servent **res) {
#warning "getservbyname_r() not implemented"
  return -1;
}


int
getservbyport_r(int port, const char *prots, struct servent *se, char *buf,
                size_t buflen, struct servent **res) {
  struct sockaddr_in sin = {
    .sin_family = AF_INET,
    .sin_port = port,
  };
  int i;
  int r;

  if(!prots) {
    if((r=getservbyport_r(port, "tcp", se, buf, buflen, res))) {
      r = getservbyport_r(port, "udp", se, buf, buflen, res);
    }
    return r;
  }
  *res = 0;

  // Align buffer
  i = (uintptr_t)buf & sizeof(char *)-1;
  if(!i) {
    i = sizeof(char *);
  }
  if(buflen <= 3*sizeof(char *)-i) {
    return ERANGE;
  }
  buf += sizeof(char *)-i;
  buflen -= sizeof(char *)-i;

  if(strcmp(prots, "tcp") && strcmp(prots, "udp")) {
    return EINVAL;
  }

  se->s_port = port;
  se->s_proto = (char *)prots;
  se->s_aliases = (void *)buf;
  buf += 2*sizeof(char *);
  buflen -= 2*sizeof(char *);
  se->s_aliases[1] = 0;
  se->s_aliases[0] = se->s_name = buf;

  switch(getnameinfo((void *)&sin, sizeof(sin), 0, 0, buf, buflen,
                      strcmp(prots, "udp") ? 0 : NI_DGRAM)) {
  case EAI_MEMORY:
  case EAI_SYSTEM:
    return ENOMEM;

  case EAI_OVERFLOW:
    return ERANGE;

  default:
    return ENOENT;

  case 0:
    break;
  }

  // A numeric port string is not a service record.
  if(strtol(buf, 0, 10) == ntohs(port)) {
    return ENOENT;
  }

  *res = se;

  return 0;
}


struct servent*
getservbyname(const char *name, const char *prots) {
  static struct servent se;
  static char *buf[2];
  struct servent *res;

  if(getservbyname_r(name, prots, &se, (void *)buf, sizeof buf, &res)) {
    return 0;
  }

  return &se;
}


struct servent*
getservbyport(int port, const char *prots) {
  static struct servent se;
  static long buf[32/sizeof(long)];
  struct servent *res;

  if(getservbyport_r(port, prots, &se, (void *)buf, sizeof buf, &res)) {
    return 0;
  }

  return &se;
}


struct protoent*
getprotobyname(const char *name) {
  if(!name) {
    return 0;
  }

  for(struct protoent *p=g_protent; p->p_name; p++) {
    if(strcmp(name, p->p_name) == 0) {
      return p;
    }

    for(char **alias=p->p_aliases; *alias; alias++) {
      if(strcmp(name, *alias) == 0) {
        return p;
      }
    }
  }

  return 0;
}
