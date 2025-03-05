int check(const unsigned char *msg, const int ll)
{
    if (ll<1) 
        return 0;
    int bit=ll-1,count=0;
    for (int i=0;i<bit;i++)
      if (msg[i]!=0)
        count++;
    int e=(count%2)?1:0;
    int true=(msg[bit]!=0)?1:0;
    return(e==true)?1:0;
}
