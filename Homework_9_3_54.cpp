int classwise(unsigned char *ip)
{
    unsigned char first = ip[0];
    if (first >= 240) return 4;
    else if (first >= 224) return 3; 
    else if (first >= 192) return 2; 
    else if (first >= 128) return 1;
    else return 0;  
}
