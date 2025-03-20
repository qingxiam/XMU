int is_in_net(unsigned char *ip, unsigned char *netip, unsigned char *mask)
{
    for (int i = 0; i < 4; i++)
        if ((ip[i] & mask[i]) != (netip[i] & mask[i]))
            return 0;
    return 1;
}
