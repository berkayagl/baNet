#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("----------------------------------------------------------------------------------- \n");

    // This is a declaration of a structure pointer named "ifaddrs" of type "struct ifaddrs".
    struct ifaddrs *ifaddresses;

    // State if the function call returns -1, i.e. an error.
    if (getifaddrs(&ifaddresses) == -1)
    {
        printf("getifaddrs call failed! c\n");
        return -1;
    }

    // The pointer named "address" points to the area of memory pointed to by the pointer "ifaddresses".
    struct ifaddrs *address = ifaddresses;

    // The loop will continue until the last element of the "address" structure.
    while (address)
    {
        //"If the "ifa_addr" field is NULL, i.e. it does not contain an address,
        //the loop simply moves the "address" variable to the next structure and moves to the next loop step.
        if (address -> ifa_addr == NULL)
        {
            address = address -> ifa_next;
            continue;
        }

        // Specifies the family of an IPv4 or IPv6 address.
        // The "ifa_addr" refers to an address structure and the "sa_family" field specifies the family of that address.
        int fmly = address -> ifa_addr -> sa_family;


        // If the address type of the network device is IPv4, it will be printed as "IPv4" and if it is IPv6,
        // it will be printed as "IPv6". The device name, flags and data field will also be printed on the screen.
        if (fmly == AF_INET || fmly == AF_INET6)
        {
            printf("%s \t", address -> ifa_name);
            printf("%d \t", address -> ifa_flags);
            printf("%s \t", address -> ifa_data);

            printf("%s \t", fmly == AF_INET ? "IPv4" : "IPv6");

            char a[100];

            const int fmlySize = fmly == AF_INET ?
                    sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);

            // The getnameinfo function is used to get the network address into an array named a and print it to the screen in the format "%s ".
            getnameinfo(address->ifa_addr,
                    fmlySize, a, sizeof(a), 0, 0, NI_NUMERICHOST);

            printf("\t%s\n", a);

        }
        // Finally, the address variable is updated with ifa_next to move to the next network interface address.
        address = address -> ifa_next;
    }
    freeifaddrs(address);
    printf("----------------------------------------------------------------------------------- \n");
    return 0;
}
