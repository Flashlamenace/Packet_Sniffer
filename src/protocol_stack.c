#pragma once
#include <netinet/in.h>
#include <stdio.h>
#include <linux/if_ether.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

void header_handling(unsigned char *buffer, int buffer_lenght){

    // ETHERNET HEADER :

    struct ethhdr *eth = (struct ethhdr *) (buffer); // Here i use a pointer to the adress of the structure so i can reference it later whitout creating x copy of 
    //                                               said struc. I then cast the struc ethhdr type to buffer in the code for clarity because this is what would have done.
    
    printf("\nETHERNET HEADER \n");
    printf(" -Destination MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
        eth->h_dest[0], eth->h_dest[1], eth->h_dest[2],
        eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);
    printf(" -Source MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
        eth->h_source[0], eth->h_source[1], eth->h_source[2],
        eth->h_source[3], eth->h_source[4], eth->h_source[5]);
    printf(" -Protocol: 0x%04x\n", ntohs(eth->h_proto));
   
    // IP HEADER :

    struct iphdr *ip = (struct iphdr *) (buffer + sizeof(struct ethhdr)); 
    //to set the proper data into the struct we need to increment the buffer pointer to after the eth header.
     
    printf("\nIP HEADER :");
    printf("\n -Version         : %d", ip->version);
    printf("\n -Type of Service : %d", ip->tos);
    printf("\n -Total Lenght    : %d", ip->tot_len);
    printf("\n -Identification  : %d", ip->id);
    printf("\n -Time to Live    : %d", ip -> ttl);
    printf("\n -Protocol        : %d", ip->protocol);
    printf("\n -Source Address  : %s",     inet_ntoa(*(struct in_addr *)&ip->saddr));
    printf("\n -Destination Addr: %s \n",  inet_ntoa(*(struct in_addr *)&ip->daddr));

    //TO DO : et faire correspondre le numéro du protocol à la str du protocole utilisé.

// Protocols Header :
    // TCP :
    struct tcphdr *tcp = (struct tcphdr *) (buffer + sizeof(struct ethhdr) + sizeof(struct iphdr));

    printf("\nTCP HEADER :");
    printf("\n -Port Source        : %d", ntohs(tcp -> source));
    printf("\n -Port Destination   : %d", ntohs(tcp -> dest));
    printf("\n -Sequence Number    : %d", ntohs(tcp -> seq));
    printf("\n -Acknoledgement seq : %d", ntohs(tcp -> ack_seq));
    
    printf("\n\n------FLAGS :");
    printf("\n       Urgent Pointer : %d", tcp->urg);
    printf("\n       Acknoledgement : %d", tcp->ack);
    printf("\n       Push           : %d", tcp->psh);
    printf("\n       Reset          : %d", tcp->rst);
    printf("\n       Synchronisation: %d", tcp->syn);
    printf("\n       Fin            : %d\n\n", tcp->fin);

    //TODO Ajouter les autres protocoles

// DATA :
    unsigned char *data = buffer - (sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct tcphdr));
    int remaining_data = buffer_lenght - (sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct tcphdr));

    printf("DATA :");
    for(int i=0; i < remaining_data; i++){
        
        if(i!=0 && i%16==0){
            printf("%.2X", data[i]);
        }
    }
    lll
}

